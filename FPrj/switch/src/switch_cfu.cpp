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
        }while(IN_Ctl_Valid != true);
        
        OUT_Ctl_Valid = false;
        OUT_Valid = false;
        tmp = IN_Ctl_Packet.read();
        if(!(tmp == OldData))
        {
            cout << "CFU: receive  control cell.\n";
            OldData = IN_Ctl_Packet.read();
            type = IN_Ctl_Type.read();

            switch(type)
            {
                case CellType::FlowSts:/*��������ֱ�Ӳ��ת�����뵥��������ͬ*/
                {
                    cell_flowsts cell_f;
                    memset(cell_f.raw_data, 0, sizeof(cell_f.raw_data));
                    tmp.extract(cell_f);
                    dest = cell_f.dest_id();
                    cout << "CFU(flow): processing   1  ~" << "  dest: " << dest << endl;
                    if(UnicastSearch(dest, &outlink) == 0)
                    {
                        cout << "CFU(flow): processing   2  ~" << "  outlink: " << outlink << endl;
                        OUT_Ctl_Link.write(outlink);
                        OUT_Ctl_Packet.write(tmp);
                        OUT_Ctl_Type.write(type);
                        OUT_Ctl_Valid = true;
                    }
                    ulBlockDataCount++;
                    OUT_DATA.write(ulBlockDataCount);
                    break;
                }
                case CellType::Credit:
                {
                    cell_credit cell_c;
                    memset(cell_c.raw_data, 0, sizeof(cell_c.raw_data));
                    tmp.extract(cell_c);
                    dest = cell_c.dest_id();
                    cout << "CFU(credit): processing   1  ~" << "  dest: " << dest << endl;
                    if(UnicastSearch(dest, &outlink) == 0)
                    {
                        cout << "CFU(credit): processing   2  ~" << "  outlink: " << outlink << endl;
                        OUT_Ctl_Link.write(outlink);
                        OUT_Ctl_Packet.write(tmp);
                        OUT_Ctl_Type.write(type);
                        OUT_Ctl_Valid = true;
                    }
                    ulBlockCount++;
                    OUT_CRDT.write(ulBlockCount);
                    break;
                }
                case CellType::Route:
                {
                    cell_route cell_r;
                    memset(cell_r.raw_data, 0, sizeof(cell_r.raw_data));
                    tmp.extract(cell_r);
                    
                    BOOL blinkrc = cell_r.route_connect();/*��·�Ƿ�ɴ�*/
                    USHORT usDestId = cell_r.dest_id();
                    USHORT usLink = cell_r.source_link() + usDestId * 18;

                    /*�������Ϣ���ݸ�Update������·�ɱ�*/
                    OUT_Dest.write( usDestId );
                    OUT_Link.write( usLink );
                    OUT_RC.write( blinkrc );
                    OUT_Valid.write( true );
                    cout << "CFU(route): out route cell. link " << usLink << endl;

                    /*
                        1.�����Ӧ�ֶ�
                        2.���ݸ�TXMacģ�飬������������·
                    */
                    cell_r.source_id(0); //switch0
                    cell_r.source_type( SourceType::FE1 );
                    
                    OUT_Ctl_Packet.write(tmp);
                    OUT_Ctl_Type.write(type);
                    //OUT_Ctl_Link0.write(0);
                    OUT_Ctl_Valid = true;

                    break;
                }
                default:
                    cout << "CFU: cell type is not supported in CFU.\n";
            }
        }
    }
}


