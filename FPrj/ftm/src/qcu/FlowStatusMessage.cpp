/*
 * @Author: your name
 * @Date: 2020-11-30 09:20:25
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2020-11-30 16:18:03
 * @Description: file content
 */
#include "FlowStatusMessage.h"

void FlowStatusMessage::set_flow_id(unsigned flow_id)
{
    if (flow_id >= VOQ_NUM)
    {
        throw Exception("error : flow_id is out of range.");
    }
    this->flow_id = flow_id;
}

unsigned FlowStatusMessage::get_flow_id() { return this->flow_id; }

void FlowStatusMessage::set_src_tm_id(unsigned src_tm_id)
{
    if (src_tm_id >= MAX_FAP)
    {
        throw Exception("error : src tm id is out of range.");
    }
    this->src_tm_id = src_tm_id;
}

unsigned FlowStatusMessage::get_src_tm_id() { return this->src_tm_id; }

void FlowStatusMessage::set_dest_tm_id(unsigned dest_tm_id)
{
    if (dest_tm_id >= MAX_FAP)
    {
        throw Exception("error : dest tm id is out of range.");
    }
    this->dest_tm_id = dest_tm_id;
}

unsigned FlowStatusMessage::get_dest_tm_id() { return this->dest_tm_id; }

void FlowStatusMessage::set_status(FlowStatus status) { this->status = status; }

FlowStatus FlowStatusMessage::get_status() { return this->status; }

void sc_trace(sc_trace_file * tf, const FlowStatusMessage & v, const std::string & name) {}
