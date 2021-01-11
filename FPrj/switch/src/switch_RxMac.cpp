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
 Func Name    : RxMac::RxMac_ProcPlane0Func
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : Rx模块定义的process实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
void RxMac::RxMac_ProcFunc()
{
    CELL InData, OutData;
    sc_uint<4> type_bit4;
    std::vector<CELL> SortQ;
    while(1)
    {
        wait();
        if(IN_ProcPlane->num_available() > 0)
        {
            OUT_Valid = false;
            OUT_Ctl_Valid = false;
            IN_ProcPlane->read(InData);
          //  cout << "RX: plane0 receive cell" << " . link :" << usLink << endl;
            ulBlockCount++;
            OUT_Rx_Block.write(ulBlockCount);

            mutex.lock();
            uiCount++;
            mutex.unlock();

            type_bit4 = InData.type;
            /* 信元格式字段type 的bit3为0表示数据信元,为1表示控制信元 */
            if(type_bit4[3] )
            {
                Rx_CtrCount++;
                OUT_Rx_Ctr.write(Rx_CtrCount);
                OUT_Ctl_Type.write(type_bit4);
                OUT_Ctl_Packet.write(InData);
                OUT_Ctl_Valid = true;
             //   cout << "RxMac: Control Cell: " << type_bit4 << endl;
            }
            else
            {
                /* 对数据进行缓存 */
                UpdateList(SortQ, InData);
                Rx_DataCount++;
                OUT_Rx_Data.write(Rx_DataCount);
                if(SortQ.size() != 0)
                {
                    /* 将SortQ中的第一个元素给OutData */
                    OutData = SortQ[0];
                    
                    /* 从缓存中删除第一个元素 */
                    SortQ.erase(SortQ.begin());
                    cout << "RxMac: Data Cell: " << type_bit4 << "   size: " << sizeof(OutData) << endl;
                    type_bit4 = OutData.type;
                    OUT_Type.write(type_bit4);
                    OUT_Packet.write(OutData);
                    OUT_Valid = true;
                }
            }
        }
    }
}

