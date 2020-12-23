#ifdef  __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include "prv_basedef.h"
#include "mythread.h"
#include "mysocket.h"
#include "utils.h"
#include "hostserver.h"

#define MAX_CHANNEL     (2)
#define MSG_ID_HOST_RETURN_ERROR    (0x7777U)
#define MSG_ID_HOST_RETURN_OK       (0x8888U)

typedef struct tagSERVER_CHANNEL
{
    SOCK        sockServer;
    BOOL_T      bCreated;
    BOOL_T      bActive;
    UINT        uiChannelNumber;
    Thmtx       mtxMutex;
}SERVER_CHANNEL_S;

typedef enum tagMSG_TYPE
{
    MSG_ID_HOST_READ = 0,
    MSG_ID_HOST_WRITE,

    MSG_ID_HOST_BUTT,
}MSG_TYPE_E;

typedef struct tagMSG_HEAD_STRUCT
{
    UINT uiMsgSeq;             /* 消息流水号 */
    UINT uiSize;               /* paylaod 有效长度 */
    UINT uiMsgType;      /* 消息类型 */
}MSG_HEAD_STRUCT;

#define MSG_HEADER_SIZE     sizeof(MSG_HEAD_STRUCT)
#define MSG_PAYLAOD_SIZE    (128)


CONST UINT g_uiPortNumber = 8888;
STATIC SOCK g_sockServer;
STATIC volatile UINT g_uiMessageSeq = 0;

STATIC SERVER_CHANNEL_S g_astConnections[MAX_CHANNEL];

STATIC VOID ServerThread(VOID);



/*****************************************************************************
 Func Name    : HostServerInit
 Date Created : 2020/12/19
 Author       : pengying21074
 Description  : hosr server 初始化
 Input        : NONE
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
ULONG HostServerInit(VOID)
{
    Thtask tTask;
    ULONG ulRetVal = ERROR_SUCCESS;

    g_sockServer = Socket_Create( SOCKET_PROTOCOL_STREAM );
    if ( Socket_INVALID == g_sockServer )
    {
        Log_Print( LOG_LEVEL_ERROR,"HostServerInit: Socket_Create( sockServer ) failed\n" );
        return ERROR_FAILED;
    }

    ulRetVal = Socket_Listen( g_sockServer, g_uiPortNumber, MAX_CHANNEL );
    if ( ulRetVal )
    {
        Log_Print(LOG_LEVEL_ERROR, "HostServerInit: Socket_Listen( sockServer ) failed\n" );
        return ulRetVal;
    }

    tTask = Task_Spawn("HostServer",
                        Task_NORMAL_PRIORITY,
                        0x1000,
                        (Task_Spawn_FuncPtr)ServerThread,
                        0);
    if(tTask == Task_INVALID_TASK)
    {
        ulRetVal = ERROR_FAILED;
        Log_Print(LOG_LEVEL_ERROR, "HostServerInit: Task_Spawn(ServerThread) failed\n");
        return ulRetVal;
    }

    return ulRetVal;
}

/*****************************************************************************
 Func Name    : ServerThread
 Date Created : 2020/12/19
 Author       : pengying21074
 Description  : hosr server 处理remote连接主线程
 Input        : NONE
 Output       : NONE
 Return       : NONE
 Caution      : 
*****************************************************************************/
STATIC VOID ServerThread(VOID)
{
    UINT uiChannelNum;
    UINT uiData;
    SOCK sockServer;
    ULONG ulRetVal = ERROR_SUCCESS;

    while(1)
    {
        sockServer = Socket_Accept( g_sockServer );
        if (Socket_INVALID == sockServer )
        {
            Log_Print(LOG_LEVEL_ERROR, "ServerThread: Socket_Accept failed\n" );
            break;
        }
        ulRetVal = Socket_Recv( sockServer, &uiChannelNum, sizeof( uiChannelNum ) );
        if(ERROR_FAILED == ulRetVal)
        {
            Socket_Shutdown( sockServer, SOCKET_SD_BOTH );
            Socket_Close( sockServer );
            Log_Print(LOG_LEVEL_ERROR, "ServerThread: invalid channel number %u received from connection\n", uiChannelNum);
            continue;
        }
        if(uiChannelNum > MAX_CHANNEL)
        {
            Log_Print(LOG_LEVEL_ERROR, "ServerThread: channel id exceed limit, max = %u, current = %u\n.",MAX_CHANNEL, uiChannelNum);
            continue;
        }
        if(g_astConnections[uiChannelNum].bCreated)
        {
            uiData = MSG_ID_HOST_RETURN_ERROR;
        }
        else
        {
            uiData = MSG_ID_HOST_RETURN_OK;
        }
        if ( Socket_Send( sockServer, &uiData, sizeof( uiData ) ) != ERROR_SUCCESS )
        {
            Socket_Shutdown( sockServer, SOCKET_SD_BOTH );
            Socket_Close( sockServer );
            Log_Print(LOG_LEVEL_ERROR, "Server thread: Cannot send accept to server\n" );
            continue;
        }
        if(g_astConnections[uiChannelNum].bCreated)
        {
            Socket_Shutdown( sockServer, SOCKET_SD_BOTH );
            Socket_Close( sockServer );
            Log_Print(LOG_LEVEL_ERROR, "ServerThread: channel %u already exist.\n",uiChannelNum);
            continue;
        }

        g_astConnections[uiChannelNum].sockServer = sockServer;
        g_astConnections[uiChannelNum].uiChannelNumber = uiChannelNum;
        g_astConnections[uiChannelNum].mtxMutex = Task_MutexCreate(BOOL_FALSE);
        g_astConnections[uiChannelNum].bCreated = BOOL_TRUE;
        g_astConnections[uiChannelNum].bActive = BOOL_TRUE;

        printf( "ServerThread: channel %u is ready\n",uiChannelNum);
    }
}

