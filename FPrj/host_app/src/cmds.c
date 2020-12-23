/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              cmds.c
   Project Code: Test App
   Module Name : CLI
   Date Created: 2020-08-02
   Author      : p21074
   Description : 命令实现函数文件

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prv_basedef.h"
#include "stack.h"
#include "cli.h"
#include "mor.h"
#include "log.h"
#include "utils.h"
#include "cmds.h"

VIEW_STACK_S g_stViewInfoStack;
volatile UINT g_uiMID;
extern CHAR g_acPrompt[BUF_SIZE_64];
//STATIC EZagtRPCServer AGTSERVER;
//volatile UINT g_uiAgtCreated = 0;

#if 0
ETH_TYPE_INFO_S g_astEthTypeInfo[IF_TYPE_ETH_BUTT] = {
    { IF_TYPE_ETH_GE,           "GE"        },
    { IF_TYPE_ETH_10GE,         "10GE"      },
    { IF_TYPE_ETH_25GE,         "25GE"      },
    { IF_TYPE_ETH_40GE,         "40GE"      },
    { IF_TYPE_ETH_50GEGAUI1,    "50GEGAUI1" },
    { IF_TYPE_ETH_50GEGAUI2,    "50GEGAUI1" },
    { IF_TYPE_ETH_100GECAUI2,   "100GECAUI2"},
    { IF_TYPE_ETH_100GECAUI4,   "100GECAUI4"},
    { IF_TYPE_ETH_100GECAUI10,  "100GECAUI10"}
};
IF_TYPE_INFO_S g_stIFParam;

//STATIC ULONG CLI_ChangViewProc(IN CONST CHAR *pcInBuf, IN VOID *pCfg);
//STATIC VOID AGT_RPCJSONTask(VOID);
//STATIC ULONG AGT_InitTask(UINT uiPort);
//STATIC ULONG AGT_CloseAgt(VOID);
STATIC ULONG CLI_SaveEthernetType(IN CONST CHAR *pcInBuf, IN UINT uiEthCode,INOUT CHAR **ppcOutBuf);
STATIC ULONG CLI_SaveInterlakenInfo(IN CONST CHAR *pcInBuf, INOUT CHAR **ppcOutBuf);
STATIC CONST CHAR *CLI_GetSubIFName(IN UINT uiCode, IN CONST ETH_TYPE_INFO_S *pstCodeName);


/*****************************************************************************
 Func Name    : CLI_SystemView
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 切换到systerm-view视图命令实现
 Input        : VOID *pData       入参数指针.
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
ULONG CLI_SystemView( IN VOID *pData)
{
    ULONG ulRetVal = ERROR_SUCCESS;
//    CHAR *pcLine = NULL;
//    CLI_MODULE_S *pstMoudle = NULL;

    IGNORE_PARAM(pData);

    /* 先保存当前视图信息 */
    ulRetVal = CLI_PushViewStack(&g_stViewInfoStack, g_acPrompt, g_uiMID);
    if(ulRetVal)
    {
        Log_Print(LOG_LEVEL_ERROR, "Save last view info failed. p1 = %s, p2 = %d\n",g_acPrompt, g_uiMID);
        return ERROR_FAILED;
    }
    /* 更新视图信息 */
    strlcpy(g_acPrompt, "~[SEMI] ",sizeof(g_acPrompt));
    g_uiMID = (UINT)CLI_MOUDLE_SYS_VIEW;

    return ERROR_SUCCESS;
}

/*****************************************************************************
 Func Name    : CLI_ChangeView2IF
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 进入接口主视图命令实现
 Input        : VOID *pData       入参数指针.
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
ULONG CLI_ChangeView2IF(IN CONST VOID *pINTBuf, IN CONST VOID *pSTRBuf)
{
    ULONG ulRetVal = ERROR_SUCCESS;

    IGNORE_PARAM(pINTBuf);
    IGNORE_PARAM(pSTRBuf);

    /* 先保存当前视图信息 */
    ulRetVal = CLI_PushViewStack(&g_stViewInfoStack, g_acPrompt, g_uiMID);
    if(ulRetVal)
    {
        Log_Print(LOG_LEVEL_ERROR, "Save last view info failed. p1 = %s, p2 = %d\n",g_acPrompt, g_uiMID);
        return ERROR_FAILED;
    }
    /* 更新视图信息 */
    strlcpy(g_acPrompt, "[IF] ",sizeof(g_acPrompt));
    g_uiMID = (UINT)CLI_MOUDLE_IF;

    return ERROR_SUCCESS;
}

