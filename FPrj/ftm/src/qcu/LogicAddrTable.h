/*
 * @Author: your name
 * @Date: 2021-01-15 09:37:10
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2021-01-15 09:52:15
 * @Description: file content
 */

#ifndef _LOGIC_ADDR_TABLE_H_
#define _LOGIC_ADDR_TABLE_H_

#include "Exception.h"
#include "config.h"
class LogicAddrTable
{
public:
    void set_addr_status(unsigned addr, bool status);
    bool get_addr_status(unsigned addr);
    static LogicAddrTable & get_instance()
    {
        static LogicAddrTable instance;
        return instance;
    }

private:
    bool logic_addr_status[PACKET_NUM_MAX];
    LogicAddrTable();
};

#endif
