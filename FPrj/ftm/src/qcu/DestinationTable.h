/*
 * @Author: your name
 * @Date: 2020-12-26 14:50:00
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2020-12-26 15:04:58
 * @Description: file content
 */
#ifndef _DESTINATION_TABLE_H
#define _DESTINATION_TABLE_H

#include "Exception.h"
#include "config.h"

class DestinationTable
{
public:
    unsigned get_dest_tm_id(unsigned voq_num);

    static DestinationTable & get_instance()
    {
        static DestinationTable instance;
        return instance;
    }

private:
    DestinationTable();
    unsigned destination_table[VOQ_NUM];
};

#endif
