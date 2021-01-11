/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              common.h
   Project Code: F-Switch
   Module Name : socket transmit & receive relative
   Date Created: 2020-11-12
   Author      : pengying21074
   Description : header file of socket relative

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#ifndef __COMMON_H_
#define __COMMON_H_

#include <sys/epoll.h>

#define ERROR_FAILED    -1
#define ERROR_SUCCESS     0
#define INVALID_SOCK    -1
#define MAX_NUM_PER_CONNECT 3

#define MAX_NUM_OF_SWITCH   36

typedef struct tagTRANSMIT_PORT_INFO
{
    USHORT usIndex;
    USHORT usPort;
}TRANSMIT_PORT_INFO_S;

typedef struct tagSOCK_INFO
{
    CHAR szAddr[32];
    USHORT usPort;
}SOCK_INFO_S;

class PORT_LINK
{
    USHORT usPort; /* 监听的端口号 */
    std::string name;       /* 识别名称 */
    UINT uiLinkNum; /* 分配的索引号 */
    INT iFD;                /* socket 文件描述句柄 */
    USHORT usConnections; /* 已连接的客户端个数 */
    INT iActive;
    INT ConnectList[MAX_NUM_PER_CONNECT];
    friend class EVENT;

    public:
    VOID ShowInfo(VOID);
    INT LinkUp(USHORT usPortNum, CONST CHAR *pcIPAddr);
    INT LinkDown(VOID);
    PORT_LINK(const std::string & LinkName, UINT uiIndex);
    PORT_LINK();
    ~PORT_LINK();
    std::string &GetName(VOID);
    INT GetFD(VOID);
    INT GetIndex(VOID);
    INT GetConnectListEle(INT Num);
    INT UpdataConnectList(INT Fd, bool ISAdd);
    USHORT GetConnection(VOID);
};

#define MAX_LISTEN_EVENT    100
class EVENT
{
    INT event_handle;
    INT ListSize;
    INT WakeupEvent;
    public:
    struct epoll_event WakeupList[MAX_LISTEN_EVENT];
    EVENT(INT Num);
    EVENT();
    ~EVENT();
    INT Init(VOID);
    INT Wait(VOID);
    INT AddEvent(INT);
    INT DelEvent(INT);
    INT GetWakeupEvent(VOID);
};

class SENDER
{
    std::string name;
    USHORT usPort;
    USHORT usIndex;
    INT iFD;
    CHAR szIPAddr[32];

    public:
    SENDER(const std::string & IdentifyName, USHORT uiID);
    SENDER();
    ~SENDER();
    INT Connect(CONST CHAR *pcAddr);
    INT Connect();
    INT MsgSend(VOID *buffer, UINT size);
};


INT PrasePortConfigFile(const CHAR *pcFile);
INT ParseSocketInfo(CONST CHAR *pcFilePath, SOCK_INFO_S *pstResult, UINT uiAddrBufSize);


#endif

