/*
 * @Author: your name
 * @Date: 2021-01-20 14:39:44
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2021-01-21 17:13:42
 * @Description: file content
 */
#ifndef _QUEUE_LIST_MANAGER_H_
#define _QUEUE_LIST_MANAGER_H_
#include "ModuleLog.h"
#include "config.h"
#include "pd.h"
#include "systemc.h"
#include <queue>
#include <vector>
SC_MODULE(QueueListManager)
{
    sc_in<bool> clk;
    sc_in<pd> packet_descriptor_in;
    sc_in<bool> packet_descriptor_in_valid;
    sc_in<unsigned> flow_id_in;
    sc_in<bool> flow_id_in_valid;
    sc_in<unsigned> flow_id_release_in;
    sc_in<bool> flow_id_release_in_valid;
    sc_out<bool> save_packet_descriptor_complete_signal_out;
    sc_out<pd> packet_descriptor_out;
    sc_out<bool> packet_descriptor_out_valid;
    std::vector<std::queue<pd> > virtual_output_queues;
    std::vector<std::queue<pd> > virtual_output_queues_reading;
    ModuleLog log;

    void en_queue();
    void de_queue();
    void release_packet_descriptor();

    SC_CTOR(QueueListManager) : virtual_output_queues(VOQ_NUM), virtual_output_queues_reading(VOQ_NUM), log(name())
    {
        SC_METHOD(en_queue);
        sensitive << clk.pos();
        SC_METHOD(de_queue);
        sensitive << clk.pos();
        SC_METHOD(release_packet_descriptor);
        sensitive << clk.pos();
    }
};

#endif