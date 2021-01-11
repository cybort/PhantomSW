/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              switch_cfu.h
   Project Code: F-Switch
   Module Name : CFU
   Date Created: 2020-12-15
   Author      : 
   Description : 控制信元分发模块定义头文件

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/
#ifndef _SWITCH_CFU_H_
#define _SWITCH_CFU_H_

SC_MODULE(Cfu)
{
    /* declare in port */
    /*控制信元*/
    sc_in<bool> IN_Ctl_Valid;
    sc_in<sc_uint<4> > IN_Ctl_Type;
    sc_in<CELL> IN_Ctl_Packet;

    sc_in_clk CLK;

    /* 控制信元 out port */
    sc_out<USHORT> OUT_Ctl_Link;
    sc_out<sc_uint<4> > OUT_Ctl_Type;
    sc_out<CELL> OUT_Ctl_Packet;
    sc_out<bool> OUT_Ctl_Valid;

    sc_out<USHORT>OUT_Dest;
    sc_out<USHORT>OUT_Link;
    sc_out<bool>OUT_RC;
    sc_out<bool>OUT_Valid;

    sc_out<ULONG> OUT_DATA;
    sc_out<ULONG> OUT_CRDT;

    ULONG ulBlockCount;
    ULONG ulBlockDataCount;


    SC_CTOR(Cfu)
    {
        SC_THREAD(Cfu_Ctl_Thread0);
        sensitive << CLK.pos();
        
        ulBlockCount = 0;
        ulBlockDataCount = 0;

        dont_initialize();
    }
    
    VOID Cfu_Ctl_Thread0();
};


#endif
