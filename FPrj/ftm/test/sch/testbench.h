/*
 * @Description:
 * @Author: f21538
 * @Date: 2021-01-21 09:10:00
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-23 09:55:36
 */
#ifndef _TEST_BENCH_H_
#define _TEST_BENCH_H_
#include "CreditInfo.h"
#include "FlowStatusMessage.h"
#include "ModuleLog.h"
#include "RootScheduler.h"
#include "systemc.h"
#include <random>
SC_MODULE(testbench)
{
    sc_in<bool> clk;

    sc_in<CreditInfo> credit_info_in;
    sc_in<bool> credit_info_in_valid;

    sc_out<FlowStatusMessage> flow_status_message_out;
    sc_out<bool> flow_status_message_out_valid;
    sc_out<sc_bv<LINK_NUM>> link_valid_out;

    std::random_device rand_engine;
    std::mt19937 mt;
    std::uniform_int_distribution<> flow_id_dist;

    ModuleLog log;

    void generate();

    SC_CTOR(testbench) : mt(rand_engine()), flow_id_dist(0, 8), log(name())
    {
        SC_THREAD(generate);
        sensitive << clk.pos();
    }
};
#endif
