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
#include "switch_TxMac.h"
#include "base64.h"

using std:: cout;
using std:: endl;
using std:: string;

/*****************************************************************************
 Func Name    : TxMac:: TxMac_Thread0()
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : Tx模块定义的process实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID TxMac:: TxMac_DataProcFunc()
{
    PACKET OutData;
    CELL InData, Old;
    sc_uint<4> Type;
    UCHAR Link;
    ULONG Bitmap;

    while(1)
    {
        do {
            wait();
        }while(IN_Valid == false);

        InData = IN_Packet.read();
        if(!(InData == Old))
        {
            cout << "Tx Mac: Recv data!" << "  type " << Type << endl;
            Old = IN_Packet.read();
            Type = IN_Type.read();
            Link = IN_Link.read();
            Bitmap = IN_Bitmap.read();

            OutData.type = Type;
            OutData.link = Link;
            OutData.bitmap = Bitmap;
            memcpy(OutData.cell.raw_data, InData.raw_data, CELL_FORMAT_SIZE);
            OUT_Count.write(ulCount);

            mutex.lock();
            OUT_Packet->write(OutData);
            cout << "fifo free:" << OUT_Packet->num_free() << endl;
            ulCount++;
            mutex.unlock();

        }
    }
}

/*****************************************************************************
 Func Name    : TxMac:: TxMac_Ctl_Thread0()
 Date Created : 2020/12/15
 Author       : 
 Description  : Tx模块定义的process实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID TxMac:: TxMac_ControlProcFunc()
{
    PACKET OutData;
    CELL InData, Old;
    sc_uint<4> Type;
    UCHAR Link;

    while(1)
    {
        do {
            wait();
        }while(IN_Ctl_Valid == false);
        InData = IN_Ctl_Packet.read();
        if(!(InData == Old))
        {
            Old = IN_Ctl_Packet.read();
            Type = IN_Ctl_Type.read();
            Link = IN_Ctl_Link.read();
//            cout << "Tx Mac: Recv data!" << "  type " << Type << endl;

            OutData.type = Type;
            OutData.link = Link;
            memcpy(OutData.cell.raw_data, InData.raw_data, CELL_FORMAT_SIZE);

            mutex.lock();
            OUT_Packet->write(OutData);
            ulCount++;
            mutex.unlock();
        }
    }
}

