/*
 * @Description: Rebuild packet from cells
 * @Author: f21538
 * @Date: 2020-11-27 18:12:15
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-01 17:57:51
 */
#ifndef _CELL_RESOLVE_H_
#define _CELL_RESOLVE_H_

#include "ModuleLog.h"
#include "MultiClockTransmitter.h"
#include "StatCounter.h"
#include "cell.h"
#include "config.h"
#include "packet_line.h"
#include "port.h"
#include <map>
#include <queue>
#include <set>
#include <utility>

struct packet_identifer;
struct cell_wait_queue;
struct cell_resolve_compare;
struct packet_line;
struct packet_wait_item;

SC_MODULE(cell_resolve)
{
    bool debug;
    sc_in<bool> clk;

    sc_in<bool> valid[TM_CELL_PER_CLOCK_LIMIT];
    sc_in<cell> data[TM_CELL_PER_CLOCK_LIMIT];

    sc_out<bool> sop, eop, pkt_valid;
    sc_out<int> mod;
    // sc_out<packet_line> pkt_out;
    sc_out<data_bus> pkt_out;

    typedef std::priority_queue<cell, std::vector<cell>, cell_resolve_compare> cell_reorder_queue;
    std::map<packet_identifer, cell_wait_queue> cell_cache;
    std::priority_queue<packet_wait_item, std::vector<packet_wait_item>, std::greater<packet_wait_item> /**/>
        packet_wait_queue;
    // MultiClockTransmitter<packet_line> tr;
    MultiClockTransmitter<data_bus> tr;

    int cur_time;
    int packet_wait_threshold;
    int cell_resolve_wait_time;

    ModuleLog log;
    StatCounter stat;

    void verify();
    void rebuild();
    void clean();
    void transfer();
    bool check_time_exceed(int timestamp, int time_threshold);
    int current_min_waiting_timeslot();
    void update_counter();

    SC_CTOR(cell_resolve)
        : debug(true), log(name()), tr(pkt_out, pkt_valid, sop, eop, mod, log), stat(name()),
          packet_wait_threshold(100), cell_resolve_wait_time(200)
    {
        SC_METHOD(verify);
        sensitive << clk.pos();
        SC_METHOD(rebuild);
        sensitive << clk.pos();
        SC_METHOD(clean);
        sensitive << clk.pos();
        SC_THREAD(transfer);
        sensitive << clk.pos();
        SC_METHOD(update_counter);
        sensitive << clk.pos();
        cur_time = 0;

        stat.register_counter("packet_rebuild_queue_size"); // cell_cache
        stat.register_counter("packet_reorder_queue_size"); // packet_wait_queue
    }
};

struct packet_identifer
{
    int timeslot;
    int src;

    bool operator==(const packet_identifer &t) const { return timeslot == t.timeslot && src == t.src; }
    bool operator<(const packet_identifer &t) const
    {
        return timeslot == t.timeslot ? src < t.src : timeslot < t.timeslot;
    }
    bool operator>(const packet_identifer &t) const
    {
        return timeslot == t.timeslot ? src > t.src : timeslot > t.timeslot;
    }
};

struct cell_wait_queue
{
    bool eop;
    int recv_time;
    std::set<cell> queue;

    cell_wait_queue() : eop(false), queue() {}
};

struct cell_resolve_compare
{
    bool operator()(cell &a, cell &b) { return a.fseq > b.fseq; }
};

struct packet_wait_item
{
    packet_identifer packet_des;
    int enqueue_time;
    std::string packet_str;

    packet_wait_item() {}
    packet_wait_item(packet_identifer des, int time, std::string &s)
        : packet_des(des), enqueue_time(time), packet_str(s)
    {
    }

    bool operator<(const packet_wait_item &t) const { return packet_des < t.packet_des; }
    bool operator>(const packet_wait_item &t) const { return packet_des > t.packet_des; }
};

#endif