/*****************************************************************************
 Func Name    : CLI_ChangeView2TM
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 进入TM视图命令实现
 Input        : VOID *pData       入参数指针.
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
ULONG CLI_ChangeView2TM(IN VOID *pData)
{
    ULONG ulRetVal = ERROR_SUCCESS;

    IGNORE_PARAM(pData);

    /* 先保存当前视图信息 */
    ulRetVal = CLI_PushViewStack(&g_stViewInfoStack, g_acPrompt, g_uiMID);
    if(ulRetVal)
    {
        Log_Print(LOG_LEVEL_ERROR, "Save last view info failed. p1 = %s, p2 = %d\n",g_acPrompt, g_uiMID);
        return ERROR_FAILED;
    }
    /* 更新视图信息 */
    strlcpy(g_acPrompt, "[TM] ",sizeof(g_acPrompt));
    g_uiMID = (UINT)CLI_MOUDLE_TM;

    return ERROR_SUCCESS;
}

/*****************************************************************************
 Func Name    : CLI_GetSubIFName
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 获取以太子类型命令
 Input        : IN UINT uiCode       编码号.
 Output       : IN CONST ETH_TYPE_INFO_S *pstCodeName  指向接口名的指针
 Return       : 
 Caution      : 
*****************************************************************************/
STATIC CONST CHAR *CLI_GetSubIFName(IN UINT uiCode, IN CONST ETH_TYPE_INFO_S *pstCodeName)
{
    CONST CHAR *szNull = "(null)";

    DBGASSERT_WITH_RETURN(NULL != pstCodeName, (CONST CHAR *)"(null)");
    
    while ((NULL != pstCodeName) && (NULL != pstCodeName->szName))
    {
        if (uiCode == pstCodeName->uiCode)
        {
            return pstCodeName->szName;
        }
        pstCodeName++;
    }
    return szNull;
}

