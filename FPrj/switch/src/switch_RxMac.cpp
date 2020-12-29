/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              switch_RxMac.cpp
   Project Code: F-Switch
   Module Name : RX MAC
   Date Created: 2020-11-12
   Author      : pengying21074
   Description : RX MAC模块实现

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/
#include <vector>
#include "systemc.h"
#include "prv_deftype.h"
#include "switch_cell.h"
#include "switch_RxMac.h"
#include "switch_route.h"

#define MAX_TIMEOUT_COUNT    50
//#define CLK_COUNT            10

ROUTE_S RouteTable[] = {
    {0,      0,      0,      true,     MAX_TIMEOUT_COUNT},
    {1,      0,      1,      true,     MAX_TIMEOUT_COUNT},
    {2,      0,      2,      true,     MAX_TIMEOUT_COUNT},
    {3,      0,      3,      true,     MAX_TIMEOUT_COUNT},
    {4,      0,      4,      true,     MAX_TIMEOUT_COUNT},
    {5,      0,      5,      true,     MAX_TIMEOUT_COUNT},
    {6,      0,      6,      true,     MAX_TIMEOUT_COUNT},
    {7,      0,      7,      true,     MAX_TIMEOUT_COUNT},
    {8,      0,      8,      true,     MAX_TIMEOUT_COUNT},
    {9,      0,      9,      true,     MAX_TIMEOUT_COUNT},
    {10,     0,      10,     true,     MAX_TIMEOUT_COUNT},
    {11,     0,      11,     true,     MAX_TIMEOUT_COUNT},
    {12,     0,      12,     true,     MAX_TIMEOUT_COUNT},
    {13,     0,      13,     true,     MAX_TIMEOUT_COUNT},
    {14,     0,      14,     true,     MAX_TIMEOUT_COUNT},
    {15,     0,      15,     true,     MAX_TIMEOUT_COUNT},
    {16,     0,      16,     true,     MAX_TIMEOUT_COUNT},
    {17,     0,      17,     true,     MAX_TIMEOUT_COUNT},
    {18,     1,      18,     true,     MAX_TIMEOUT_COUNT},
    {19,     1,      19,     true,     MAX_TIMEOUT_COUNT},
    {20,     1,      20,     true,     MAX_TIMEOUT_COUNT},
    {21,     1,      21,     true,     MAX_TIMEOUT_COUNT},
    {22,     1,      22,     true,     MAX_TIMEOUT_COUNT},
    {23,     1,      23,     true,     MAX_TIMEOUT_COUNT},
    {24,     1,      24,     true,     MAX_TIMEOUT_COUNT},
    {25,     1,      25,     true,     MAX_TIMEOUT_COUNT},
    {26,     1,      26,     true,     MAX_TIMEOUT_COUNT},
    {27,     1,      27,     true,     MAX_TIMEOUT_COUNT},
    {28,     1,      28,     true,     MAX_TIMEOUT_COUNT},
    {29,     1,      29,     true,     MAX_TIMEOUT_COUNT},
    {30,     1,      30,     true,     MAX_TIMEOUT_COUNT},
    {31,     1,      31,     true,     MAX_TIMEOUT_COUNT},
    {32,     1,      32,     true,     MAX_TIMEOUT_COUNT},
    {33,     1,      33,     true,     MAX_TIMEOUT_COUNT},
    {34,     1,      34,     true,     MAX_TIMEOUT_COUNT},
    {35,     1,      35,     true,     MAX_TIMEOUT_COUNT}
};

ULONG g_ulLinkUpdatedStatus = 0;
/*****************************************************************************
 Func Name    : UpdateList
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : 根据信元timeslot缓存队列
 Input        : vector<CELL> & Dest     目标队列
                CELL InsertData         待缓存的cell
 Output       : NONE
 Return       : 队列深度
 Caution      :
*****************************************************************************/
INT UpdateList(std::vector<CELL> & Dest, CELL InsertData)
{
    std::vector<CELL>::iterator it;

    /* 容器为空时直接入队 */
    if(Dest.size() == 0)
    {
        Dest.push_back(InsertData);
        return Dest.size();
    }

    for(it = Dest.begin(); it < Dest.end(); it++)
    {
        if(InsertData.fts < it->fts)
        break;
    }
    /* 最大的timeslot */
    if(it == Dest.end())
    {
        Dest.push_back(InsertData);
    }
    else
    {
        Dest.insert(it, InsertData);
    }
    return Dest.size();
}

