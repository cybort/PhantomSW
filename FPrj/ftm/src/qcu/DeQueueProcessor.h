/*
 * @Author: your name
 * @Date: 2021-01-20 14:02:30
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2021-01-25 14:22:50
 * @Description: file content
 */
#ifndef _DE_QUEUE_PROCESSOR_H
#define _DE_QUEUE_PROCESSOR_H

#include "DeQueueCommand.h"
#include "DeQueueReport.h"
#include "Fifo.hpp"
#include "LogicAddrTable.h"
#include "pd.h"
#include "systemc.h"

SC_MODULE(DeQueueProcessor)
{
    sc_in<bool> clk;
    sc_in<DeQueueCommand> de_queue_command_in;
    sc_in<bool> de_queue_command_in_valid;
    sc_in<pd> packet_descriptor_in;
    sc_in<bool> packet_descriptor_in_valid;
    sc_in<bool> read_packet_complete_signal_in;
    sc_out<unsigned> de_queue_flow_id_out;
    sc_out<bool> de_queue_flow_id_out_valid;
    sc_out<unsigned> de_queue_flow_id_release_out;
    sc_out<bool> de_queue_flow_id_release_out_valid;
    sc_out<unsigned> logic_addr_out;
    sc_out<bool> logic_addr_out_valid;
    sc_out<DeQueueReport> de_queue_report_out_to_cavd;
    sc_out<bool> de_queue_report_out_to_cavd_valid;
    sc_out<DeQueueReport> de_queue_report_out_to_queue_sch;
    sc_out<bool> de_queue_report_out_to_queue_sch_valid;
    sc_out<DeQueueReport> de_queue_report_out_to_credit_manager;
    sc_out<bool> de_queue_report_out_to_credit_manager_valid;
    Fifo<pd> packet_descriptor_fifo;
    Fifo<unsigned> logic_addr_release_fifo;

    void rcev_de_queue_command();
    void rcev_logic_addr();
    void trans_de_queue_report();

    SC_CTOR(DeQueueProcessor)
    {
        SC_METHOD(rcev_de_queue_command);
        sensitive << clk.pos();
        SC_METHOD(rcev_logic_addr);
        sensitive << clk.pos();
        SC_METHOD(trans_de_queue_report);
        sensitive << clk.pos();
    }
};

#endif