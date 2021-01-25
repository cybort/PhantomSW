/*
 * @Description: SystemC main function
 * @Author: f21538
 * @Date: 2020-12-01 11:09:07
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-23 14:43:58
 */
#include "BufferManager.h"
//#include "ConfigInterface.h"
#include "ConfigDB.h"
#include "ConfigInterface.h"
#include "ConfigResolver.h"
#include "Interface.h"
#include "QueueControlUnit.h"
#include "Scheduler.h"
#include "config.h"
#include "pd.h"
#include "stat_module.h"
#include "switch_interface.h"
#include "testbench.h"
#include "wred.h"

#include "clock_step.h"

int sc_main(int argc, char * argv[])
{

    sc_clock clk("clk", sc_time(20, SC_MS), 0.5, sc_time(1, SC_MS));
    sc_signal<cell> tx_data[TM_CELL_PER_CLOCK_LIMIT], rx_data[TM_CELL_PER_CLOCK_LIMIT];
    sc_signal<bool> tx_valid[TM_CELL_PER_CLOCK_LIMIT], rx_valid[TM_CELL_PER_CLOCK_LIMIT];

    sc_signal<bool> pkt_valid_up, pkt_sop_up, pkt_eop_up;
    sc_signal<int> pkt_mod_up;

    sc_signal<data_bus> packet_up;

    sc_signal<bool> pkt_sop_down, pkt_eop_down, pkt_valid_down;
    sc_signal<int> pkt_mod_down;

    sc_signal<data_bus> packet_down;

    sc_signal<pd> wred_pd;
    sc_signal<bool> wred_rd;
    sc_signal<bool> validPd;
    sc_signal<bool> valid_report;
    sc_signal<DeQueueReport> report;

    sc_signal<data_bus> packet_sender_to_voq_manager, packet_voq_manager_to_buffer_manager;
    sc_signal<bool> sop_sender_to_voq_manager, sop_voq_manager_to_buffer_manager;
    sc_signal<bool> eop_sender_to_voq_manager, eop_voq_manager_to_buffer_manager;
    sc_signal<int> mod_sender_to_voq_manager, mod_voq_manager_to_buffer_manager;
    sc_signal<bool> packet_valid_sender_to_voq_manager, packet_valid_voq_manager_to_buffer_manager;
    sc_signal<bool> voq_manager_packet_read;

    sc_signal<pd> packet_descriptor;
    sc_signal<bool> packet_descriptor_valid;
    sc_signal<bool> packet_descriptor_fc;

    sc_signal<unsigned> write_logic_addr_qcu_to_bmm, read_logic_addr_qcu_to_bmm;
    sc_signal<bool> read_logic_addr_valid_qcu_to_bm;

    sc_signal<FlowStatusMessage> flow_status_message_up, flow_status_message_down;
    sc_signal<bool> flow_status_message_up_valid, flow_status_message_down_valid;

    sc_signal<CreditInfo> credit_info_up, credit_info_down;
    sc_signal<bool> credit_info_up_valid, credit_info_down_valid;

    sc_signal<bool> read_complete_signal_bmm_to_qcu, write_complete_signal_bmm_to_qcu;

    sc_signal<sc_bv<LINK_MAX>> link_valid_swi_to_scheduler;

    std::cout << "TM_BASE_SERVER_PORT " << TM_BASE_SERVER_PORT << " SW_BASE_SERVER_PORT " << SW_BASE_SERVER_PORT
              << " STREAM_SEND_PORT " << STREAM_SEND_PORT << std::endl;
    ConfigResolver config;
    char cur_dir[500];
    getcwd(cur_dir, 500);
    config.set_string("ini", "pwd", cur_dir);

    clock_step cs("clock_step");
    cs.clk(clk);
    if (config.get_bool("clock_step", "debug") == true)
    {
        cs.debug = true;
    }
    if (config.get_bool("clock_step", "step_mode") == true)
    {
        cs.step_mode = clock_step::Step;
    }

    testbench tb("testbench");
    tb.clk(clk);
    tb.sop_r_up(sop_sender_to_voq_manager);
    tb.eop_r_up(eop_sender_to_voq_manager);
    tb.valid_pkt_r_up(packet_valid_sender_to_voq_manager);
    tb.packet_r_up(packet_sender_to_voq_manager);
    tb.mod_r_up(mod_sender_to_voq_manager);

    tb.sop_r_down(pkt_sop_down);
    tb.eop_r_down(pkt_eop_down);
    tb.valid_pkt_r_down(pkt_valid_down);
    tb.packet_r_down(packet_down);
    tb.mod_r_down(pkt_mod_down);

    switch_interface si("switch_interface");
    si.clk(clk);
    si.pkt_valid_up(pkt_valid_up);
    si.pkt_sop_up(pkt_sop_up);
    si.pkt_eop_up(pkt_eop_up);
    si.pkt_mod_up(pkt_mod_up);
    si.packet_up(packet_up);
    si.pkt_valid_down(pkt_valid_down);
    si.pkt_sop_down(pkt_sop_down);
    si.pkt_eop_down(pkt_eop_down);
    si.pkt_mod_down(pkt_mod_down);
    si.packet_down(packet_down);
    si.flow_status_in(flow_status_message_up);
    si.valid_flow_status_in(flow_status_message_up_valid);
    si.flow_status_out(flow_status_message_down);
    si.valid_flow_status_out(flow_status_message_down_valid);
    si.credit_info_in(credit_info_up);
    si.valid_credit_info_in(credit_info_up_valid);
    si.credit_info_out(credit_info_down);
    si.valid_credit_info_out(credit_info_down_valid);
    si.link_valid_out(link_valid_swi_to_scheduler);

    si.t.shuffle_depth = 10; // 85;
    si.cr.cell_resolve_wait_time = 300;
    si.cr.packet_wait_threshold = 80;

    stat_module stat("stat_module");
    stat.clk(clk);

    Interface nif("nif");
    wred wred_ins("wred");
    QueueControlUnit qcu("qcu");
    BufferManager buffer_manager("buffer_manager");
    ConfigInterface ci("config_interface");
    Scheduler sch("sch");

    sch.clk(clk);
    sch.flow_status_message_in(flow_status_message_down);
    sch.flow_status_message_in_valid(flow_status_message_down_valid);
    sch.credit_info_out(credit_info_up);
    sch.credit_info_out_valid(credit_info_up_valid);
    sch.link_valid_in(link_valid_swi_to_scheduler);

    nif.clk(clk);
    nif.pd_out(wred_pd);
    nif.wred_rd(wred_rd);
    nif.valid_pd(validPd);

    nif.sop_out(sop_sender_to_voq_manager);
    nif.eop_out(eop_sender_to_voq_manager);
    nif.validSlice_out(packet_valid_sender_to_voq_manager);
    nif.mod_out(mod_sender_to_voq_manager);
    nif.sls_out(packet_sender_to_voq_manager);
    nif.packet_read(voq_manager_packet_read);

    nif.sop_in(pkt_sop_down);
    nif.eop_in(pkt_eop_down);
    nif.validSlice_in(pkt_valid_down);
    nif.mod_in(pkt_mod_down);
    nif.sls_in(packet_down);

    wred_ins.clk(clk);
    wred_ins.rd_rqst(wred_rd);
    wred_ins.Pd_in(wred_pd);
    wred_ins.validPd(validPd);
    wred_ins.pd_valid_out(packet_descriptor_valid);
    wred_ins.Pd_to_qm(packet_descriptor);
    wred_ins.pd_fc(packet_descriptor_fc);
    wred_ins.dq_report_valid(valid_report);
    wred_ins.dq_report(report);

    qcu.clk(clk);
    qcu.packet_in(packet_sender_to_voq_manager);
    qcu.packet_in_sop(sop_sender_to_voq_manager);
    qcu.packet_in_eop(eop_sender_to_voq_manager);
    qcu.packet_in_valid(packet_valid_sender_to_voq_manager);
    qcu.packet_in_mod(mod_sender_to_voq_manager);
    qcu.packet_read(voq_manager_packet_read);

    qcu.packet_descriptor_in(packet_descriptor);
    qcu.packet_descriptor_in_valid(packet_descriptor_valid);
    qcu.packet_descriptor_fc(packet_descriptor_fc);

    qcu.packet_out(packet_voq_manager_to_buffer_manager);
    qcu.packet_out_sop(sop_voq_manager_to_buffer_manager);
    qcu.packet_out_eop(eop_voq_manager_to_buffer_manager);
    qcu.packet_out_mod(mod_voq_manager_to_buffer_manager);
    qcu.packet_out_valid(packet_valid_voq_manager_to_buffer_manager);

    qcu.write_logic_addr_out(write_logic_addr_qcu_to_bmm);

    qcu.read_logic_addr_out(read_logic_addr_qcu_to_bmm);
    qcu.read_logic_addr_out_valid(read_logic_addr_valid_qcu_to_bm);

    // qcu.flow_status_message_in(flow_status_message_down);
    // qcu.flow_status_message_in_valid(flow_status_message_down_valid);
    qcu.flow_status_message_out(flow_status_message_up);
    qcu.flow_status_message_out_valid(flow_status_message_up_valid);

    qcu.credit_info_in(credit_info_down);
    qcu.credit_info_in_valid(credit_info_down_valid);
    // qcu.credit_info_out(credit_info_up);
    // qcu.credit_info_out_valid(credit_info_up_valid);

    qcu.de_queue_report_out(report);
    qcu.de_queue_report_out_valid(valid_report);

    qcu.read_packet_complete_signal_in(read_complete_signal_bmm_to_qcu);
    qcu.write_packet_complete_signal_in(write_complete_signal_bmm_to_qcu);

    buffer_manager.clk(clk);
    buffer_manager.packet_in(packet_voq_manager_to_buffer_manager);
    buffer_manager.packet_in_sop(sop_voq_manager_to_buffer_manager);
    buffer_manager.packet_in_eop(eop_voq_manager_to_buffer_manager);
    buffer_manager.packet_in_mod(mod_voq_manager_to_buffer_manager);
    buffer_manager.packet_in_valid(packet_valid_voq_manager_to_buffer_manager);

    buffer_manager.packet_out(packet_up);
    buffer_manager.packet_out_sop(pkt_sop_up);
    buffer_manager.packet_out_eop(pkt_eop_up);
    buffer_manager.packet_out_mod(pkt_mod_up);
    buffer_manager.packet_out_valid(pkt_valid_up);

    buffer_manager.read_logic_addr_in(read_logic_addr_qcu_to_bmm);
    buffer_manager.read_logic_addr_in_valid(read_logic_addr_valid_qcu_to_bm);

    buffer_manager.write_logic_addr_in(write_logic_addr_qcu_to_bmm);

    buffer_manager.read_complete_signal_out(read_complete_signal_bmm_to_qcu);
    buffer_manager.write_complete_signal_out(write_complete_signal_bmm_to_qcu);

    ci.clk(clk);

    sc_start();

    return 0;
}
