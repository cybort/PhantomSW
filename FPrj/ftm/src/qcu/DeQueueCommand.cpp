/*
 * @Author: your name
 * @Date: 2020-11-30 09:20:25
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2020-11-30 16:17:28
 * @Description: file content
 */
#include "DeQueueCommand.h"

void DeQueueCommand::set_flow_id(unsigned flow_id)
{
    if (flow_id >= VOQ_NUM)
    {
        throw Exception("error : flow_id is out of range.");
    }
    this->flow_id = flow_id;
}

unsigned DeQueueCommand::get_flow_id() { return this->flow_id; }

void sc_trace(sc_trace_file *tf, const DeQueueCommand &v, const std::string &name) {}
