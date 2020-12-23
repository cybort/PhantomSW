/*
 * @Author: your name
 * @Date: 2020-11-26 14:00:38
 * @LastEditors: duyang
 * @LastEditTime: 2020-12-01 09:45:22
 * @Description: file content
 */
#ifndef _STREAM_H_
#define _STREAM_H_

#include "Packet.h"

#define _SEC_ 1000000
#define _LOAD_RES_ 1000000

typedef struct
{
    bool streamtype;
    bool mix;
    unsigned burst;
    unsigned loadpersec;
    unsigned TM_ID;

    IPacket pktdata;

    void reset()
    {
        streamtype = 0;
        mix = 0;
        burst = 0;
        loadpersec = 0;
        TM_ID = 0;
    }
} STREAM_S;

#endif