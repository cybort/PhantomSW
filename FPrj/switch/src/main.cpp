#include <iostream>
#include <unistd.h>
#include "systemc.h"
#include "tlm_utils/tlm_quantumkeeper.h"
#include "prv_deftype.h"
#include "switch_recv.h"
#include "switch_cell.h"
#include "switch_RxMac.h"
#include "switch_route.h"
#include "switch_cfu.h"
#include "switch_TxMac.h"
//#include "switch_proc1.h"
#include "common.h"
#include "switch_send.h"

/* TIME module make the clock of simulator keep track of real time,
   other module can use the same clock as TIME module, also different.
   Because of TIME module, all modules use real time clock during simulation.
*/
SC_MODULE(TIME)
{
    /* declare port */
    sc_in_clk clk;

    /* user-defined variables */
    tlm_utils::tlm_quantumkeeper keeper;

    SC_CTOR(TIME)
    {
        SC_THREAD(SetRealTimeSync);
        sensitive << clk.pos();

        tlm_utils::tlm_quantumkeeper::set_global_quantum(sc_time(10, SC_MS));
        keeper.reset();
        dont_initialize();
    }
    void SetRealTimeSync();
};
void TIME::SetRealTimeSync()
{
    sc_time IncPeriod(1, SC_MS);
    UINT uiTimeout;

    while(1)
    {
        uiTimeout = 10;

        while(uiTimeout--)
        {
            usleep(1000);   /* real time of delay, not systemC time */
            keeper.inc(IncPeriod);
            if (keeper.need_sync())
            {
                keeper.sync();
            }
        }
        wait();
    }
}