/*****************************************************************************
 Func Name    : Host_GetMsgFromRemote
 Date Created : 2020/12/19
 Author       : pengying21074
 Description  : hosr server请求remote数据接口
 Input        : UINT uiChannleId    remote channel id
                VOID *pInBuf        发送remote的数据包,携带请求的信息
                UINT uiInBufSize    入buffer size
                UINT uiOutBufSize   出buffer size
 Output       : VOID *pOutBuf       remote返回数据缓存区
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
ULONG Host_GetMsgFromRemote(UINT uiChannleId, VOID *pInBuf, UINT uiInBufSize, VOID *pOutBuf, UINT uiOutBufSize)
{
    MSG_HEAD_STRUCT stMsgHeader;
    UCHAR *pucData;
    UCHAR aucBuffer[MSG_HEADER_SIZE + MSG_PAYLAOD_SIZE] = {0};
    ULONG ulRetVal = ERROR_SUCCESS;
    UINT uiBufferOff = 0;
    UINT uiRecvSize;
    UINT uiResideSize;

    *((UINT *)(aucBuffer + uiBufferOff)) = g_uiMessageSeq;
    uiBufferOff += sizeof(UINT);
    *((UINT *)(aucBuffer + uiBufferOff)) = uiInBufSize;
    uiBufferOff += sizeof(UINT);
    *((UINT *)(aucBuffer + uiBufferOff)) = (UINT)MSG_ID_HOST_READ;
    uiBufferOff += sizeof(UINT);

    /* 消息长度超过定义的payload长度,还是会发送此消息,接收端可能无法正常解析*/
    CLI_Memcpy(aucBuffer + uiBufferOff, pInBuf, (uiInBufSize > MSG_PAYLAOD_SIZE) ? MSG_PAYLAOD_SIZE : uiInBufSize);

    ulRetVal = Task_MutexLock(g_astConnections[uiChannleId].mtxMutex);
    YNTEST_CHK_FAILED(ulRetVal, "Host_GetMsgFromRemote: Task_MutexLock failed\n");

    ulRetVal = Socket_Send(g_astConnections[uiChannleId].sockServer, (VOID *)aucBuffer, 
                            MSG_HEADER_SIZE + ((uiInBufSize > MSG_PAYLAOD_SIZE) ? MSG_PAYLAOD_SIZE : uiInBufSize));
    if(ulRetVal)
    {
        Task_MutexUnlock(g_astConnections[uiChannleId].mtxMutex);
        Log_Print(LOG_LEVEL_ERROR, "Host_GetMsgFromRemote: Socket_Send failed\n");
        return ulRetVal;
    }

    g_uiMessageSeq++;
    ulRetVal = Socket_Wait(g_astConnections[uiChannleId].sockServer, 3000);
    if(ulRetVal == ERROR_FAILED)
    {
        Task_MutexUnlock(g_astConnections[uiChannleId].mtxMutex);
        Log_Print(LOG_LEVEL_ERROR, "Host_GetMsgFromRemote: Socket_Wait failed\n");
        return ulRetVal;
    }
    if(ulRetVal == ERROR_TIMEOUT)
    {
        ulRetVal = ERROR_SUCCESS;
        Task_MutexUnlock(g_astConnections[uiChannleId].mtxMutex);
        Log_Print(LOG_LEVEL_WARNING, "Host_GetMsgFromRemote: Socket_Wait timeout\n");
        return ulRetVal;
    }

    ulRetVal = Socket_Recv(g_astConnections[uiChannleId].sockServer, (VOID *) &stMsgHeader, MSG_HEADER_SIZE);
    if(ulRetVal)
    {
        Task_MutexUnlock(g_astConnections[uiChannleId].mtxMutex);
        Log_Print(LOG_LEVEL_ERROR, "Host_GetMsgFromRemote: Socket_Recv failed\n");
        return ulRetVal;
    }
    uiRecvSize = stMsgHeader.uiSize;
    uiResideSize = uiOutBufSize;
    pucData = (UCHAR *)pOutBuf;
    
    do
    {
        if(MSG_PAYLAOD_SIZE < uiRecvSize )
        {
            ulRetVal = Socket_Recv(g_astConnections[uiChannleId].sockServer, (VOID *) aucBuffer, MSG_PAYLAOD_SIZE);
            if(ulRetVal)
            {
                Task_MutexUnlock(g_astConnections[uiChannleId].mtxMutex);
                Log_Print(LOG_LEVEL_ERROR, "Host_GetMsgFromRemote: Socket_Recv failed\n");
                return ulRetVal;
            }
            if(MSG_PAYLAOD_SIZE < uiResideSize)
            {
                CLI_Memcpy(pucData, aucBuffer, MSG_PAYLAOD_SIZE);
                pucData += MSG_PAYLAOD_SIZE;
                uiRecvSize -= MSG_PAYLAOD_SIZE;
                uiResideSize -= MSG_PAYLAOD_SIZE;
            }
            else
            {
                Log_Print(LOG_LEVEL_ERROR, "Host_GetMsgFromRemote: no sufficient space for storing message\n");
            }
        }
        else
        {
            ulRetVal = Socket_Recv(g_astConnections[uiChannleId].sockServer, (VOID *) aucBuffer, uiRecvSize);
            if(ulRetVal)
            {
                Task_MutexUnlock(g_astConnections[uiChannleId].mtxMutex);
                Log_Print(LOG_LEVEL_ERROR, "Host_GetMsgFromRemote: Socket_Recv failed\n");
                return ulRetVal;
            }

            if(uiRecvSize < uiResideSize)
            {
                CLI_Memcpy(pucData, aucBuffer, uiRecvSize);
                pucData += uiRecvSize;
                uiRecvSize = 0;
                uiResideSize -= uiRecvSize;
            }
            else
            {
                Log_Print(LOG_LEVEL_ERROR, "Host_GetMsgFromRemote: no sufficient space for storing message\n");
            }
        }
    }while(uiRecvSize);
    Task_MutexUnlock(g_astConnections[uiChannleId].mtxMutex);

    return ulRetVal;
}

