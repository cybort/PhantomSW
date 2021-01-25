/*
 * @Author: your name
 * @Date: 2020-11-30 16:53:13
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2020-12-26 18:03:33
 * @Description: file content
 */
#ifndef _CREDIT_INFO_H_
#define _CREDIT_INFO_H_

#include "Exception.h"
#include "config.h"
#include "systemc.h"

#define CREDIT_INFO_CREDIT_OFF 0
#define CREDIT_INFO_CREDIT_SLOW 64
#define CREDIT_INFO_CREDIT_NORMAL 256
struct CreditInfo
{
public:
    CreditInfo() : flow_id(-1), src_tm_id(0), dest_tm_id(0), credit(CREDIT_INFO_CREDIT_OFF) {}
    void set_flow_id(unsigned flow_id);
    unsigned get_flow_id();
    void set_src_tm_id(unsigned src_tm_id);
    unsigned get_src_tm_id();
    void set_dest_tm_id(unsigned dest_tm_id);
    unsigned get_dest_tm_id();
    void set_credit(unsigned credit);
    unsigned get_credit();
    bool operator==(const CreditInfo & rhs) const { return (rhs.flow_id == flow_id && rhs.credit == credit); }
    friend std::ostream & operator<<(std::ostream & os, const CreditInfo & t)
    {
        return os << t.flow_id << "," << t.credit;
    }

private:
    unsigned flow_id;
    unsigned src_tm_id;
    unsigned dest_tm_id;
    unsigned credit;
};

extern void sc_trace(sc_trace_file * tf, const CreditInfo & v, const std::string & name);

#endif
