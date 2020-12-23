#ifndef _HOST_SERVER_H_
#define _HOST_SERVER_H_

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct tagCLI_CMD_PARAM
{
    CHAR acModName[32];
    CHAR acConfigName[32];
    UINT uiValue;
    UINT uiAddr;
}CLI_CMD_PARAM_S;


ULONG HostServerInit(VOID);
ULONG Host_GetMsgFromRemote(UINT uiChannleId, VOID *pInBuf, UINT uiInBufSize, VOID *pOutBuf, UINT uiOutBufSize);
ULONG Host_SendMsgtoRemote(UINT uiChannleId, VOID *pInBuf, UINT uiInBufSize);
ULONG CLI_CmdSetValue(UINT uiChannelId, CLI_CMD_PARAM_S *pstParam);
ULONG CLI_CmdSetValuebyAddr(UINT uiChannelId, CLI_CMD_PARAM_S *pstParam);
ULONG CLI_CmdGetValue(UINT uiChannelId, CLI_CMD_PARAM_S *pstParam, VOID *pOutBuf, UINT uiSize);
ULONG CLI_CmdGetValuebyAddr(UINT uiChannelId, CLI_CMD_PARAM_S *pstParam, VOID *pOutBuf, UINT uiSize);


#ifdef  __cplusplus
}
#endif

#endif