int sc_main(int argc, char **argv)
{
    //sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);

    PrasePortConfigFile("./portmap.txt");
    
    sc_fifo<CELL> RX_FIFO0(MAX_FIFO_SIZE);
    sc_fifo<CELL> RX_FIFO1(MAX_FIFO_SIZE);
    sc_fifo<CELL> RX_FIFO2(MAX_FIFO_SIZE);
    sc_fifo<CELL> RX_FIFO3(MAX_FIFO_SIZE);
    sc_signal<USHORT> REC2RX_LINK0;
    sc_signal<USHORT> REC2RX_LINK1;
    sc_signal<USHORT> REC2RX_LINK2;
    sc_signal<USHORT> REC2RX_LINK3;

    sc_fifo<PACKET> TX_FIFO(MAX_FIFO_SIZE);

    sc_signal<bool> RX2ROUTE_VALID0;
    sc_signal<bool> RX2ROUTE_VALID1;
    sc_signal<bool> RX2ROUTE_VALID2;
    sc_signal<bool> RX2ROUTE_VALID3;

    sc_signal<sc_uint<4> > RX2ROUTE_TYPE0;
    sc_signal<sc_uint<4> > RX2ROUTE_TYPE1;
    sc_signal<sc_uint<4> > RX2ROUTE_TYPE2;
    sc_signal<sc_uint<4> > RX2ROUTE_TYPE3;

    sc_signal<CELL> RX2ROUTE_VALUE0;
    sc_signal<CELL> RX2ROUTE_VALUE1;
    sc_signal<CELL> RX2ROUTE_VALUE2;
    sc_signal<CELL> RX2ROUTE_VALUE3;

//    sc_signal<bool> RX2ROUTE_EOC;
//    sc_signal<bool> RX2ROUTE_SOC;
    sc_signal<bool> RX2CFU_VALID0;
    sc_signal<sc_uint<4> > RX2CFU_TYPE0;
    sc_signal<CELL> RX2CFU_DATA0;
    sc_signal<USHORT> RX2CFU_LINK0;

    sc_signal<bool> RX2CFU_VALID1;
    sc_signal<sc_uint<4> > RX2CFU_TYPE1;
    sc_signal<CELL> RX2CFU_DATA1;
    sc_signal<USHORT> RX2CFU_LINK1;

    sc_signal<bool> RX2CFU_VALID2;
    sc_signal<sc_uint<4> > RX2CFU_TYPE2;
    sc_signal<CELL> RX2CFU_DATA2;
    sc_signal<USHORT> RX2CFU_LINK2;

    sc_signal<bool> RX2CFU_VALID3;
    sc_signal<sc_uint<4> > RX2CFU_TYPE3;
    sc_signal<CELL> RX2CFU_DATA3;
    sc_signal<USHORT> RX2CFU_LINK3;

    sc_signal<bool> ROUTE2TX_VALID0;
    sc_signal<bool> ROUTE2TX_VALID1;
    sc_signal<bool> ROUTE2TX_VALID2;
    sc_signal<bool> ROUTE2TX_VALID3;

    sc_signal<USHORT> ROUTE2TX_LINK0;
    sc_signal<USHORT> ROUTE2TX_LINK1;
    sc_signal<USHORT> ROUTE2TX_LINK2;
    sc_signal<USHORT> ROUTE2TX_LINK3;

    sc_signal<CELL> ROUTE2TX_VALUE0;
    sc_signal<CELL> ROUTE2TX_VALUE1;
    sc_signal<CELL> ROUTE2TX_VALUE2;
    sc_signal<CELL> ROUTE2TX_VALUE3;

    sc_signal<sc_uint<4> > ROUTE2TX_TYPE0;
    sc_signal<sc_uint<4> > ROUTE2TX_TYPE1;
    sc_signal<sc_uint<4> > ROUTE2TX_TYPE2;
    sc_signal<sc_uint<4> > ROUTE2TX_TYPE3;

    sc_signal<sc_uint<36> > ROUTE2TX_BITMAP0;
    sc_signal<sc_uint<36> > ROUTE2TX_BITMAP1;
    sc_signal<sc_uint<36> > ROUTE2TX_BITMAP2;
    sc_signal<sc_uint<36> > ROUTE2TX_BITMAP3;

    sc_signal<bool> CFU2TX_VALID0;
    sc_signal<USHORT> CFU2TX_LINK0;
    sc_signal<CELL> CFU2TX_DATA0;
    sc_signal<sc_uint<4> > CFU2TX_TYPE0;

    sc_signal<bool> CFU2TX_VALID1;
    sc_signal<USHORT> CFU2TX_LINK1;
    sc_signal<CELL> CFU2TX_DATA1;
    sc_signal<sc_uint<4> > CFU2TX_TYPE1;

    sc_signal<bool> CFU2TX_VALID2;
    sc_signal<USHORT> CFU2TX_LINK2;
    sc_signal<CELL> CFU2TX_DATA2;
    sc_signal<sc_uint<4> > CFU2TX_TYPE2;

    sc_signal<bool> CFU2TX_VALID3;
    sc_signal<USHORT> CFU2TX_LINK3;
    sc_signal<CELL> CFU2TX_DATA3;
    sc_signal<sc_uint<4> > CFU2TX_TYPE3;

    sc_signal<USHORT>CFU2RFU_DEST0;
    sc_signal<USHORT>CFU2RFU_LINK0;
    sc_signal<bool>CFU2RFU_RC0;
    sc_signal<bool>CFU2RFU_VALID0;

    sc_signal<USHORT>CFU2RFU_DEST1;
    sc_signal<USHORT>CFU2RFU_LINK1;
    sc_signal<bool>CFU2RFU_RC1;
    sc_signal<bool>CFU2RFU_VALID1;

    sc_signal<USHORT>CFU2RFU_DEST2;
    sc_signal<USHORT>CFU2RFU_LINK2;
    sc_signal<bool>CFU2RFU_RC2;
    sc_signal<bool>CFU2RFU_VALID2;

    sc_signal<USHORT>CFU2RFU_DEST3;
    sc_signal<USHORT>CFU2RFU_LINK3;
    sc_signal<bool>CFU2RFU_RC3;
    sc_signal<bool>CFU2RFU_VALID3;

    sc_set_time_resolution(1, SC_MS);
    sc_clock clock1("SYNC", sc_time(10, SC_MS), 0.5, sc_time(0.0, SC_MS), true);
    sc_clock clock2("RECV", sc_time(2000, SC_MS), 0.5, sc_time(0.0, SC_MS), true);
    sc_clock clock3("PROC", sc_time(2000, SC_MS), 0.5, sc_time(0.0, SC_MS), true);
    sc_clock clock4("TRANSMIT", sc_time(2000, SC_MS), 0.5, sc_time(0.0, SC_MS), true);

    TIME SYNC("sync");
    SYNC.clk(clock1);
    
    /* 模拟serdes接口 */
    Receiver Input("receive");
    Input.OUT_ProcPlane0(RX_FIFO0);
    Input.OUT_ProcPlane1(RX_FIFO1);
    Input.OUT_ProcPlane2(RX_FIFO2);
    Input.OUT_ProcPlane3(RX_FIFO3);

    Input.OUT_Link0(REC2RX_LINK0);
    Input.OUT_Link1(REC2RX_LINK1);
    Input.OUT_Link2(REC2RX_LINK2);
    Input.OUT_Link3(REC2RX_LINK3);
    
    Input.CLK(clock2);

    /* RX */
    RxMac RX("rx");
    RX.IN_ProcPlane0(RX_FIFO0);
    RX.IN_ProcPlane1(RX_FIFO1);
    RX.IN_ProcPlane2(RX_FIFO2);
    RX.IN_ProcPlane3(RX_FIFO3);

    RX.IN_Link0(REC2RX_LINK0);
    RX.IN_Link1(REC2RX_LINK1);
    RX.IN_Link2(REC2RX_LINK2);
    RX.IN_Link3(REC2RX_LINK3);
    
    RX.OUT_Valid0(RX2ROUTE_VALID0);
    RX.OUT_Valid1(RX2ROUTE_VALID1);
    RX.OUT_Valid2(RX2ROUTE_VALID2);
    RX.OUT_Valid3(RX2ROUTE_VALID3);
    
    RX.OUT_Type0(RX2ROUTE_TYPE0);
    RX.OUT_Type1(RX2ROUTE_TYPE1);
    RX.OUT_Type2(RX2ROUTE_TYPE2);
    RX.OUT_Type3(RX2ROUTE_TYPE3);
    
    RX.OUT_Packet0(RX2ROUTE_VALUE0);
    RX.OUT_Packet1(RX2ROUTE_VALUE1);
    RX.OUT_Packet2(RX2ROUTE_VALUE2);
    RX.OUT_Packet3(RX2ROUTE_VALUE3);
    //    RX.OUT_Eoc(EOC);
    //    RX.OUT_Soc(SOC);

    RX.OUT_Ctl_Valid0(RX2CFU_VALID0);
    RX.OUT_Ctl_Type0(RX2CFU_TYPE0);
    RX.OUT_Ctl_Packet0(RX2CFU_DATA0);
    RX.OUT_Ctl_Link0(RX2CFU_LINK0);

    RX.OUT_Ctl_Valid1(RX2CFU_VALID1);
    RX.OUT_Ctl_Type1(RX2CFU_TYPE1);
    RX.OUT_Ctl_Packet1(RX2CFU_DATA1);
    RX.OUT_Ctl_Link1(RX2CFU_LINK1);

    RX.OUT_Ctl_Valid2(RX2CFU_VALID2);
    RX.OUT_Ctl_Type2(RX2CFU_TYPE2);
    RX.OUT_Ctl_Packet2(RX2CFU_DATA2);
    RX.OUT_Ctl_Link2(RX2CFU_LINK2);

    RX.OUT_Ctl_Valid3(RX2CFU_VALID3);
    RX.OUT_Ctl_Type3(RX2CFU_TYPE3);
    RX.OUT_Ctl_Packet3(RX2CFU_DATA3);
    RX.OUT_Ctl_Link3(RX2CFU_LINK3);
    RX.CLK(clock3);

    /* 路由 */
    Route R("route");
    /*数据信元-输入-信号绑定*/
    R.IN_Valid0(RX2ROUTE_VALID0);
    R.IN_Valid1(RX2ROUTE_VALID1);
    R.IN_Valid2(RX2ROUTE_VALID2);
    R.IN_Valid3(RX2ROUTE_VALID3);
    
    R.IN_Packet0(RX2ROUTE_VALUE0);
    R.IN_Packet1(RX2ROUTE_VALUE1);
    R.IN_Packet2(RX2ROUTE_VALUE2);
    R.IN_Packet3(RX2ROUTE_VALUE3);
    
    R.IN_Type0(RX2ROUTE_TYPE0);
    R.IN_Type1(RX2ROUTE_TYPE1);
    R.IN_Type2(RX2ROUTE_TYPE2);
    R.IN_Type3(RX2ROUTE_TYPE3);
    
    /*数据信元-输出-信号绑定*/
    R.OUT_Link0(ROUTE2TX_LINK0);
    R.OUT_Link1(ROUTE2TX_LINK1);
    R.OUT_Link2(ROUTE2TX_LINK2);
    R.OUT_Link3(ROUTE2TX_LINK3);
    
    R.OUT_Packet0(ROUTE2TX_VALUE0);
    R.OUT_Packet1(ROUTE2TX_VALUE1);
    R.OUT_Packet2(ROUTE2TX_VALUE2);
    R.OUT_Packet3(ROUTE2TX_VALUE3);
    
    R.OUT_Valid0(ROUTE2TX_VALID0);
    R.OUT_Valid1(ROUTE2TX_VALID1);
    R.OUT_Valid2(ROUTE2TX_VALID2);
    R.OUT_Valid3(ROUTE2TX_VALID3);
    
    R.OUT_Bitmap0(ROUTE2TX_BITMAP0);
    R.OUT_Bitmap1(ROUTE2TX_BITMAP1);
    R.OUT_Bitmap2(ROUTE2TX_BITMAP2);
    R.OUT_Bitmap3(ROUTE2TX_BITMAP3);
    
    R.OUT_Type0(ROUTE2TX_TYPE0);
    R.OUT_Type1(ROUTE2TX_TYPE1);
    R.OUT_Type2(ROUTE2TX_TYPE2);
    R.OUT_Type3(ROUTE2TX_TYPE3);
    R.CLK(clock3);

    /*控制信元*/
    Cfu CF("cfu");
    /*控制信元-输入-信号绑定*/
    CF.IN_Ctl_Valid0(RX2CFU_VALID0);
    CF.IN_Ctl_Packet0(RX2CFU_DATA0);
    CF.IN_Ctl_Type0(RX2CFU_TYPE0);
    CF.IN_Ctl_Link0(RX2CFU_LINK0);

    CF.IN_Ctl_Valid1(RX2CFU_VALID1);
    CF.IN_Ctl_Packet1(RX2CFU_DATA1);
    CF.IN_Ctl_Type1(RX2CFU_TYPE1);
    CF.IN_Ctl_Link1(RX2CFU_LINK1);

    CF.IN_Ctl_Valid2(RX2CFU_VALID2);
    CF.IN_Ctl_Packet2(RX2CFU_DATA2);
    CF.IN_Ctl_Type2(RX2CFU_TYPE2);
    CF.IN_Ctl_Link2(RX2CFU_LINK2);

    CF.IN_Ctl_Valid3(RX2CFU_VALID3);
    CF.IN_Ctl_Packet3(RX2CFU_DATA3);
    CF.IN_Ctl_Type3(RX2CFU_TYPE3);
    CF.IN_Ctl_Link3(RX2CFU_LINK3);
    CF.CLK(clock3);

    /*控制信元-输出-信号绑定*/
    CF.OUT_Ctl_Link0(CFU2TX_LINK0);
    CF.OUT_Ctl_Packet0(CFU2TX_DATA0);
    CF.OUT_Ctl_Valid0(CFU2TX_VALID0);
    CF.OUT_Ctl_Type0(CFU2TX_TYPE0);

    CF.OUT_Ctl_Link1(CFU2TX_LINK1);
    CF.OUT_Ctl_Packet1(CFU2TX_DATA1);
    CF.OUT_Ctl_Valid1(CFU2TX_VALID1);
    CF.OUT_Ctl_Type1(CFU2TX_TYPE1);

    CF.OUT_Ctl_Link2(CFU2TX_LINK2);
    CF.OUT_Ctl_Packet2(CFU2TX_DATA2);
    CF.OUT_Ctl_Valid2(CFU2TX_VALID2);
    CF.OUT_Ctl_Type2(CFU2TX_TYPE2);

    CF.OUT_Ctl_Link3(CFU2TX_LINK3);
    CF.OUT_Ctl_Packet3(CFU2TX_DATA3);
    CF.OUT_Ctl_Valid3(CFU2TX_VALID3);
    CF.OUT_Ctl_Type3(CFU2TX_TYPE3);

    CF.OUT_Dest0(CFU2RFU_DEST0);
    CF.OUT_Link0(CFU2RFU_LINK0);
    CF.OUT_RC0(CFU2RFU_RC0);
    CF.OUT_Valid0(CFU2RFU_VALID0);

    CF.OUT_Dest1(CFU2RFU_DEST1);
    CF.OUT_Link1(CFU2RFU_LINK1);
    CF.OUT_RC1(CFU2RFU_RC1);
    CF.OUT_Valid1(CFU2RFU_VALID1);

    CF.OUT_Dest2(CFU2RFU_DEST2);
    CF.OUT_Link2(CFU2RFU_LINK2);
    CF.OUT_RC2(CFU2RFU_RC2);
    CF.OUT_Valid2(CFU2RFU_VALID2);

    CF.OUT_Dest3(CFU2RFU_DEST3);
    CF.OUT_Link3(CFU2RFU_LINK3);
    CF.OUT_RC3(CFU2RFU_RC3);
    CF.OUT_Valid3(CFU2RFU_VALID3);

    /*Update Table*/
    Update Up("update");
    Up.IN_Dest0(CFU2RFU_DEST0);
    Up.IN_Link0(CFU2RFU_LINK0);
    Up.IN_RC0(CFU2RFU_RC0);
    Up.IN_Valid0(CFU2RFU_VALID0);

    Up.IN_Dest1(CFU2RFU_DEST1);
    Up.IN_Link1(CFU2RFU_LINK1);
    Up.IN_RC1(CFU2RFU_RC1);
    Up.IN_Valid1(CFU2RFU_VALID1);

    Up.IN_Dest2(CFU2RFU_DEST2);
    Up.IN_Link2(CFU2RFU_LINK2);
    Up.IN_RC2(CFU2RFU_RC2);
    Up.IN_Valid2(CFU2RFU_VALID2);

    Up.IN_Dest3(CFU2RFU_DEST3);
    Up.IN_Link3(CFU2RFU_LINK3);
    Up.IN_RC3(CFU2RFU_RC3);
    Up.IN_Valid3(CFU2RFU_VALID3);

    Up.CLK(clock3);
    
    /* TX */
    TxMac TX("tx");
    /*数据信元-输入-信号绑定*/
    TX.IN_Valid0(ROUTE2TX_VALID0);
    TX.IN_Valid1(ROUTE2TX_VALID1);
    TX.IN_Valid2(ROUTE2TX_VALID2);
    TX.IN_Valid3(ROUTE2TX_VALID3);
    
    TX.IN_Type0(ROUTE2TX_TYPE0);
    TX.IN_Type1(ROUTE2TX_TYPE1);
    TX.IN_Type2(ROUTE2TX_TYPE2);
    TX.IN_Type3(ROUTE2TX_TYPE3);
    
    TX.IN_Packet0(ROUTE2TX_VALUE0);
    TX.IN_Packet1(ROUTE2TX_VALUE1);
    TX.IN_Packet2(ROUTE2TX_VALUE2);
    TX.IN_Packet3(ROUTE2TX_VALUE3);
    
    TX.IN_Link0(ROUTE2TX_LINK0);
    TX.IN_Link1(ROUTE2TX_LINK1);
    TX.IN_Link2(ROUTE2TX_LINK2);
    TX.IN_Link3(ROUTE2TX_LINK3);
    
    TX.IN_Bitmap0(ROUTE2TX_BITMAP0);
    TX.IN_Bitmap1(ROUTE2TX_BITMAP1);
    TX.IN_Bitmap2(ROUTE2TX_BITMAP2);
    TX.IN_Bitmap3(ROUTE2TX_BITMAP3);

    /*控制信元-输入-信号绑定*/
    TX.IN_Ctl_Link0(CFU2TX_LINK0);
    TX.IN_Ctl_Packet0(CFU2TX_DATA0);
    TX.IN_Ctl_Valid0(CFU2TX_VALID0);
    TX.IN_Ctl_Type0(CFU2TX_TYPE0);

    TX.IN_Ctl_Link1(CFU2TX_LINK1);
    TX.IN_Ctl_Packet1(CFU2TX_DATA1);
    TX.IN_Ctl_Valid1(CFU2TX_VALID1);
    TX.IN_Ctl_Type1(CFU2TX_TYPE1);

    TX.IN_Ctl_Link2(CFU2TX_LINK2);
    TX.IN_Ctl_Packet2(CFU2TX_DATA2);
    TX.IN_Ctl_Valid2(CFU2TX_VALID2);
    TX.IN_Ctl_Type2(CFU2TX_TYPE2);

    TX.IN_Ctl_Link3(CFU2TX_LINK3);
    TX.IN_Ctl_Packet3(CFU2TX_DATA3);
    TX.IN_Ctl_Valid3(CFU2TX_VALID3);
    TX.IN_Ctl_Type3(CFU2TX_TYPE3);

    TX.OUT_Packet0(TX_FIFO);
    TX.CLK(clock3);

    Transmit SEND("sender");
    SEND.IN_Packet0(TX_FIFO);
    SEND.CLK(clock4);

    std::cout << "Simulation start ...\n";
    sc_start();

    return 0;
}
