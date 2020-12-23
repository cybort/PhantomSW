/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              switch_route.cpp
   Project Code: F-Switch
   Module Name : ROUTE
   Date Created: 2020-11-12
   Author      : pengying21074
   Description : 路由模块实现

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>

#include "systemc.h"
#include "prv_deftype.h"
#include "switch_cell.h"
#include "switch_route.h"

#define MAX_TIMEOUT_COUNT    120
#define CLK_COUNT            40
static ROUTE_S RouteTable[] = {
    {0,      0,      0,      true,     MAX_TIMEOUT_COUNT,     CLK_COUNT},
    {1,      0,      1,      true,     MAX_TIMEOUT_COUNT,     CLK_COUNT},
    {2,      0,      2,      true,     MAX_TIMEOUT_COUNT,     CLK_COUNT},
    {3,      0,      3,      true,     MAX_TIMEOUT_COUNT,     CLK_COUNT},
    {4,      0,      4,      true,     MAX_TIMEOUT_COUNT,     CLK_COUNT},
    {5,      0,      5,      true,     MAX_TIMEOUT_COUNT,     CLK_COUNT},
    {6,      0,      6,      true,     MAX_TIMEOUT_COUNT,     CLK_COUNT},
    {7,      0,      7,      true,     MAX_TIMEOUT_COUNT,     CLK_COUNT},
    {8,      0,      8,      true,     MAX_TIMEOUT_COUNT,     CLK_COUNT},
    {9,      1,      9,      true,     MAX_TIMEOUT_COUNT,     CLK_COUNT},
    {10,     1,      10,     true,     MAX_TIMEOUT_COUNT,     CLK_COUNT},
    {11,     1,      11,     true,     MAX_TIMEOUT_COUNT,     CLK_COUNT},
    {12,     1,      12,     true,     MAX_TIMEOUT_COUNT,     CLK_COUNT},
    {13,     1,      13,     true,     MAX_TIMEOUT_COUNT,     CLK_COUNT},
    {14,     1,      14,     true,     MAX_TIMEOUT_COUNT,     CLK_COUNT},
    {15,     1,      15,     true,     MAX_TIMEOUT_COUNT,     CLK_COUNT},
    {16,     1,      16,     true,     MAX_TIMEOUT_COUNT,     CLK_COUNT},
    {17,     1,      17,     true,     MAX_TIMEOUT_COUNT,     CLK_COUNT},
};


UNICAST_ROUTE_S UnicastRouteTable[] = {
    {0,     0,      0x001ff},
    {1,     1,      0x3fe00},
};

static UINT g_uiLastTimeslot;//整个Switch的TimeSlot
ULONG g_ulLinkUpdatedStatus = 0;
/* bitmap 指定位置置位 */
/*****************************************************************************
 Func Name    : BitMapSet
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : bitmap置位指定位
 Input        : void *pDest     指向bitmap的指针
                USHORT usPostion    指定bitmap中需要置位的位置
 Output       : NONE
 Return       : 0       操作成功
                -1      操作失败
 Caution      :
*****************************************************************************/
INT BitMapSet(void *pDest, USHORT usPostion)
{
    UCHAR *pucTmp;
    USHORT usIndex;
    USHORT usOffset;

    if(NULL == pDest)
    {
        cout << "null pointer detected.\n";
        return -1;
    }
    if(usPostion >= MAX_LINKS)
    {
        cout << "out of range.\n";
        return -1;
    }

    pucTmp = (UCHAR *)pDest;
    usIndex = usPostion / BITS_OF_CHAR;
    usOffset = usPostion % BITS_OF_CHAR;

    pucTmp[usIndex] |= (1 << usOffset);

    return 0;
}

