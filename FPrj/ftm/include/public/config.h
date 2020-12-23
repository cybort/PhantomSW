#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "ConfigResolver.h"
#include "systemc.h"

#define _TM_ID_ (ConfigResolver::GetInstance().get_int("port", "SRC_TM_ID", 0))
#define _VERSION_ 0
#define PACKET_NUM_MAX (1024 * 1024)
// #define ADDRESS_BUS_BANDWIDTH ((int)floor(log2(PACKET_NUM_MAX))+1)
#define DATA_BUS_BANDWIDTH 160
#define VOQ_NUM (96 * 1024)
#define MAX_FAP (32)

struct data_bus
{
    char bytes[DATA_BUS_BANDWIDTH];

    bool operator==(const data_bus & d) const
    {
        return std::equal(this->bytes, this->bytes + sizeof(this->bytes), d.bytes);
    }
    friend std::ostream & operator<<(std::ostream & os, const data_bus & t) { return os << ""; }
};
void sc_trace(sc_trace_file * tf, const data_bus & d, const sc_string & name);
// void sc_trace(sc_core::sc_trace_file*, data_bus const&, std::basic_string<char, std::char_traits<char>,
// std::allocator<char> > const&);

#endif