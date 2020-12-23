/*
 * @Description: Receive cells from switch
 * @Author: f21538
 * @Date: 2020-11-27 18:12:14
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-17 13:55:46
 */
#ifndef _RX_H_
#define _RX_H_

#include "CreditInfo.h"
#include "FlowStatusMessage.h"
#include "ModuleLog.h"
#include "QueueSocketHandler.h"
#include "StatCounter.h"
#include "cell.h"
#include "port.h"
#include "simple_queue.h"
#include "tlm_utils/tlm_quantumkeeper.h"
#include <map>

SC_MODULE(rx)
{
    bool debug;
    sc_in<bool> clk;

    sc_out<bool> valid[TM_CELL_PER_CLOCK_LIMIT];
    sc_out<cell> data[TM_CELL_PER_CLOCK_LIMIT];
    sc_out<FlowStatusMessage> flow_status_out;
    sc_out<bool> valid_flow_status_out;
    sc_out<CreditInfo> credit_info_out;
    sc_out<bool> valid_credit_info_out;
    tlm_utils::tlm_quantumkeeper keeper;

    QueueSocketHandler<cell, std::priority_queue<cell, std::vector<cell>, std::greater<cell> > > h;
    ModuleLog log;
    StatCounter stat;
    ConfigAccesssor conf;
    simple_prio_queue<cell, std::greater<cell> > transfer_queue;
    simple_queue<cell_flowsts> flowsts_queue;
    simple_queue<cell_credit> credit_queue;
    std::map<int /*src_id*/, std::map<int /*flow_id>*/, int /*reqseq*/> > last_reqseq;

    void recv();
    void classify();
    void sch();
    void ctrl_info();
    void update_counter();
    bool check_request_sequence(int src_id, int flow_id, int seq);
    bool check_cycle_between(int cycle_len, int start, int end, int x);

    SC_CTOR(rx) : debug(false), log(name()), stat(name()), conf(name())
    {
        tlm_utils::tlm_quantumkeeper::set_global_quantum(sc_time(10, SC_MS));
        keeper.reset();
        SC_THREAD(recv);
        sensitive << clk.pos();
        SC_METHOD(classify);
        sensitive << clk.pos();
        SC_METHOD(sch);
        sensitive << clk.pos();
        SC_METHOD(ctrl_info);
        sensitive << clk.pos();
        SC_METHOD(update_counter);
        sensitive << clk.pos();

        stat.register_counter("rx_queue_size");

        conf.register_config("rx_validate_reqseq");
    }
};

#endif