/* bitmap 指定位置复位 */
/*****************************************************************************
 Func Name    : BitMapClear
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : bitmap复位指定位
 Input        : void *pDest     指向bitmap的指针
                USHORT usPostion    指定bitmap中需要清除的位置
 Output       : NONE
 Return       : 0       操作成功
                -1      操作失败
 Caution      :
*****************************************************************************/
INT BitMapClear(void *pDest, USHORT usPostion)
{
    UCHAR *pucTmp;
    USHORT usIndex;
    USHORT usOffset;

    if(NULL == pDest)
    {
        cout << "null pointer detected.\n";
        return -1;
    }
    if(usPostion >= MAX_LINKS)
    {
        cout << "out of range.\n";
        return -1;
    }

    pucTmp = (UCHAR *)pDest;
    usIndex = usPostion / BITS_OF_CHAR;
    usOffset = usPostion % BITS_OF_CHAR;

    pucTmp[usIndex] &= ~(1 << usOffset);

    return 0;
}

/* bitmap 判断指定位置状态 */
/*****************************************************************************
 Func Name    : BitMapValid
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : 检查bitmap中指定位置是否置位
 Input        : void *pDest     指向bitmap的指针
                USHORT usPostion    指定bitmap中需要检查的位置
 Output       : NONE
 Return       : true       置位
                false      0
 Caution      :
*****************************************************************************/
bool BitMapValid(void *pDest, USHORT usPostion)
{
    UCHAR *pucTmp;
    USHORT usIndex;
    USHORT usOffset;

    pucTmp = (UCHAR *)pDest;
    usIndex = usPostion / BITS_OF_CHAR;
    usOffset = usPostion % BITS_OF_CHAR;

    if(pucTmp[usIndex] & (1 << usOffset))
    return true;
    else
    return false;
}

/* 单播路由查表 */
/*****************************************************************************
 Func Name    : UnicastSearch
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : 单播查表
 Input        : USHORT dest     目的id
                
 Output       : USHORT *plink    指向出link 索引号
 Return       : 0       操作成功
                -1      操作失败
 Caution      :
*****************************************************************************/
INT UnicastSearch(USHORT dest, USHORT *plink)
{
    std::vector<USHORT> result;
    UINT result_size;
    UINT rand_port;

    srand(time(0));
    for(INT loop = 0; loop < MAX_LINKS; loop++)
    {
        if(BitMapValid(&UnicastRouteTable[dest].ulLinkValid, loop) == true)
        {
            result.push_back(loop);
        }
    }

    result_size = result.size();
    if(0 == result_size)
    {
        cout << "UnicastSearch: no route to destination " << dest << endl;
        return -1;
    }
    else
    {
        rand_port = rand() % result_size;
        *plink = result[rand_port];
        return 0;
    }
}

/*****************************************************************************
 Func Name    : Route::Route_func_entry()
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : ROUTE模块定义的process实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
void Route::Route_Thread0()
{
    CELL tmp;
    CELL OldData;
    USHORT dest;
    USHORT outlink;
    UINT type;
    
    while(1)
    {
        /* 等待valid 信号拉高 */
        do {
            wait();
        }while(IN_Valid0 != true);
        
        OUT_Valid0 = false;
        tmp = IN_Packet0.read();
        if(!(tmp == OldData))
        {
            OldData = IN_Packet0.read();
            type = IN_Type0.read();

            switch(type)
            {
                case CellType::Unicast:
                {
                    //cout << "Route: processing   1  ~" << "  dest: " << dest << endl;
                    dest = tmp.dest_id;
                    if(UnicastSearch(dest, &outlink) == 0)
                    {
                        //cout << "Route: processing   2  ~" << "  outlink: " << outlink << endl;
                        OUT_Link0.write(outlink);
                        OUT_Packet0.write(tmp);
                        OUT_Type0.write(type);
                        OUT_Valid0 = true;
                    }
                    break;
                }
                case CellType::Multicast:
                /* 组播暂未合入 */
                    break;
                case CellType::Empty:
                {
                    if(g_uiLastTimeslot < tmp.fts)
                    {
                        tmp.fts = g_uiLastTimeslot;
                    }
                    OUT_Packet0.write(tmp);
                    OUT_Type0.write(type);
                    OUT_Valid0 = true;
                    break;
                }
                default:
                    cout << "Route: cell type is not supported.\n";
            }
            g_uiLastTimeslot = tmp.fts;
        }
    }
}

