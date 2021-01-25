/*
 * @Description:
 * @Author: f21538
 * @Date: 2021-01-20 15:46:14
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-23 13:44:04
 */
#include "Flow.h"
#include "FlowCreditFiller.h"
#include "FlowStatusResolver.h"
#include "RootScheduler.h"
#include "SE.h"
#include "VOQ.h"
#include "systemc.h"
#include "testbench.h"

int sc_main(int argc, char * argv[])
{

    sc_clock clk("clk", sc_time(10, SC_MS), 0.5, sc_time(1, SC_MS));
    sc_signal<sc_bv<LINK_NUM>> link_valid_testbench_to_root_scheduler;
    sc_signal<FlowStatusMessage> flow_status_message_testbench_to_flow_status_resolver;
    sc_signal<bool> flow_status_message_valid_testbench_to_flow_status_resolver;
    sc_signal<CreditInfo> credit_info_flow_status_resolver_to_testbench;
    sc_signal<bool> credit_info_valid_flow_status_resolver_to_testbench;

    FlowStatusResolver fsr("FlowStatusResolver");
    fsr.clk(clk);
    fsr.flow_status_message_in(flow_status_message_testbench_to_flow_status_resolver);
    fsr.flow_status_message_in_valid(flow_status_message_valid_testbench_to_flow_status_resolver);
    fsr.credit_info_out(credit_info_flow_status_resolver_to_testbench);
    fsr.credit_info_out_valid(credit_info_valid_flow_status_resolver_to_testbench);

    RootScheduler rs("RootScheduler");
    rs.clk(clk);
    rs.link_valid(link_valid_testbench_to_root_scheduler);

    FlowCreditFiller fcf("FlowCreditFiller");
    fcf.clk(clk);

    testbench tb("testbench--");
    tb.clk(clk);
    tb.link_valid_out(link_valid_testbench_to_root_scheduler);
    tb.flow_status_message_out(flow_status_message_testbench_to_flow_status_resolver);
    tb.flow_status_message_out_valid(flow_status_message_valid_testbench_to_flow_status_resolver);
    tb.credit_info_in(credit_info_flow_status_resolver_to_testbench);
    tb.credit_info_in_valid(credit_info_valid_flow_status_resolver_to_testbench);

    sc_start();
}
