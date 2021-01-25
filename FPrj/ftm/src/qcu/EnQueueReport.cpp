/*
 * @Author: your name
 * @Date: 2020-11-30 09:20:25
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2020-12-26 14:42:20
 * @Description: file content
 */
#include "EnQueueReport.h"

void EnQueueReport::set_flow_id(unsigned flow_id)
{
    if (flow_id >= VOQ_NUM)
    {
        throw Exception("error : flow_id is out of range.");
    }
    this->flow_id = flow_id;
}

unsigned EnQueueReport::get_flow_id() { return this->flow_id; }

void EnQueueReport::set_packet_size(unsigned packet_size)
{
    if (packet_size <= 0)
    {
        throw Exception("error : packet_size must lager than 0.");
    }
    this->packet_size = packet_size;
}

unsigned EnQueueReport::get_packet_size() { return this->packet_size; }

void sc_trace(sc_trace_file * tf, const EnQueueReport & v, const std::string & name) {}