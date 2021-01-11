/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              switch_RxMac.cpp
   Project Code: F-Switch
   Module Name : RX MAC
   Date Created: 2020-11-12
   Author      : pengying21074
   Description : RX MACģ��ʵ��

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
 Description  : ������Ԫtimeslot�������
 Input        : vector<CELL> & Dest     Ŀ�����
                CELL InsertData         �������cell
 Output       : NONE
 Return       : �������
 Caution      :
*****************************************************************************/
INT UpdateList(std::vector<CELL> & Dest, CELL InsertData)
{
    std::vector<CELL>::iterator it;

    /* ����Ϊ��ʱֱ����� */
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
    /* ����timeslot */
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
 Description  : Rxģ�鶨���processʵ��
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
            /* ��Ԫ��ʽ�ֶ�type ��bit3Ϊ0��ʾ������Ԫ,Ϊ1��ʾ������Ԫ */
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
                /* �����ݽ��л��� */
                UpdateList(SortQ, InData);
                Rx_DataCount++;
                OUT_Rx_Data.write(Rx_DataCount);
                if(SortQ.size() != 0)
                {
                    /* ��SortQ�еĵ�һ��Ԫ�ظ�OutData */
                    OutData = SortQ[0];
                    
                    /* �ӻ�����ɾ����һ��Ԫ�� */
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

