/*
 * @Author: your name
 * @Date: 2021-01-18 09:46:58
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2021-01-22 11:37:33
 * @Description: file content
 */

#ifndef _QUEUE_SCH_H_
#define _QUEUE_SCH_H_

#include "CreditInfo.h"
#include "DeQueueCommand.h"
#include "DeQueueReport.h"
#include "EnQueueReport.h"
#include "Fifo.hpp"
#include "ModuleLog.h"
#include "StatCounter.h"
#include "systemc.h"
#include <vector>
SC_MODULE(QueueSch)
{
    sc_in<bool> clk;
    sc_in<EnQueueReport> en_queue_report_in;
    sc_in<bool> en_queue_report_in_valid;
    sc_in<DeQueueReport> de_queue_report_in;
    sc_in<bool> de_queue_report_in_valid;
    sc_in<CreditInfo> credit_info_in;
    sc_in<bool> credit_info_in_valid;
    sc_out<DeQueueCommand> de_queue_command_out;
    sc_out<bool> de_queue_command_out_valid;
    Fifo<unsigned> en_queue_report_fifo;
    Fifo<unsigned> write_request_fifo;
    Fifo<unsigned> read_request_fifo;
    /*CLOS SCH Q*/
    Fifo<unsigned> high_priority_multicast;
    Fifo<unsigned> low_priority_multicast;
    Fifo<unsigned> high_priority_local_unicast;
    Fifo<unsigned> low_priority_local_unicast;
    Fifo<unsigned> high_priority_remote_unicast;
    Fifo<unsigned> low_priority_remote_unicast;
    Fifo<unsigned> ageing;
    enum QueuePriority
    {
        H_MULTICAST,
        L_MULTICAST,
        H_LOCAL_UNICAST,
        L_LOCAL_UNICAST,
        H_REMOTE_UNICAST,
        L_REMOTE_UNICAST
    };
    /*Queueing List*/
    std::vector<bool> sch_queueing_list;
    std::vector<int> credit_balance;
    std::vector<unsigned> queue_size;
    std::vector<QueuePriority> queue_priority_list;

    ModuleLog log;
    StatCounter counter;

    void clos_sch();
    void request_rcev();
    void sch_queueing_trigger();
    void sch_queueing(unsigned flow_id);

    SC_CTOR(QueueSch)
        : high_priority_multicast(128), low_priority_multicast(128), high_priority_local_unicast(128),
          low_priority_local_unicast(128), high_priority_remote_unicast(128), low_priority_remote_unicast(128),
          ageing(128), en_queue_report_fifo(64), sch_queueing_list(VOQ_NUM, false), credit_balance(VOQ_NUM, 0),
          queue_size(VOQ_NUM, 0), queue_priority_list(VOQ_NUM, H_MULTICAST), log(name()), counter(name())
    {
        for (int i = 0; i < VOQ_NUM; i++)
        {
            if (i == 4)
            {
                queue_priority_list[i] = H_MULTICAST;
            }
            if (i > 1 && i < 4)
            {
                queue_priority_list[i] = L_MULTICAST;
            }
            if (i >= 4 && i < VOQ_NUM - 1)
            {
                queue_priority_list[i] = H_REMOTE_UNICAST;
            }
            if (i == VOQ_NUM - 1)
            {
                queue_priority_list[i] = L_REMOTE_UNICAST;
            }
        }
        SC_THREAD(clos_sch);
        sensitive << clk.pos();
        SC_METHOD(request_rcev);
        sensitive << clk.pos();
        SC_THREAD(sch_queueing_trigger);
        sensitive << clk.pos();
        counter.register_counter("queue_size", StatCounterBase::Repeated);
        counter.register_counter("credit_balance", StatCounterBase::Repeated);
        counter.register_counter("sch_queueing_size", StatCounterBase::Repeated);
    }
};

#endif