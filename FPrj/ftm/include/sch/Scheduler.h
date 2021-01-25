/*
 * @Description:
 * @Author: f21538
 * @Date: 2021-01-23 13:45:07
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-23 14:57:31
 */
#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "Flow.h"
#include "FlowCreditFiller.h"
#include "FlowStatusResolver.h"
#include "RootScheduler.h"
#include "SE.h"
#include "VOQ.h"
#include "systemc.h"
SC_MODULE(Scheduler)
{
    bool debug;
    sc_in<bool> clk;

    sc_in<sc_bv<LINK_NUM>> link_valid_in;
    sc_in<FlowStatusMessage> flow_status_message_in;
    sc_in<bool> flow_status_message_in_valid;

    sc_out<CreditInfo> credit_info_out;
    sc_out<bool> credit_info_out_valid;

    FlowStatusResolver fsr;
    RootScheduler rs;
    FlowCreditFiller fcf;

    SC_CTOR(Scheduler) : fsr("FlowStatusResolver"), rs("RootScheduler"), fcf("FlowCreditFiller")
    {

        fsr.clk(clk);
        fsr.flow_status_message_in(flow_status_message_in);
        fsr.flow_status_message_in_valid(flow_status_message_in_valid);
        fsr.credit_info_out(credit_info_out);
        fsr.credit_info_out_valid(credit_info_out_valid);

        rs.clk(clk);
        rs.link_valid(link_valid_in);
        rs.flow_status_resolver_name = fsr.name();

        fcf.clk(clk);
    }
};

#endif
