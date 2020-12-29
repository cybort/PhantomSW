/*
 * @Author: your name
 * @Date: 2020-12-26 14:50:11
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2020-12-26 15:16:30
 * @Description: file content
 */

#include "DestinationTable.h"

DestinationTable::DestinationTable()
{
    for (int voq = 0; voq < VOQ_NUM / 2 - 1; voq++)
    {
        this->destination_table[voq] = 1;
    }
    for (int voq = VOQ_NUM / 2; voq < VOQ_NUM - 1; voq++)
    {
        this->destination_table[voq] = 0;
    }
}
unsigned DestinationTable::get_dest_tm_id(unsigned voq_num) { return this->destination_table[voq_num]; }