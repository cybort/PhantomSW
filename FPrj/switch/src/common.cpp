/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              common.cpp
   Project Code: F-Switch
   Module Name : socket transmit & receive relative
   Date Created: 2020-11-12
   Author      : pengying21074
   Description : implementation of socket relative

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include "prv_deftype.h"

#include "common.h"

using std::cout;
using std::endl;

#define REMOTE_ADDR "10.114.220.169"
#define MAX_PARAM_NUM   2

/* default constructor  */
/*****************************************************************************
 Func Name    : PORT_LINK::PORT_LINK
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : default constructor
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
PORT_LINK::PORT_LINK()
{
    usPort = 0xffff;
    name = "UNKNOWN";
    uiLinkNum = 0xffffffff;
    iFD = INVALID_SOCK;
    usConnections = 0;
    for(INT i=0; i<MAX_NUM_PER_CONNECT; i++)
    {
        ConnectList[i] = INVALID_SOCK;
    }
    iActive = 0;
}

/* user implement constructor */
/*****************************************************************************
 Func Name    : PORT_LINK::PORT_LINK
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : user implement constructor
 Input        : string & LinkName   name of link
                UINT uiIndex        index of link
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
PORT_LINK::PORT_LINK(const std::string & LinkName, UINT uiIndex)
{
    usPort = 0xffff;
    name = LinkName;
    uiLinkNum = uiIndex;
    iFD = INVALID_SOCK;
    usConnections = 0;
    for(INT i=0; i<MAX_NUM_PER_CONNECT; i++)
    {
        ConnectList[i] = INVALID_SOCK;
    }
    iActive = 0;
}

/* destructor */
/*****************************************************************************
 Func Name    : PORT_LINK::~PORT_LINK
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : destructor
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
PORT_LINK::~PORT_LINK() {}

/* show Link port info */
/*****************************************************************************
 Func Name    : PORT_LINK::ShowInfo
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : show Link port info
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
VOID PORT_LINK::ShowInfo(VOID)
{
    cout<<"Name: "<<name<<endl;
    cout<<"Index: "<<uiLinkNum<<endl;
    cout<<"ListenPort: "<<usPort<<endl;
    cout<<"SocketFD: "<< iFD<<endl;
    cout<< "Curent connection: " << usConnections << endl;
    cout<< "Status: " << ((iActive == 0) ? "down" : "up") << endl;
}

/* Link up */
/*****************************************************************************
 Func Name    : PORT_LINK::LinkUp
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : Link up
 Input        : USHORT usPortNum    port number which socket listen to
 Output       : NONE
 Return       : ERROR_SUCCESS       success
                ERROR_FAILED        failed
 Caution      :
*****************************************************************************/
INT PORT_LINK::LinkUp(USHORT usPortNum)
{
    INT iRet = ERROR_SUCCESS;
    struct sockaddr_in stSockParam;
    INT iLen;
    INT iFd;

    stSockParam.sin_family = AF_INET;
    stSockParam.sin_addr.s_addr = inet_addr("10.114.220.169");
    stSockParam.sin_port = htons(usPortNum);
    iLen = sizeof(stSockParam);

    iFd = socket(AF_INET, SOCK_STREAM, 0);
    if(ERROR_FAILED == iFd)
    {
        perror("Socket create");
        return ERROR_FAILED;
    }
    iRet = bind(iFd, (struct sockaddr *)&stSockParam, iLen);
    if( ERROR_SUCCESS != iRet)
    {
        perror("Socket bind");
        return ERROR_FAILED;
    }
    iRet = listen(iFd, 3);
    if(ERROR_SUCCESS != iRet)
    {
        perror("Socket listen");
        return ERROR_FAILED;
    }
    iFD = iFd;
    iActive = 1;
    return ERROR_SUCCESS;
}

/*****************************************************************************
 Func Name    : PORT_LINK::LinkDown
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : close the fd
 Input        : NONE
 Output       : NONE
 Return       : 0         success
                -1        failed
 Caution      :
*****************************************************************************/
INT PORT_LINK::LinkDown(VOID)
{
    close(iFD);
    iFD = INVALID_SOCK;
    iActive = 0;
    usConnections = 0;
    uiLinkNum = 0xffffffff;

    return 0;
}

