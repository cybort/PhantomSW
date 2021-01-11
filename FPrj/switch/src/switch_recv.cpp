#include <iostream>
#include <cstdio>
/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              switch_recv.cpp
   Project Code: F-Switch
   Module Name : CELL
   Date Created: 2020-11-12
   Author      : pengying21074
   Description : ģ��serdes����ģ��ʵ��

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#include <cstring>
#include <string>

#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include "systemc.h"
#include "prv_deftype.h"
#include "switch_recv.h"
#include "common.h"
#include "switch_cell.h"
#include "base64.h"
#include "switch_route.h"

using std::cout;
using std::endl;
using std::string;

#define MAX_RECEIVE_LINK    (36)
#define MAX_PLANE           (4)
#define MAX_TIMEOUT_COUNT    50

#if 0
LINK_MAP_INFO_S g_astLinkMapInfo[MAX_PLANE] = 
{
    {
        .uiPlane = 0,
        .uiLinkNum = 9,
        .auiLinkList = {0, 1, 2, 3, 4, 5, 6, 7, 8},
    },
    {
        .uiPlane = 1,
        .uiLinkNum = 9,
        .auiLinkList = {9, 10, 11, 12, 13, 14, 15, 16, 17},
    },
    {
        .uiPlane = 2,
        .uiLinkNum = 9,
        .auiLinkList = {18, 19, 20, 21, 22, 23, 24, 25, 26},
    },
    {
        .uiPlane = 3,
        .uiLinkNum = 9,
        .auiLinkList = {27, 28, 29, 30, 31, 32, 33, 34, 35},
    }
};
#endif

LINK_MAP_INFO_S g_astLinkMapInfo[MAX_PLANE] = 
{
    {0, 9, {0, 1, 2, 3, 4, 5, 6, 7, 8}},
    {1, 9, {9, 10, 11, 12, 13, 14, 15, 16, 17}},
    {2, 9, {18, 19, 20, 21, 22, 23, 24, 25, 26}},
    {3, 9, {27, 28, 29, 30, 31, 32, 33, 34, 35}}
};    

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
STATIC SOCK_INFO_S g_stListenSocketParam = {{"10.114.220.169"}, 11023};

/* ����link,�жϴ�fd�Ƿ��Ǹ�link�����б��Ѵ���fd,���Ƿ��ظ�link������,���򷵻�-1*/
/*****************************************************************************
 Func Name    : VisitLink
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : ����link,�жϴ�fd�Ƿ��Ǹ�link�����б��Ѵ���fd,���Ƿ��ظ�link
                ������,���򷵻�-1
 Input        : PORT_LINK *pLink     ָ����жϵ�link
                INT Num              ������
                INT Fd               Ŀ��fd
 Output       : NONE
 Return       : �ɹ�: link������, ʧ��: -1
 Caution      :
*****************************************************************************/
INT VisitLink(PORT_LINK *pLink, INT Num, INT Fd)
{
    USHORT CurConnect;
    
    for(INT i = 0; i < Num; i++)
    {
        CurConnect = pLink[i].GetConnection();
        if(CurConnect == 0)
        {
            continue;
        }
        else
        {
            for(USHORT j = 0; j<CurConnect; j++)
            {
                if(Fd == pLink[i].GetConnectListEle(j))
                {
                    return pLink[i].GetIndex();
                }
            }
        }
    }
    return ERROR_FAILED;
}

/* ����link,�жϴ�fd�Ƿ��Ǹ�link�󶨵�fd,���Ƿ��ظ�link������,���򷵻�-1*/
/*****************************************************************************
 Func Name    : VisitLinkFd
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : ����link,�жϴ�fd�Ƿ��Ǹ�link�󶨵�fd,���Ƿ��ظ�link
                ������,���򷵻�-1
 Input        : PORT_LINK *pLink     ָ����жϵ�link
                INT Num              ������
                INT Fd               Ŀ��fd
 Output       : NONE
 Return       : �ɹ�: link������, ʧ��: -1
 Caution      :
*****************************************************************************/
INT VisitLinkFd(PORT_LINK *pLink, INT Num, INT Fd)
{
    for(INT i = 0; i < Num; i++)
    {
        if(Fd == pLink[i].GetFD())
        {
            return pLink[i].GetIndex();
        }
    }
    return ERROR_FAILED;
}

