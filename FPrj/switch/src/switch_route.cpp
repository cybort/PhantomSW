/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              switch_route.cpp
   Project Code: F-Switch
   Module Name : ROUTE
   Date Created: 2020-11-12
   Author      : pengying21074
   Description : ·��ģ��ʵ��

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

UNICAST_ROUTE_S UnicastRouteTable[] = {
    {0,     0,      0x00003ffff},
    {1,     1,      0xffffc0000},
};

static UINT g_uiLastTimeslot;//����Switch��TimeSlot
extern ROUTE_S RouteTable[];


/* bitmap ָ��λ����λ */
/*****************************************************************************
 Func Name    : BitMapSet
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : bitmap��λָ��λ
 Input        : void *pDest     ָ��bitmap��ָ��
                USHORT usPostion    ָ��bitmap����Ҫ��λ��λ��
 Output       : NONE
 Return       : 0       �����ɹ�
                -1      ����ʧ��
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

/* bitmap ָ��λ�ø�λ */
/*****************************************************************************
 Func Name    : BitMapClear
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : bitmap��λָ��λ
 Input        : void *pDest     ָ��bitmap��ָ��
                USHORT usPostion    ָ��bitmap����Ҫ�����λ��
 Output       : NONE
 Return       : 0       �����ɹ�
                -1      ����ʧ��
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

/* bitmap �ж�ָ��λ��״̬ */
/*****************************************************************************
 Func Name    : BitMapValid
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : ���bitmap��ָ��λ���Ƿ���λ
 Input        : void *pDest     ָ��bitmap��ָ��
                USHORT usPostion    ָ��bitmap����Ҫ����λ��
 Output       : NONE
 Return       : true       ��λ
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

/* ����·�ɲ�� */
/*****************************************************************************
 Func Name    : UnicastSearch
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : �������
 Input        : USHORT dest     Ŀ��id
                
 Output       : USHORT *plink    ָ���link ������
 Return       : 0       �����ɹ�
                -1      ����ʧ��
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
        if ( (BitMapValid(&UnicastRouteTable[dest].ulLinkValid, loop) == true) && 
            (RouteTable[loop].bLinkValid) )
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
 Description  : ROUTEģ�鶨���processʵ��
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
void Route::Route_ProcFunc()
{
    CELL tmp;
    CELL OldData;
    USHORT dest;
    USHORT outlink;
    UINT type;
    
    while(1)
    {
        /* �ȴ�valid �ź����� */
        do {
            wait();
        }while(IN_Valid != true);
        
        OUT_Valid = false;
        tmp = IN_Packet.read();
        if(!(tmp == OldData))
        {
            OldData = IN_Packet.read();
            type = IN_Type.read();

            switch(type)
            {
                case CellType::Unicast:
                {
                    cout << "Route: processing   1  ~" << "  dest: " << dest << endl;
                    dest = tmp.dest_id;
                    if(UnicastSearch(dest, &outlink) == 0)
                    {
                        cout << "Route: processing   2  ~" << "  outlink: " << outlink << endl;
                        OUT_Link.write(outlink);
                        OUT_Packet.write(tmp);
                        OUT_Type.write(type);
                        OUT_Valid = true;
                    }
                    break;
                }
                case CellType::Multicast:
                /* �鲥��δ���� */
                    break;
                case CellType::Empty:
                {
                    if(g_uiLastTimeslot < tmp.fts)
                    {
                        tmp.fts = g_uiLastTimeslot;
                    }
                    OUT_Packet.write(tmp);
                    OUT_Type.write(type);
                    OUT_Valid = true;
                    break;
                }
                default:
                    cout << "Route: cell type is not supported.\n";
            }
            g_uiLastTimeslot = tmp.fts;

            ulBlockCount++;
            OUT_Count.write(ulBlockCount);
        }
    }
}

/*****************************************************************************
 Func Name    : Update::Update_Route_Thread0()
 Date Created : 2020/12/16
 Author       : 
 Description  : ROUTEģ�鶨��Ŀ�����Ԫ����ʵ��
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID Update::Update_ProcFunc()
{
    INT ret;
    BOOL bRC = FALSE;
        
    while(TRUE)
    {
        /* �ȴ�valid �ź����� */
        do {
            wait();
        }while(IN_Valid != true);

        bRC = IN_RC.read();
        USHORT usLink= IN_Link.read();
        USHORT usDest = RouteTable[ usLink ].usDestination;
        cout << "Update:link " << usLink << endl;
        if ( bRC )
        {
            ret = BitMapSet( &UnicastRouteTable[ usDest ].ulLinkValid, usLink );
        }
        else
        {
            cout << "link " << usLink << " cannot reach dest " << usDest << endl;
        }
    }
}

