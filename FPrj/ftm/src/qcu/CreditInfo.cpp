/*
 * @Author: Zhao Yunpeng
 * @Date: 2020-11-30 09:20:25
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2020-11-30 16:15:17
 * @Description: file content
 */
#include "CreditInfo.h"

void CreditInfo::set_flow_id(unsigned flow_id)
{
    if (flow_id >= VOQ_NUM)
    {
        throw Exception("error : flow_id is out of range.");
    }
    this->flow_id = flow_id;
}

unsigned CreditInfo::get_flow_id() { return this->flow_id; }

void CreditInfo::set_src_tm_id(unsigned src_tm_id)
{
    if (src_tm_id >= MAX_FAP)
    {
        throw Exception("error : src tm id is out of range.");
    }
    this->src_tm_id = src_tm_id;
}

unsigned CreditInfo::get_src_tm_id() { return this->src_tm_id; }

void CreditInfo::set_dest_tm_id(unsigned dest_tm_id)
{
    if (dest_tm_id >= MAX_FAP)
    {
        throw Exception("error : dest tm id is out of range.");
    }
    this->dest_tm_id = dest_tm_id;
}

unsigned CreditInfo::get_dest_tm_id() { return this->dest_tm_id; }

void CreditInfo::set_credit(unsigned credit) { this->credit = credit; }

unsigned CreditInfo::get_credit() { return this->credit; }

void sc_trace(sc_trace_file * tf, const CreditInfo & v, const std::string & name) {}