/*****************************************************************************
 Func Name    : CLI_SaveEthernetType
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 保存进入的接口类型
 Input        : CONST CHAR *pcInBuf       入Buffer.
 Output       : CHAR **ppcOutBuf          出Buffer
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
STATIC ULONG CLI_SaveEthernetType(IN CONST CHAR *pcInBuf, IN UINT uiEthCode, INOUT CHAR **ppcOutBuf)
{
    CHAR *pcTemp = NULL;
    CONST CHAR *pcStr = {"[Ethernet"};
    UINT uiSize;
    UINT uiNum,i;
    UINT uiVisit = 0;
    UINT uiInSize;
    UINT auiData[4] = {0};
    UINT uiLoop = 0;
    BOOL_T bFirst = BOOL_TRUE;

    DBGASSERT(NULL != pcInBuf);
    DBGASSERT(NULL != ppcOutBuf);

    uiInSize = strlen(pcInBuf);
    uiSize = strlen(pcStr) + uiInSize;
    pcTemp = (CHAR *)malloc(uiSize+32);
    if(NULL == pcTemp)
    {
        Log_Print(LOG_LEVEL_ERROR, "malloc failed.\n");
        return ERROR_FAILED;
    }
    YNTEST_CLEAR_BUF(pcTemp, uiSize+32);
    strlcpy(pcTemp, pcStr, uiSize+32);
    strlcpy(pcTemp + strlen(pcTemp), GETNAME_BYCODE_IFTYPE(uiEthCode), uiSize+32);
    g_stIFParam.enType = (IF_TYPE_E)uiEthCode;

    while(uiVisit < uiInSize)
    {
        if(pcInBuf[uiVisit] < '0' || pcInBuf[uiVisit] > '9')
        {
            Log_Print(LOG_LEVEL_ERROR, "wrong interface parameter. p = %s\n",pcInBuf);
            return ERROR_FAILED;
        }
        i = CLI_Str2dec(pcInBuf + uiVisit, &uiNum);
        uiVisit += i;
        auiData[uiLoop++] = uiNum;
        if(4 < uiLoop)
        {
            break;
        }
        if(bFirst)
        {
            bFirst = BOOL_FALSE;
            sprintf(pcTemp + strlen(pcTemp), "-%d",uiNum);
        }
        else
        {
            sprintf(pcTemp + strlen(pcTemp), "/%d",uiNum);
        }
        uiVisit++;
    }
    sprintf(pcTemp + strlen(pcTemp), "%s","] ");
    if(uiLoop < 4)
    {
        Log_Print(LOG_LEVEL_ERROR, "wrong interface parameter. p = %s\n",pcInBuf);
        return ERROR_FAILED;
    }
    else
    {
        g_stIFParam.uiChip = auiData[0];
        g_stIFParam.uiSide = auiData[1];
        g_stIFParam.uiEngine = auiData[2];
        g_stIFParam.uiIFNum = auiData[3];
    }
    *ppcOutBuf = pcTemp;
    return ERROR_SUCCESS;
}

/*****************************************************************************
 Func Name    : CLI_SaveInterlakenInfo
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 保存ILK信息
 Input        : CONST CHAR *pcInBuf       入Buffer.
 Output       : CHAR **ppcOutBuf          出Buffer
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
STATIC ULONG CLI_SaveInterlakenInfo(IN CONST CHAR *pcInBuf, INOUT CHAR **ppcOutBuf)
{
    CHAR *pcTemp = NULL;
    CONST CHAR *pcStr = {"[Interlaken"};
    UINT uiSize;
    UINT uiNum,i;
    UINT uiVisit = 0;
    BOOL_T bIsFirst = BOOL_TRUE;
    UINT uiInSize;
    UINT uiLoop = 0;
    UINT auiData[4] = {0};

    DBGASSERT(NULL != pcInBuf);
    DBGASSERT(NULL != ppcOutBuf);

    uiInSize = strlen(pcInBuf);
    uiSize = strlen(pcStr) + strlen(pcInBuf);
    pcTemp = (CHAR *)malloc(uiSize+4);
    if(NULL == pcTemp)
    {
        Log_Print(LOG_LEVEL_ERROR, "Malloc failed.\n");
        return ERROR_FAILED;
    }
    YNTEST_CLEAR_BUF(pcTemp, uiSize+4);
    strlcpy(pcTemp, pcStr, uiSize+4);
    g_stIFParam.enType = IF_TYPE_ILKN;

    while(uiVisit < uiInSize)
    {
        if(pcInBuf[uiVisit] < '0' || pcInBuf[uiVisit] > '9')
        {
            Log_Print(LOG_LEVEL_ERROR, "wrong interface parameter. p = %s\n",pcInBuf);
            return ERROR_FAILED;
        }
        i = CLI_Str2dec(pcInBuf + uiVisit, &uiNum);
        uiVisit += i;
        auiData[uiLoop++] = uiNum;
        if(4 < uiLoop)
        {
            break;
        }
        if(bIsFirst)
        {
            bIsFirst = BOOL_FALSE;
            sprintf(pcTemp + strlen(pcTemp), "-%d",uiNum);
        }
        else
        {
            sprintf(pcTemp + strlen(pcTemp), "/%d",uiNum);
        }
        uiVisit++;
    }
    sprintf(pcTemp + strlen(pcTemp), "%s","] ");
    if(uiLoop < 4)
    {
        Log_Print(LOG_LEVEL_ERROR, "wrong interface parameter.\n");
        return ERROR_FAILED;
    }
    else
    {
        g_stIFParam.uiChip = auiData[0];
        g_stIFParam.uiSide = auiData[1];
        g_stIFParam.uiEngine = auiData[2];
        g_stIFParam.uiIFNum = auiData[3];
    }
    *ppcOutBuf = pcTemp;
    return ERROR_SUCCESS;
}

/*****************************************************************************
 Func Name    : CLI_ChangeView2SubIF
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 进入接口子视图ETH或ILK
 Input        : VOID *pData       入参数指针.
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
ULONG CLI_ChangeView2SubIF(IN VOID *pData)
{
    ULONG ulRetVal = ERROR_SUCCESS;
    IF_SUB_VIEW_S stParam ;
    SUB_IF_TYPE_E enType;
    UINT uiEthCode;
    CHAR *pcNewPrompt = NULL;
    CLI_PARAM_PRASE_S astParam[] = {
                                    {MOR_SYSVIEW_IF_OPT, &stParam.uiSubType, sizeof(stParam.uiSubType)},
                                    {MOR_SYSVIEW_IF_STYPE, stParam.szInfo, sizeof(stParam.szInfo)},
                                    {MOR_SYSVIEW_IF_ETHTYPE, &uiEthCode, sizeof(uiEthCode)},
                                   };

    YNTEST_CHK_PTR_FAILED(pData);

    STRUCT_INIT(&stParam, sizeof(stParam));
    /* 先保存当前视图信息 */
    ulRetVal = CLI_PushViewStack(&g_stViewInfoStack, g_acPrompt, g_uiMID);
    if(ulRetVal)
    {
        Log_Print(LOG_LEVEL_ERROR, "Save last view info failed. p1 = %s, p2 = %d\n",g_acPrompt, g_uiMID);
        return ERROR_FAILED;
    }
    ulRetVal = CLI_PRASE_ParamPrase(pData, astParam, ARRAY_SIZE(astParam));
    YNTEST_CHK_RET_FAILED(ulRetVal, "Prase parameter failed.\n");
    enType = (SUB_IF_TYPE_E)stParam.uiSubType;
    switch(enType)
    {
        case SUB_IF_ETH:
        {
            ulRetVal = CLI_SaveEthernetType((CONST CHAR *) stParam.szInfo, uiEthCode, &pcNewPrompt);
            if(ulRetVal || (NULL == pcNewPrompt))
            {
                Log_Print(LOG_LEVEL_ERROR, "Save new prompt failed.\n");
                return ERROR_FAILED;
            }
            /* 更新视图信息 */
            strlcpy(g_acPrompt, pcNewPrompt, sizeof(g_acPrompt));
            g_uiMID = (UINT)CLI_MOUDLE_IF_ETH;
            break;
        }
        case SUB_IF_ILK:
        {
            ulRetVal = CLI_SaveInterlakenInfo((CONST CHAR *) stParam.szInfo, &pcNewPrompt);
            if(ulRetVal || (NULL == pcNewPrompt))
            {
                Log_Print(LOG_LEVEL_ERROR, "Save new prompt failed.\n");
                return ERROR_FAILED;
            }
            /* 更新视图信息 */
            strlcpy(g_acPrompt, pcNewPrompt, sizeof(g_acPrompt));
            g_uiMID = (UINT)CLI_MOUDLE_IF_ILK;
            break;
        }
        default :break;
        
    }
    free(pcNewPrompt);
    return ERROR_SUCCESS;

}

