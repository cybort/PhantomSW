/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              help.c
   Project Code: Test App
   Module Name : cli key word description
   Date Created: 2020-08-08
   Author      : p21074
   Description : ����ؼ���������Ϣʵ���ļ�

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
#include "prv_basedef.h"
#include "global.h"
#include "help.h"


STATIC ULONG CLI_KeyInfoInit(VOID);
STATIC ULONG CLI_LoadModleStr(UINT uiMoudle, CONST CHAR *ppcGroup[], UINT uiNum);

STR_INFO_S g_astKeyInfo[MAX_MOUDLE];

/********************************************************
*                   PUBLICģ��ؼ���ID                       *
********************************************************/

STATIC CONST CHAR *g_aszPublicStr[] = {
    "",                                                 /* PUBLIC_IDS_BEGIN */
    "Display imformation of specific",                  /* PUBLIC_IDS_DIS */
    "Set value on specfic",                             /* PUBLIC_IDS_SET */
    "Specficed module name, string format(1-16)",       /* PUBLIC_IDS_MOD */
    "Specficed config name, string format(1-16)",       /* PUBLIC_IDS_CONFIG */
    "parameter value",                                  /* PUBLIC_IDS_VALUE */
    "parameter value of address",                       /* PUBLIC_IDS_ADDR */
    "Value",                                            /* PUBLIC_IDS_ADDR */
    "Specficed address",                                /* PUBLIC_IDS_ADDR */
};


/*****************************************************************************
 Func Name    : CLI_KeyInfoInit
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �ؼ���������Ϣ�����س�ʼ��API
 Input        : NONE
 Output       : NONE
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : 
*****************************************************************************/
STATIC ULONG CLI_KeyInfoInit(VOID)
{
    UINT uiLoop;

    for(uiLoop = 0; uiLoop < MAX_MOUDLE; uiLoop++)
    {
        g_astKeyInfo[uiLoop].ppcStrGroup = NULL;
        g_astKeyInfo[uiLoop].bUsed = BOOL_FALSE;
        g_astKeyInfo[uiLoop].uiMoudle = USELESS_PARA;
        g_astKeyInfo[uiLoop].uiSize = 0;
    }
    return ERROR_SUCCESS;
}

/* ���عؼ�����Ϣ���鵽ȫ�ֽṹ����,��ģ������� */
/*****************************************************************************
 Func Name    : CLI_LoadModleStr
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ���عؼ�����Ϣ���鵽ȫ�ֽṹ����,��ģ�������
 Input        : UINT uiMoudle       ģ��ID
                CONST CHAR *ppcGroup[]  ģ��ؼ�������group
                UINT uiNum          ģ������group size
 Output       : NONE
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : 
*****************************************************************************/
STATIC ULONG CLI_LoadModleStr(IN UINT uiMoudle, IN CONST CHAR *ppcGroup[], IN UINT uiNum)
{
    UINT uiLoop = 0;
    
    YNTEST_CHK_FAILED(uiMoudle >= MAX_MOUDLE, "Exceed maxium moudle number, moudle = %d\n",uiMoudle);
    YNTEST_CHK_PTR_FAILED(ppcGroup);

    while((uiLoop < MAX_MOUDLE) && (BOOL_TRUE == g_astKeyInfo[uiLoop].bUsed))
    {
        /* �Ѿ�load�����ｫ����load */
        if(uiMoudle == g_astKeyInfo[uiLoop].uiMoudle)
        {
            return ERROR_SUCCESS;
        }
        uiLoop++;
    }
    if(MAX_MOUDLE == uiLoop)
    {
        Log_Print(LOG_LEVEL_ERROR, "CLI_LoadModleStr: moudle num exceed limit.\n");
        return ERROR_FAILED;
    }

    g_astKeyInfo[uiLoop].bUsed = BOOL_TRUE;
    g_astKeyInfo[uiLoop].ppcStrGroup = (CHAR **)ppcGroup;
    g_astKeyInfo[uiLoop].uiMoudle = uiMoudle;
    g_astKeyInfo[uiLoop].uiSize = uiNum;

    return ERROR_SUCCESS;

}

/* ��ȡ�����ַ�����Ϣ */
/*****************************************************************************
 Func Name    : CLI_GetHelpString
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ��ȡ�ؼ���������ϢAPI
 Input        : UINT uiStrId    �ؼ�������ID
 Output       : NONE
 Return       : �ɹ�: ����ָ��ùؼ�����Ϣ��ָ�룻
                ʧ��: ����NULL
 Caution      : 
*****************************************************************************/
VOID *CLI_GetHelpString(IN UINT uiStrId)
{
    UINT uiMoudle;
    UINT uiHelpStr;
    UINT uiLoop = 0;

    uiMoudle = ((uiStrId - STR_BASE) >> 16) & 0xFF;
    uiHelpStr = uiStrId & 0xFFFF;

    while((uiLoop < MAX_MOUDLE) && (uiMoudle != g_astKeyInfo[uiLoop].uiMoudle))
    {
        uiLoop++;
    }

    /* ģ��ID����string id������Χֱ�ӷ���NULL */
    if((uiLoop >= MAX_MOUDLE) || (uiHelpStr >= g_astKeyInfo[uiLoop].uiSize))
    {
        return NULL;
    }
    if(NULL != g_astKeyInfo[uiLoop].ppcStrGroup[uiHelpStr])
    {
        return (VOID *)g_astKeyInfo[uiLoop].ppcStrGroup[uiHelpStr];
    }
    else
    {
        return NULL;
    }
}

/*****************************************************************************
 Func Name    : CLI_LoadAllMoudleStr
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �������йؼ�����Ϣ
 Input        : NONE
 Output       : NONE
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : 
*****************************************************************************/
ULONG CLI_LoadAllMoudleStr(VOID)
{
    ULONG ulRetVal = ERROR_SUCCESS;

    ulRetVal = CLI_KeyInfoInit();

    ulRetVal += CLI_LoadModleStr(CLI_MOUDLE_PUBLIC, g_aszPublicStr, ARRAY_SIZE(g_aszPublicStr));
    
    return ulRetVal;
}


#ifdef  __cplusplus
}
#endif

