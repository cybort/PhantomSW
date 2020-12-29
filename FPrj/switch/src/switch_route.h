/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              switch_route.h
   Project Code: F-Switch
   Module Name : ROUTE
   Date Created: 2020-11-12
   Author      : pengying21074
   Description : 路由模块定义头文件

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#ifndef _SWITCH_ROUTE_H_
#define _SWITCH_ROUTE_H_

#define MAX_LINKS           (36U)
#define BITS_OF_CHAR        (8U)
#define MAX_BITMAP_COUNT    ((MAX_LINKS/BITS_OF_CHAR) + ((MAX_LINKS%BITS_OF_CHAR) ? 1 : 0))

using std::cout;
using std::endl;

enum StausTypeDef
{
    SUCCESS = 0,
    FAILED,
    OUT_OF_RANGE,
    NULL_POINTER,
};

struct ROUTE_S
{
    USHORT usIndex;
    USHORT usDestination;
    USHORT uiLinkId;
    bool   bLinkValid;
    USHORT usTimeOut;
};

struct UNICAST_ROUTE_S
{
    USHORT usIndex;
    USHORT usDestination;
    unsigned long ulLinkValid;  /* 当前Switch明确只有36条link，故使用long作为bitmap存储已经足够 */
};

SC_MODULE(Route)
{
    /* declare in port */
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

    sc_in_clk CLK;
    
    /* declare out port */
    sc_out<USHORT> OUT_Link0;
    sc_out<USHORT> OUT_Link1;
    sc_out<USHORT> OUT_Link2;
    sc_out<USHORT> OUT_Link3;
    
    sc_out<sc_uint<4> > OUT_Type0;
    sc_out<sc_uint<4> > OUT_Type1;
    sc_out<sc_uint<4> > OUT_Type2;
    sc_out<sc_uint<4> > OUT_Type3;
    
    sc_out<CELL> OUT_Packet0;
    sc_out<CELL> OUT_Packet1;
    sc_out<CELL> OUT_Packet2;
    sc_out<CELL> OUT_Packet3;
    
    sc_out<bool> OUT_Valid0;
    sc_out<bool> OUT_Valid1;
    sc_out<bool> OUT_Valid2;
    sc_out<bool> OUT_Valid3;
    
    sc_out<sc_uint<36> >OUT_Bitmap0;
    sc_out<sc_uint<36> >OUT_Bitmap1;
    sc_out<sc_uint<36> >OUT_Bitmap2;
    sc_out<sc_uint<36> >OUT_Bitmap3;

    SC_CTOR(Route)
    {
        SC_THREAD(Route_Thread0);
        sensitive << CLK.pos();

        SC_THREAD(Route_Thread1);
        sensitive << CLK.pos();

        SC_THREAD(Route_Thread2);
        sensitive << CLK.pos();

        SC_THREAD(Route_Thread3);
        sensitive << CLK.pos();
        
        dont_initialize();
    }
    VOID Route_Thread0();
    VOID Route_Thread1();
    VOID Route_Thread2();
    VOID Route_Thread3();
};



INT BitMapSet(void *pDest, USHORT usPostion);
INT BitMapClear(void *pDest, USHORT usPostion);
bool BitMapValid(void *pDest, USHORT usPostion);
INT UnicastSearch(USHORT dest, USHORT *plink);


SC_MODULE(Update)
{
    sc_in<USHORT>IN_Dest0;
    sc_in<USHORT>IN_Link0;
    sc_in<bool>IN_RC0;
    sc_in<bool>IN_Valid0;
    sc_in_clk CLK;

    sc_in<USHORT>IN_Dest1;
    sc_in<USHORT>IN_Link1;
    sc_in<bool>IN_RC1;
    sc_in<bool>IN_Valid1;

    sc_in<USHORT>IN_Dest2;
    sc_in<USHORT>IN_Link2;
    sc_in<bool>IN_RC2;
    sc_in<bool>IN_Valid2;

    sc_in<USHORT>IN_Dest3;
    sc_in<USHORT>IN_Link3;
    sc_in<bool>IN_RC3;
    sc_in<bool>IN_Valid3;

    SC_CTOR(Update)
    {

        SC_THREAD(Update_Route_Thread0);
        sensitive << CLK.pos();
        
        SC_THREAD(Update_Route_Thread1);
        sensitive << CLK.pos();

        SC_THREAD(Update_Route_Thread2);
        sensitive << CLK.pos();

        SC_THREAD(Update_Route_Thread3);
        sensitive << CLK.pos();

        dont_initialize();
    }
    VOID Update_Route_Thread0();
    VOID Update_Route_Thread1();
    VOID Update_Route_Thread2();
    VOID Update_Route_Thread3();

};


#endif