VOID ShowMem(UCHAR *pStart, UINT uiSize)
{
    UINT uiLoop = 0;
    UINT uiCnt = 0;
    UINT uiTotal = 0;
    UCHAR ucTemp;
    UINT i = 0;
    while( uiLoop < uiSize )
    {
        if(uiCnt == 0) 
        {
            if(uiLoop +11 < uiSize)
            printf(" %p - %p :",pStart+uiLoop, pStart+uiLoop+11);
            else
            printf(" %p - %p :",pStart+uiLoop, pStart+uiSize-1);
        }
        ucTemp = *(pStart + uiLoop);
        printf("%02X",ucTemp);
        uiCnt++;
        uiLoop++;
        i++;
        if( i == 4)
        {
            printf("  ");
            i =0;
        }
        if(uiCnt == 12)
        {
            printf("\n");
            uiCnt = 0;
        }
    }
    printf("\n");
    return;
}

/* ��ʾcell���� */
/*****************************************************************************
 Func Name    : DisplayPacket
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : ����debug������ʾcell����
 Input        : 
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID DisplayPacket(VOID *pInbuf, UINT uiSize)
{
    UINT *puiData;
    UINT uiRemainSize;
    USHORT usOffset = 0;
    INT iCount = 0;

    puiData = (UINT *)pInbuf;
    uiRemainSize = uiSize;

    while(uiRemainSize > 0)
    {
        cout.flags(std::ios::right|std::ios::hex);
        cout.width(8);
        cout.fill('0');
        cout << *puiData << " ";
        iCount++;
        puiData++;
        uiRemainSize -=4;
        if(iCount == 4)
        {
            iCount = 0;
            cout << endl;
        }
        if(uiRemainSize < 4)
        {
            break;
        }
    }
    cout << endl;

    
}

/*****************************************************************************
 Func Name    : GetLinkPlane
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : ��ȡ��linkӳ���ƽ����Ϣ
 Input        : UINT uiLink     link����
 Output       : NONE
 Return       : ƽ������
 Caution      :
*****************************************************************************/
UINT GetLinkPlane(UINT uiLink)
{
    UINT uiLoop, uiSubLoop;
    UINT uiNum;
    UINT *puiLinkList;

    for(uiLoop = 0; uiLoop < MAX_PLANE; uiLoop++)
    {
        uiNum = g_astLinkMapInfo[uiLoop].uiLinkNum;
        puiLinkList = g_astLinkMapInfo[uiLoop].auiLinkList;
        for(uiSubLoop = 0; uiSubLoop < uiNum; uiSubLoop++)
        {
            if(uiLink == puiLinkList[uiSubLoop])
            {
                return uiLoop;
            }
        }
    }
    return (MAX_PLANE);
}

/*****************************************************************************
 Func Name    : ReadOnSocket
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : ��ָ��fd��ȡ����ֱ��������������read buffer��
 Input        : 
 Output       : NONE
 Return       : ʣ����Ҫ��ȡ���ֽ���
 Caution      :
*****************************************************************************/
UINT ReadOnSocket(INT iFd, UINT uiDestSize, VOID *pBuf, UINT uiSize, CHAR Delim)
{
    CHAR cChar;
    CHAR *pcOutBuf = (CHAR *)pBuf;
    UINT uiCurPos = 0;

    memset(pcOutBuf, 0, uiSize);
    while(1)
    {
        if(read(iFd, &cChar, 1))
        {
            if((Delim != cChar) && (uiCurPos < uiSize))
            {
                pcOutBuf[uiCurPos++] = cChar;
            }
            else if(uiCurPos < uiSize)
            {
                pcOutBuf[uiCurPos++] = Delim;
                break;
            }
            else
            {
                cout << "Read buffer is full.\n";
                break;
            }
        }
        else
        {
            break;
        }
    }

    return uiCurPos;

}

/*****************************************************************************
 Func Name    : UpdateLinkValidStatus
 Date Created : 2020/12/23
 Author       : 
 Description  : Rxģ�鶨���processʵ��
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
    ret = BitMapSet( &g_ulLinkUpdatedStatus, usLink );/*��¼�Ѹ��¹�����·*/
    return;
}

