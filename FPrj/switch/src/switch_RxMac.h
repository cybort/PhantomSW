/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              switch_RxMac.h
   Project Code: F-Switch
   Module Name : ROUTE
   Date Created: 2020-11-12
   Author      : pengying21074
   Description : RX MAC模块定义头文件

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#ifndef _SWITCH_RXMAC_H_
#define _SWITCH_RXMAC_H_

SC_MODULE(RxMac)
{
    sc_port<sc_fifo_in_if<CELL> > IN_ProcPlane0;
    sc_port<sc_fifo_in_if<CELL> > IN_ProcPlane1;
    sc_port<sc_fifo_in_if<CELL> > IN_ProcPlane2;
    sc_port<sc_fifo_in_if<CELL> > IN_ProcPlane3;
    sc_port< sc_fifo_in_if<USHORT> > IN_Link0;
    sc_port< sc_fifo_in_if<USHORT> > IN_Link1;
    sc_port< sc_fifo_in_if<USHORT> > IN_Link2;
    sc_port< sc_fifo_in_if<USHORT> > IN_Link3;

    /*数据信元处理*/
    sc_out<bool> OUT_Valid0;
    sc_out<sc_uint<4> > OUT_Type0;
    sc_out<CELL> OUT_Packet0;

    sc_out<bool> OUT_Valid1;
    sc_out<sc_uint<4> > OUT_Type1;
    sc_out<CELL> OUT_Packet1;

    sc_out<bool> OUT_Valid2;
    sc_out<sc_uint<4> > OUT_Type2;
    sc_out<CELL> OUT_Packet2;

    sc_out<bool> OUT_Valid3;
    sc_out<sc_uint<4> > OUT_Type3;
    sc_out<CELL> OUT_Packet3;

//    sc_out<bool> OUT_Eoc;
//    sc_out<bool> OUT_Soc;

    /*控制信元*/
    sc_out<bool> OUT_Ctl_Valid0;
    sc_out<sc_uint<4> > OUT_Ctl_Type0;
    sc_out<CELL> OUT_Ctl_Packet0;

    sc_out<bool> OUT_Ctl_Valid1;
    sc_out<sc_uint<4> > OUT_Ctl_Type1;
    sc_out<CELL> OUT_Ctl_Packet1;

    sc_out<bool> OUT_Ctl_Valid2;
    sc_out<sc_uint<4> > OUT_Ctl_Type2;
    sc_out<CELL> OUT_Ctl_Packet2;

    sc_out<bool> OUT_Ctl_Valid3;
    sc_out<sc_uint<4> > OUT_Ctl_Type3;
    sc_out<CELL> OUT_Ctl_Packet3;

    sc_in_clk CLK;
    sc_mutex mutex;

    unsigned int uiCount;
    
    void RxMac_ProcPlane0Func();
    void RxMac_ProcPlane1Func();
    void RxMac_ProcPlane2Func();
    void RxMac_ProcPlane3Func();
    void RxMac_Update_LinkStatus();

    SC_CTOR(RxMac)
    {
        SC_THREAD(RxMac_ProcPlane0Func);
        sensitive << CLK.pos();

        SC_THREAD(RxMac_ProcPlane1Func);
        sensitive << CLK.pos();

        SC_THREAD(RxMac_ProcPlane2Func);
        sensitive << CLK.pos();

        SC_THREAD(RxMac_ProcPlane3Func);
        sensitive << CLK.pos();

        SC_THREAD(RxMac_Update_LinkStatus);
        sensitive << CLK.pos();

        uiCount = 0;
        dont_initialize(); /* 初始化阶段不执行process定义的method */
    }
};

#endif

