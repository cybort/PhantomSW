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
    sc_port<sc_fifo_in_if<CELL> > IN_ProcPlane;

    /*数据信元处理*/
    sc_out<bool> OUT_Valid;
    sc_out<sc_uint<4> > OUT_Type;
    sc_out<CELL> OUT_Packet;

    sc_out<ULONG> OUT_Rx_Block;
    sc_out<ULONG> OUT_Rx_Data;
    sc_out<ULONG> OUT_Rx_Ctr;

//    sc_out<bool> OUT_Eoc;
//    sc_out<bool> OUT_Soc;

    /*控制信元*/
    sc_out<bool> OUT_Ctl_Valid;
    sc_out<sc_uint<4> > OUT_Ctl_Type;
    sc_out<CELL> OUT_Ctl_Packet;

    sc_in_clk CLK;
    sc_mutex mutex;

    ULONG ulBlockCount;
    ULONG Rx_DataCount;
    ULONG Rx_CtrCount;
    UINT uiCount;
    
    void RxMac_ProcFunc();
    SC_CTOR(RxMac)
    {
        SC_THREAD(RxMac_ProcFunc);
        sensitive << CLK.pos();

        ulBlockCount = 0;
        Rx_DataCount = 0;
        Rx_CtrCount = 0;
        uiCount = 0;
        
        dont_initialize(); /* 初始化阶段不执行process定义的method */
    }
};

#endif