/*****************************************************************************
 Func Name    : PORT_LINK::GetName
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : get the name of link
 Input        : NONE
 Output       : NONE
 Return       : name of link
 Caution      :
*****************************************************************************/
std::string &PORT_LINK::GetName(VOID)
{
    return name;
}

/*****************************************************************************
 Func Name    : PORT_LINK::GetFD
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : get the fd which link listen to
 Input        : NONE
 Output       : NONE
 Return       : file decription of link
 Caution      :
*****************************************************************************/
INT PORT_LINK::GetFD(VOID)
{
    return iFD;
}

/*****************************************************************************
 Func Name    : PORT_LINK::GetIndex
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : get the index of link
 Input        : NONE
 Output       : NONE
 Return       : number of link
 Caution      :
*****************************************************************************/
INT PORT_LINK::GetIndex(VOID)
{
    return uiLinkNum;
}

/*****************************************************************************
 Func Name    : PORT_LINK::UpdataConnectList
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : 更新链路连接列表fd
 Input        : INT Fd      需要跟新的fd
                bool ISAdd  更新的方式,true:add false:delete
 Output       : NONE
 Return       : 0   操作成功
                -1  操作失败
 Caution      :
*****************************************************************************/
INT PORT_LINK::UpdataConnectList(INT Fd, bool ISAdd)
{
    INT CurPos;
    
    if(ISAdd)
    {
        if(usConnections == MAX_NUM_PER_CONNECT)
        {
            cout << "error: Link connection exceed limit" << endl;
            return ERROR_FAILED;
        }
        ConnectList[usConnections++] = Fd;
    }
    else
    {
        if(usConnections == 0)
        {
            cout << "error: Link connection is none, can't delet\n";
            return ERROR_FAILED;
        }
        for(INT i = 0; i < usConnections; i++)
        {
            if(ConnectList[i] == Fd)
            {
                CurPos = i;
                break;
            }
        }
        for(INT j = CurPos; j < usConnections - 1; j++)
        {
            ConnectList[j] = ConnectList[j+1];
        }
        usConnections--;
    }
    return ERROR_SUCCESS;
}

/*****************************************************************************
 Func Name    : PORT_LINK::GetConnectListEle
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : 获取连接列表fd
 Input        : INT Num     index
 Output       : NONE
 Return       : 
 Caution      :
*****************************************************************************/
INT PORT_LINK::GetConnectListEle(INT Num)
{
    return ConnectList[Num];
}

/*****************************************************************************
 Func Name    : PORT_LINK::GetConnection
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : 获取连接个数
 Input        : NONE
 Output       : NONE
 Return       : 当前连接的个数
 Caution      :
*****************************************************************************/
USHORT PORT_LINK::GetConnection(VOID)
{
    return usConnections;
}

/*****************************************************************************
 Func Name    : EVENT::Init
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : event时间资源监听初始化
 Input        : NONE
 Output       : NONE
 Return       : 0   操作成功
                -1  操作失败
 Caution      :
*****************************************************************************/
INT EVENT::Init(VOID)
{
    event_handle = epoll_create(ListSize);
    if(event_handle < 0)
    {
        perror("Event init");
        return ERROR_FAILED;
    }
    return 0;
}

/*****************************************************************************
 Func Name    : EVENT::EVENT
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : user implemente constructor
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
EVENT::EVENT(INT Num)
{
    ListSize = Num;
    WakeupEvent = 0;
}
/*****************************************************************************
 Func Name    : EVENT::EVENT
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : default constructor
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
EVENT::EVENT(){}

/*****************************************************************************
 Func Name    : EVENT::~EVENT
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : deconstructor
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
EVENT::~EVENT(){}

/*****************************************************************************
 Func Name    : EVENT::AddEvent
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : 将需要监听的fd加入event事件监听列表
 Input        : INT fd      需要监听的fd
 Output       : NONE
 Return       : 0   操作成功
                -1  操作失败
 Caution      :
*****************************************************************************/
INT EVENT::AddEvent(INT fd)
{
    struct epoll_event stParam;
    INT ret = ERROR_SUCCESS;

    stParam.data.fd = fd;
    stParam.events = EPOLLIN | EPOLLET;

    ret = epoll_ctl(event_handle, EPOLL_CTL_ADD, fd, &stParam);
    if(ERROR_SUCCESS != ret)
    {
        perror("Add event");
        return ret;
    }
    return ret;
}

