/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              switch_cfu.cpp
   Project Code: F-Switch
   Module Name : CFU
   Date Created: 2020-12-15
   Author      : 
   Description : ������Ԫ�ַ�ʵ��

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
#include "switch_cfu.h"

using std:: cout;
using std:: endl;

/*****************************************************************************
 Func Name    : Cfu::Cfu_Ctl_Thread0()
 Date Created : 2020/12/15
 Author       : 
 Description  : ROUTEģ�鶨��Ŀ�����Ԫ����ʵ��
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID Cfu::Cfu_Ctl_Thread0()
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
        }while(IN_Ctl_Valid0 != true);
        
        OUT_Ctl_Valid0 = false;
        OUT_Valid0 = false;
        tmp = IN_Ctl_Packet0.read();
        if(!(tmp == OldData))
        {
            OldData = IN_Ctl_Packet0.read();
            type = IN_Ctl_Type0.read();

            switch(type)
            {
                case CellType::FlowSts:/*��������ֱ�Ӳ��ת�����뵥��������ͬ*/
                {
                    cell_flowsts cell_f;
                    tmp.extract(cell_f);
                    dest = cell_f.dest_id();
                    if(UnicastSearch(dest, &outlink) == 0)
                    {
                        OUT_Ctl_Link0.write(outlink);
                        OUT_Ctl_Packet0.write(tmp);
                        OUT_Ctl_Type0.write(type);
                        OUT_Ctl_Valid0 = true;
                    }
                    break;
                }
                case CellType::Credit:
                {
                    cell_credit cell_c;
                    tmp.extract(cell_c);
                    dest = cell_c.dest_id();
                    if(UnicastSearch(dest, &outlink) == 0)
                    {
                        OUT_Ctl_Link0.write(outlink);
                        OUT_Ctl_Packet0.write(tmp);
                        OUT_Ctl_Type0.write(type);
                        OUT_Ctl_Valid0 = true;
                    }
                    break;
                }
                case CellType::Route:
                {
                    cell_route cell_r;
                    tmp.extract(cell_r);
                    
                    BOOL blinkrc = cell_r.route_connect();/*��·�Ƿ�ɴ�*/
                    USHORT usDestId = cell_r.dest_id();
                    USHORT usLink = cell_r.source_link() + usDestId * 18;

                    /*�������Ϣ���ݸ�Update������·�ɱ�*/
                    OUT_Dest0.write( usDestId );
                    OUT_Link0.write( usLink );
                    OUT_RC0.write( blinkrc );
                    OUT_Valid0.write( true );

                    /*
                        1.�����Ӧ�ֶ�
                        2.���ݸ�TXMacģ�飬������������·
                    */
                    cell_r.source_id(0); //switch0
                    cell_r.source_type( SourceType::FE1 );
                    
                    OUT_Ctl_Packet0.write(tmp);
                    OUT_Ctl_Type0.write(type);
                    //OUT_Ctl_Link0.write(0);
                    OUT_Ctl_Valid0 = true;

                    break;
                }
                default:
                    cout << "CFU: cell type is not supported in CFU.\n";
            }
        }
    }
}

/*****************************************************************************
 Func Name    : Cfu::Cfu_Ctl_Thread1()
 Date Created : 2020/12/15
 Author       : 
 Description  : ROUTEģ�鶨��Ŀ�����Ԫ����ʵ��
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID Cfu::Cfu_Ctl_Thread1()
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
        }while(IN_Ctl_Valid1 != true);
        
        OUT_Ctl_Valid1 = false;
        OUT_Valid1 = false;
        tmp = IN_Ctl_Packet1.read();
        if(!(tmp == OldData))
        {
            OldData = IN_Ctl_Packet1.read();
            type = IN_Ctl_Type1.read();

            switch(type)
            {
                case CellType::FlowSts:/*��������ֱ�Ӳ��ת�����뵥��������ͬ*/
                {
                    cell_flowsts cell_f;
                    tmp.extract(cell_f);

                    dest = cell_f.dest_id();
                    if(UnicastSearch(dest, &outlink) == 0)
                    {
                        OUT_Ctl_Link1.write(outlink);
                        OUT_Ctl_Packet1.write(tmp);
                        OUT_Ctl_Type1.write(type);
                        OUT_Ctl_Valid1 = true;
                    }
                    break;
                }
                case CellType::Credit:
                {
                    cell_credit cell_c;
                    tmp.extract(cell_c);

                    dest = cell_c.dest_id();
                    if(UnicastSearch(dest, &outlink) == 0)
                    {
                        OUT_Ctl_Link1.write(outlink);
                        OUT_Ctl_Packet1.write(tmp);
                        OUT_Ctl_Type1.write(type);
                        OUT_Ctl_Valid1 = true;
                    }
                    break;
                }
                case CellType::Route:
                {
                    cell_route cell_r;
                    tmp.extract(cell_r);
                    
                    BOOL blinkrc = cell_r.route_connect();/*��·�Ƿ�ɴ�*/
                    USHORT usDestId = cell_r.dest_id();
                    USHORT usLink = cell_r.source_link() + usDestId * 18;

                    /*�������Ϣ���ݸ�Update������·�ɱ�*/
                    OUT_Dest1.write( usDestId );
                    OUT_Link1.write( usLink );
                    OUT_RC1.write( blinkrc );
                    OUT_Valid1.write( true );

                    /*
                        1.�����Ӧ�ֶ�
                        2.���ݸ�TXMacģ�飬������������·
                    */
                    cell_r.source_id(0); //switch0
                    cell_r.source_type( SourceType::FE1 );

                    OUT_Ctl_Packet1.write(tmp);
                    OUT_Ctl_Type1.write(type);
                    //OUT_Ctl_Link1.write(0);
                    OUT_Ctl_Valid1 = true;
                    break;
                }
                default:
                    cout << "CFU: cell type is not supported in CFU.\n";
            }
        }
    }
}

