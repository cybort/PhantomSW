/*
 * @Description: Packet interaction with cell related module
 * @Author: f21538
 * @Date: 2020-11-27 18:12:14
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-28 15:41:38
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

    sc_in<bool> sop_r_up;
    sc_in<bool> eop_r_up;
    sc_in<bool> valid_pkt_r_up;
    sc_in<int> mod_r_up;
    sc_in<data_bus> packet_r_up;

    sc_in<bool> sop_r_down;
    sc_in<bool> eop_r_down;
    sc_in<bool> valid_pkt_r_down;
    sc_in<int> mod_r_down;
    sc_in<data_bus> packet_r_down;

    // MultiClockTransmitter<packet_line> tx;
    // MultiClockTransmitter<data_bus> tx;
    // MultiClockReceiver<packet_line> rx;
    MultiClockReceiver<data_bus> rx_down, rx_up;
    StatCounter stat;

    // void send_pkt();
    // void clear_signal();
    void recv_pkt_up();
    void recv_pkt_down();

    SC_CTOR(testbench)
        : /*rx(packet, valid_pkt, sop, eop, mod),*/ rx_up(packet_r_up, valid_pkt_r_up, sop_r_up, eop_r_up, mod_r_up),
          rx_down(packet_r_down, valid_pkt_r_down, sop_r_down, eop_r_down, mod_r_down), stat(name())
    {
        // SC_THREAD(send_pkt);
        // sensitive << clk.pos();
        SC_THREAD(recv_pkt_up);
        sensitive << clk.pos();
        SC_THREAD(recv_pkt_down);
        sensitive << clk.pos();
        // stat.register_counter("init_packet_num");
        stat.register_counter("up_from_nif_packet_num");
        stat.register_counter("down_to_nif_packet_num");
    }
};
#endif
