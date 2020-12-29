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
VOID TxMac:: TxMac_Thread0()
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
        }while(IN_Valid0 == false);

        InData = IN_Packet0.read();
        if(!(InData == Old))
        {
            Old = IN_Packet0.read();
            Type = IN_Type0.read();
            Link = IN_Link0.read();
            Bitmap = IN_Bitmap0.read();

            OutData.type = Type;
            OutData.link = Link;
            OutData.bitmap = Bitmap;
            memcpy(OutData.cell.raw_data, InData.raw_data, sizeof(OutData.cell.raw_data));

            mutex.lock();
            OUT_Packet0->write(OutData);
            mutex.unlock();
        }
    }
}

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
VOID TxMac:: TxMac_Thread1()
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
        }while(IN_Valid1 == false);

        InData = IN_Packet1.read();
        if(!(InData == Old))
        {
            Old = IN_Packet1.read();
            Type = IN_Type1.read();
            Link = IN_Link1.read();
            Bitmap = IN_Bitmap1.read();

            OutData.type = Type;
            OutData.link = Link;
            OutData.bitmap = Bitmap;
            memcpy(OutData.cell.raw_data, InData.raw_data, sizeof(OutData.cell.raw_data));

            mutex.lock();
            OUT_Packet0->write(OutData);
            mutex.unlock();
        }
    }
}

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
VOID TxMac:: TxMac_Thread2()
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
        }while(IN_Valid2 == false);

        InData = IN_Packet2.read();
        if(!(InData == Old))
        {
            Old = IN_Packet2.read();
            Type = IN_Type2.read();
            Link = IN_Link2.read();
            Bitmap = IN_Bitmap2.read();

            OutData.type = Type;
            OutData.link = Link;
            OutData.bitmap = Bitmap;
            memcpy(OutData.cell.raw_data, InData.raw_data, sizeof(OutData.cell.raw_data));

            mutex.lock();
            OUT_Packet0->write(OutData);
            mutex.unlock();
        }
    }
}

/*****************************************************************************
 Func Name    : TxMac:: TxMac_Thread3()
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : Tx模块定义的process实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID TxMac:: TxMac_Thread3()
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
        }while(IN_Valid3 == false);

        InData = IN_Packet3.read();
        if(!(InData == Old))
        {
            Old = IN_Packet3.read();
            Type = IN_Type3.read();
            Link = IN_Link3.read();
            Bitmap = IN_Bitmap3.read();

            OutData.type = Type;
            OutData.link = Link;
            OutData.bitmap = Bitmap;
            memcpy(OutData.cell.raw_data, InData.raw_data, sizeof(OutData.cell.raw_data));

            mutex.lock();
            OUT_Packet0->write(OutData);
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
VOID TxMac:: TxMac_Ctl_Thread0()
{
    PACKET OutData;
    CELL InData, Old;
    sc_uint<4> Type;
    UCHAR Link;

    while(1)
    {
        do {
            wait();
        }while(IN_Ctl_Valid0 == false);
        InData = IN_Ctl_Packet0.read();
        if(!(InData == Old))
        {
            Old = IN_Ctl_Packet0.read();
            Type = IN_Ctl_Type0.read();
            Link = IN_Ctl_Link0.read();

            OutData.type = Type;
            OutData.link = Link;
            memcpy(OutData.cell.raw_data, InData.raw_data, sizeof(OutData.cell.raw_data));

            mutex.lock();
            OUT_Packet0->write(OutData);
            mutex.unlock();
        }
    }
}

/*****************************************************************************
 Func Name    : TxMac:: TxMac_Ctl_Thread1()
 Date Created : 2020/12/15
 Author       : 
 Description  : Tx模块定义的process实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID TxMac:: TxMac_Ctl_Thread1()
{
    PACKET OutData;
    CELL InData, Old;
    sc_uint<4> Type;
    UCHAR Link;

    while(1)
    {
        do {
            wait();
        }while(IN_Ctl_Valid1 == false);

        InData = IN_Ctl_Packet1.read();
        if(!(InData == Old))
        {
            Old = IN_Ctl_Packet1.read();
            Type = IN_Ctl_Type1.read();
            Link = IN_Ctl_Link1.read();

            OutData.type = Type;
            OutData.link = Link;
            memcpy(OutData.cell.raw_data, InData.raw_data, sizeof(OutData.cell.raw_data));

            mutex.lock();
            OUT_Packet0->write(OutData);
            mutex.unlock();
        }
    }
}

/*****************************************************************************
 Func Name    : TxMac:: TxMac_Ctl_Thread2()
 Date Created : 2020/12/15
 Author       : 
 Description  : Tx模块定义的process实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID TxMac:: TxMac_Ctl_Thread2()
{
    PACKET OutData;
    CELL InData, Old;
    sc_uint<4> Type;
    UCHAR Link;

    while(1)
    {
        do {
            wait();
        }while(IN_Ctl_Valid2 == false);

        InData = IN_Ctl_Packet2.read();
        if(!(InData == Old))
        {
            Old = IN_Ctl_Packet2.read();
            Type = IN_Ctl_Type2.read();
            Link = IN_Ctl_Link2.read();

            OutData.type = Type;
            OutData.link = Link;
            memcpy(OutData.cell.raw_data, InData.raw_data, sizeof(OutData.cell.raw_data));

            mutex.lock();
            OUT_Packet0->write(OutData);
            mutex.unlock();
        }
    }
}

/*****************************************************************************
 Func Name    : TxMac:: TxMac_Ctl_Thread3()
 Date Created : 2020/12/15
 Author       : 
 Description  : Tx模块定义的process实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID TxMac:: TxMac_Ctl_Thread3()
{
    PACKET OutData;
    CELL InData, Old;
    sc_uint<4> Type;
    UCHAR Link;

    while(1)
    {
        do {
            wait();
        }while(IN_Ctl_Valid3 == false);

        InData = IN_Ctl_Packet3.read();
        if(!(InData == Old))
        {
            Old = IN_Ctl_Packet3.read();
            Type = IN_Ctl_Type3.read();
            Link = IN_Ctl_Link3.read();

            OutData.type = Type;
            OutData.link = Link;
            memcpy(OutData.cell.raw_data, InData.raw_data, sizeof(OutData.cell.raw_data));

            mutex.lock();
            OUT_Packet0->write(OutData);
            mutex.unlock();
        }
    }
}

