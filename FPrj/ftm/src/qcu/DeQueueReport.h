/*
 * @Author: your name
 * @Date: 2020-11-30 09:20:25
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2020-12-02 09:53:25
 * @Description: file content
 */
#ifndef _DE_QUEUE_REPORT_H
#define _DE_QUEUE_REPORT_H

#include "Exception.h"
#include "config.h"
#include "systemc.h"

struct DeQueueReport
{
public:
    DeQueueReport() : flow_id(-1), packet_size(0) {}

    DeQueueReport(unsigned flow_id, unsigned packet_size)
    {
        this->flow_id = flow_id;
        this->packet_size = packet_size;
    }
    unsigned get_flow_id() const;
    void set_flow_id(unsigned flow_id);
    unsigned get_packet_size() const;
    void set_packet_size(unsigned packet_size);
    bool operator==(const DeQueueReport & rhs) const
    {
        return (rhs.flow_id == flow_id && rhs.packet_size == packet_size);
    }
    friend std::ostream & operator<<(std::ostream & os, const DeQueueReport & t)
    {
        return os << t.flow_id << "," << t.packet_size;
    }

private:
    unsigned flow_id;
    unsigned packet_size;
};

extern void sc_trace(sc_trace_file * tf, const DeQueueReport & v, const std::string & name);

#endif
