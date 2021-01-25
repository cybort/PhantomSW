/*
 * @Author: your name
 * @Date: 2021-01-20 14:02:42
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2021-01-25 14:23:57
 * @Description: file content
 */
#include "DeQueueProcessor.h"

void DeQueueProcessor::rcev_de_queue_command()
{
    DeQueueCommand de_queue_command;
    unsigned flow_id = -1;
    de_queue_flow_id_out_valid.write(false);
    if (de_queue_command_in_valid.read())
    {
        de_queue_command = de_queue_command_in.read();
        flow_id = de_queue_command.get_flow_id();
        de_queue_flow_id_out.write(flow_id);
        de_queue_flow_id_out_valid.write(true);
    }
}

void DeQueueProcessor::rcev_logic_addr()
{
    unsigned logic_addr = -1;
    pd packet_descriptor;
    logic_addr_out_valid.write(false);
    if (packet_descriptor_in_valid.read())
    {
        packet_descriptor = packet_descriptor_in.read();
        packet_descriptor_fifo.push(packet_descriptor);
        logic_addr = packet_descriptor.get_addr();
        logic_addr_out.write(logic_addr);
        logic_addr_out_valid.write(true);
        logic_addr_release_fifo.push(logic_addr);
    }
}

void DeQueueProcessor::trans_de_queue_report()
{
    pd packet_descriptor;
    DeQueueReport de_queue_report;
    de_queue_report_out_to_cavd_valid.write(false);
    de_queue_report_out_to_credit_manager_valid.write(false);
    de_queue_report_out_to_queue_sch_valid.write(false);
    unsigned logic_addr = -1;
    if (read_packet_complete_signal_in.read())
    {
        packet_descriptor = packet_descriptor_fifo.pop();
        de_queue_report.set_flow_id(packet_descriptor.get_flowID());
        de_queue_report.set_packet_size(packet_descriptor.get_length());
        de_queue_report_out_to_cavd.write(de_queue_report);
        de_queue_report_out_to_credit_manager.write(de_queue_report);
        de_queue_report_out_to_queue_sch.write(de_queue_report);
        de_queue_report_out_to_cavd_valid.write(true);
        de_queue_report_out_to_credit_manager_valid.write(true);
        de_queue_report_out_to_queue_sch_valid.write(true);
        logic_addr = logic_addr_release_fifo.pop();
        LogicAddrTable::get_instance().set_addr_status(logic_addr, false);
    }
}
