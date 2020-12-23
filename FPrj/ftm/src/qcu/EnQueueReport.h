/*
 * @Author: your name
 * @Date: 2020-11-30 09:20:25
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2020-12-02 09:53:36
 * @Description: file content
 */
#ifndef _EN_QUEUE_REPORT_H
#define _EN_QUEUE_REPORT_H

#include "Exception.h"
#include "config.h"
#include "systemc.h"

struct EnQueueReport
{
public:
    EnQueueReport() : flow_id(-1), packet_size(0) {}

    EnQueueReport(unsigned flowid, unsigned bytes)
    {
        this->flow_id = flow_id;
        this->packet_size = packet_size;
    }
    unsigned get_flow_id();
    void set_flow_id(unsigned flow_id);
    unsigned get_packet_size();
    void set_packet_size(unsigned packet_size);
    bool operator==(const EnQueueReport &rhs) const
    {
        return (rhs.flow_id == flow_id && rhs.packet_size == packet_size);
    }
    friend std::ostream& operator<<(std::ostream& os, const EnQueueReport& t) { return os<<t.flow_id<<","<<t.packet_size; }

private:
    unsigned flow_id;
    unsigned packet_size;
};

extern void sc_trace(sc_trace_file *tf, const EnQueueReport &v, const std::string &name);

#endif