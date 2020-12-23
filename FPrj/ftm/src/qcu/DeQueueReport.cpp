/*
 * @Author: your name
 * @Date: 2020-11-30 09:20:25
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2020-11-30 16:17:19
 * @Description: file content
 */
#include "DeQueueReport.h"

void DeQueueReport::set_flow_id(unsigned flow_id)
{
    if (flow_id >= VOQ_NUM)
    {
        throw Exception("error : flow_id is out of range.");
    }
    this->flow_id = flow_id;
}

unsigned DeQueueReport::get_flow_id() const { return this->flow_id; }

void DeQueueReport::set_packet_size(unsigned packet_size)
{
    if (packet_size == 0)
    {
        throw Exception("error : packet_size must be lagger than 0.");
    }
    this->packet_size = packet_size;
}

unsigned DeQueueReport::get_packet_size() const { return this->packet_size; }

extern void sc_trace(sc_trace_file * tf, const DeQueueReport & v, const std::string & name) {}
