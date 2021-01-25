/*
 * @Author: your name
 * @Date: 2020-11-30 09:20:25
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2021-01-21 16:47:23
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
#include "Fifo.hpp"
#include "FlowStatusMessage.h"
#include "ModuleLog.h"
#include "StatCounter.h"
#include <vector>

#define BACK_OFF_TH (32 * 1024)
#define BACK_OFF_EXIT_TH (32 * 1024)
#define BACK_LOG_OFF_TH (32 * 1024)
#define BACK_LOG_OFF_EXIT_TH (32 * 1024)
#define OFF_TO_SLOW_TH (0)
#define OFF_TO_NORMAL_TH (25 * 1024)
#define NORMAL_TO_SLOW_TH (25 * 1024)
#define SLOW_TO_NORMAL_TH (26 * 1024)
#define EMPTY_CREDIT_TH (256)

SC_MODULE(CreditManager)
{
    sc_in<bool> clk;
    sc_in<CreditInfo> credit_info_in;
    sc_in<bool> credit_info_in_valid;
    sc_in<EnQueueReport> en_queue_report_in;
    sc_in<bool> en_queue_report_in_valid;
    sc_in<DeQueueReport> de_queue_report_in;
    sc_in<bool> de_queue_report_in_valid;
    sc_out<FlowStatusMessage> flow_status_message_out;
    sc_out<bool> flow_status_message_out_valid;
    sc_out<CreditInfo> credit_info_out;
    sc_out<bool> credit_info_out_valid;
    Fifo<unsigned> en_queue_report_fifo;
    Fifo<unsigned> write_request_fifo;
    Fifo<unsigned> read_request_fifo;
    Fifo<CreditInfo> unicast_credit_fifo;
    Fifo<CreditInfo> multicast_credit_fifo;
    Fifo<FlowStatusMessage> flow_status_message_fifo;
    std::vector<CreditRequestStatus> old_crs;
    std::vector<int> credit_balance;
    std::vector<int> queue_size;
    ModuleLog log;
    StatCounter stat_counter;

    void recv_request();
    void recv_credit();
    void trans_fsm();
    void trans_credit();
    void crs_state_machine(unsigned flow_id);
    void multicast_credit_generator();
    void crs_state_machine_trigger();
    SC_CTOR(CreditManager)
        : log(name()), stat_counter(name()), old_crs(VOQ_NUM, STATUS_OFF), credit_balance(VOQ_NUM, 0),
          queue_size(VOQ_NUM, 0)
    {
        SC_THREAD(crs_state_machine_trigger);
        sensitive << clk.pos();
        SC_METHOD(recv_request);
        sensitive << clk.pos();
        SC_THREAD(multicast_credit_generator);
        sensitive << clk.pos();
        SC_METHOD(trans_fsm);
        sensitive << clk.pos();
        SC_THREAD(trans_credit);
        sensitive << clk.pos();
        SC_METHOD(recv_credit);
        sensitive << clk.pos();
    }
};

#endif