/*****************************************************************************
 Func Name    : CLI_Exit2LastView
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 退出当前视图返回上一视图
 Input        : VOID *pData       入参数指针.
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
ULONG CLI_Exit2LastView( IN VOID *pData)
{
    ULONG ulRetVal = ERROR_SUCCESS;
    CHAR acNewPrompt[32] = {0};
    UINT uiNum;
    
    IGNORE_PARAM(pData);

    ulRetVal = CLI_PopViewStack(&g_stViewInfoStack, acNewPrompt, sizeof(acNewPrompt), &uiNum);
    if(ulRetVal)
    {
        Log_Print(LOG_LEVEL_ERROR, "Update view info fialed.\n");
        return ulRetVal;
    }

    /* 更新视图信息 */
    (VOID)strlcpy(g_acPrompt, acNewPrompt, sizeof(g_acPrompt));
    g_uiMID = uiNum;

    return ulRetVal;
}
#endif

#if 0
STATIC VOID AGT_RPCJSONTask(VOID)
{
    EZagtRPC_ServerRun(AGTSERVER);
    return;
}

STATIC ULONG AGT_InitTask(UINT uiPort)
{
    EZtask      task;
    EZstatus    ret = EZok;

    /* Create rpc server for given port */
    AGTSERVER = EZagtRPC_CreateServer( uiPort );
    if( NULL == AGTSERVER )
    {
      printf( "AGT_Init: Cannot create agt server" );
      return ERROR_FAILED;
    }

    /* Register standard CP commands */
    ret = EZagt_RegisterFunctions( AGTSERVER );
    if ( EZok != ret )
    {
      printf( "AGT_Init: Cannot register standard CP functions" );
      return ERROR_FAILED;
    }

    /* Register standard CP commands */
    ret = EZagtCPMain_RegisterFunctions( AGTSERVER );
    if ( EZok != ret )
    {
      printf( "AGT_Init: Cannot register CP main functions" );
      return ERROR_FAILED;
    }

    /* Create task for run rpc-json commands  */
    task = EZosTask_Spawn( "agt",
                           EZosTask_NORMAL_PRIORITY,
                           0x100000,
                           (EZosTask_Spawn_FuncPtr)AGT_RPCJSONTask,
                           0 );

    if(  EZosTask_INVALID_TASK == task )
    {
      printf( "AGT_Init: Cannot spawn agt thread" );
      return ERROR_FAILED;
    }

    return ERROR_SUCCESS;
}