/*****************************************************************************
 Func Name    : UpdateLinkValidStatus
 Date Created : 2020/12/23
 Author       : 
 Description  : Rx模块定义的process实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
void UpdateLinkValidStatus( USHORT usLink )
{
    INT ret;
    RouteTable[ usLink ].bLinkValid = TRUE;
    RouteTable[ usLink ].usTimeOut = MAX_TIMEOUT_COUNT;
    ret = BitMapSet( &g_ulLinkUpdatedStatus, usLink );/*记录已更新过的链路*/
    return;
}

/*****************************************************************************
 Func Name    : RxMac::RxMac_ProcPlane0Func
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : Rx模块定义的process实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
void RxMac::RxMac_ProcPlane0Func()
{
    CELL InData, OutData;
    sc_uint<4> type_bit4;
    std::vector<CELL> SortQ;
    USHORT usLink = 0;
    while(1)
    {
        wait();
        if(IN_ProcPlane0->num_available() > 0)
        {
            OUT_Valid0 = false;
            OUT_Ctl_Valid0 = false;
            IN_ProcPlane0->read(InData);
            IN_Link0->read(usLink);

            mutex.lock();
            uiCount++;
            UpdateLinkValidStatus(usLink);
            mutex.unlock();

            type_bit4 = InData.type;
            /* 信元格式字段type 的bit3为0表示数据信元,为1表示控制信元 */
            if(type_bit4[3] )
            {
                OUT_Ctl_Type0.write(type_bit4);
                OUT_Ctl_Packet0.write(InData);
                OUT_Ctl_Valid0 = true;
            }
            else
            {
                /* 对数据进行缓存 */
                UpdateList(SortQ, InData);
                if(SortQ.size() != 0)
                {
                    OutData = SortQ[0];//将SortQ中的第一个元素给OutData
                    /* 从缓存中删除第一个元素 */
                    SortQ.erase(SortQ.begin());
                    type_bit4 = OutData.type;
                    OUT_Type0.write(type_bit4);
                    OUT_Packet0.write(OutData);
                    OUT_Valid0 = true;
                }
            }
        }
    }
}

/*****************************************************************************
 Func Name    : RxMac::RxMac_ProcPlane0Func
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : Rx模块定义的process实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
void RxMac::RxMac_ProcPlane1Func()
{
    CELL InData, OutData;
    sc_uint<4> type_bit4;
    std::vector<CELL> SortQ;
    USHORT usLink = 0;
    while(1)
    {
        wait();
        if(IN_ProcPlane1->num_available() > 0)
        {
            OUT_Valid1 = false;
            OUT_Ctl_Valid1 = false;
            IN_ProcPlane1->read(InData);
            IN_Link1->read(usLink);

            mutex.lock();
            uiCount++;
            UpdateLinkValidStatus(usLink);
            mutex.unlock();

            type_bit4 = InData.type;
            /* 信元格式字段type 的bit3为0表示数据信元,为1表示控制信元 */
            if (type_bit4[3])
            {
                OUT_Ctl_Type1.write(type_bit4);
                OUT_Ctl_Packet1.write(InData);
                OUT_Ctl_Valid1 = true;
            }
            else
            {
                /* 对数据进行缓存 */
                UpdateList(SortQ, InData);
                if(SortQ.size() != 0)
                {
                    OutData = SortQ[0];
                    /* 从缓存中删除第一个元素 */
                    SortQ.erase(SortQ.begin());
                    type_bit4 = OutData.type;
                    OUT_Type1.write(type_bit4);
                    OUT_Packet1.write(OutData);
                    OUT_Valid1 = true;
                }
            }
        }
    }
}
/*****************************************************************************
 Func Name    : RxMac::RxMac_ProcPlane0Func
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : Rx模块定义的process实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
void RxMac::RxMac_ProcPlane2Func()
{
    CELL InData, OutData;
    sc_uint<4> type_bit4;
    std::vector<CELL> SortQ;
    USHORT usLink = 0;
    while(1)
    {
        wait();
        if(IN_ProcPlane2->num_available() > 0)
        {
            OUT_Valid2 = false;
            OUT_Ctl_Valid2 = false;
            IN_ProcPlane2->read(InData);
            IN_Link2->read(usLink);
            
            mutex.lock();
            uiCount++;
            UpdateLinkValidStatus(usLink);
            mutex.unlock();

            type_bit4 = InData.type;
            /* 信元格式字段type 的bit3为0表示数据信元,为1表示控制信元 */
            if (type_bit4[3])
            {
                OUT_Ctl_Type2.write(type_bit4);
                OUT_Ctl_Packet2.write(InData);
                OUT_Ctl_Valid2 = true;
            }
            else
            {
                UpdateList(SortQ, InData);
                if(SortQ.size() != 0)
                {
                    OutData = SortQ[0];
                    /* 从缓存中删除第一个元素 */
                    SortQ.erase(SortQ.begin());
                    type_bit4 = OutData.type;
                    OUT_Type2.write(type_bit4);
                    OUT_Packet2.write(OutData);
                    OUT_Valid2 = true;
                }
            }
        }
    }
}


