/*
 * @Author: your name
 * @Date: 2020-11-30 16:53:13
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2020-12-03 11:18:32
 * @Description: file content
 */
#ifndef _QUEUE_MANAGER_H_
#define _QUEUE_MANAGER_H_
#include "DeQueueCommand.h"
#include "DeQueueReport.h"
#include "EnQueueReport.h"
#include "Exception.h"
#include "Fifo.hpp"
#include "ModuleLog.h"
#include "MultiClockReceiver.h"
#include "MultiClockTransmitter.h"
#include "Packet.h"
#include "config.h"
#include "pd.h"
#include "systemc.h"

#define PD_FIFO_SIZE 16

SC_MODULE(QueueManager)
{
    sc_in<bool> clk;
    /*packet in*/
    sc_in<data_bus> packet_in;
    sc_in<bool> packet_in_valid;
    sc_in<bool> packet_in_sop;
    sc_in<bool> packet_in_eop;
    sc_in<int> packet_in_mod;
    /*packet addr in*/
    sc_in<unsigned> addr_in;
    sc_in<bool> addr_in_valid;
    /*packet descriptor in */
    sc_in<pd> packet_descriptor_in;
    sc_in<bool> packet_descriptor_in_valid;
    /*dequeue command in */
    sc_in<DeQueueCommand> dequeue_command_in;
    sc_in<bool> dequeue_command_in_valid;
    /*packet out*/
    sc_out<data_bus> packet_out;
    sc_out<bool> packet_out_valid;
    sc_out<bool> packet_out_sop;
    sc_out<bool> packet_out_eop;
    sc_out<int> packet_out_mod;
    /*packet read out*/
    sc_out<bool> packet_read;
    /*packet descriptor flow control*/
    sc_out<bool> packet_descriptor_fc;
    /*enqueue report out*/
    sc_out<EnQueueReport> enqueue_report_out;
    sc_out<bool> enqueue_report_out_valid;
    /*packet addr out*/
    sc_out<unsigned> addr_out;
    sc_out<bool> addr_out_valid;
    MultiClockTransmitter<data_bus> trs;
    MultiClockReceiver<data_bus> recv;
    /*dequeue report out*/
    sc_out<DeQueueReport> dequeue_report_to_cm_out;
    sc_out<bool> dequeue_report_to_cm_out_valid;
    sc_out<DeQueueReport> dequeue_report_to_cavd_out;
    sc_out<bool> dequeue_report_to_cavd_out_valid;
    /*packet fifo*/
    Fifo<FPacket> packet_in_fifo;
    Fifo<FPacket> packet_out_fifo;
    /*packet descriptor fifo*/
    Fifo<pd> packet_descriptor_in_fifo;
    Fifo<pd> packet_descriptor_process_fifo;

    std::queue<pd> queues[VOQ_NUM];
    unsigned queue_sizes[VOQ_NUM];
    unsigned destination_table[VOQ_NUM];
    ModuleLog log;

    void recv_packet();
    void trans_packet();
    void recv_packet_descriptor();
    void filt();
    void enqueue();
    void dequeue();
    void init_dest_table();

    SC_CTOR(QueueManager)
        : trs(packet_out, packet_out_valid, packet_out_sop, packet_out_eop, packet_out_mod),
          recv(packet_in, packet_in_valid, packet_in_sop, packet_in_eop, packet_in_mod), log(name())
    {
        memset(queue_sizes, 0, sizeof(int) * VOQ_NUM);
        memset(destination_table, 0, sizeof(int) * VOQ_NUM);
        SC_THREAD(recv_packet);
        sensitive << clk.pos();
        SC_THREAD(trans_packet);
        sensitive << clk.pos();
        SC_METHOD(filt);
        sensitive << clk.pos();
        SC_METHOD(enqueue);
        sensitive << clk.pos();
        SC_METHOD(dequeue);
        sensitive << clk.pos();
        SC_METHOD(recv_packet_descriptor);
        sensitive << clk.pos();
    }
};

#endif