/*****************************************************************************
 Func Name    : Receiver::Recv_func_entry
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : Recvģ�鶨��processʵ��
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID Receiver::Recv_ProcFunc(VOID)
{
    UINT uiLoop;
    INT iWakeUp;
    INT iRet = 0;
    INT iFd,iClientFd;
    UINT uiIndex = 0;
    INT iCtlRead;
    USHORT listen_port = 11023;
    CELL read_data;
    CHAR *pcReadBuf;
    INT MsgLink;
    string strDecode;  /* base64������ */
    UINT uiLen;
    UINT uiPlane;
    UINT uiRemain, uiReadSize;
    UINT uiTotalRead = 0;
    EVENT Notification = EVENT(100);    /* event �¼���Դ���������� */
    USHORT uiPlaneStatus = 0x7;//0x7-111,ÿ��bit����һ��BLOCK

    /* ����˿ڴ���,��ʵ�������� */
    PORT_LINK Link[MAX_RECEIVE_LINK] = {
        PORT_LINK("link0", 0),
        PORT_LINK("link1", 1),
        PORT_LINK("link2", 2),
        PORT_LINK("link3", 3),
        PORT_LINK("link4", 4),
        PORT_LINK("link5", 5),
        PORT_LINK("link6", 6),
        PORT_LINK("link7", 7),
        PORT_LINK("link8", 8),
        PORT_LINK("link9", 9),
        PORT_LINK("link10", 10),
        PORT_LINK("link11", 11),
        PORT_LINK("link12", 12),
        PORT_LINK("link13", 13),
        PORT_LINK("link14", 14),
        PORT_LINK("link15", 15),
        PORT_LINK("link16", 16),
        PORT_LINK("link17", 17),
        PORT_LINK("link18", 18),
        PORT_LINK("link19", 19),
        PORT_LINK("link20", 20),
        PORT_LINK("link21", 21),
        PORT_LINK("link22", 22),
        PORT_LINK("link23", 23),
        PORT_LINK("link24", 24),
        PORT_LINK("link25", 25),
        PORT_LINK("link26", 26),
        PORT_LINK("link27", 27),
        PORT_LINK("link28", 28),
        PORT_LINK("link29", 29),
        PORT_LINK("link30", 30),
        PORT_LINK("link31", 31),
        PORT_LINK("link32", 32),
        PORT_LINK("link33", 33),
        PORT_LINK("link34", 34),
        PORT_LINK("link35", 35),
    };

    /* event�¼���������ʼ�� */
    iRet = Notification.Init();
    if(iRet != ERROR_SUCCESS)
    {
        exit(1);
    }

    if(ParseSocketInfo( "switch_ip.txt", &g_stListenSocketParam, sizeof(g_stListenSocketParam.szAddr)) != ERROR_SUCCESS)
    {
        cout << "switch listen ip and port use default, ip :127.0.0.1, first port: 11024\n";
    }
    /* port��ʼ�� */
    for(uiLoop = 0; uiLoop < MAX_RECEIVE_LINK; uiLoop++)
    {
        /* port socket����������ָ���˿� */
        iRet = Link[uiLoop].LinkUp(++g_stListenSocketParam.usPort, g_stListenSocketParam.szAddr);
        if(0 != iRet)
        {
            cout << "Recv: Rx " << Link[uiLoop].GetName()<<" link up failed!!\n";
            continue;
        }

        /* port �󶨵�socket fd����event�¼��������ļ����б� */
        iRet = Notification.AddEvent(Link[uiLoop].GetFD());
        if(0 != iRet)
        {
            cout<<"Recv: listen "<<Link[uiLoop].GetName()<<" failed!!\n";
            continue;
        }
    }
    while(1)
    {
        wait(); /* ÿ�� ���һ��socket fd�Ƿ��л����¼� */

        /* �ȴ������ӵ�fd������,������÷�������ʽ */
        iRet = Notification.Wait();
        iWakeUp = Notification.GetWakeupEvent();

        /* �����ӵ�fd���л����¼�,���δ���ÿ�������ѵ��¼� */
        /* ��������Ļ����¼���3�����ͣ�
                1) ������socket fd�����µĿͻ�����������
                2) ������socket fd�пͻ��˷������ݵ�ĳfd
                3) remote �ر�socket����
        */
        if(iWakeUp > 0)
        {
            cout << "wakeup: " << iWakeUp << endl;
            for(uiLoop = 0; uiLoop < iWakeUp; uiLoop++)
            {
                iFd = Notification.WakeupList[uiLoop].data.fd;

                /* �����յ����ݵ�fd�󶨵�link,����fd������link�󶨵�fd�򷵻�ERROR_FAILED */
                uiIndex = VisitLinkFd(Link, sizeof(Link)/sizeof(Link[0]), iFd);
                
                /* new costumer connect to link */
                if( ERROR_FAILED != uiIndex)
                {
                    iClientFd = accept(iFd, NULL, NULL);
                    if(Link[uiIndex].UpdataConnectList(iClientFd, true) == ERROR_FAILED)
                    {
                        cout << "Recv: updata connect list failed!!\n";
                        continue;
                    }
                    /* ��accept()���ص����ں���clientͨ�ŵ�fd��������б� */
                    iRet = Notification.AddEvent(iClientFd);
                    if(ERROR_SUCCESS != iRet)
                    {
                        cout << "Recv: Rx " << Link[uiIndex].GetName()<< " accept new connection failed!!\n";
                    }
                }
                /* new message received on link */
                else
                {
                    /* Get link which the message from */
                    MsgLink = VisitLink(Link, sizeof(Link)/sizeof(Link[0]), iFd);
                    if(ERROR_FAILED == MsgLink)
                    {
                        cout << "Recv: new message received from undefined link\n";
                    }
                    else
                    {
                        ioctl(iFd,FIONREAD,&iCtlRead);
                        
                        /* ��socket�����ݿɶ������λ�������Ϊremote�ر�socket */
                        if(iCtlRead == 0)
                        {
                            if(ERROR_SUCCESS == Notification.DelEvent(iFd) &&
                                ERROR_SUCCESS == Link[MsgLink].UpdataConnectList(iFd, false))
                            {
                                close(iFd);
                                cout << "Recv: remove connection on Rx " << Link[MsgLink].GetName() << ", fd = " <<iFd<<endl;
                            }
                            else
                            {
                                cout << "Recv: remove connection Rx" << Link[MsgLink].GetName() << " failed, fd = " <<iFd<<endl;
                            }
                        }
                        
                        /* remote �������͹�����Ҫ�������� */
                        else
                        {
                            cout << "Recv: Rx " << Link[MsgLink].GetName() << " receive message :\n";
                            UpdateLinkValidStatus(MsgLink);

                           /* ������ʱ��������socket�������� */
                           pcReadBuf = new char[iCtlRead+1];
                           uiRemain = iCtlRead;
                           uiTotalRead = 0;
                           do {
                                uiReadSize = ReadOnSocket(iFd, uiRemain, pcReadBuf, iCtlRead+1, '\n');
                                uiTotalRead += uiReadSize;
                                uiRemain = iCtlRead - uiTotalRead;
                                pcReadBuf[uiReadSize] = '\0';
                                
                                /* ��Ҫ������һ���ַ��Ƿ�Ϊ���з�,������û��з� */
                                if('\n' == pcReadBuf[uiReadSize - 1])
                                {
                                    ulCount++;
                                    OUT_RecvOK.write(ulCount);
                                    /* �˴��հ���� */
                                     pcReadBuf[uiReadSize - 1] = '\0';
                                     /* decode  */
                                     strDecode = base64_decode(pcReadBuf);
                                     

                                     /* �������������ݵ�outdata�˿� */
                                     memset(read_data.raw_data, 0, CELL_FORMAT_SIZE);
                                     uiLen = strDecode.length();
                                     strDecode.copy(read_data.raw_data, uiLen);
                                     //cout << "Recv: RX Cell type : " << read_data.type << "  Cell Len: " << uiLen << "  rece len:" << iCtlRead << endl;

                                     //DisplayPacket(read_data.raw_data, sizeof(read_data.raw_data));
                                      /* ��cell ���浽fifo,��ͬ����ƽ��ʹ�ò�ͬfifo */
                                     uiPlane = GetLinkPlane(MsgLink);
                                     //cout << "Plane Index :" << uiPlane << "    PlaneStatus : " << uiPlaneStatus << endl;
                                      switch(uiPlane)
                                     {
                                         case 0:
                                             OUT_ProcPlane0->write(read_data);
                                             break;
                                         case 1:
                                            OUT_ProcPlane1->write(read_data);
                                            break;
                                         case 2:
                                             OUT_ProcPlane2->write(read_data);
                                             break;
                                         case 3:
                                             OUT_ProcPlane3->write(read_data);
                                             break;
                                         default:
                                            cout << "process plane not defined.\n";
                                     }
                                     //cout << "fifo: remain = " << OUT_Packet->num_free() << endl;
                                }
                                else
                                {
                                    cout << "Recv: receive cell failed\n";
                                  //  ulCountFail++;
                                  //  OUT_RecvFail.write(ulCountFail);
                                }
                            }while(uiRemain != 0);
                            /* �ͷŶ�̬������ڴ� */
                             delete [] pcReadBuf;
                        }
                    }
                }
            }
        }
    }
}

/*****************************************************************************
 Func Name    : Receiver::Recv_Update_LinkStatus()
 Date Created : 2020/12/15
 Author       : 
 Description  : ROUTEģ�鶨��Ŀ�����Ԫ����ʵ��
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID Receiver::Recv_Update_LinkStatus()
{
    USHORT usIndex;
    INT     ret = 0;

    /*���ж��Ƿ����µ�·����Ԫ���������·����Ϣ*/
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
        g_ulLinkUpdatedStatus = 0;/*����һ�ֺ�����*/
        for ( usIndex = 0; usIndex < sizeof(RouteTable)/sizeof(RouteTable[0]); usIndex++)
        {
            cout << "link id: " << RouteTable[ usIndex ].uiLinkId;
            cout << "     statue: " << RouteTable[ usIndex ].bLinkValid;
            cout << "     timeout: " << RouteTable[ usIndex ].usTimeOut << endl;
        }
        printf("link status : 0x%x\n", g_ulLinkAvailable );
        cout << endl;
    }
}