/*****************************************************************************
 Func Name    : Route::Route_func_entry()
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : ROUTE模块定义的process实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
void Route::Route_Thread1()
{
    CELL tmp;
    CELL OldData;
    USHORT dest;
    USHORT outlink;
    UINT type;
    
    while(1)
    {
        /* 等待valid 信号拉高 */
        do {
            wait();
        }while(IN_Valid1 != true);
        
        OUT_Valid1 = false;
        tmp = IN_Packet1.read();
        if(!(tmp == OldData))
        {
            OldData = IN_Packet1.read();
            type = IN_Type1.read();

            switch(type)
            {
                case CellType::Unicast:
                {
                    //cout << "Route: processing   1  ~" << "  dest: " << dest << endl;
                    dest = tmp.dest_id;
                    if(UnicastSearch(dest, &outlink) == 0)
                    {
                        //cout << "Route: processing   2  ~" << "  outlink: " << outlink << endl;
                        OUT_Link1.write(outlink);
                        OUT_Packet1.write(tmp);
                        OUT_Type1.write(type);
                        OUT_Valid1 = true;
                    }
                    break;
                }
                case CellType::Multicast:
                /* 组播暂未合入 */
                    break;
                case CellType::Empty:
                {
                    if(g_uiLastTimeslot < tmp.fts)
                    {
                        tmp.fts = g_uiLastTimeslot;
                    }
                    OUT_Packet1.write(tmp);
                    OUT_Type1.write(type);
                    OUT_Valid1 = true;
                    break;
                }
                default:
                    cout << "Route: cell type is not support.\n";
            }
            g_uiLastTimeslot = tmp.fts;
        }
    }
}


/*****************************************************************************
 Func Name    : Route::Route_func_entry()
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : ROUTE模块定义的process实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
void Route::Route_Thread2()
{
    CELL tmp;
    CELL OldData;
    USHORT dest;
    USHORT outlink;
    UINT type;
    
    while(1)
    {
        /* 等待valid 信号拉高 */
        do {
            wait();
        }while(IN_Valid2 != true);
        
        OUT_Valid2 = false;
        tmp = IN_Packet2.read();
        if(!(tmp == OldData))
        {
            OldData = IN_Packet2.read();
            type = IN_Type2.read();

            switch(type)
            {
                case CellType::Unicast:
                {
                    //cout << "Route: processing   1  ~" << "  dest: " << dest << endl;
                    dest = tmp.dest_id;
                    if(UnicastSearch(dest, &outlink) == 0)
                    {
                        //cout << "Route: processing   2  ~" << "  outlink: " << outlink << endl;
                        OUT_Link2.write(outlink);
                        OUT_Packet2.write(tmp);
                        OUT_Type2.write(type);
                        OUT_Valid2 = true;
                    }
                    break;
                }
                case CellType::Multicast:
                /* 组播暂未合入 */
                    break;
                case CellType::Empty:
                {
                    if(g_uiLastTimeslot < tmp.fts)
                    {
                        tmp.fts = g_uiLastTimeslot;
                    }
                    OUT_Packet2.write(tmp);
                    OUT_Type2.write(type);
                    OUT_Valid2 = true;
                    break;
                }
                default:
                    cout << "Route: cell type is not defined.\n";
            }
            g_uiLastTimeslot = tmp.fts;
        }
    }
}

/*****************************************************************************
 Func Name    : Route::Route_func_entry()
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : ROUTE模块定义的process实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
void Route::Route_Thread3()
{
    CELL tmp;
    CELL OldData;
    USHORT dest;
    USHORT outlink;
    UINT type;
    
    while(1)
    {
        /* 等待valid 信号拉高 */
        do {
            wait();
        }while(IN_Valid3 != true);
        
        OUT_Valid3 = false;
        tmp = IN_Packet3.read();
        if(!(tmp == OldData))
        {
            OldData = IN_Packet3.read();
            type = IN_Type3.read();

            switch(type)
            {
                case CellType::Unicast:
                {
                    cout << "Route: processing   1  ~" << "  dest: " << dest << endl;
                    dest = tmp.dest_id;
                    if(UnicastSearch(dest, &outlink) == 0)
                    {
                        cout << "Route: processing   2  ~" << "  outlink: " << outlink << endl;
                        OUT_Link3.write(outlink);
                        OUT_Packet3.write(tmp);
                        OUT_Type3.write(type);
                        OUT_Valid3 = true;
                    }
                    break;
                }
                case CellType::Multicast:
                /* 组播暂未合入 */
                    break;
                case CellType::Empty:
                {
                    if(g_uiLastTimeslot < tmp.fts)
                    {
                        tmp.fts = g_uiLastTimeslot;
                    }
                    OUT_Packet3.write(tmp);
                    OUT_Type3.write(type);
                    OUT_Valid3 = true;
                    break;
                }
                default:
                    cout << "Route: cell type is not defined.\n";
            }
            g_uiLastTimeslot = tmp.fts;
        }
    }
}

