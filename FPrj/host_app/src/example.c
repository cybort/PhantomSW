#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "prv_basedef.h"

#include "cli.h"
#include "help.h"
#include "cmds.h"
#include "mor.h"
#include "example.h"
#include "hostserver.h"

ULONG CLI_CommandGet(IN     VOID *pData);
ULONG CLI_CommandSet(IN VOID *pData);

CLI_CIOCTL_CB_S g_astCLI_CIOCTLCallBack[] = {
                                                {PUBLIC_CMD_DIS,    CLI_CommandGet},
                                                {PUBLIC_CMD_SET,    CLI_CommandSet},
                                                {USELESS_PARA, NULL},
                                            };

ULONG CLI_CmdRegister(VOID)
{
    CLI_BEGIN(CLI_MOUDLE_PUBLIC);
    
    CLI_DEF_ELEMENT("$1",   "display",          PUBLIC_IDS_DIS);
    CLI_DEF_ELEMENT("$2",   "set",              PUBLIC_IDS_SET);
    CLI_DEF_ELEMENT("$3",   "STRING<1-16>",     PUBLIC_IDS_MOD,         MOR_PUBLIC_DIS_MOD);
    CLI_DEF_ELEMENT("$4",   "STRING<1-16>",     PUBLIC_IDS_CONFIG,      MOR_PUBLIC_DIS_CONFIG);
    CLI_DEF_ELEMENT("$5",   "value",            PUBLIC_IDS_VALUE);
    CLI_DEF_ELEMENT("$6",   "INTEGER",          PUBLIC_IDS_VALUE_VAL,   MOR_PUBLIC_DIS_VALUE);
    CLI_DEF_ELEMENT("$7",   "address",          PUBLIC_IDS_ADDR);
    CLI_DEF_ELEMENT("$8",   "INTEGER",          PUBLIC_IDS_ADDR_VAL,    MOR_PUBLIC_DIS_ADDR);


    CLI_DEF_CMD(" $1 $3 $4 $5 $6 [ $7 $8 ] ", PUBLIC_CMD_DIS);
    CLI_DEF_CMD(" $2 $3 $4 $5 $6 [ $7 $8 ] ", PUBLIC_CMD_SET);
    
    CLI_END;
}




ULONG CLI_CommandGet(VOID *pData)
{
    ULONG ulRetVal = ERROR_SUCCESS;
    CLI_CMD_PARAM_S stParam;
    UCHAR aucBuffer[256] = {0};

    /* ������Ҫ�����Ĳ��� */
    CLI_PARAM_PRASE_S astPara[] = 
    { 
        {MOR_PUBLIC_DIS_MOD,        stParam.acModName,     sizeof(stParam.acModName)}, 
        {MOR_PUBLIC_DIS_CONFIG,     stParam.acConfigName,  sizeof(stParam.acConfigName)}, 
        {MOR_PUBLIC_DIS_VALUE,      &stParam.uiValue,      sizeof(stParam.uiValue)}, 
        {MOR_PUBLIC_DIS_ADDR,       &stParam.uiAddr,       sizeof(stParam.uiAddr)}, 
    };

    YNTEST_CHK_PTR_FAILED(pData);

    STRUCT_INIT(&stParam, sizeof(stParam));
    stParam.uiAddr = USELESS_PARA;

    /* ��������,ֻ���������������MOR�Żᱻ����,Ϊ����MOR�Ĳ������������,
       ��������������δ����ָ��MOR�Ĳ�����Ҫ����Ĭ��ֵ*/
    ulRetVal = CLI_PRASE_ParamPrase(pData, astPara, ARRAY_SIZE(astPara));
    YNTEST_CHK_RET_FAILED(ulRetVal, "Prase parameter failed.\n");

    if(stParam.uiAddr == USELESS_PARA)
    {
        ulRetVal = CLI_CmdGetValue(0, &stParam, aucBuffer, 256);
        YNTEST_CHK_RET_FAILED(ulRetVal, "CLI_CmdGetValue failed.\n");
    }
    else
    {
        ulRetVal = CLI_CmdGetValuebyAddr(0, &stParam, aucBuffer, 256);
        YNTEST_CHK_RET_FAILED(ulRetVal, "CLI_CmdGetValuebyAddr failed.\n");
    }

    return ulRetVal;
}