STATIC ULONG AGT_CloseAgt(VOID)
{
    EZagtRPC_ServerStop( AGTSERVER );
    EZosTask_Delay(10);
    EZagtRPC_ServerDestroy( AGTSERVER );

    return ERROR_SUCCESS;
}

ULONG CLI_AGT_CreatAgt(VOID *pData)
{
    ULONG ulRetVal = ERROR_SUCCESS;
    UINT uiAgtPort = 6666;
    AGT_PARAM_S stAgt;
    CHAR acInBuf[12] = {0};
    CLI_PARAM_PRASE_S astParam[] = {
    {MOR_PUBLIC_AGT_OPT,    &stAgt.uiOpt, sizeof(stAgt.uiOpt)},
    };

    YNTEST_CHK_PTR_FAILED(pData);

    STRUCT_INIT(&stAgt, sizeof(stAgt));
    ulRetVal = CLI_PRASE_ParamPrase(pData, astParam, ARRAY_SIZE(astParam));
    YNTEST_CHK_RET_FAILED(ulRetVal, "Prase parameter failed.\n");
    
    switch(stAgt.uiOpt)
    {
        case AGT_OPT_ENABLE:
        if( 0 == g_uiAgtCreated )
        {
            ulRetVal = AGT_InitTask( uiAgtPort );
            YNTEST_CHK_RET_FAILED(ulRetVal, "ERROR ! failed to create agent on port %u \n ", uiAgtPort);
            printf("\nAgent Created Success, Port: %u\n\n", uiAgtPort );
            g_uiAgtCreated = 1;
        }
        else
        {
            printf("\nAgent have already been created on port \'%u\'\n",uiAgtPort);
        }
        break;
        
        case AGT_OPT_DISABLE:
        if(0 == g_uiAgtCreated)
        {
            printf("\nWarning ! Agent is not created, nothing to be done!\n");
        }
        else
        {
            printf("\nWould you like to close the Agent port \'%u\'? (y/n)\n", uiAgtPort );
            scanf ( "%9s", acInBuf );
            if( strcmp( "y", acInBuf) == 0 )
            {
                ulRetVal = AGT_CloseAgt();
                YNTEST_CHK_RET_FAILED(ulRetVal," \nERROR ! failed to delete agent\n ");

                printf("Agent closed successfully!\n");
                g_uiAgtCreated = 0;
            }
        }
        break;

        default:
        printf("Operation not defined!\n");
    }
    return ulRetVal;
}
#endif

#ifdef  __cplusplus
}
#endif  /* __cplusplus end */

