/*
 * @Description:
 * @Author: f21538
 * @Date: 2020-11-26 14:12:04
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-01 14:33:15
 */
#include "cell.h"
/*
bool operator== (const cell& c1, const cell& c2)
{
        return std::equal(c1.raw_data, c1.raw_data+CELL_SIZE, c2.raw_data);
}
bool operator< (const cell& c1, const cell& c2)
{
    return c1.packet_id == c2.packet_id ? (c1.cell_id > c2.cell_id):(c1.packet_id > c2.packet_id);
}*/

void sc_trace(sc_trace_file *tf, const cell &v, const sc_string &name)
{
    sc_trace(tf, v.packet_id(), name + ".pid");
    sc_trace(tf, v.cell_id(), name + ".cid");
    for (int i = 0; i < CELL_SIZE - 2; i++)
        sc_trace(tf, v.data[i], name + ".dat");
}