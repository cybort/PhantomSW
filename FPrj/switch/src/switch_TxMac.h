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
    sc_in<bool> IN_Valid0;
    sc_in<bool> IN_Valid1;
    sc_in<bool> IN_Valid2;
    sc_in<bool> IN_Valid3;
    
    sc_in<CELL> IN_Packet0;
    sc_in<CELL> IN_Packet1;
    sc_in<CELL> IN_Packet2;
    sc_in<CELL> IN_Packet3;
    
    sc_in<sc_uint<4> > IN_Type0;
    sc_in<sc_uint<4> > IN_Type1;
    sc_in<sc_uint<4> > IN_Type2;
    sc_in<sc_uint<4> > IN_Type3;
    
    sc_in<USHORT> IN_Link0;
    sc_in<USHORT> IN_Link1;
    sc_in<USHORT> IN_Link2;
    sc_in<USHORT> IN_Link3;
    
    sc_in<sc_uint<36> > IN_Bitmap0;
    sc_in<sc_uint<36> > IN_Bitmap1;
    sc_in<sc_uint<36> > IN_Bitmap2;
    sc_in<sc_uint<36> > IN_Bitmap3;

    /* 控制信元 in port */
    sc_in<USHORT> IN_Ctl_Link0;
    sc_in<sc_uint<4> > IN_Ctl_Type0;
    sc_in<CELL> IN_Ctl_Packet0;
    sc_in<bool> IN_Ctl_Valid0;

    sc_in<USHORT> IN_Ctl_Link1;
    sc_in<sc_uint<4> > IN_Ctl_Type1;
    sc_in<CELL> IN_Ctl_Packet1;
    sc_in<bool> IN_Ctl_Valid1;

    sc_in<USHORT> IN_Ctl_Link2;
    sc_in<sc_uint<4> > IN_Ctl_Type2;
    sc_in<CELL> IN_Ctl_Packet2;
    sc_in<bool> IN_Ctl_Valid2;

    sc_in<USHORT> IN_Ctl_Link3;
    sc_in<sc_uint<4> > IN_Ctl_Type3;
    sc_in<CELL> IN_Ctl_Packet3;
    sc_in<bool> IN_Ctl_Valid3;

    sc_port<sc_fifo_out_if<PACKET> > OUT_Packet0;
//    sc_port<sc_fifo_out_if<PACKET> > OUT_Packet1;
//    sc_port<sc_fifo_out_if<PACKET> > OUT_Packet2;
//    sc_port<sc_fifo_out_if<PACKET> > OUT_Packet3;
    
    sc_in_clk CLK;

    sc_mutex mutex;

    unsigned int uiCount;

    SC_CTOR(TxMac)
    {
        SC_THREAD(TxMac_Ctl_Thread0);
        sensitive << CLK;

        SC_THREAD(TxMac_Ctl_Thread1);
        sensitive << CLK;

        SC_THREAD(TxMac_Ctl_Thread2);
        sensitive << CLK;

        SC_THREAD(TxMac_Ctl_Thread3);
        sensitive << CLK;

        SC_THREAD(TxMac_Thread0);
        sensitive << CLK;

        SC_THREAD(TxMac_Thread1);
        sensitive << CLK;

        SC_THREAD(TxMac_Thread2);
        sensitive << CLK;

        SC_THREAD(TxMac_Thread3);
        sensitive << CLK;
        uiCount = 0;
        dont_initialize();
    }
    VOID TxMac_Ctl_Thread0();
    VOID TxMac_Ctl_Thread1();
    VOID TxMac_Ctl_Thread2();
    VOID TxMac_Ctl_Thread3();

    VOID TxMac_Thread0();
    VOID TxMac_Thread1();
    VOID TxMac_Thread2();
    VOID TxMac_Thread3();
};


#endif

