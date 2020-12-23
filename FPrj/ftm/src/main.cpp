/*
 * @Description: SystemC main function
 * @Author: f21538
 * @Date: 2020-12-01 11:09:07
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-01 14:31:26
 */
#include "BufferManager.h"
//#include "ConfigInterface.h"
#include "ConfigDB.h"
#include "ConfigResolver.h"
#include "QueueControlUnit.h"
#include "config.h"
#include "pd.h"
#include "stat_module.h"
#include "switch_interface.h"
#include "testbench.h"
#include "Interface.h"
#include "wred.h"

#include "clock_step.h"

int sc_main(int argc, char * argv[])
{
    sc_clock clk("clk", sc_time(20, SC_MS), 0.5, sc_time(1, SC_MS));
    sc_signal<cell> tx_data[TM_CELL_PER_CLOCK_LIMIT], rx_data[TM_CELL_PER_CLOCK_LIMIT];
    sc_signal<bool> tx_valid[TM_CELL_PER_CLOCK_LIMIT], rx_valid[TM_CELL_PER_CLOCK_LIMIT];

    sc_signal<bool> pkt_valid_up, pkt_sop_up, pkt_eop_up;
    sc_signal<int> pkt_mod_up;
    // sc_signal<packet_line> packet_up;
    sc_signal<data_bus> packet_up;

    sc_signal<bool> pkt_sop_down, pkt_eop_down, pkt_valid_down;
    sc_signal<int> pkt_mod_down;
    // sc_signal<packet_line> packet_down;
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

    sc_signal<unsigned> addr_vm_to_bm, addr_bm_to_vm;
    sc_signal<bool> addr_valid_vm_to_bm, addr_valid_bm_to_vm;

    sc_signal<FlowStatusMessage> flow_status_message_up, flow_status_message_down;
    sc_signal<bool> flow_status_message_up_valid, flow_status_message_down_valid;

    sc_signal<CreditInfo> credit_info_up, credit_info_down;
    sc_signal<bool> credit_info_up_valid, credit_info_down_valid;

    //   sc_fifo<FPacket>(10) FPacket_fifo_rx_to_vifin;
    //   sc_fifo<pd>(10) pd_fifo_rx_to_vifin;

    std::cout << "TM_BASE_SERVER_PORT " << TM_BASE_SERVER_PORT << " SW_BASE_SERVER_PORT " << SW_BASE_SERVER_PORT
              << " STREAM_SEND_PORT " << STREAM_SEND_PORT << std::endl;
    ConfigResolver config;
    char cur_dir[500];
    getcwd(cur_dir, 500);
    config.set_string("ini", "pwd", cur_dir);
    // Statcounter ca("1");
    // try {
    //    ConfigDB::GetInstance().update_config("1", "2", 3);
    // ca.update_counter("2", 3);
    //}
    // catch (Exception& e)
    //{
    //    std::cout<<"error"<<e.ToString()<<std::endl<<e.Stack()<<std::endl;
    //}

    // config.set_string("clock_step", "step_mode", "true");
    // config.set_int("port", "TM_BASE_SERVER_PORT", TM_BASE_SERVER_PORT);
    // config.set_int("port", "SW_BASE_SERVER_PORT", SW_BASE_SERVER_PORT);
    // config.set_int("port", "STREAM_SEND_PORT", STREAM_SEND_PORT);

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
    // tb.sop(pkt_sop_up);
    // tb.eop(pkt_eop_up);
    // tb.valid_pkt(pkt_valid_up);
    // tb.packet(packet_up);
    // tb.mod(pkt_mod_up);
    tb.sop_r(pkt_sop_down);
    tb.eop_r(pkt_eop_down);
    tb.valid_pkt_r(pkt_valid_down);
    tb.packet_r(packet_down);
    tb.mod_r(pkt_mod_down);

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

    si.t.shuffle_depth = 0; // 85;
    si.cr.cell_resolve_wait_time = 300;
    si.cr.packet_wait_threshold = 80;

    stat_module stat("stat_module");
    stat.clk(clk);

    //   rxif rx("rxif");
    Interface nif("nif");
    wred wred_ins("wred");
    QueueControlUnit qcu("qcu");
    BufferManager buffer_manager("buffer_manager");
    // ConfigInterface ci("config_interface");

    //    rx.clk(clk);
    //   rx.fpacket_fifo_to_vifin(FPacket_fifo_rx_to_vifin);
    //    rx.pd_fifo_to_vifin(pd_fifo_rx_to_vifin);

    nif.clk(clk);
    nif.pd_out(wred_pd);
    nif.wred_rd(wred_rd);
    nif.valid_pd(validPd);
    //    wrx.fpacket_fifo_from_rxif(FPacket_fifo_rx_to_vifin);
    //    wrx.pd_fifo_to_from_rxif(pd_fifo_rx_to_vifin);

    nif.sop_out(sop_sender_to_voq_manager);
    nif.eop_out(eop_sender_to_voq_manager);
    nif.validSlice_out(packet_valid_sender_to_voq_manager);
    nif.mod_out(mod_sender_to_voq_manager);
    nif.sls_out(packet_sender_to_voq_manager);
    nif.packet_read(voq_manager_packet_read);
    /*
        vrx.sop_in(sop);
        vrx.eop_in(eop);
        vrx.validSlice_in(valid);
        vrx.mod_in(mod);
        vrx.sls_in(data);
    */

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

    qcu.addr_in(addr_bm_to_vm);
    qcu.addr_in_valid(addr_valid_bm_to_vm);

    qcu.addr_out(addr_vm_to_bm);
    qcu.addr_out_valid(addr_valid_vm_to_bm);

    qcu.flow_status_message_in(flow_status_message_down);
    qcu.flow_status_message_in_valid(flow_status_message_down_valid);
    qcu.flow_status_message_out(flow_status_message_up);
    qcu.flow_status_message_out_valid(flow_status_message_up_valid);

    qcu.credit_info_in(credit_info_down);
    qcu.credit_info_in_valid(credit_info_down_valid);
    qcu.credit_info_out(credit_info_up);
    qcu.credit_info_out_valid(credit_info_up_valid);

    qcu.dequeue_report_to_cavd_out_valid(valid_report);
    qcu.dequeue_report_to_cavd_out(report);

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

    buffer_manager.addr_in(addr_vm_to_bm);
    buffer_manager.addr_in_valid(addr_valid_vm_to_bm);

    buffer_manager.addr_out(addr_bm_to_vm);
    buffer_manager.addr_out_valid(addr_valid_bm_to_vm);

    // ci.clk(clk);

    /*cell_gen cg("cell_gen");
    cg.debug = true;
    cg.clk(clk);
    cg.sop(pkt_sop_up);
    cg.eop(pkt_eop_up);
    cg.valid_pkt(pkt_valid_up);
    cg.packet(packet_up);
    cg.mod(pkt_mod_up);
    for (int i = 0; i < TM_CELL_PER_CLOCK_LIMIT; i++)
    {
        cg.valid[i](tx_valid[i]);
        cg.data[i](tx_data[i]);
    }

    rx r("rx");
    r.debug = true;
    r.clk(clk);
    for (int i = 0; i < TM_CELL_PER_CLOCK_LIMIT; i++)
    {
        r.valid[i](rx_valid[i]);
        r.data[i](rx_data[i]);
    }

    cell_resolve cr("cell_resolve");
    cr.debug = true;
    cr.clk(clk);
    cr.sop(pkt_sop_down);
    cr.eop(pkt_eop_down);
    cr.pkt_valid(pkt_valid_down);
    cr.mod(pkt_mod_down);
    cr.pkt_out(packet_down);
    for (int i = 0; i < TM_CELL_PER_CLOCK_LIMIT; i++)
    {
        cr.valid[i](rx_valid[i]);
        cr.data[i](rx_data[i]);
    }

    tx t("tx");
    t.debug = true;
    t.clk(clk);
    for (int i = 0; i < TM_CELL_PER_CLOCK_LIMIT; i++)
    {
        t.valid[i](tx_valid[i]);
        t.data[i](tx_data[i]);
    }*/

    /*
        sc_trace_file *tf = sc_create_vcd_trace_file("ftm");
        sc_trace(tf, clk.signal(), "clk");
        for (int i = 0; i < TM_CELL_PER_CLOCK_LIMIT; i++)
        {

            sc_trace(tf, tx_data[i], "tx_data");
            sc_trace(tf, tx_valid[i], "tx_valid");

            sc_trace(tf, rx_data[i], "rx_data");
            sc_trace(tf, rx_valid[i], "rx_valid");
        }*/

    //  sc_start(sc_time(2000, SC_MS));
    sc_start();

    //   sc_close_vcd_trace_file(tf);

    return 0;
}
