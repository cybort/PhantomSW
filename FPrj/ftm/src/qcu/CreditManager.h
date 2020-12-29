/*
 * @Author: your name
 * @Date: 2020-11-30 09:20:25
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2020-12-26 17:20:43
 * @Description: file content
 */
#ifndef _CREDIT_MANAGER_H_
#define _CREDIT_MANAGER_H_

#include "CreditInfo.h"
#include "DeQueueCommand.h"
#include "DeQueueReport.h"
#include "DestinationTable.h"
#include "EnQueueReport.h"
#include "Exception.h"
#include "FlowStatusMessage.h"
#include "ModuleLog.h"
#include "StatCounter.h"

#define CREDIT_MANAGER_QUEUE_NUM (96 * 1024)
#define CREDIT_MANAGER_CREDIT_RESOLUTION_4 4 // 4B
SC_MODULE(CreditManager)
{
    sc_in<bool> clk;
    sc_in<CreditInfo> credit_info_in;
    sc_in<bool> credit_info_in_valid;
    sc_in<EnQueueReport> enqueue_report;
    sc_in<bool> enqueue_report_valid;
    sc_in<DeQueueReport> dequeue_report;
    sc_in<bool> dequeue_report_valid;
    sc_out<DeQueueCommand> dequeue_command;
    sc_out<bool> dequeue_command_valid;
    sc_out<FlowStatusMessage> flow_status_message_out;
    sc_out<bool> flow_status_message_out_valid;

    FlowStatusMessage flow_status_message_local;
    int credit_balance[CREDIT_MANAGER_QUEUE_NUM];
    unsigned queue_size[CREDIT_MANAGER_QUEUE_NUM];
    ModuleLog log;
    StatCounter stat_counter;

    void dequeue_sch();
    void dequeue_report_event();
    void enqueue_report_event();
    void credit_apply();
    void credit_accept();
    SC_CTOR(CreditManager) : log(name()), stat_counter(name())
    {
        SC_METHOD(enqueue_report_event);
        sensitive << clk.pos();
        SC_THREAD(dequeue_sch);
        sensitive << clk.pos();
        SC_THREAD(credit_apply);
        sensitive << clk.pos();
        SC_METHOD(credit_accept);
        sensitive << clk.pos();
        SC_METHOD(dequeue_report_event);
        sensitive << clk.pos();
        memset(credit_balance, 0, sizeof(int) * CREDIT_MANAGER_QUEUE_NUM);
        memset(queue_size, 0, sizeof(unsigned) * CREDIT_MANAGER_QUEUE_NUM);
        stat_counter.register_counter("flow status msg", StatCounterBase::Repeated);
        stat_counter.register_counter("credit recv");
    }
};

#endif
