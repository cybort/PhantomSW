/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              stack.c
   Project Code: Test App
   Module Name : User Stack
   Date Created: 2020-08-02
   Author      : p21074
   Description : 用户定义栈结构实现接口

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/


#ifdef  __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "prv_basedef.h"
#include "log.h"
#include "utils.h"
#include "stack.h"

/*****************************************************************************
 Func Name    : CLI_InitViewStack
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : Initialize struct
 Input        : VIEW_STACK_S *pstPara      Target to be initialized
 Output       : none
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      :
*****************************************************************************/

ULONG CLI_InitViewStack(VIEW_STACK_S *pstPara)
{
    UINT uiLoop = 0;
    
    for(uiLoop = 0; uiLoop < MAX_STACK_SIZE; uiLoop++)
    {
        pstPara->pacPrompt[uiLoop] = NULL;
        pstPara->auiMoudle[uiLoop] = DEFAULT_MOUDLE;
    }
    pstPara->uiTop = MAX_STACK_SIZE;

    return ERROR_SUCCESS;
}

/* 入栈操作 */
/*****************************************************************************
 Func Name    : CLI_PushViewStack
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : Push data in stack 
 Input        : VIEW_STACK_S *pstPara      Target stack
                IN CONST VOID *pInBuf      Current view is going to be saved
                UINT uiNum                 Current moudle to be saved
 Output       : none
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      :
*****************************************************************************/

ULONG CLI_PushViewStack(VIEW_STACK_S *pstStack, IN CONST VOID *pInBuf, UINT uiNum)
{
    CHAR *pcTemp;
    UINT uiLen;

    YNTEST_CHK_PTR_FAILED(pstStack);
    YNTEST_CHK_PTR_FAILED(pInBuf);

    if(pstStack->uiTop == 0)
    {
        Log_Print(LOG_LEVEL_ERROR, "Stack over flow, current stack size is %d\n",pstStack->uiTop);
        return ERROR_FAILED;
    }
    uiLen = strlen(pInBuf);
    pstStack->uiTop--;
    pcTemp = malloc(uiLen + 1);
    if(NULL == pcTemp)
    {
        Log_Print(LOG_LEVEL_ERROR, "malloc failed.\n");
        return ERROR_FAILED;
    }
    YNTEST_CLEAR_BUF(pcTemp,uiLen+1);
    CLI_Memcpy(pcTemp, pInBuf, uiLen);
    pcTemp[uiLen] = '\0';
    pstStack->pacPrompt[pstStack->uiTop] = pcTemp;
    pstStack->auiMoudle[pstStack->uiTop] = uiNum;

    return ERROR_SUCCESS;
}

/* 出栈操作 */
/*****************************************************************************
 Func Name    : CLI_PopViewStack
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : Push data in stack 
 Input        : VIEW_STACK_S *pstPara      Target stack
                UINT uiBufSize             Out buffer size
 Output       : CHAR *pcOutBuf             Pointer to the out buffer
                UINT *uiNum                Pointer to the moudle id
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      :
*****************************************************************************/

ULONG CLI_PopViewStack(IN VIEW_STACK_S *pstStack, OUT CHAR *pcOutBuf, IN UINT uiBufSize, OUT UINT *uiNum)
{
    ULONG ulRetVal = ERROR_SUCCESS;

    YNTEST_CHK_PTR_FAILED(pstStack);
    YNTEST_CHK_PTR_FAILED(pcOutBuf);

    if(pstStack->uiTop == MAX_STACK_SIZE)
    {
        Log_Print(LOG_LEVEL_ERROR, "Pop stack failed, stack is empty.\n");
        return ERROR_FAILED;
    }
    (VOID)strlcpy(pcOutBuf, pstStack->pacPrompt[pstStack->uiTop], uiBufSize);
    *uiNum = pstStack->auiMoudle[pstStack->uiTop];

    /* 出栈后释放申请的内存空间 */
    free(pstStack->pacPrompt[pstStack->uiTop]);
    pstStack->pacPrompt[pstStack->uiTop] = NULL;
    pstStack->uiTop++;

    return ulRetVal;
}


#ifdef  __cplusplus
}
#endif

