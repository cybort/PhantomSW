/*
 * @Author: your name
 * @Date: 2021-01-15 09:40:36
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2021-01-15 09:47:40
 * @Description: file content
 */

#include "LogicAddrTable.h"

LogicAddrTable::LogicAddrTable() { memset(this->logic_addr_status, false, sizeof(bool) * PACKET_NUM_MAX); }

void LogicAddrTable::set_addr_status(unsigned addr, bool status)
{
    if (addr >= PACKET_NUM_MAX)
    {
        throw Exception("error: addr invalid");
    }
    this->logic_addr_status[addr] = status;
}

bool LogicAddrTable::get_addr_status(unsigned addr)
{
    if (addr >= PACKET_NUM_MAX)
    {
        throw Exception("error: addr invalid");
    }
    return this->logic_addr_status[addr];
}
