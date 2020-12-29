/*
 * @Description: Split packet and generate cells
 * @Author: f21538
 * @Date: 2020-11-27 18:12:14
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-26 14:55:14
 */
#ifndef _CELL_GEN_H_
#define _CELL_GEN_H_

#include "Header.h"
#include "ModuleLog.h"
#include "MultiClockReceiver.h"
#include "Packet.h"
#include "StatCounter.h"
#include "cell.h"
#include "config.h"
#include "packet_line.h"
#include "port.h"
#include "simple_queue.h"
#include "testbench.h"
#include <string>

SC_MODULE(cell_gen)
{
    bool debug;
    sc_in<bool> clk;
    sc_in<bool> sop;
    sc_in<bool> eop;
    sc_in<bool> valid_pkt;
    sc_in<int> mod;
    // sc_in<packet_line> packet;
    sc_in<data_bus> packet;

    sc_out<bool> valid[TM_CELL_PER_CLOCK_LIMIT];
    sc_out<cell> data[TM_CELL_PER_CLOCK_LIMIT];

    simple_queue<cell> cell_q;
    simple_queue<std::string> pkt_q;
    simple_queue<int> cell_num_q;
    bool long_pkt_started;
    int current_t;
    int timeslot;
    int cell_num_remain;
    std::string current_p;
    int current_seq;

    // MultiClockReceiver<packet_line> rc;
    MultiClockReceiver<data_bus> rc;
    ModuleLog log;
    StatCounter stat;

    // void recv_pkt();/*deprecated*/
    void recv();
    void split();
    cell & fill_cell(cell & c, const char * str, int str_size, int dest_id);
    void transfer();
    void update_counter();

    SC_CTOR(cell_gen) : debug(false), log(name()), rc(packet, valid_pkt, sop, eop, mod, log), stat(name())
    {
        SC_THREAD(recv);
        sensitive << clk.pos();
        SC_METHOD(split);
        sensitive << clk.pos();
        SC_METHOD(transfer);
        sensitive << clk.pos();
        SC_METHOD(update_counter);
        sensitive << clk.pos();
        rc.set_debug(true);
        long_pkt_started = false;
        timeslot = 0;
        current_t = 0;
        cell_num_remain = 0;
        current_p = "";
        current_seq = 0;

        stat.register_counter("packet_waiting_split");             // pkt_q
        stat.register_counter("cell_waiting_transfer");            // cell_q
        stat.register_counter("cell_waiting_transfer_by_packets"); // cell_num_q
        stat.register_counter("packet_up");
    }
};

#endif
