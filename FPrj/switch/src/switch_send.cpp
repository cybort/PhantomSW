#include <iostream>
#include <string>
#include <cstring>
/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              switch_TxMac.cpp
   Project Code: F-Switch
   Module Name : ROUTE
   Date Created: 2020-11-12
   Author      : pengying21074
   Description : TX MAC模块实现

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#include "systemc.h"
#include "prv_deftype.h"
#include "switch_cell.h"
#include "common.h"
#include "switch_send.h"
#include "switch_route.h"
#include "base64.h"

#define MAX_TRANSMIT_LINK    36

extern ROUTE_S RouteTable[];

using std:: cout;
using std:: endl;
using std:: string;

ULONG g_ulLinkUsedStatus = 0xfffffffff;

VOID UpdateLinkStatus(USHORT usLink, BOOL_T bStatus)
{
    if(bStatus)
    {
        BitMapSet(&g_ulLinkUsedStatus, usLink);
    }
    else
    {
        BitMapClear(&g_ulLinkUsedStatus, usLink);
    }
    return;
}


/*****************************************************************************
 Func Name    : EmptySearch
 Date Created : 
 Author       : 
 Description  : 
 Input        : USHORT dest     目的id
                
 Output       : USHORT *plink    指向出link 索引号
 Return       : 0       操作成功
                -1      操作失败
 Caution      :
*****************************************************************************/
INT EmptySearch(ULONG ulStatus, USHORT *plink)
{
    std::vector<USHORT> result;
    UINT result_size;
    UINT rand_port;

    srand(time(0));
    for(INT loop = 0; loop < MAX_LINKS; loop++)
    {
        /*空闲元查找路由，不需要看该链路是否有效*/
        if( BitMapValid(&ulStatus, loop) == true )
        {
            result.push_back(loop);
        }
    }

    result_size = result.size();
    if(0 == result_size)
    {
        cout << "EmptySearch: no link to send empty cell " << endl;
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
 Func Name    : TxMac:: Transmit_func_entry()
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : Tx模块定义的process实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID Transmit:: Transmit_FuncEntry()
{
    UINT uiLoop;
    INT iRet = ERROR_SUCCESS;
    PACKET InData;
    USHORT usOutLink;
    string strEncode;
    CHAR *pBuffer;
    UINT uiLen;
    UINT uiType;
    UINT uiAvaCell; /* 需要发送的cell个数 */

    SENDER Link[MAX_TRANSMIT_LINK] = {
                        SENDER("link0", 0),
                        SENDER("link1", 1),
                        SENDER("link2", 2),
                        SENDER("link3", 3),
                        SENDER("link4", 4),
                        SENDER("link5", 5),
                        SENDER("link6", 6),
                        SENDER("link7", 7),
                        SENDER("link8", 8),
                        SENDER("link9", 9),
                        SENDER("link10", 10),
                        SENDER("link11", 11),
                        SENDER("link12", 12),
                        SENDER("link13", 13),
                        SENDER("link14", 14),
                        SENDER("link15", 15),
                        SENDER("link16", 16),
                        SENDER("link17", 17),
                        SENDER("link18", 18),
                        SENDER("link19", 19),
                        SENDER("link20", 20),
                        SENDER("link21", 21),
                        SENDER("link22", 22),
                        SENDER("link23", 23),
                        SENDER("link24", 24),
                        SENDER("link25", 25),
                        SENDER("link26", 26),
                        SENDER("link27", 27),
                        SENDER("link28", 28),
                        SENDER("link29", 29),
                        SENDER("link30", 30),
                        SENDER("link31", 31),
                        SENDER("link32", 32),
                        SENDER("link33", 33),
                        SENDER("link34", 34),
                        SENDER("link35", 35)
                    };

    for(uiLoop = 0; uiLoop < MAX_TRANSMIT_LINK; uiLoop++)
    {
        iRet = Link[uiLoop].Connect();
        if(ERROR_FAILED == iRet )
        continue;
    }

    while(1)
    {
        do{
            wait();
        }while(IN_Packet0->num_available() == 0);

        uiAvaCell = IN_Packet0->num_available();
    //    cout << "Transmit num: " << uiAvaCell << endl;
        for(uiLoop = 0; uiLoop < uiAvaCell; uiLoop++)
        {
            IN_Packet0->read(InData);
            usOutLink = InData.link;
            uiType = InData.type;

            switch( uiType )
            {
                case CellType::Unicast:
                case CellType::Empty:
                {
                    strEncode = base64_encode((unsigned char *)InData.cell.raw_data, sizeof(InData.cell.raw_data));/* base64 编码 */
                    break;
                }
                case CellType::FlowSts:
                {
                    cell_flowsts cell_f;
                    InData.cell.extract(cell_f);
                    strEncode = base64_encode((unsigned char *)cell_f.raw_data, sizeof(cell_f.raw_data));/* base64 编码 */
                    break;
                }
                case CellType::Credit:
                {
                    cell_credit cell_c;
                    InData.cell.extract(cell_c);
                    strEncode = base64_encode((unsigned char *)cell_c.raw_data, sizeof(cell_c.raw_data));/* base64 编码 */
                    break;
                }
                case CellType::Route:
                {
                    cell_route cell_r;
                    InData.cell.extract(cell_r);
                    strEncode = base64_encode((unsigned char *)cell_r.raw_data, sizeof(cell_r.raw_data));/* base64 编码 */
                    break;
                }
                default:
                    cout << "Not supported!";
            }

            /* 发送buffer填充 */
            uiLen = strEncode.length();

            pBuffer = new char[uiLen + 1];
            memset(pBuffer, 0, uiLen + 1);

            strEncode.copy(pBuffer, uiLen);
            pBuffer[uiLen] = '\n';

            switch(uiType)
            {
                case CellType::Unicast: 
                case CellType::Credit:
                case CellType::FlowSts:
                {
                    Link[usOutLink].MsgSend(pBuffer, uiLen + 1);
                    UpdateLinkStatus(usOutLink, BOOL_FALSE);
                    break;
                }
                case CellType::Multicast:
                {
                    break;
                }
                case CellType::Empty:
                {
                    USHORT outlink;
                    if(EmptySearch(g_ulLinkUsedStatus, &outlink) == 0)
                    {
                        Link[outlink].MsgSend(pBuffer, uiLen + 1);
                        cout << "Send: Empty cell outlink  " << outlink << endl;
                    }
                    #if 0
                    for(uiLoop = 0; uiLoop < MAX_TRANSMIT_LINK; uiLoop++)
                    {
                        if(!(BitMapValid(&g_ulLinkUsedStatus, uiLoop)))
                        {
                            Link[uiLoop].MsgSend(pBuffer, uiLen + 1);
                            //cout << "Send: link  " << uiLoop << endl;
                        }
                    }
                    #endif
                    break;
                }
                case CellType::Route:
                {
                    for(uiLoop = 0; uiLoop < MAX_TRANSMIT_LINK; uiLoop++)/*向所有链路广播*/
                    {
                        Link[uiLoop].MsgSend(pBuffer, uiLen + 1);
                    }
                    break;
                }
                default:
                    cout << "Send: cell type is not defined.\n";
            }
            delete [] pBuffer;
        }
        g_ulLinkUsedStatus = 0xfffffffff;
    }
}
