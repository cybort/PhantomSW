/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              help.c
   Project Code: Test App
   Module Name : cli key word description
   Date Created: 2020-08-08
   Author      : p21074
   Description : 命令关键字描述信息实现文件

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
*                   PUBLIC模块关键字ID                       *
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
 Description  : 关键字描述信息索引池初始化API
 Input        : NONE
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
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

/* 挂载关键字信息数组到全局结构体下,按模块组挂载 */
/*****************************************************************************
 Func Name    : CLI_LoadModleStr
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 挂载关键字信息数组到全局结构体下,按模块组挂载
 Input        : UINT uiMoudle       模块ID
                CONST CHAR *ppcGroup[]  模块关键字索引group
                UINT uiNum          模块索引group size
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
STATIC ULONG CLI_LoadModleStr(IN UINT uiMoudle, IN CONST CHAR *ppcGroup[], IN UINT uiNum)
{
    UINT uiLoop = 0;
    
    YNTEST_CHK_FAILED(uiMoudle >= MAX_MOUDLE, "Exceed maxium moudle number, moudle = %d\n",uiMoudle);
    YNTEST_CHK_PTR_FAILED(ppcGroup);

    while((uiLoop < MAX_MOUDLE) && (BOOL_TRUE == g_astKeyInfo[uiLoop].bUsed))
    {
        /* 已经load过这里将不再load */
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

/* 获取帮助字符串信息 */
/*****************************************************************************
 Func Name    : CLI_GetHelpString
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 获取关键字描述信息API
 Input        : UINT uiStrId    关键字索引ID
 Output       : NONE
 Return       : 成功: 返回指向该关键字信息的指针；
                失败: 返回NULL
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

    /* 模块ID或者string id超过范围直接返回NULL */
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
 Description  : 加载所有关键字信息
 Input        : NONE
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
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

