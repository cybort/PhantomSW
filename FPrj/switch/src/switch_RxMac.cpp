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
void RxMac::RxMac_ProcPlane0Func()
{
    CELL InData, OutData;
    sc_uint<4> type_bit4;
    std::vector<CELL> SortQ;
    while(1)
    {
        wait();
        if(IN_ProcPlane0->num_available() > 0)
        {
            OUT_Valid0 = false;
            OUT_Ctl_Valid0 = false;
            IN_ProcPlane0->read(InData);
            //cout << "RX: plane0 receive cell" << "  size :" << sizeof(InData.raw_data) << endl;

            mutex.lock();
            uiCount++;
            mutex.unlock();

            type_bit4 = InData.type;
            /* ��Ԫ��ʽ�ֶ�type ��bit3Ϊ0��ʾ������Ԫ,Ϊ1��ʾ������Ԫ */
            if(type_bit4[3] )
            {
                USHORT usLink = IN_Link0.read();

                OUT_Ctl_Type0.write(type_bit4);
                OUT_Ctl_Packet0.write(InData);
                OUT_Ctl_Valid0 = true;
                OUT_Ctl_Link0.write( usLink );
                cout << "RxMac: Control Cell: " << type_bit4 << "   link: " << usLink << endl;
            }
            else
            {
                /* �����ݽ��л��� */
                UpdateList(SortQ, InData);
                if(SortQ.size() != 0)
                {
                    OutData = SortQ[0];//��SortQ�еĵ�һ��Ԫ�ظ�OutData
                    /* �ӻ�����ɾ����һ��Ԫ�� */
                    SortQ.erase(SortQ.begin());
                    //cout << "  Data Cell: " << type_bit4 << "   size: " << sizeof(OutData) << endl;
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
 Description  : Rxģ�鶨���processʵ��
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
    
    while(1)
    {
        wait();
        if(IN_ProcPlane1->num_available() > 0)
        {
            OUT_Valid1 = false;
            OUT_Ctl_Valid1 = false;
            IN_ProcPlane1->read(InData);
            //cout << "RX: plane1 receive cell" << "  size :" << sizeof(InData.raw_data) << endl;

            mutex.lock();
            uiCount++;
            mutex.unlock();

            type_bit4 = InData.type;
            /* ��Ԫ��ʽ�ֶ�type ��bit3Ϊ0��ʾ������Ԫ,Ϊ1��ʾ������Ԫ */
            if (type_bit4[3])
            {
                USHORT usLink = IN_Link1.read();

                OUT_Ctl_Type1.write(type_bit4);
                OUT_Ctl_Packet1.write(InData);
                OUT_Ctl_Valid1 = true;
                OUT_Ctl_Link1.write( usLink );
                //cout << "RxMac: Control Cell: " << type_bit4 << "   size: " << sizeof(InData) << endl;
            }
            else
            {
                /* �����ݽ��л��� */
                UpdateList(SortQ, InData);
                if(SortQ.size() != 0)
                {
                    OutData = SortQ[0];
                    /* �ӻ�����ɾ����һ��Ԫ�� */
                    SortQ.erase(SortQ.begin());
                    //cout << "  Data Cell: " << type_bit4 << "   size: " << sizeof(OutData) << endl;
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
 Description  : Rxģ�鶨���processʵ��
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
    
    while(1)
    {
        wait();
        if(IN_ProcPlane2->num_available() > 0)
        {
            OUT_Valid2 = false;
            OUT_Ctl_Valid2 = false;
            IN_ProcPlane2->read(InData);
            //cout << "RX: plane2 receive cell" << "  size :" << sizeof(InData.raw_data) << endl;
            
            mutex.lock();
            uiCount++;
            mutex.unlock();

            type_bit4 = InData.type;
            /* ��Ԫ��ʽ�ֶ�type ��bit3Ϊ0��ʾ������Ԫ,Ϊ1��ʾ������Ԫ */
            if (type_bit4[3])
            {
                USHORT usLink = IN_Link0.read();

                OUT_Ctl_Type2.write(type_bit4);
                OUT_Ctl_Packet2.write(InData);
                OUT_Ctl_Valid2 = true;
                OUT_Ctl_Link2.write( usLink );
                //cout << "RxMac: Control Cell: " << type_bit4 << "   size: " << sizeof(InData) << endl;
            }
            else
            {
                UpdateList(SortQ, InData);
                if(SortQ.size() != 0)
                {
                    OutData = SortQ[0];
                    /* �ӻ�����ɾ����һ��Ԫ�� */
                    SortQ.erase(SortQ.begin());
                    //cout << "  Data Cell: " << type_bit4 << "   size: " << sizeof(OutData) << endl;
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
 Description  : Rxģ�鶨���processʵ��
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
    
    while(1)
    {
        wait();
        if(IN_ProcPlane3->num_available() > 0)
        {
            OUT_Valid3 = false;
            OUT_Ctl_Valid3 = false;
            IN_ProcPlane3->read(InData);
            //cout << "RX: plane3 receive cell" << "  size :" << sizeof(InData.raw_data) << endl;

            mutex.lock();
            uiCount++;
            mutex.unlock();

            type_bit4 = InData.type;
            /* ��Ԫ��ʽ�ֶ�type ��bit3Ϊ1��ʾ������Ԫ,Ϊ0��ʾ������Ԫ */
            if ( type_bit4[3] )
            {
                USHORT usLink = IN_Link0.read();

                OUT_Ctl_Type3.write(type_bit4);
                OUT_Ctl_Packet3.write(InData);
                OUT_Ctl_Valid3 = true;
                OUT_Ctl_Link3.write( usLink );
                //cout << "RxMac: Control Cell: " << type_bit4 << "   size: " << sizeof(InData) << endl;
            }
            else
            {
                /* �����ݽ��л��� */
                UpdateList(SortQ, InData);
                if(SortQ.size() != 0)
                {
                    OutData = SortQ[0];
                    /* �ӻ�����ɾ����һ��Ԫ�� */
                    SortQ.erase(SortQ.begin());
                    //cout << "  Data Cell: " << type_bit4 << "   size: " << sizeof(OutData) << endl;

                    type_bit4 = OutData.type;
                    OUT_Type3.write(type_bit4);
                    OUT_Packet3.write(OutData);
                    OUT_Valid3 = true;
                }
            }
        }
    }
}
