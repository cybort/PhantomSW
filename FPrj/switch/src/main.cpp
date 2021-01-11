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
#include "common.h"
#include "switch_send.h"
#include "switch_counter.h"

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

    sc_fifo<PACKET> TX_FIFO0(MAX_FIFO_SIZE);
    sc_fifo<PACKET> TX_FIFO1(MAX_FIFO_SIZE);
    sc_fifo<PACKET> TX_FIFO2(MAX_FIFO_SIZE);
    sc_fifo<PACKET> TX_FIFO3(MAX_FIFO_SIZE);

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

    sc_signal<bool> RX2CFU_VALID1;
    sc_signal<sc_uint<4> > RX2CFU_TYPE1;
    sc_signal<CELL> RX2CFU_DATA1;

    sc_signal<bool> RX2CFU_VALID2;
    sc_signal<sc_uint<4> > RX2CFU_TYPE2;
    sc_signal<CELL> RX2CFU_DATA2;

    sc_signal<bool> RX2CFU_VALID3;
    sc_signal<sc_uint<4> > RX2CFU_TYPE3;
    sc_signal<CELL> RX2CFU_DATA3;

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
    /* counter signal */
    sc_signal<ULONG> RECV2COUNTER;
    sc_signal<ULONG> SEND2COUNTER;

    sc_signal<ULONG> RX1TOTAL2COUNTER;
    sc_signal<ULONG> RX2TOTAL2COUNTER;
    sc_signal<ULONG> RX3TOTAL2COUNTER;
    sc_signal<ULONG> RX4TOTAL2COUNTER;
    sc_signal<ULONG> RX1DATA2COUNTER;
    sc_signal<ULONG> RX2DATA2COUNTER;
    sc_signal<ULONG> RX3DATA2COUNTER;
    sc_signal<ULONG> RX4DATA2COUNTER;
    sc_signal<ULONG> RX1CTR2COUNTER;
    sc_signal<ULONG> RX2CTR2COUNTER;
    sc_signal<ULONG> RX3CTR2COUNTER;
    sc_signal<ULONG> RX4CTR2COUNTER;

    sc_signal<ULONG> CFU0DATA2COUNTER;
    sc_signal<ULONG> CFU1DATA2COUNTER;
    sc_signal<ULONG> CFU2DATA2COUNTER;
    sc_signal<ULONG> CFU3DATA2COUNTER;
    sc_signal<ULONG> CFU0CTR2COUNTER;
    sc_signal<ULONG> CFU1CTR2COUNTER;
    sc_signal<ULONG> CFU2CTR2COUNTER;
    sc_signal<ULONG> CFU3CTR2COUNTER;

    sc_signal<ULONG> ROUTER02COUNTER;
    sc_signal<ULONG> ROUTER12COUNTER;
    sc_signal<ULONG> ROUTER22COUNTER;
    sc_signal<ULONG> ROUTER32COUNTER;

    sc_signal<ULONG> TX02COUNTER;
    sc_signal<ULONG> TX12COUNTER;
    sc_signal<ULONG> TX22COUNTER;
    sc_signal<ULONG> TX32COUNTER;
    /* counter signal end */

    sc_set_time_resolution(1, SC_US);
    sc_clock clock1("SYNC", sc_time(2, SC_MS), 0.5, sc_time(0.0, SC_MS), true);
    sc_clock clock2("RECV", sc_time(8, SC_MS), 0.5, sc_time(0.0, SC_MS), true);
    sc_clock clock3("PROC", sc_time(2, SC_MS), 0.5, sc_time(0.0, SC_MS), true);
    sc_clock clock4("TRANSMIT", sc_time(2, SC_MS), 0.5, sc_time(0.0, SC_MS), true);

    TIME SYNC("sync");
    SYNC.clk(clock1);
    
    /* 模拟serdes接口 */
    Receiver Input("receive");
    Input.OUT_ProcPlane0(RX_FIFO0);
    Input.OUT_ProcPlane1(RX_FIFO1);
    Input.OUT_ProcPlane2(RX_FIFO2);
    Input.OUT_ProcPlane3(RX_FIFO3);

    Input.OUT_RecvOK(RECV2COUNTER);
    
    Input.CLK(clock2);

    /* RX Block0 */
    RxMac RX0("rx0");
    RX0.IN_ProcPlane(RX_FIFO0);
    RX0.OUT_Valid(RX2ROUTE_VALID0);
    RX0.OUT_Type(RX2ROUTE_TYPE0);
    RX0.OUT_Packet(RX2ROUTE_VALUE0);
    RX0.OUT_Ctl_Valid(RX2CFU_VALID0);
    RX0.OUT_Ctl_Type(RX2CFU_TYPE0);
    RX0.OUT_Ctl_Packet(RX2CFU_DATA0);
    RX0.OUT_Rx_Block(RX1TOTAL2COUNTER);
    RX0.OUT_Rx_Data(RX1DATA2COUNTER);
    RX0.OUT_Rx_Ctr(RX1CTR2COUNTER);
    RX0.CLK(clock3);

    /* RX Block1 */
    RxMac RX1("rx1");
    RX1.IN_ProcPlane(RX_FIFO1);
    RX1.OUT_Valid(RX2ROUTE_VALID1);
    RX1.OUT_Type(RX2ROUTE_TYPE1);
    RX1.OUT_Packet(RX2ROUTE_VALUE1);
    RX1.OUT_Ctl_Valid(RX2CFU_VALID1);
    RX1.OUT_Ctl_Type(RX2CFU_TYPE1);
    RX1.OUT_Ctl_Packet(RX2CFU_DATA1);
    RX1.OUT_Rx_Block(RX2TOTAL2COUNTER);
    RX1.OUT_Rx_Data(RX2DATA2COUNTER);
    RX1.OUT_Rx_Ctr(RX2CTR2COUNTER);
    RX1.CLK(clock3);

    /* RX Block2 */
    RxMac RX2("rx2");
    RX2.IN_ProcPlane(RX_FIFO2);
    RX2.OUT_Valid(RX2ROUTE_VALID2);
    RX2.OUT_Type(RX2ROUTE_TYPE2);
    RX2.OUT_Packet(RX2ROUTE_VALUE2);
    RX2.OUT_Ctl_Valid(RX2CFU_VALID2);
    RX2.OUT_Ctl_Type(RX2CFU_TYPE2);
    RX2.OUT_Ctl_Packet(RX2CFU_DATA2);
    RX2.OUT_Rx_Block(RX3TOTAL2COUNTER);
    RX2.OUT_Rx_Data(RX3DATA2COUNTER);
    RX2.OUT_Rx_Ctr(RX3CTR2COUNTER);
    RX2.CLK(clock3);

    /* RX Block3 */
    RxMac RX3("rx3");
    RX3.IN_ProcPlane(RX_FIFO3);
    RX3.OUT_Valid(RX2ROUTE_VALID3);
    RX3.OUT_Type(RX2ROUTE_TYPE3);
    RX3.OUT_Packet(RX2ROUTE_VALUE3);
    RX3.OUT_Ctl_Valid(RX2CFU_VALID3);
    RX3.OUT_Ctl_Type(RX2CFU_TYPE3);
    RX3.OUT_Ctl_Packet(RX2CFU_DATA3);
    RX3.OUT_Rx_Block(RX4TOTAL2COUNTER);
    RX3.OUT_Rx_Data(RX4DATA2COUNTER);
    RX3.OUT_Rx_Ctr(RX4CTR2COUNTER);
    RX3.CLK(clock3);

    /* Route Block0 */
    Route R0("route0");
    R0.IN_Valid(RX2ROUTE_VALID0);
    R0.IN_Packet(RX2ROUTE_VALUE0);
    R0.IN_Type(RX2ROUTE_TYPE0);
    R0.OUT_Link(ROUTE2TX_LINK0);
    R0.OUT_Packet(ROUTE2TX_VALUE0);
    R0.OUT_Valid(ROUTE2TX_VALID0);
    R0.OUT_Bitmap(ROUTE2TX_BITMAP0);
    R0.OUT_Type(ROUTE2TX_TYPE0);
    R0.OUT_Count(ROUTER02COUNTER);
    R0.CLK(clock3);
    
    /* Route Block1 */
    Route R1("route1");
    R1.IN_Valid(RX2ROUTE_VALID1);
    R1.IN_Packet(RX2ROUTE_VALUE1);
    R1.IN_Type(RX2ROUTE_TYPE1);
    R1.OUT_Link(ROUTE2TX_LINK1);
    R1.OUT_Packet(ROUTE2TX_VALUE1);
    R1.OUT_Valid(ROUTE2TX_VALID1);
    R1.OUT_Bitmap(ROUTE2TX_BITMAP1);
    R1.OUT_Type(ROUTE2TX_TYPE1);
    R1.OUT_Count(ROUTER12COUNTER);
    R1.CLK(clock3);

    /* Route Block2 */
    Route R2("route2");
    R2.IN_Valid(RX2ROUTE_VALID2);
    R2.IN_Packet(RX2ROUTE_VALUE2);
    R2.IN_Type(RX2ROUTE_TYPE2);
    R2.OUT_Link(ROUTE2TX_LINK2);
    R2.OUT_Packet(ROUTE2TX_VALUE2);
    R2.OUT_Valid(ROUTE2TX_VALID2);
    R2.OUT_Bitmap(ROUTE2TX_BITMAP2);
    R2.OUT_Type(ROUTE2TX_TYPE2);
    R2.OUT_Count(ROUTER22COUNTER);
    R2.CLK(clock3);

    /* Route Block3 */
    Route R3("route3");
    R3.IN_Valid(RX2ROUTE_VALID3);
    R3.IN_Packet(RX2ROUTE_VALUE3);
    R3.IN_Type(RX2ROUTE_TYPE3);
    R3.OUT_Link(ROUTE2TX_LINK3);
    R3.OUT_Packet(ROUTE2TX_VALUE3);
    R3.OUT_Valid(ROUTE2TX_VALID3);
    R3.OUT_Bitmap(ROUTE2TX_BITMAP3);
    R3.OUT_Type(ROUTE2TX_TYPE3);
    R3.OUT_Count(ROUTER32COUNTER);
    R3.CLK(clock3);

    /* CCS Block0 */
    Cfu CF0("cfu0");
    /*控制信元-输入-信号绑定*/
    CF0.IN_Ctl_Valid(RX2CFU_VALID0);
    CF0.IN_Ctl_Packet(RX2CFU_DATA0);
    CF0.IN_Ctl_Type(RX2CFU_TYPE0);
    CF0.OUT_Ctl_Link(CFU2TX_LINK0);
    CF0.OUT_Ctl_Packet(CFU2TX_DATA0);
    CF0.OUT_Ctl_Valid(CFU2TX_VALID0);
    CF0.OUT_Ctl_Type(CFU2TX_TYPE0);
    CF0.OUT_Dest(CFU2RFU_DEST0);
    CF0.OUT_Link(CFU2RFU_LINK0);
    CF0.OUT_RC(CFU2RFU_RC0);
    CF0.OUT_Valid(CFU2RFU_VALID0);
    CF0.OUT_DATA(CFU0DATA2COUNTER);
    CF0.OUT_CRDT(CFU0CTR2COUNTER);
    CF0.CLK(clock3);

    /* CCS Block0 */
    Cfu CF1("cfu1");
    CF1.IN_Ctl_Valid(RX2CFU_VALID1);
    CF1.IN_Ctl_Packet(RX2CFU_DATA1);
    CF1.IN_Ctl_Type(RX2CFU_TYPE1);
    CF1.OUT_Ctl_Link(CFU2TX_LINK1);
    CF1.OUT_Ctl_Packet(CFU2TX_DATA1);
    CF1.OUT_Ctl_Valid(CFU2TX_VALID1);
    CF1.OUT_Ctl_Type(CFU2TX_TYPE1);
    CF1.OUT_Dest(CFU2RFU_DEST1);
    CF1.OUT_Link(CFU2RFU_LINK1);
    CF1.OUT_RC(CFU2RFU_RC1);
    CF1.OUT_Valid(CFU2RFU_VALID1);
    CF1.OUT_DATA(CFU1DATA2COUNTER);
    CF1.OUT_CRDT(CFU1CTR2COUNTER);
    CF1.CLK(clock3);
    
    /* CCS Block0 */
    Cfu CF2("cfu2");
    CF2.IN_Ctl_Valid(RX2CFU_VALID2);
    CF2.IN_Ctl_Packet(RX2CFU_DATA2);
    CF2.IN_Ctl_Type(RX2CFU_TYPE2);
    CF2.OUT_Ctl_Link(CFU2TX_LINK2);
    CF2.OUT_Ctl_Packet(CFU2TX_DATA2);
    CF2.OUT_Ctl_Valid(CFU2TX_VALID2);
    CF2.OUT_Ctl_Type(CFU2TX_TYPE2);
    CF2.OUT_Dest(CFU2RFU_DEST2);
    CF2.OUT_Link(CFU2RFU_LINK2);
    CF2.OUT_RC(CFU2RFU_RC2);
    CF2.OUT_Valid(CFU2RFU_VALID2);
    CF2.OUT_DATA(CFU2DATA2COUNTER);
    CF2.OUT_CRDT(CFU2CTR2COUNTER);
    CF2.CLK(clock3);

    /* CCS Block0 */
    Cfu CF3("cfu3");
    CF3.IN_Ctl_Valid(RX2CFU_VALID3);
    CF3.IN_Ctl_Packet(RX2CFU_DATA3);
    CF3.IN_Ctl_Type(RX2CFU_TYPE3);
    CF3.OUT_Ctl_Link(CFU2TX_LINK3);
    CF3.OUT_Ctl_Packet(CFU2TX_DATA3);
    CF3.OUT_Ctl_Valid(CFU2TX_VALID3);
    CF3.OUT_Ctl_Type(CFU2TX_TYPE3);
    CF3.OUT_Dest(CFU2RFU_DEST3);
    CF3.OUT_Link(CFU2RFU_LINK3);
    CF3.OUT_RC(CFU2RFU_RC3);
    CF3.OUT_Valid(CFU2RFU_VALID3);
    CF3.OUT_DATA(CFU3DATA2COUNTER);
    CF3.OUT_CRDT(CFU3CTR2COUNTER);
    CF3.CLK(clock3);


    /*Update Table*/
    Update Up0("update0");
    Up0.IN_Dest(CFU2RFU_DEST0);
    Up0.IN_Link(CFU2RFU_LINK0);
    Up0.IN_RC(CFU2RFU_RC0);
    Up0.IN_Valid(CFU2RFU_VALID0);
    Up0.CLK(clock3);
    
    Update Up1("update1");
    Up1.IN_Dest(CFU2RFU_DEST1);
    Up1.IN_Link(CFU2RFU_LINK1);
    Up1.IN_RC(CFU2RFU_RC1);
    Up1.IN_Valid(CFU2RFU_VALID1);
    Up1.CLK(clock3);

    Update Up2("update2");
    Up2.IN_Dest(CFU2RFU_DEST2);
    Up2.IN_Link(CFU2RFU_LINK2);
    Up2.IN_RC(CFU2RFU_RC2);
    Up2.IN_Valid(CFU2RFU_VALID2);
    Up2.CLK(clock3);

    Update Up3("update3");
    Up3.IN_Dest(CFU2RFU_DEST3);
    Up3.IN_Link(CFU2RFU_LINK3);
    Up3.IN_RC(CFU2RFU_RC3);
    Up3.IN_Valid(CFU2RFU_VALID3);
    Up3.CLK(clock3);

    
    /* TX Block0 */
    TxMac TX0("tx0");
    /*数据信元-输入-信号绑定*/
    TX0.IN_Valid(ROUTE2TX_VALID0);
    TX0.IN_Type(ROUTE2TX_TYPE0);
    TX0.IN_Packet(ROUTE2TX_VALUE0);
    TX0.IN_Link(ROUTE2TX_LINK0);
    TX0.IN_Bitmap(ROUTE2TX_BITMAP0);
    TX0.IN_Ctl_Link(CFU2TX_LINK0);
    TX0.IN_Ctl_Packet(CFU2TX_DATA0);
    TX0.IN_Ctl_Valid(CFU2TX_VALID0);
    TX0.IN_Ctl_Type(CFU2TX_TYPE0);
    TX0.OUT_Packet(TX_FIFO0);
    TX0.OUT_Count(TX02COUNTER);
    TX0.CLK(clock3);

    TxMac TX1("tx1");
    TX1.IN_Valid(ROUTE2TX_VALID1);
    TX1.IN_Type(ROUTE2TX_TYPE1);
    TX1.IN_Packet(ROUTE2TX_VALUE1);
    TX1.IN_Link(ROUTE2TX_LINK1);
    TX1.IN_Bitmap(ROUTE2TX_BITMAP1);
    TX1.IN_Ctl_Link(CFU2TX_LINK1);
    TX1.IN_Ctl_Packet(CFU2TX_DATA1);
    TX1.IN_Ctl_Valid(CFU2TX_VALID1);
    TX1.IN_Ctl_Type(CFU2TX_TYPE1);
    TX1.OUT_Packet(TX_FIFO1);
    TX1.OUT_Count(TX12COUNTER);
    TX1.CLK(clock3);
    
    TxMac TX2("tx2");
    TX2.IN_Valid(ROUTE2TX_VALID2);
    TX2.IN_Type(ROUTE2TX_TYPE2);
    TX2.IN_Packet(ROUTE2TX_VALUE2);
    TX2.IN_Link(ROUTE2TX_LINK2);
    TX2.IN_Bitmap(ROUTE2TX_BITMAP2);
    TX2.IN_Ctl_Link(CFU2TX_LINK2);
    TX2.IN_Ctl_Packet(CFU2TX_DATA2);
    TX2.IN_Ctl_Valid(CFU2TX_VALID2);
    TX2.IN_Ctl_Type(CFU2TX_TYPE2);
    TX2.OUT_Packet(TX_FIFO2);
    TX2.OUT_Count(TX22COUNTER);
    TX2.CLK(clock3);

    TxMac TX3("tx3");
    TX3.IN_Valid(ROUTE2TX_VALID3);
    TX3.IN_Type(ROUTE2TX_TYPE3);
    TX3.IN_Packet(ROUTE2TX_VALUE3);
    TX3.IN_Link(ROUTE2TX_LINK3);
    TX3.IN_Bitmap(ROUTE2TX_BITMAP3);
    TX3.IN_Ctl_Link(CFU2TX_LINK3);
    TX3.IN_Ctl_Packet(CFU2TX_DATA3);
    TX3.IN_Ctl_Valid(CFU2TX_VALID3);
    TX3.IN_Ctl_Type(CFU2TX_TYPE3);
    TX3.OUT_Packet(TX_FIFO3);
    TX3.OUT_Count(TX32COUNTER);
    TX3.CLK(clock3);

    Transmit SEND("sender");
    SEND.IN_Packet0(TX_FIFO0);
    SEND.IN_Packet1(TX_FIFO1);
    SEND.IN_Packet2(TX_FIFO2);
    SEND.IN_Packet3(TX_FIFO3);
    SEND.CLK(clock3);
    SEND.OUT_Count(SEND2COUNTER);

    Counter COUNTER("counter");
    COUNTER.IN_Recv(RECV2COUNTER);
    COUNTER.IN_Rx_Block0(RX1TOTAL2COUNTER);
    COUNTER.IN_Rx_Block1(RX2TOTAL2COUNTER);
    COUNTER.IN_Rx_Block2(RX3TOTAL2COUNTER);
    COUNTER.IN_Rx_Block3(RX4TOTAL2COUNTER);
    
    COUNTER.IN_Rx_0_Data(RX1DATA2COUNTER);
    COUNTER.IN_Rx_1_Data(RX2DATA2COUNTER);
    COUNTER.IN_Rx_2_Data(RX3DATA2COUNTER);
    COUNTER.IN_Rx_3_Data(RX4DATA2COUNTER);
    
    COUNTER.IN_Rx_0_Ctr(RX1CTR2COUNTER);
    COUNTER.IN_Rx_1_Ctr(RX2CTR2COUNTER);
    COUNTER.IN_Rx_2_Ctr(RX3CTR2COUNTER);
    COUNTER.IN_Rx_3_Ctr(RX4CTR2COUNTER);

    COUNTER.IN_Route_Block0(ROUTER02COUNTER);
    COUNTER.IN_Route_Block1(ROUTER12COUNTER);
    COUNTER.IN_Route_Block2(ROUTER22COUNTER);
    COUNTER.IN_Route_Block3(ROUTER32COUNTER);

    COUNTER.IN_CFU_Block0(CFU0CTR2COUNTER);
    COUNTER.IN_CFU_Block1(CFU1CTR2COUNTER);
    COUNTER.IN_CFU_Block2(CFU2CTR2COUNTER);
    COUNTER.IN_CFU_Block3(CFU3CTR2COUNTER);

    COUNTER.IN_CFU_BlockData0(CFU0DATA2COUNTER);
    COUNTER.IN_CFU_BlockData1(CFU1DATA2COUNTER);
    COUNTER.IN_CFU_BlockData2(CFU2DATA2COUNTER);
    COUNTER.IN_CFU_BlockData3(CFU3DATA2COUNTER);

    COUNTER.IN_Tx_Block0(TX02COUNTER);
    COUNTER.IN_Tx_Block1(TX12COUNTER);
    COUNTER.IN_Tx_Block2(TX22COUNTER);
    COUNTER.IN_Tx_Block3(TX32COUNTER);

    COUNTER.IN_Send(SEND2COUNTER);

    COUNTER.CLK(clock2);

    std::cout << "Simulation start ...\n";
    sc_start();

    return 0;
}
