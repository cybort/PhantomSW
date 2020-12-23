/*
 * @Description: Internal bandwidth
 * @Author: f21538
 * @Date: 2020-11-26 14:12:04
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-01 15:33:01
 */
#ifndef _PACKET_LINE_H_
#define _PACKET_LINE_H_
#include "port.h"
#include "systemc.h"
#include <algorithm>
struct packet_line
{
    char raw_data[PKT_DATA_BANDWIDTH];

    bool operator==(const packet_line &t) const
    {
        return std::equal(raw_data, raw_data + sizeof(packet_line), t.raw_data);
    }
};
void sc_trace(sc_trace_file *tf, const packet_line &v, const std::string &name);

#endif