/*****************************************************************************
 Func Name    : EVENT::DelEvent
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : 将指定fd从event事件监听列表中删除
 Input        : INT fd      需要删除的fd
 Output       : NONE
 Return       : 0   操作成功
                -1  操作失败
 Caution      :
*****************************************************************************/
INT EVENT::DelEvent(INT fd)
{
    INT ret = ERROR_SUCCESS;

    ret = epoll_ctl(event_handle, EPOLL_CTL_DEL, fd, (epoll_event *)NULL);
    if(ERROR_SUCCESS != ret)
    {
        perror("Delet event");
        return ret;
    }
    return ret;
}

/*****************************************************************************
 Func Name    : EVENT::Wait
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : 等待event事件监听列表有唤醒事件
 Input        : NONE
 Output       : NONE
 Return       : 0   操作成功
                -1  操作失败
 Caution      :
*****************************************************************************/
INT EVENT::Wait(VOID)
{
    INT ret;

    ret = epoll_wait(event_handle, WakeupList, MAX_LISTEN_EVENT, 0);
    if(ret < 0)
    {
        perror("Wait event");
        return ERROR_FAILED;
    }

    WakeupEvent = ret;
    return ERROR_SUCCESS;
}

/*****************************************************************************
 Func Name    : EVENT::GetWakeupEvent
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : 获取唤醒事件的数目
 Input        : NONE
 Output       : NONE
 Return       : 被唤醒事件的数量
 Caution      :
*****************************************************************************/
INT EVENT::GetWakeupEvent(VOID)
{
    return WakeupEvent;
}


TRANSMIT_PORT_INFO_S g_astPortMapInfo[MAX_NUM_OF_SWITCH] =
{
    {0,      11024},
    {1,      11025},
    {2,      11026},
    {3,      11027},
    {4,      11028},
    {5,      11029},
    {6,      11030},
    {7,      11031},
    {8,      11032},
    {9,      11033},
    {10,     11034},
    {11,     11035},
    {12,     11036},
    {13,     11037},
    {14,     11038},
    {15,     11039},
    {16,     11040},
    {17,     11041},
    {18,     11042},
    {19,     11043},
    {20,     11044},
    {21,     11045},
    {22,     11046},
    {23,     11047},
    {24,     11048},
    {25,     11049},
    {26,     11050},
    {27,     11051},
    {28,     11052},
    {29,     11053},
    {30,     11054},
    {31,     11055},
    {32,     11056},
    {33,     11057},
    {34,     11058},
    {35,     11059},
};

USHORT GetPortNum(USHORT usIndex)
{
    UINT uiLoop;

    for(uiLoop = 0; uiLoop < MAX_NUM_OF_SWITCH; uiLoop++)
    {
        if(g_astPortMapInfo[uiLoop].usIndex == usIndex)
        return g_astPortMapInfo[uiLoop].usPort;
    }
    cout << "error: link " << usIndex << ": port number is not defined.\n";
    return 0xffff;
}

