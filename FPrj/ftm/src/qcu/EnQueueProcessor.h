/*
 * @Author: your name
 * @Date: 2021-01-13 13:36:45
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2021-01-21 10:40:17
 * @Description: file content
 */
#ifndef _EN_QUEUE_PROCESSOR_H_
#define _EN_QUEUE_PROCESSOR_H_
#include "DestinationTable.h"
#include "EnQueueReport.h"
#include "Fifo.hpp"
#include "LogicAddrTable.h"
#include "ModuleLog.h"
#include "MultiClockReceiver.h"
#include "MultiClockTransmitter.h"
#include "Packet.h"
#include "StatCounter.h"
#include "config.h"
#include "pd.h"
#include "systemc.h"

SC_MODULE(EnQueueProcessor)
{
    sc_in<bool> clk;
    /*packet in*/
    sc_in<data_bus> packet_in;
    sc_in<bool> packet_in_valid;
    sc_in<bool> packet_in_sop;
    sc_in<bool> packet_in_eop;
    sc_in<int> packet_in_mod;
    /*packet descriptor in */
    sc_in<pd> packet_descriptor_in;
    sc_in<bool> packet_descriptor_in_valid;
    /*save complete signal*/
    sc_in<bool> write_packet_complete_signal_in;
    /*save packet descriptor signal*/
    sc_in<bool> write_packet_descriptor_complete_signal_in;
    /*packet out*/
    sc_out<data_bus> packet_out;
    sc_out<bool> packet_out_valid;
    sc_out<bool> packet_out_sop;
    sc_out<bool> packet_out_eop;
    sc_out<int> packet_out_mod;
    /*logic addr out*/
    sc_out<unsigned> logic_addr_out;
    /*packet read out*/
    sc_out<bool> packet_read;
    /*packet descriptor flow control*/
    sc_out<bool> packet_descriptor_fc;
    /*packet descriptor out */
    sc_out<pd> packet_descriptor_out;
    sc_out<bool> packet_descriptor_out_valid;
    /*enqueue report out*/
    sc_out<EnQueueReport> enqueue_report_to_queue_sch_out;
    sc_out<bool> enqueue_report_to_queue_sch_out_valid;
    sc_out<EnQueueReport> enqueue_report_to_credit_manager_out;
    sc_out<bool> enqueue_report_to_credit_manager_out_valid;
    /*packet transmitter&receiver*/
    MultiClockTransmitter<data_bus> trs;
    MultiClockReceiver<data_bus> recv;
    /*packet fifo*/
    Fifo<FPacket> packet_in_fifo;
    Fifo<FPacket> packet_out_fifo;
    /*logic addr fifo*/
    Fifo<unsigned> logic_addr_out_fifo;
    /*packet descriptor fifo*/
    Fifo<pd> packet_descriptor_in_fifo;
    Fifo<pd> packet_descriptor_out_fifo;
    /*enqueue report fifo*/
    Fifo<EnQueueReport> en_queue_report_out_fifo;
    ModuleLog log;
    StatCounter stat_counter;

    void recv_packet();
    void trans_packet();
    void recv_packet_descriptor();
    void trans_packet_descriptor();
    void process();
    void trans_en_queue_report();

    SC_CTOR(EnQueueProcessor)
        : trs(packet_out, packet_out_valid, packet_out_sop, packet_out_eop, packet_out_mod),
          recv(packet_in, packet_in_valid, packet_in_sop, packet_in_eop, packet_in_mod), log(name()),
          packet_descriptor_in_fifo(16), stat_counter("en_queue_processor")
    {
        SC_THREAD(recv_packet);
        sensitive << clk.pos();
        SC_THREAD(trans_packet);
        sensitive << clk.pos();
        SC_METHOD(process);
        sensitive << clk.pos();
        SC_METHOD(trans_en_queue_report);
        sensitive << clk.pos();
        SC_METHOD(recv_packet_descriptor);
        sensitive << clk.pos();
        SC_METHOD(trans_packet_descriptor);
        sensitive << clk.pos();
        stat_counter.register_counter("enqueue_report_generate", StatCounterBase::Repeated);
    }
};

#endif