/*****************************************************************************
 Func Name    : Cfu::Cfu_Ctl_Thread2()
 Date Created : 2020/12/15
 Author       : 
 Description  : ROUTEģ�鶨��Ŀ�����Ԫ����ʵ��
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID Cfu::Cfu_Ctl_Thread2()
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
        }while(IN_Ctl_Valid2 != true);
        
        OUT_Ctl_Valid2 = false;
        OUT_Valid2 = false;
        tmp = IN_Ctl_Packet2.read();
        if(!(tmp == OldData))
        {
            OldData = IN_Ctl_Packet2.read();
            type = IN_Ctl_Type2.read();

            switch(type)
            {
                case CellType::FlowSts:/*��������ֱ�Ӳ��ת�����뵥��������ͬ*/
                {
                    cell_flowsts cell_f;
                    tmp.extract(cell_f);
                    dest = cell_f.dest_id();
                    if(UnicastSearch(dest, &outlink) == 0)
                    {
                        OUT_Ctl_Link2.write(outlink);
                        OUT_Ctl_Packet2.write(tmp);
                        OUT_Ctl_Type2.write(type);
                        OUT_Ctl_Valid2 = true;
                    }
                    break;
                }
                case CellType::Credit:
                {
                    cell_credit cell_c;
                    tmp.extract(cell_c);
                    dest = cell_c.dest_id();
                    if(UnicastSearch(dest, &outlink) == 0)
                    {
                        OUT_Ctl_Link2.write(outlink);
                        OUT_Ctl_Packet2.write(tmp);
                        OUT_Ctl_Type2.write(type);
                        OUT_Ctl_Valid2 = true;
                    }
                    break;
                }
                case CellType::Route:
                {
                    cell_route cell_r;
                    tmp.extract(cell_r);
                    
                    BOOL blinkrc = cell_r.route_connect();/*��·�Ƿ�ɴ�*/
                    USHORT usDestId = cell_r.dest_id();
                    USHORT usLink = cell_r.source_link() + usDestId * 18;

                    /*�������Ϣ���ݸ�Update������·�ɱ�*/
                    OUT_Dest2.write( usDestId );
                    OUT_Link2.write( usLink );
                    OUT_RC2.write( blinkrc );
                    OUT_Valid2.write( true );

                    /*
                        1.�����Ӧ�ֶ�
                        2.���ݸ�TXMacģ�飬������������·
                    */
                    cell_r.source_id(0); //switch0
                    cell_r.source_type( SourceType::FE1 );

                    OUT_Ctl_Packet2.write(tmp);
                    OUT_Ctl_Type2.write(type);
                    //OUT_Ctl_Link2.write(0);
                    OUT_Ctl_Valid2 = true;
                    break;
                }
                default:
                    cout << "CFU: cell type is not supported in CFU.\n";
            }
        }
    }
}

/*****************************************************************************
 Func Name    : Cfu::Cfu_Ctl_Thread3()
 Date Created : 2020/12/15
 Author       : 
 Description  : ROUTEģ�鶨��Ŀ�����Ԫ����ʵ��
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID Cfu::Cfu_Ctl_Thread3()
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
        }while(IN_Ctl_Valid3 != true);
        
        OUT_Ctl_Valid3 = false;
        OUT_Valid3 = false;
        tmp = IN_Ctl_Packet3.read();
        if(!(tmp == OldData))
        {
            OldData = IN_Ctl_Packet3.read();
            type = IN_Ctl_Type3.read();

            switch(type)
            {
                case CellType::FlowSts:/*��������ֱ�Ӳ��ת�����뵥��������ͬ*/
                {
                    cell_flowsts cell_f;
                    tmp.extract(cell_f);
                    dest = cell_f.dest_id();
                    if(UnicastSearch(dest, &outlink) == 0)
                    {
                        OUT_Ctl_Link3.write(outlink);
                        OUT_Ctl_Packet3.write(tmp);
                        OUT_Ctl_Type3.write(type);
                        OUT_Ctl_Valid3 = true;
                    }
                    break;
                }
                case CellType::Credit:
                {
                    cell_credit cell_c;
                    tmp.extract(cell_c);
                    dest = cell_c.dest_id();
                    if(UnicastSearch(dest, &outlink) == 0)
                    {
                        OUT_Ctl_Link3.write(outlink);
                        OUT_Ctl_Packet3.write(tmp);
                        OUT_Ctl_Type3.write(type);
                        OUT_Ctl_Valid3 = true;
                    }
                    break;
                }
                case CellType::Route:
                {
                    cell_route cell_r;
                    tmp.extract(cell_r);

                    BOOL blinkrc = cell_r.route_connect();/*��·�Ƿ�ɴ�*/
                    USHORT usDestId = cell_r.dest_id();
                    USHORT usLink = cell_r.source_link() + usDestId * 18;

                    /*�������Ϣ���ݸ�Update������·�ɱ�*/
                    OUT_Dest3.write( usDestId );
                    OUT_Link3.write( usLink );
                    OUT_RC3.write( blinkrc );
                    OUT_Valid3.write( true );

                    /*
                        1.�����Ӧ�ֶ�
                        2.���ݸ�TXMacģ�飬������������·
                    */
                    cell_r.source_id(0); //switch0
                    cell_r.source_type( SourceType::FE1 );

                    OUT_Ctl_Packet3.write(tmp);
                    OUT_Ctl_Type3.write(type);
                    //OUT_Ctl_Link3.write(0);
                    OUT_Ctl_Valid3 = true;
                    break;
                }
                default:
                    cout << "CFU: cell type is not supported in CFU.\n";
            }
        }
    }
}

