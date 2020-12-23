/*
 * @Description: Packet interaction with cell related module
 * @Author: f21538
 * @Date: 2020-11-27 18:12:14
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-01 14:30:28
 */
#ifndef _TESTBENCH_H_
#define _TESTBENCH_H_

#include "MultiClockReceiver.h"
#include "MultiClockTransmitter.h"
#include "StatCounter.h"
#include "config.h"
#include "packet_line.h"
#include "systemc.h"

SC_MODULE(testbench)
{
    sc_in<bool> clk;

    // sc_out<bool> sop;
    // sc_out<bool> eop;
    // sc_out<bool> valid_pkt;
    // sc_out<int> mod;
    // sc_out<packet_line> packet;
    // sc_out<data_bus> packet;

    sc_in<bool> sop_r;
    sc_in<bool> eop_r;
    sc_in<bool> valid_pkt_r;
    sc_in<int> mod_r;
    // sc_in<packet_line> packet_r;
    sc_in<data_bus> packet_r;

    // MultiClockTransmitter<packet_line> tx;
    // MultiClockTransmitter<data_bus> tx;
    // MultiClockReceiver<packet_line> rx;
    MultiClockReceiver<data_bus> rx;
    StatCounter stat;

    void send_pkt();
    void clear_signal();
    void recv_pkt();

    SC_CTOR(testbench)
        : /*rx(packet, valid_pkt, sop, eop, mod),*/ rx(packet_r, valid_pkt_r, sop_r, eop_r, mod_r), stat(name())
    {
        // SC_THREAD(send_pkt);
        // sensitive << clk.pos();
        SC_THREAD(recv_pkt);
        sensitive << clk.pos();
        stat.register_counter("init_packet_num");
        stat.register_counter("received_packet_num");
    }
};
#endif