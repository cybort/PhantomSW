#include <cstring>
#include <string>
#include <fstream>

#include "systemc.h"
#include "prv_deftype.h"
#include "switch_counter.h"

using std::cout;
using std::endl;
using std::string;

VOID Counter::CountProc()
{
    #if 0
    ULONG RecvCountTmp = 0;
    ULONG SendCountTmp = 0;
    ULONG RxBlock0CountTmp = 0;
    ULONG RxBlock1CountTmp = 0;
    ULONG RxBlock2CountTmp = 0;
    ULONG RxBlock3CountTmp = 0;
    ULONG RouteBlock0CountTmp = 0;
    ULONG RouteBlock1CountTmp = 0;
    ULONG RouteBlock2CountTmp = 0;
    ULONG RouteBlock3CountTmp = 0;
    ULONG TxBlock0CountTmp = 0;
    ULONG TxBlock1CountTmp = 0;
    ULONG TxBlock2CountTmp = 0;
    ULONG TxBlock3CountTmp = 0;
    ULONG CfuBlock0CountTmp = 0;
    ULONG CfuBlock1CountTmp = 0;
    ULONG CfuBlock2CountTmp = 0;
    ULONG CfuBlock3CountTmp = 0;
    #endif
    std::ofstream ofs;
    while(1)
    {
        wait();
        ulClkCount++;
        RecvCount = IN_Recv.read();
        SendCount = IN_Send.read();
        
        RxBlock0Count = IN_Rx_Block0.read();
        RxBlock1Count = IN_Rx_Block1.read();
        RxBlock2Count = IN_Rx_Block2.read();
        RxBlock3Count = IN_Rx_Block3.read();
        Rx_0_DataCount = IN_Rx_0_Data.read();
        Rx_1_DataCount = IN_Rx_1_Data.read();
        Rx_2_DataCount = IN_Rx_2_Data.read();
        Rx_3_DataCount = IN_Rx_3_Data.read();
        Rx_0_CtrCount = IN_Rx_0_Ctr.read();
        Rx_1_CtrCount = IN_Rx_1_Ctr.read();
        Rx_2_CtrCount = IN_Rx_2_Ctr.read();
        Rx_3_CtrCount = IN_Rx_3_Ctr.read();
        
        RouteBlock0Count  = IN_Route_Block0.read();
        RouteBlock1Count = IN_Route_Block1.read();
        RouteBlock2Count = IN_Route_Block2.read();
        RouteBlock3Count = IN_Route_Block3.read();
        
        TxBlock0Count = IN_Tx_Block0.read();
        TxBlock1Count = IN_Tx_Block1.read();
        TxBlock2Count = IN_Tx_Block2.read();
        TxBlock3Count = IN_Tx_Block3.read();
        
        CfuBlock0Count = IN_CFU_Block0.read();
        CfuBlock1Count = IN_CFU_Block1.read();
        CfuBlock2Count = IN_CFU_Block2.read();
        CfuBlock3Count = IN_CFU_Block3.read();
        CfuBlock0DataCount = IN_CFU_BlockData0.read();
        CfuBlock1DataCount = IN_CFU_BlockData1.read();
        CfuBlock2DataCount = IN_CFU_BlockData2.read();
        CfuBlock3DataCount = IN_CFU_BlockData3.read();
#if 0
        ofs.open("./log.txt", std::ofstream::out | std::ofstream::app);
        ofs << endl << "===== clock " << ulClkCount << " module statistic =====" << endl;
        ofs << "\tModule Receiver:    " << RecvCount << endl;
        ofs << "\tModule Sender:    " << SendCount << endl;
        ofs << "\tModule Rx_0:    Total : " << RxBlock0Count << "  Data : " << Rx_0_DataCount << "  Ctr : " << Rx_0_CtrCount << endl;
        ofs << "\tModule Rx_1:    Total : " << RxBlock1Count << "  Data : " << Rx_1_DataCount << "  Ctr : " << Rx_1_CtrCount << endl;
        ofs << "\tModule Rx_2:    Total : " << RxBlock2Count << "  Data : " << Rx_2_DataCount << "  Ctr : " << Rx_2_CtrCount << endl;
        ofs << "\tModule Rx_3:    Total : " << RxBlock3Count << "  Data : " << Rx_3_DataCount << "  Ctr : " << Rx_3_CtrCount << endl;
        ofs << "\tModule Route_0:    " << RouteBlock0Count << endl;
        ofs << "\tModule Route_1:    " << RouteBlock1Count << endl;
        ofs << "\tModule Route_2:    " << RouteBlock2Count << endl;
        ofs << "\tModule Route_3:    " << RouteBlock3Count << endl;
        ofs << "\tModule Cfu_0:    DataFlow : " << CfuBlock0DataCount << "  Credit : " << CfuBlock0Count << endl;
        ofs << "\tModule Cfu_1:    DataFlow : " << CfuBlock1DataCount << "  Credit : " << CfuBlock1Count << endl;
        ofs << "\tModule Cfu_2:    DataFlow : " << CfuBlock2DataCount << "  Credit : " << CfuBlock2Count << endl;
        ofs << "\tModule Cfu_3:    DataFlow : " << CfuBlock3DataCount << "  Credit : " << CfuBlock3Count << endl;
        ofs << "\tModule Tx_0:    " << TxBlock0Count << endl;
        ofs << "\tModule Tx_1:    " << TxBlock1Count << endl;
        ofs << "\tModule Tx_2:    " << TxBlock2Count << endl;
        ofs << "\tModule Tx_3:    " << TxBlock3Count << endl;

        ofs.close();
#endif
    }
}

