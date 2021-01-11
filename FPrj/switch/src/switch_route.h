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
    sc_in<bool> IN_Valid;
    sc_in<CELL> IN_Packet;
    sc_in<sc_uint<4> > IN_Type;

    sc_in_clk CLK;
    
    /* declare out port */
    sc_out<USHORT> OUT_Link;
    sc_out<sc_uint<4> > OUT_Type;
    sc_out<CELL> OUT_Packet;
    sc_out<bool> OUT_Valid;
    sc_out<sc_uint<36> >OUT_Bitmap;
    sc_out<ULONG> OUT_Count;

    ULONG ulBlockCount;

    SC_CTOR(Route)
    {
        SC_THREAD(Route_ProcFunc);
        sensitive << CLK.pos();

        ulBlockCount = 0;
        
        dont_initialize();
    }
    VOID Route_ProcFunc();
};

SC_MODULE(Update)
{
    sc_in<USHORT>IN_Dest;
    sc_in<USHORT>IN_Link;
    sc_in<bool>IN_RC;
    sc_in<bool>IN_Valid;
    sc_in_clk CLK;

    SC_CTOR(Update)
    {
        SC_THREAD(Update_ProcFunc);
        sensitive << CLK.pos();
        
        dont_initialize();
    }
    VOID Update_ProcFunc();
};



INT BitMapSet(void *pDest, USHORT usPostion);
INT BitMapClear(void *pDest, USHORT usPostion);
bool BitMapValid(void *pDest, USHORT usPostion);
INT UnicastSearch(USHORT dest, USHORT *plink);





#endif