/*****************************************************************************
 Func Name    : Update::Update_Route_Table()
 Date Created : 2020/12/15
 Author       : 
 Description  : ROUTE模块定义的控制信元处理实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID Update::Update_Route_Table()
{
    USHORT usIndex;

    /*先判断是否有新的路由信元，带来相关路由信息*/
    while(TRUE)
    {
        wait();

        for ( usIndex = 0; usIndex < sizeof(RouteTable)/sizeof(ROUTE_S); usIndex++)
        {
            if ( BitMapValid(&g_ulLinkUpdatedStatus, usIndex) )
            {
                //cout << " Update: link id " << usIndex << "has been updated" << endl;
                continue;
            }
            //cout << " Update: link id " << usIndex << endl;
            if ( !RouteTable[ usIndex ].bRouteConnect )
            {
                continue;
            }
            else
            {
                if ( ( RouteTable[ usIndex ].usTimeOut == 0 ) )
                {
                    if( RouteTable[ usIndex ].usTimeCount == 0 )
                    {
                        RouteTable[ usIndex ].bRouteConnect = FALSE;
                        USHORT usDest = RouteTable[ usIndex ].usDestination;
                        INT ret = BitMapClear( &UnicastRouteTable[ usDest ].ulLinkValid, usIndex );
                        continue;
                    }
                    else
                    {
                        RouteTable[ usIndex ].usTimeCount -= 1;
                        continue;
                    }
                }
                else
                {
                    if( RouteTable[ usIndex ].usTimeCount == 0 )
                    {
                        RouteTable[ usIndex ].usTimeOut -= 1;
                        RouteTable[ usIndex ].usTimeCount = CLK_COUNT;
                        continue;
                    }
                    RouteTable[ usIndex ].usTimeCount -= 1;
                    continue;
                }
            }
        }
        g_ulLinkUpdatedStatus = 0;/*更新一轮后清零*/
        #if 0
        for ( usIndex = 0; usIndex < sizeof(RouteTable)/sizeof(ROUTE_S); usIndex++)
        {
            cout << "link id: " << RouteTable[ usIndex ].uiLinkId;
            cout << "     statue: " << RouteTable[ usIndex ].bRouteConnect;
            cout << "     timeout: " << RouteTable[ usIndex ].usTimeOut;
            cout << "     count: " << RouteTable[ usIndex ].usTimeCount << endl;
        }
        printf("dest0 0x%x\t", UnicastRouteTable[ 0 ].ulLinkValid);
        printf("dest1 0x%x\n", UnicastRouteTable[ 1 ].ulLinkValid);
        cout << endl;
        #endif
    }
}


/*****************************************************************************
 Func Name    : Update::Update_Route_Thread0()
 Date Created : 2020/12/16
 Author       : 
 Description  : ROUTE模块定义的控制信元处理实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID Update::Update_Route_Thread0()
{
    INT ret;
    BOOL bRC = FALSE;
        
    while(TRUE)
    {
        /* 等待valid 信号拉高 */
        do {
            wait();
        }while(IN_Valid0 != true);

        bRC = IN_RC0.read();
        USHORT usLink= IN_Link0.read();
        USHORT usDest = RouteTable[ usLink ].usDestination;
        cout << "Update:link " << usLink << endl;
        if ( bRC )
        {
            ret = BitMapSet( &UnicastRouteTable[ usDest ].ulLinkValid, usLink );
            ret = BitMapSet( &g_ulLinkUpdatedStatus, usLink );/*记录已更新过的链路*/

            RouteTable[ usLink ].bRouteConnect = TRUE;
            RouteTable[ usLink ].usTimeOut = MAX_TIMEOUT_COUNT;
            RouteTable[ usLink ].usTimeCount = CLK_COUNT;
        }
        else
        {
            cout << "link " << usLink << " cannot reach dest " << usDest << endl;
        }
    }
}

