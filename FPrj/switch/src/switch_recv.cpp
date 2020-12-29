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
   Description : 模拟serdes接收模块实现

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

using std::cout;
using std::endl;
using std::string;

#define MAX_RECEIVE_LINK    (36)
#define MAX_PLANE           (4)

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
    {0, 12, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}},
    {1, 12, {9, 10, 11, 12, 13, 14, 15, 16, 17}},
    {2, 12, {18, 19, 20, 21, 22, 23, 24, 25, 26}},
    {3, 9, {27, 28, 29, 30, 31, 32, 33, 34, 35}}
};    


/* 遍历link,判断此fd是否是该link连接列表已存在fd,若是返回该link索引号,否则返回-1*/
/*****************************************************************************
 Func Name    : VisitLink
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : 遍历link,判断此fd是否是该link连接列表已存在fd,若是返回该link
                索引号,否则返回-1
 Input        : PORT_LINK *pLink     指向待判断的link
                INT Num              连接数
                INT Fd               目标fd
 Output       : NONE
 Return       : 成功: link索引号, 失败: -1
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

/* 遍历link,判断此fd是否是该link绑定的fd,若是返回该link索引号,否则返回-1*/
/*****************************************************************************
 Func Name    : VisitLinkFd
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : 遍历link,判断此fd是否是该link绑定的fd,若是返回该link
                索引号,否则返回-1
 Input        : PORT_LINK *pLink     指向待判断的link
                INT Num              连接数
                INT Fd               目标fd
 Output       : NONE
 Return       : 成功: link索引号, 失败: -1
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

/* 显示cell内容 */
/*****************************************************************************
 Func Name    : DisplayPacket
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : 用于debug调试显示cell内容
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
 Description  : 获取此link映射的平面信息
 Input        : UINT uiLink     link索引
 Output       : NONE
 Return       : 平面索引
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
 Description  : 从指定fd读取数据直到遇到结束符或read buffer满
 Input        : 
 Output       : NONE
 Return       : 剩余需要读取的字节数
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
 Func Name    : Receiver::Recv_func_entry
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : Recv模块定义process实现
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID Receiver::Recv_FuncEntry(VOID)
{
    UINT uiLoop;
    INT iWakeUp;
    INT iRet = 0;
    INT iFd,iClientFd;
    UINT uiIndex = 0;
    INT iCtlRead;
    USHORT listen_port = 10023;
    CELL read_data;
    CHAR *pcReadBuf;
    INT MsgLink;
    string strDecode;  /* base64解码结果 */
    UINT uiLen;
    UINT uiPlane;
    UINT uiRemain, uiReadSize;
    UINT uiTotalRead = 0;
    EVENT Notification = EVENT(100);    /* event 事件资源监视器创建 */

    /* 虚拟端口创建,类实例化对象 */
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

    /* event事件监视器初始化 */
    iRet = Notification.Init();
    if(iRet != ERROR_SUCCESS)
    {
        exit(1);
    }

    /* port初始化 */
    for(uiLoop = 0; uiLoop < MAX_RECEIVE_LINK; uiLoop++)
    {
        /* port socket创建并监听指定端口 */
        iRet = Link[uiLoop].LinkUp(++listen_port);
        if(0 != iRet)
        {
            cout << "Recv: Rx " << Link[uiLoop].GetName()<<" link up failed!!\n";
            continue;
        }

        /* port 绑定的socket fd加入event事件监视器的监视列表 */
        iRet = Notification.AddEvent(Link[uiLoop].GetFD());
        if(0 != iRet)
        {
            cout<<"Recv: listen "<<Link[uiLoop].GetName()<<" failed!!\n";
            continue;
        }
    }
    while(1)
    {
        wait(); /* 每隔 检查一次socket fd是否有唤醒事件 */

        /* 等待被监视的fd被唤醒,这里采用非阻塞方式 */
        iRet = Notification.Wait();
        iWakeUp = Notification.GetWakeupEvent();

        /* 被监视的fd中有唤醒事件,依次处理每个被唤醒的事件 */
        /* 这里产生的唤醒事件有3种类型：
                1) 监听的socket fd中有新的客户端连接请求
                2) 监听的socket fd中客户端发送数据到某fd
                3) remote 关闭socket连接
        */
        if(iWakeUp > 0)
        {
            cout << "wakeup: " << iWakeUp << endl;
            for(uiLoop = 0; uiLoop < iWakeUp; uiLoop++)
            {
                iFd = Notification.WakeupList[uiLoop].data.fd;

                /* 返回收到数据的fd绑定的link,若该fd不是与link绑定的fd则返回ERROR_FAILED */
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
                    /* 将accept()返回的用于和新client通信的fd加入监视列表 */
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
                        
                        /* 此socket无数据可读，本次唤醒是因为remote关闭socket */
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
                        
                        /* remote 有数据送过来需要立即接收 */
                        else
                        {
                            cout << "Recv: Rx " << Link[MsgLink].GetName() << " receive message :\n";
                            
                           /* 分配临时缓存区存socket接收数据 */
                           pcReadBuf = new char[iCtlRead+1];
                           uiRemain = iCtlRead;
                           uiTotalRead = 0;
                           do {
                                uiReadSize = ReadOnSocket(iFd, uiRemain, pcReadBuf, iCtlRead+1, '\n');
                                uiTotalRead += uiReadSize;
                                uiRemain = iCtlRead - uiTotalRead;
                                pcReadBuf[uiReadSize] = '\0';
                                
                                /* 需要检查最后一个字符是否为换行符,并处理该换行符 */
                                if('\n' == pcReadBuf[uiReadSize - 1])
                                {
                                    /* 此次收包完成 */
                                     pcReadBuf[uiReadSize - 1] = '\0';
                                     /* decode  */
                                     strDecode = base64_decode(pcReadBuf);
                                     

                                     /* 拷贝解码后的数据到outdata端口 */
                                     memset(read_data.raw_data, 0, CELL_FORMAT_SIZE);
                                     uiLen = strDecode.length();
                                     strDecode.copy(read_data.raw_data, uiLen);
                                     //cout << "Recv: RX Cell type : " << read_data.type << "  Cell Len: " << uiLen << "  rece len:" << iCtlRead << endl;

                                     DisplayPacket(read_data.raw_data, sizeof(read_data.raw_data));
                                      /* 将cell 缓存到fifo,不同处理平面使用不同fifo */
                                     uiPlane = GetLinkPlane(MsgLink);
                                     //cout << "Plane Index :" << uiPlane << "    PlaneStatus : " << uiPlaneStatus << endl;
                                      switch(uiPlane)
                                     {
                                         case 0:
                                             OUT_ProcPlane0->write(read_data);
                                             OUT_Link0->write( MsgLink );
                                             break;
                                         case 1:
                                            OUT_ProcPlane1->write(read_data);
                                            OUT_Link1->write( MsgLink );
                                            break;
                                         case 2:
                                             OUT_ProcPlane2->write(read_data);
                                             OUT_Link2->write( MsgLink );
                                             break;
                                         case 3:
                                             OUT_ProcPlane3->write(read_data);
                                             OUT_Link3->write( MsgLink );
                                             break;
                                         default:
                                            cout << "process plane not defined.\n";
                                     }
                                     //cout << "fifo: remain = " << OUT_Packet->num_free() << endl;
                                }
                                else
                                {
                                    cout << "Recv: receive cell failed\n";
                                }
                            }while(uiRemain != 0);
                            /* 释放动态分配的内存 */
                             delete [] pcReadBuf;
                        }
                    }
                }
            }
        }
    }
}
