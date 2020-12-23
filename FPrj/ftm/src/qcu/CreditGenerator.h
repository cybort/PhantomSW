/*
 * @Author: Zhao Yunpeng
 * @Date: 2020-11-30 09:20:25
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2020-11-30 16:16:14
 * @Description: file content
 */
#ifndef _CREDIT_GENERATOR_H_
#define _CREDIT_GENERATOR_H_

#include "CreditInfo.h"
#include "Exception.h"
#include "FlowStatusMessage.h"
#include "ModuleLog.h"

SC_MODULE(CreditGenerator)
{
    sc_in<bool> clk;
    sc_in<FlowStatusMessage> flow_status_message_in;
    sc_in<bool> flow_status_message_in_valid;
    sc_out<CreditInfo> credit_info_out;
    sc_out<bool> credit_info_out_valid;

    CreditInfo creditInfo_local;
    ModuleLog log;

    void generate();

    SC_CTOR(CreditGenerator) : log(name())
    {
        SC_METHOD(generate);
        sensitive << clk.pos();
    }
};

#endif
