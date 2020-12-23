/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              switch_TxMac.h
   Project Code: F-Switch
   Module Name : ROUTE
   Date Created: 2020-11-12
   Author      : pengying21074
   Description : TX MAC模块定义头文件

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#ifndef _SWITCH_SENDER_H_
#define _SWITCH_SENDER_H_

#include "switch_TxMac.h"

SC_MODULE(Transmit)
{
    sc_port<sc_fifo_in_if<PACKET> >IN_Packet0;
//    sc_port<sc_fifo_in_if<PACKET> >IN_Packet1;
//    sc_port<sc_fifo_in_if<PACKET> >IN_Packet2;
//    sc_port<sc_fifo_in_if<PACKET> >IN_Packet3;
    sc_in_clk CLK;

    unsigned int uiCount;

    SC_CTOR(Transmit)
    {
        SC_THREAD(Transmit_FuncEntry);
        sensitive << CLK;
        uiCount = 0;
    }
    VOID Transmit_FuncEntry();
};


#endif