INT PrasePortConfigFile(const CHAR *pcFile)
{
    CHAR ReadBuf[64] = {0};
    CHAR Str2Int[16] = {0};
    CHAR *pcCurPos = NULL;
    UINT uiSize = 0;
    USHORT ausParam[MAX_PARAM_NUM];
    USHORT i = 0;
    UINT uiLoop;
    UINT uiCopyLen;
    std::ifstream file(pcFile, std::ifstream::in);
    
    if(file)
    {
        while(file.getline(ReadBuf, 64, '\n'))
        {
         //   cout << ReadBuf << endl;
            while(ReadBuf[uiSize])
            {
                while(ReadBuf[uiSize] && (ReadBuf[uiSize] == '#'))
                uiSize++;
                pcCurPos = ReadBuf + uiSize;
                while(ReadBuf[uiSize] && (ReadBuf[uiSize] != '#'))
                uiSize++;
                if(ReadBuf[uiSize])
                ReadBuf[uiSize++] = '\0';
                uiCopyLen = strlen(pcCurPos);
                strncpy(Str2Int, pcCurPos, uiCopyLen);
                Str2Int[uiCopyLen] = '\0';
                ausParam[i++] = (USHORT)atoi(Str2Int);
                
                /* 多余2个参数退出本轮解析,忽略多余参数 */
                if(MAX_PARAM_NUM == i)
                break;
            }
            for(uiLoop = 0; uiLoop < MAX_NUM_OF_SWITCH; uiLoop++)
            {
                //cout << "index = "<< ausParam[0] << endl;
                if(ausParam[0] == g_astPortMapInfo[uiLoop].usIndex)
                break;
            }
            if(uiLoop == MAX_NUM_OF_SWITCH)
            {
                cout << "can not find the specilize link " << ausParam[0] << endl;
                continue;
            }
            else if( MAX_PARAM_NUM > i || (ausParam[1] >= 0xffff && ausParam[1] <= 1024))
            {
                cout << "invalid port number [" << ausParam[1] << "] config on"<< " link " << ausParam[0] << endl;
                continue;
            }
            else {
                g_astPortMapInfo[uiLoop].usPort = ausParam[1];
            }

            /* 重置状态开始下一轮解析 */
            memset(ReadBuf, 0, sizeof(ReadBuf));
            i = 0;
            uiSize = 0;
        }
        if(file.eof())
        file.close();
    }
    else
    {
        cout << "the file of port mapping is not find!!!\n";
        return ERROR_FAILED;
    }
    return ERROR_SUCCESS;
}

/*****************************************************************************
 Func Name    : SENDER::SENDER
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : user implemente constructor
 Input        : string & IdentifyName
                USHORT DestiPort
                USHORT uiID
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
SENDER::SENDER(const std :: string & IdentifyName, USHORT usID)
{
    name = IdentifyName;
    usPort = GetPortNum(usID);
    usIndex = usID;
    iFD = INVALID_SOCK;
    
}

/*****************************************************************************
 Func Name    : SENDER::SENDER
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : default constructor
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
SENDER::SENDER() {}

/*****************************************************************************
 Func Name    : SENDER::SENDER
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : deconstructor
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
SENDER::~SENDER() {}

/*****************************************************************************
 Func Name    : SENDER::SENDER
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : 模拟TX MAC 发送端socket建立
 Input        : NONE
 Output       : NONE
 Return       : 0   操作成功
                -1  操作失败
 Caution      :
*****************************************************************************/
INT SENDER::Connect(VOID)
{
    INT iRet = ERROR_SUCCESS;
    INT sockFd = INVALID_SOCK;
    struct sockaddr_in stSockParam;

    stSockParam.sin_family = AF_INET;
    stSockParam.sin_addr.s_addr = inet_addr(REMOTE_ADDR);

    if(usPort == 0xffff)
    {
        return ERROR_FAILED;
    }
    stSockParam.sin_port = htons(usPort);

    sockFd = socket(AF_INET, SOCK_STREAM, 0);
    iRet = connect(sockFd, (struct sockaddr*)&stSockParam, sizeof(stSockParam));
    if(iRet != ERROR_SUCCESS)
    {
        perror("Socket connect");
        cout << "Tx " << name << " is not available.\n";
        return ERROR_FAILED;
    }
    iFD = sockFd;
    return ERROR_SUCCESS;
}

/*****************************************************************************
 Func Name    : SENDER::SENDER
 Date Created : 2020/11/12
 Author       : pengying21074
 Description  : 模拟TX MAC 发送数据包
 Input        : VOID *buffer    待发送缓存区
                UINT size       发送数据缓存区size
 Output       : NONE
 Return       : 0   操作成功
                -1  操作失败
 Caution      :
*****************************************************************************/
INT SENDER::MsgSend(VOID *buffer, UINT size)
{
    INT retry = 5;
    
    if(INVALID_SOCK != iFD)
    return (send(iFD, buffer, size,0));
    else{
        cout << name << "MsgSend: send message failed!\n";
        cout << "MsgSend: Retrying...\n";
        do{
            if(ERROR_SUCCESS == Connect())
            return (send(iFD, buffer, size,0));
        }while(--retry);
    }
    cout << "MsgSend: current link is not available.\n";
    return ERROR_FAILED;
}