ULONG CLI_CommandSet(IN    VOID *pData)
{
    ULONG ulRetVal = ERROR_SUCCESS;
    CLI_CMD_PARAM_S stParam;
    
    CLI_PARAM_PRASE_S astPara[] = 
    { 
        {MOR_PUBLIC_DIS_MOD,        stParam.acModName,     sizeof(stParam.acModName)}, 
        {MOR_PUBLIC_DIS_CONFIG,     stParam.acConfigName,  sizeof(stParam.acConfigName)}, 
        {MOR_PUBLIC_DIS_VALUE,      &stParam.uiValue,      sizeof(stParam.uiValue)}, 
        {MOR_PUBLIC_DIS_ADDR,       &stParam.uiAddr,       sizeof(stParam.uiAddr)}, 
    };

    YNTEST_CHK_PTR_FAILED(pData);

    STRUCT_INIT(&stParam, sizeof(stParam));
    stParam.uiAddr = USELESS_PARA;

    /* ��������,ֻ���������������MOR�Żᱻ����,Ϊ����MOR�Ĳ������������,
       ��������������δ����ָ��MOR�Ĳ�����Ҫ����Ĭ��ֵ*/
    ulRetVal = CLI_PRASE_ParamPrase(pData, astPara, ARRAY_SIZE(astPara));
    YNTEST_CHK_RET_FAILED(ulRetVal, "Prase parameter failed.\n");


    if(stParam.uiAddr == USELESS_PARA)
    {
        ulRetVal = CLI_CmdSetValue(0, &stParam);
        YNTEST_CHK_RET_FAILED(ulRetVal, "CLI_CmdSetValue failed.\n");
    }
    else
    {
        ulRetVal = CLI_CmdSetValuebyAddr(0, &stParam);
        YNTEST_CHK_RET_FAILED(ulRetVal, "CLI_CmdSetValuebyAddr failed.\n");
    }
    return ulRetVal;
}


/*****************************************************************************
 Func Name    : CLI_PublicCliGetCallBack
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : publicģ����������
 Input        : UINT uiCmd          ����id
 Output       : CLI_CIOCTL_PF *ppCallBack �ص�API��ַ
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : 
*****************************************************************************/
STATIC ULONG CLI_PublicCliGetCallBack(UINT uiKey, CLI_CIOCTL_PF *ppCallBack)
{
    UINT uiLoop;
    
    for(uiLoop=0; uiLoop < ARRAY_SIZE(g_astCLI_CIOCTLCallBack); uiLoop++)
    {
        if((uiKey == g_astCLI_CIOCTLCallBack[uiLoop].uiKey) && \
            (NULL != g_astCLI_CIOCTLCallBack[uiLoop].pfCallBack))
        {
            *ppCallBack = g_astCLI_CIOCTLCallBack[uiLoop].pfCallBack;
            return ERROR_SUCCESS;
        }
    }
    return ERROR_FAILED;
}


/*****************************************************************************
 Func Name    : CLI_PUBLIC_CallBack
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : publicģ��ص�����ʵ��
 Input        : UINT uiCmd      ����id
                VOID *pData     ���ò���
 Output       : NONE
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : 
*****************************************************************************/
ULONG CLI_PUBLIC_CallBack(IN UINT uiCmd, IN VOID *pData)
{
    CLI_CIOCTL_PF pfCmdProc = NULL;
    ULONG ulRetVal = ERROR_SUCCESS;
    UINT uiKey = uiCmd;
    
    ulRetVal = CLI_PublicCliGetCallBack(uiKey, &pfCmdProc);
    YNTEST_CHK_FAILED(ulRetVal, "get command callback failed.\n");
    return pfCmdProc(pData);
}



#ifdef  __cplusplus
}
#endif  /* __cplusplus end */

