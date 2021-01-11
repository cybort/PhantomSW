#ifndef _SWITCH_COUNTER_H
#define _SWITCH_COUNTER_H

#include "systemc.h"

SC_MODULE(Counter)
{
    sc_in<ULONG> IN_Recv;
    sc_in<ULONG> IN_Rx_Block0;
    sc_in<ULONG> IN_Rx_Block1;
    sc_in<ULONG> IN_Rx_Block2;
    sc_in<ULONG> IN_Rx_Block3;
    sc_in<ULONG> IN_Rx_0_Data;
    sc_in<ULONG> IN_Rx_1_Data;
    sc_in<ULONG> IN_Rx_2_Data;
    sc_in<ULONG> IN_Rx_3_Data;
    sc_in<ULONG> IN_Rx_0_Ctr;
    sc_in<ULONG> IN_Rx_1_Ctr;
    sc_in<ULONG> IN_Rx_2_Ctr;
    sc_in<ULONG> IN_Rx_3_Ctr;

    sc_in<ULONG> IN_Route_Block0;
    sc_in<ULONG> IN_Route_Block1;
    sc_in<ULONG> IN_Route_Block2;
    sc_in<ULONG> IN_Route_Block3;

    sc_in<ULONG> IN_Tx_Block0;
    sc_in<ULONG> IN_Tx_Block1;
    sc_in<ULONG> IN_Tx_Block2;
    sc_in<ULONG> IN_Tx_Block3;

    
    sc_in<ULONG> IN_Send;

    sc_in<ULONG> IN_CFU_Block0;
    sc_in<ULONG> IN_CFU_Block1;
    sc_in<ULONG> IN_CFU_Block2;
    sc_in<ULONG> IN_CFU_Block3;
    sc_in<ULONG> IN_CFU_BlockData0;
    sc_in<ULONG> IN_CFU_BlockData1;
    sc_in<ULONG> IN_CFU_BlockData2;
    sc_in<ULONG> IN_CFU_BlockData3;

    sc_in_clk CLK;

    ULONG ulClkCount;
    ULONG RecvCount;
    ULONG SendCount;
    
    ULONG RxBlock0Count;
    ULONG RxBlock1Count;
    ULONG RxBlock2Count;
    ULONG RxBlock3Count;
    ULONG Rx_0_DataCount;
    ULONG Rx_1_DataCount;
    ULONG Rx_2_DataCount;
    ULONG Rx_3_DataCount;
    ULONG Rx_0_CtrCount;
    ULONG Rx_1_CtrCount;
    ULONG Rx_2_CtrCount;
    ULONG Rx_3_CtrCount;
    
    ULONG RouteBlock0Count ;
    ULONG RouteBlock1Count ;
    ULONG RouteBlock2Count;
    ULONG RouteBlock3Count;
    
    ULONG TxBlock0Count ;
    ULONG TxBlock1Count ;
    ULONG TxBlock2Count ;
    ULONG TxBlock3Count ;
    
    ULONG CfuBlock0Count;
    ULONG CfuBlock1Count;
    ULONG CfuBlock2Count;
    ULONG CfuBlock3Count;
    ULONG CfuBlock0DataCount;
    ULONG CfuBlock1DataCount;
    ULONG CfuBlock2DataCount;
    ULONG CfuBlock3DataCount;

    SC_CTOR(Counter)
    {
        SC_THREAD(CountProc);
        sensitive << CLK.pos();

        ulClkCount = 0;
        RecvCount = 0;
        SendCount = 0;
        
        RxBlock0Count = 0;
        RxBlock1Count = 0;
        RxBlock2Count = 0;
        RxBlock3Count = 0;
        Rx_0_DataCount = 0;
        Rx_1_DataCount = 0;
        Rx_2_DataCount = 0;
        Rx_3_DataCount = 0;
        Rx_0_CtrCount = 0;
        Rx_1_CtrCount = 0;
        Rx_2_CtrCount = 0;
        Rx_3_CtrCount = 0;
        
        RouteBlock0Count = 0;
        RouteBlock1Count = 0;
        RouteBlock2Count = 0;
        RouteBlock3Count = 0;
        TxBlock0Count = 0;
        TxBlock1Count = 0;
        TxBlock2Count = 0;
        TxBlock3Count = 0;
        CfuBlock0Count = 0;
        CfuBlock1Count = 0;
        CfuBlock2Count = 0;
        CfuBlock3Count = 0;
        CfuBlock0DataCount = 0;
        CfuBlock1DataCount = 0;
        CfuBlock2DataCount = 0;
        CfuBlock3DataCount = 0;

        dont_initialize();
    }
    VOID CountProc();
};

#endif