/*****************************************************************************
 Func Name    : Update::Update_Route_Thread1()
 Date Created : 2020/12/16
 Author       : 
 Description  : ROUTE模块定义的控制信元处理实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID Update::Update_Route_Thread1()
{
    INT ret;
    BOOL bRC = FALSE;
        
    while(TRUE)
    {
        /* 等待valid 信号拉高 */
        do {
            wait();
        }while(IN_Valid1 != true);

        bRC = IN_RC1.read();
        USHORT usLink= IN_Link1.read();
        USHORT usDest = RouteTable[ usLink ].usDestination;
        cout << "Update:link " << usLink << endl;
        if ( bRC )
        {
            ret = BitMapSet( &UnicastRouteTable[ usDest ].ulLinkValid, usLink );
            ret = BitMapSet( &g_ulLinkUpdatedStatus, usLink );/*记录已更新过的链路*/

            RouteTable[ usLink ].bRouteConnect = TRUE;
            RouteTable[ usLink ].usTimeOut = MAX_TIMEOUT_COUNT;
            RouteTable[ usLink ].usTimeCount = CLK_COUNT;
        }
        else
        {
            cout << "link " << usLink << " cannot reach dest " << usDest << endl;
        }
    }
}

/*****************************************************************************
 Func Name    : Update::Update_Route_Thread2()
 Date Created : 2020/12/16
 Author       : 
 Description  : ROUTE模块定义的控制信元处理实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID Update::Update_Route_Thread2()
{
    INT ret;
    BOOL bRC = FALSE;
        
    while(TRUE)
    {
        /* 等待valid 信号拉高 */
        do {
            wait();
        }while(IN_Valid2 != true);

        bRC = IN_RC2.read();
        USHORT usLink= IN_Link2.read();
        USHORT usDest = RouteTable[ usLink ].usDestination;
        cout << "Update:link " << usLink << endl;
        if ( bRC )
        {
            ret = BitMapSet( &UnicastRouteTable[ usDest ].ulLinkValid, usLink );
            ret = BitMapSet( &g_ulLinkUpdatedStatus, usLink );/*记录已更新过的链路*/

            RouteTable[ usLink ].bRouteConnect = TRUE;
            RouteTable[ usLink ].usTimeOut = MAX_TIMEOUT_COUNT;
            RouteTable[ usLink ].usTimeCount = CLK_COUNT;
        }
        else
        {
            cout << "link " << usLink << " cannot reach dest " << usDest << endl;
        }
    }
}

/*****************************************************************************
 Func Name    : Update::Update_Route_Thread3()
 Date Created : 2020/12/16
 Author       : 
 Description  : ROUTE模块定义的控制信元处理实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID Update::Update_Route_Thread3()
{
    INT ret;
    BOOL bRC = FALSE;
        
    while(TRUE)
    {
        /* 等待valid 信号拉高 */
        do {
            wait();
        }while(IN_Valid3 != true);

        bRC = IN_RC3.read();
        USHORT usLink= IN_Link3.read();
        USHORT usDest = RouteTable[ usLink ].usDestination;
        cout << "Update:link " << usLink << endl;
        if ( bRC )
        {
            ret = BitMapSet( &UnicastRouteTable[ usDest ].ulLinkValid, usLink );
            ret = BitMapSet( &g_ulLinkUpdatedStatus, usLink );/*记录已更新过的链路*/

            RouteTable[ usLink ].bRouteConnect = TRUE;
            RouteTable[ usLink ].usTimeOut = MAX_TIMEOUT_COUNT;
            RouteTable[ usLink ].usTimeCount = CLK_COUNT;
        }
        else
        {
            cout << "link " << usLink << " cannot reach dest " << usDest << endl;
        }
    }
}
