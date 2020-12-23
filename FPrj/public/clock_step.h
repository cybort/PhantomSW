/*
 * @Description: Run systemc code clock by clock
 * @Author: f21538
 * @Date: 2020-11-30 16:15:30
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-01 14:40:42
 */
#ifndef _CLOCK_STEP_H_
#define _CLOCK_STEP_H_

#include "ModuleLog.h"
#include "port.h"
#include "systemc.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <sstream>
#include <string>

struct not_digit
{
    bool operator()(const char c) { return !std::isdigit(c); }
};

SC_MODULE(clock_step)
{
    bool debug;
    sc_in<bool> clk;

    long long current_clock;
    long long clocks_remain;
    enum
    {
        Continuous,
        Step
    } step_mode;
    not_digit not_a_digit;

    ModuleLog log;

    void per_clock();

    SC_CTOR(clock_step) : debug(false), current_clock(0), clocks_remain(1), log(name())
    {
        SC_METHOD(per_clock);
        sensitive << clk.pos();
    }
};

#endif
