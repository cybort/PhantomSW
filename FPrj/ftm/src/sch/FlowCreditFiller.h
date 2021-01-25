/*
 * @Description:
 * @Author: f21538
 * @Date: 2021-01-14 14:50:38
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-22 17:36:56
 */
#ifndef _FLOW_CREDIT_FILLER_H_
#define _FLOW_CREDIT_FILLER_H_
#include "ConfigDB.h"
#include "Flow.h"
#include "systemc.h"
SC_MODULE(FlowCreditFiller)
{
    sc_in<bool> clk;
    int clk_remain;

    ConfigAccesssor config;

    void add_credit()
    {
        if (clk_remain > 0)
        {
            clk_remain--;
        }

        if (clk_remain == 0)
        {
            clk_remain = config.retrieve_config("rtc");
        }
        else
        {
            return;
        }

        for (auto & pair : FlowPool::flows)
        {
            if (pair.second.is_enabled())
            {
                pair.second.add_credit();
            }
        }
    }
    SC_CTOR(FlowCreditFiller) : config(name())
    {
        SC_METHOD(add_credit);
        sensitive << clk.pos();

        config.register_config("rtc");
        config.update_config("rtc", 1);
    }
};
#endif
