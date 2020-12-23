/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              switch_recv.h
   Project Code: F-Switch
   Module Name : CELL
   Date Created: 2020-11-12
   Author      : pengying21074
   Description : 模拟serdes接收模块定义头文件

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#ifndef __SWITCH_RECV_H_
#define __SWITCH_RECV_H_

#include "systemc.h"
#include "switch_cell.h"

#if 0
struct pkt
{
    unsigned int data;

   inline bool operator == (const pkt& rhs) const
   {
     return (rhs.data == data);
   }
};

inline ostream& operator << ( ostream& os, const pkt& a )
{
    os << "streaming of struct pkt not implemented";
    return os;
}

inline void
#if defined(SC_API_VERSION_STRING)
sc_trace( sc_trace_file* tf, const pkt& a, const std::string& name )
#else
sc_trace( sc_trace_file* tf, const pkt& a, const sc_string& name )
#endif
{
  sc_trace( tf, a.data, name + ".data" );
}
#endif

typedef struct tagLINK_MAP_INFO
{
    UINT uiPlane;
    UINT uiLinkNum;
    UINT auiLinkList[36];
}LINK_MAP_INFO_S;

SC_MODULE(Receiver)
{
    sc_port<sc_fifo_out_if<CELL> > OUT_ProcPlane0;
    sc_port<sc_fifo_out_if<CELL> > OUT_ProcPlane1;
    sc_port<sc_fifo_out_if<CELL> > OUT_ProcPlane2;
    sc_port<sc_fifo_out_if<CELL> > OUT_ProcPlane3;
    sc_in_clk CLK;

    sc_out<USHORT> OUT_Link0;
    sc_out<USHORT> OUT_Link1;
    sc_out<USHORT> OUT_Link2;
    sc_out<USHORT> OUT_Link3;

    void Recv_FuncEntry(void);
    SC_CTOR(Receiver)
    {
        SC_THREAD(Recv_FuncEntry);
        sensitive << CLK.pos();
        dont_initialize();
    }
};

#endif