/*****************************************************************************
 Func Name    : Host_SendMsgtoRemote
 Date Created : 2020/12/19
 Author       : pengying21074
 Description  : hosr server向remote发送数据接口
 Input        : UINT uiChannleId    remote channel id
                VOID *pInBuf        发送remote的数据包,携带请求的信息
                UINT uiInBufSize    入buffer size
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
ULONG Host_SendMsgtoRemote(UINT uiChannleId, VOID *pInBuf, UINT uiInBufSize)
{
    UCHAR aucBuffer[MSG_HEADER_SIZE + MSG_PAYLAOD_SIZE] = {0};
    ULONG ulRetVal = ERROR_SUCCESS;
    UINT uiBufferOff = 0;

    *((UINT *)(aucBuffer + uiBufferOff)) = g_uiMessageSeq;
    uiBufferOff += sizeof(UINT);
    *((UINT *)(aucBuffer + uiBufferOff)) = uiInBufSize;
    uiBufferOff += sizeof(UINT);
    *((UINT *)(aucBuffer + uiBufferOff)) = (UINT)MSG_ID_HOST_WRITE;
    uiBufferOff += sizeof(UINT);
    CLI_Memcpy(aucBuffer + uiBufferOff, pInBuf, (uiInBufSize > MSG_PAYLAOD_SIZE) ? MSG_PAYLAOD_SIZE : uiInBufSize);

    ulRetVal = Task_MutexLock(g_astConnections[uiChannleId].mtxMutex);
    YNTEST_CHK_FAILED(ulRetVal, "Host_SendMsgtoRemote: Task_MutexLock failed\n");

    ulRetVal = Socket_Send(g_astConnections[uiChannleId].sockServer, (VOID *)aucBuffer, 
                            MSG_HEADER_SIZE + ((uiInBufSize > MSG_PAYLAOD_SIZE) ? MSG_PAYLAOD_SIZE : uiInBufSize));
    if(ulRetVal)
    {
        Task_MutexUnlock(g_astConnections[uiChannleId].mtxMutex);
        Log_Print(LOG_LEVEL_ERROR, "Host_SendMsgtoRemote: Socket_Send failed\n");
        return ulRetVal;
    }
    Task_MutexUnlock(g_astConnections[uiChannleId].mtxMutex);

    return ulRetVal;
}

/*****************************************************************************
 Func Name    : CLI_CmdSetValue
 Date Created : 2020/12/19
 Author       : pengying21074
 Description  : set命令API接口
 Input        : UINT uiChannleId    remote channel id
                CLI_CMD_PARAM_S *pstParam   指向CLI命令输入参数结构指针
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
ULONG CLI_CmdSetValue(UINT uiChannelId, CLI_CMD_PARAM_S *pstParam)
{
    ULONG ulRetVal = ERROR_SUCCESS;
    UCHAR aucBuffer[sizeof(CLI_CMD_PARAM_S) + 8] = {0};
    UINT uiBufSizeCnt = 0;

    YNTEST_CHK_PTR_FAILED(pstParam);

    CLI_Memcpy(aucBuffer + uiBufSizeCnt, pstParam->acModName, strlen(pstParam->acModName));
    uiBufSizeCnt += strlen(pstParam->acModName);
    CLI_Memcpy(aucBuffer + uiBufSizeCnt, "#", 1);
    uiBufSizeCnt += 1;

    CLI_Memcpy(aucBuffer + uiBufSizeCnt, pstParam->acConfigName, strlen(pstParam->acConfigName));
    uiBufSizeCnt += strlen(pstParam->acConfigName);
    CLI_Memcpy(aucBuffer + uiBufSizeCnt, "#", 1);
    uiBufSizeCnt += 1;
    *((UINT *)(aucBuffer + uiBufSizeCnt)) = pstParam->uiValue;
    uiBufSizeCnt += sizeof(UINT);
    CLI_Memcpy(aucBuffer + uiBufSizeCnt, "#\n", 2);
    uiBufSizeCnt += 2;

    ulRetVal = Host_SendMsgtoRemote(uiChannelId, aucBuffer, uiBufSizeCnt);
    YNTEST_CHK_FAILED(ulRetVal, "CLI_CmdSetValue: Host_SendMsgtoRemote failed\n");

    return ulRetVal;
}

/*****************************************************************************
 Func Name    : CLI_CmdSetValuebyAddr
 Date Created : 2020/12/19
 Author       : pengying21074
 Description  : set命令API接口
 Input        : UINT uiChannleId    remote channel id
                CLI_CMD_PARAM_S *pstParam   指向CLI命令输入参数结构指针
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
ULONG CLI_CmdSetValuebyAddr(UINT uiChannelId, CLI_CMD_PARAM_S *pstParam)
{
    ULONG ulRetVal = ERROR_SUCCESS;
    UCHAR aucBuffer[sizeof(CLI_CMD_PARAM_S) + 8] = {0};
    UINT uiBufSizeCnt = 0;

    YNTEST_CHK_PTR_FAILED(pstParam);

    CLI_Memcpy(aucBuffer + uiBufSizeCnt, pstParam->acModName, strlen(pstParam->acModName));
    uiBufSizeCnt += strlen(pstParam->acModName);
    CLI_Memcpy(aucBuffer + uiBufSizeCnt, "#", 1);
    uiBufSizeCnt += 1;

    CLI_Memcpy(aucBuffer + uiBufSizeCnt, pstParam->acConfigName, strlen(pstParam->acConfigName));
    uiBufSizeCnt += strlen(pstParam->acConfigName);
    CLI_Memcpy(aucBuffer + uiBufSizeCnt, "#", 1);
    uiBufSizeCnt += 1;
    *((UINT *)(aucBuffer + uiBufSizeCnt)) = pstParam->uiValue;
    uiBufSizeCnt += sizeof(UINT);
    CLI_Memcpy(aucBuffer + uiBufSizeCnt, "#", 1);
    uiBufSizeCnt += 1;
    *((UINT *)(aucBuffer + uiBufSizeCnt)) = pstParam->uiAddr;
    uiBufSizeCnt += sizeof(UINT);
    CLI_Memcpy(aucBuffer + uiBufSizeCnt, "#\n", 2);
    uiBufSizeCnt += 2;

    ulRetVal = Host_SendMsgtoRemote(uiChannelId, aucBuffer, uiBufSizeCnt);
    YNTEST_CHK_FAILED(ulRetVal, "CLI_CmdSetValue: Host_SendMsgtoRemote failed\n");

    return ulRetVal;
}

/*****************************************************************************
 Func Name    : CLI_CmdGetValue
 Date Created : 2020/12/19
 Author       : pengying21074
 Description  : Get命令API接口
 Input        : UINT uiChannleId    remote channel id
                CLI_CMD_PARAM_S *pstParam   指向CLI命令输入参数结构指针
                UINT uiSize     缓存Get指令返回数据缓存区长度
 Output       : VOID *pOutBuf   缓存Get指令返回数据缓存区指针
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
ULONG CLI_CmdGetValue(UINT uiChannelId, CLI_CMD_PARAM_S *pstParam, VOID *pOutBuf, UINT uiSize)
{
    ULONG ulRetVal = ERROR_SUCCESS;
    UCHAR aucBuffer[sizeof(CLI_CMD_PARAM_S) + 8] = {0};
    UINT uiBufSizeCnt = 0;

    YNTEST_CHK_PTR_FAILED(pstParam);
    YNTEST_CHK_PTR_FAILED(pOutBuf);

    CLI_Memcpy(aucBuffer + uiBufSizeCnt, pstParam->acModName, strlen(pstParam->acModName));
    uiBufSizeCnt += strlen(pstParam->acModName);
    CLI_Memcpy(aucBuffer + uiBufSizeCnt, "#", 1);
    uiBufSizeCnt += 1;

    CLI_Memcpy(aucBuffer + uiBufSizeCnt, pstParam->acConfigName, strlen(pstParam->acConfigName));
    uiBufSizeCnt += strlen(pstParam->acConfigName);
    CLI_Memcpy(aucBuffer + uiBufSizeCnt, "#", 1);
    uiBufSizeCnt += 1;
    *((UINT *)(aucBuffer + uiBufSizeCnt)) = pstParam->uiValue;
    uiBufSizeCnt += sizeof(UINT);
    CLI_Memcpy(aucBuffer + uiBufSizeCnt, "#\n", 2);
    uiBufSizeCnt += 2;

    ulRetVal = Host_GetMsgFromRemote(uiChannelId, aucBuffer, uiBufSizeCnt, pOutBuf, uiSize);
    YNTEST_CHK_FAILED(ulRetVal, "CLI_CmdSetValue: Host_GetMsgFromRemote failed\n");

    return ulRetVal;
}

/*****************************************************************************
 Func Name    : CLI_CmdGetValuebyAddr
 Date Created : 2020/12/19
 Author       : pengying21074
 Description  : Get命令API接口
 Input        : UINT uiChannleId    remote channel id
                CLI_CMD_PARAM_S *pstParam   指向CLI命令输入参数结构指针
                UINT uiSize     缓存Get指令返回数据缓存区长度
 Output       : VOID *pOutBuf   缓存Get指令返回数据缓存区指针
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
ULONG CLI_CmdGetValuebyAddr(UINT uiChannelId, CLI_CMD_PARAM_S *pstParam, VOID *pOutBuf, UINT uiSize)
{
    ULONG ulRetVal = ERROR_SUCCESS;
    UCHAR aucBuffer[sizeof(CLI_CMD_PARAM_S) + 8] = {0};
    UINT uiBufSizeCnt = 0;

    YNTEST_CHK_PTR_FAILED(pstParam);
    YNTEST_CHK_PTR_FAILED(pOutBuf);

    CLI_Memcpy(aucBuffer + uiBufSizeCnt, pstParam->acModName, strlen(pstParam->acModName));
    uiBufSizeCnt += strlen(pstParam->acModName);
    CLI_Memcpy(aucBuffer + uiBufSizeCnt, "#", 1);
    uiBufSizeCnt += 1;

    CLI_Memcpy(aucBuffer + uiBufSizeCnt, pstParam->acConfigName, strlen(pstParam->acConfigName));
    uiBufSizeCnt += strlen(pstParam->acConfigName);
    CLI_Memcpy(aucBuffer + uiBufSizeCnt, "#", 1);
    uiBufSizeCnt += 1;

    *((UINT *)(aucBuffer + uiBufSizeCnt)) = pstParam->uiValue;
    CLI_Memcpy(aucBuffer + uiBufSizeCnt, "#", 1);
    uiBufSizeCnt += 1;
    *((UINT *)(aucBuffer + uiBufSizeCnt)) = pstParam->uiAddr;
    uiBufSizeCnt += sizeof(UINT);
    CLI_Memcpy(aucBuffer + uiBufSizeCnt, "#\n", 2);
    uiBufSizeCnt += 2;

    ulRetVal = Host_GetMsgFromRemote(uiChannelId, aucBuffer, uiBufSizeCnt, pOutBuf, uiSize);
    YNTEST_CHK_FAILED(ulRetVal, "CLI_CmdSetValue: Host_GetMsgFromRemote failed\n");

    return ulRetVal;
}




#ifdef  __cplusplus
}
#endif

