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

#ifndef _SWITCH_TXMAC_H_
#define _SWITCH_TXMAC_H_

#include "switch_cell.h"

struct PACKET
{
    unsigned char link;
    unsigned char type;
    unsigned long bitmap;
    CELL          cell;

    PACKET(){}
    inline bool operator == (const PACKET & rhs) const
    { return (this->cell == rhs.cell && this->link == rhs.link && this->type == rhs.type && 
              this->bitmap == rhs.bitmap);}
};
inline ostream& operator << ( ostream& os, const PACKET & a )
{
    os << "streaming of struct pkt not implemented";
    return os;
}



SC_MODULE(TxMac)
{
    sc_in<bool> IN_Valid;
    sc_in<CELL> IN_Packet;
    sc_in<sc_uint<4> > IN_Type;
    sc_in<USHORT> IN_Link;
    sc_in<sc_uint<36> > IN_Bitmap;

    /* 控制信元 in port */
    sc_in<USHORT> IN_Ctl_Link;
    sc_in<sc_uint<4> > IN_Ctl_Type;
    sc_in<CELL> IN_Ctl_Packet;
    sc_in<bool> IN_Ctl_Valid;

    sc_out<ULONG> OUT_Count;
    sc_port<sc_fifo_out_if<PACKET> > OUT_Packet;
    
    sc_in_clk CLK;
    sc_mutex mutex;

    ULONG ulCount;


    SC_CTOR(TxMac)
    {
        SC_THREAD(TxMac_ControlProcFunc);
        sensitive << CLK;

        SC_THREAD(TxMac_DataProcFunc);
        sensitive << CLK;

        ulCount = 0;

        dont_initialize();
    }
    VOID TxMac_ControlProcFunc();
    VOID TxMac_DataProcFunc();
};


#endif