/*****************************************************************************
 Func Name    : RxMac::RxMac_ProcPlane0Func
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : Rx模块定义的process实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
void RxMac::RxMac_ProcPlane3Func()
{
    CELL InData, OutData;
    sc_uint<4> type_bit4;
    std::vector<CELL> SortQ;
    USHORT usLink = 0;
    while(1)
    {
        wait();
        if(IN_ProcPlane3->num_available() > 0)
        {
            OUT_Valid3 = false;
            OUT_Ctl_Valid3 = false;
            IN_ProcPlane3->read(InData);
            IN_Link3->read(usLink);

            mutex.lock();
            uiCount++;
            UpdateLinkValidStatus(usLink);
            mutex.unlock();

            type_bit4 = InData.type;
            /* 信元格式字段type 的bit3为1表示控制信元,为0表示数据信元 */
            if ( type_bit4[3] )
            {
                OUT_Ctl_Type3.write(type_bit4);
                OUT_Ctl_Packet3.write(InData);
                OUT_Ctl_Valid3 = true;
            }
            else
            {
                /* 对数据进行缓存 */
                UpdateList(SortQ, InData);
                if(SortQ.size() != 0)
                {
                    OutData = SortQ[0];
                    /* 从缓存中删除第一个元素 */
                    SortQ.erase(SortQ.begin());
                    type_bit4 = OutData.type;
                    OUT_Type3.write(type_bit4);
                    OUT_Packet3.write(OutData);
                    OUT_Valid3 = true;
                }
            }
        }
    }
}

/*****************************************************************************
 Func Name    : RxMac::Update_Link_Table()
 Date Created : 2020/12/15
 Author       : 
 Description  : ROUTE模块定义的控制信元处理实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID RxMac::RxMac_Update_LinkStatus()
{
    USHORT usIndex;
    INT     ret = 0;

    /*先判断是否有新的路由信元，带来相关路由信息*/
    while(TRUE)
    {
        wait();
        ULONG   g_ulLinkAvailable = 0xfffffffff;
        for ( usIndex = 0; usIndex < sizeof(RouteTable)/sizeof(RouteTable[0]); usIndex++)
        {
            if ( BitMapValid(&g_ulLinkUpdatedStatus, usIndex) )
            {
                //cout << " Update: link id " << usIndex << "has been updated" << endl;
                continue;
            }
            //cout << " Update: link id " << usIndex << endl;
            if ( !RouteTable[ usIndex ].bLinkValid )
            {
                ret = BitMapClear( &g_ulLinkAvailable, usIndex);
                continue;
            }
            else
            {
                if ( ( RouteTable[ usIndex ].usTimeOut == 0 ) )
                {
                    RouteTable[ usIndex ].bLinkValid = FALSE;
                    continue;
                }
                else
                {
                    RouteTable[ usIndex ].usTimeOut -= 1;
                    continue;
                }
            }
        }
        #if 0
        for ( usIndex = 0; usIndex < sizeof(RouteTable)/sizeof(RouteTable[0]); usIndex++)
        {
            cout << "link id: " << RouteTable[ usIndex ].uiLinkId;
            cout << "     statue: " << RouteTable[ usIndex ].bLinkValid;
            cout << "     timeout: " << RouteTable[ usIndex ].usTimeOut << endl;
        }
        printf("link status : 0x%x\n", g_ulLinkAvailable );
        cout << endl;
        #endif
    }
}

