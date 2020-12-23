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
    sc_in<bool> IN_Ctl_Valid0;
    sc_in<sc_uint<4> > IN_Ctl_Type0;
    sc_in<CELL> IN_Ctl_Packet0;
    sc_in<USHORT> IN_Ctl_Link0;

    sc_in<bool> IN_Ctl_Valid1;
    sc_in<sc_uint<4> > IN_Ctl_Type1;
    sc_in<CELL> IN_Ctl_Packet1;
    sc_in<USHORT> IN_Ctl_Link1;

    sc_in<bool> IN_Ctl_Valid2;
    sc_in<sc_uint<4> > IN_Ctl_Type2;
    sc_in<CELL> IN_Ctl_Packet2;
    sc_in<USHORT> IN_Ctl_Link2;

    sc_in<bool> IN_Ctl_Valid3;
    sc_in<sc_uint<4> > IN_Ctl_Type3;
    sc_in<CELL> IN_Ctl_Packet3;
    sc_in<USHORT> IN_Ctl_Link3;
    sc_in_clk CLK;

    /* 控制信元 out port */
    sc_out<USHORT> OUT_Ctl_Link0;
    sc_out<sc_uint<4> > OUT_Ctl_Type0;
    sc_out<CELL> OUT_Ctl_Packet0;
    sc_out<bool> OUT_Ctl_Valid0;

    sc_out<USHORT> OUT_Ctl_Link1;
    sc_out<sc_uint<4> > OUT_Ctl_Type1;
    sc_out<CELL> OUT_Ctl_Packet1;
    sc_out<bool> OUT_Ctl_Valid1;

    sc_out<USHORT> OUT_Ctl_Link2;
    sc_out<sc_uint<4> > OUT_Ctl_Type2;
    sc_out<CELL> OUT_Ctl_Packet2;
    sc_out<bool> OUT_Ctl_Valid2;

    sc_out<USHORT> OUT_Ctl_Link3;
    sc_out<sc_uint<4> > OUT_Ctl_Type3;
    sc_out<CELL> OUT_Ctl_Packet3;
    sc_out<bool> OUT_Ctl_Valid3;

    sc_out<USHORT>OUT_Dest0;
    sc_out<USHORT>OUT_Link0;
    sc_out<bool>OUT_RC0;
    sc_out<bool>OUT_Valid0;

    sc_out<USHORT>OUT_Dest1;
    sc_out<USHORT>OUT_Link1;
    sc_out<bool>OUT_RC1;
    sc_out<bool>OUT_Valid1;

    sc_out<USHORT>OUT_Dest2;
    sc_out<USHORT>OUT_Link2;
    sc_out<bool>OUT_RC2;
    sc_out<bool>OUT_Valid2;

    sc_out<USHORT>OUT_Dest3;
    sc_out<USHORT>OUT_Link3;
    sc_out<bool>OUT_RC3;
    sc_out<bool>OUT_Valid3;

    SC_CTOR(Cfu)
    {
        SC_THREAD(Cfu_Ctl_Thread0);
        sensitive << CLK.pos();

        SC_THREAD(Cfu_Ctl_Thread1);
        sensitive << CLK.pos();

        SC_THREAD(Cfu_Ctl_Thread2);
        sensitive << CLK.pos();

        SC_THREAD(Cfu_Ctl_Thread3);
        sensitive << CLK.pos();

        dont_initialize();
    }
    
    VOID Cfu_Ctl_Thread0();
    VOID Cfu_Ctl_Thread1();
    VOID Cfu_Ctl_Thread2();
    VOID Cfu_Ctl_Thread3();
};


#endif
