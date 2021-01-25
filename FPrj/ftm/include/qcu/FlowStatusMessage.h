/*
 * @Author: your name
 * @Date: 2020-11-30 09:20:25
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-22 13:56:59
 * @Description: file content
 */
#ifndef _FLOW_STATUS_MESSAGE_H
#define _FLOW_STATUS_MESSAGE_H

#include "Exception.h"
#include "config.h"
#include "systemc.h"

#define FLOW_STATUS_MESSAGE_REQUIRE_OFF 0
#define FLOW_STATUS_MESSAGE_REQUIRE_SLOW 1
#define FLOW_STATUS_MESSAGE_REQUIRE_NORMAL 2

enum CreditRequestStatus
{
    STATUS_OFF,
    STATUS_SLOW,
    STATUS_NORMAL
};

struct FlowStatusMessage
{
public:
    FlowStatusMessage() : flow_id(-1), src_tm_id(0), dest_tm_id(0), status(STATUS_OFF) {}
    void set_flow_id(unsigned flow_id);
    unsigned get_flow_id();
    void set_src_tm_id(unsigned src_tm_id);
    unsigned get_src_tm_id();
    void set_dest_tm_id(unsigned dest_tm_id);
    unsigned get_dest_tm_id();
    void set_status(CreditRequestStatus status);
    CreditRequestStatus get_status();
    bool operator==(const FlowStatusMessage & rhs) const { return (rhs.flow_id == flow_id && rhs.status == status); }
    friend std::ostream & operator<<(std::ostream & os, const FlowStatusMessage & t)
    {
        return os << t.flow_id << "," << t.status;
    }

private:
    unsigned flow_id;
    unsigned src_tm_id;
    unsigned dest_tm_id;
    CreditRequestStatus status;
};

extern void sc_trace(sc_trace_file * tf, const FlowStatusMessage & v, const std::string & name);

#endif
