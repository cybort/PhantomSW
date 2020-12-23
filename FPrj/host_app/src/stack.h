/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              stack.h
   Project Code: Test App
   Module Name : User Stack
   Date Created: 2020-08-02
   Author      : p21074
   Description : 用户定义栈结构头文件

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/


#ifndef __CLI_STACK_H__
#define __CLI_STACK_H__

#ifdef  __cplusplus
extern "C" {
#endif

#define MAX_STACK_SIZE (4)      /* 定义数据栈的最大深度 */
#define DEFAULT_MOUDLE  (0xffU)

typedef struct tagVIEW_STACK
{
    CHAR *pacPrompt[MAX_STACK_SIZE];
    UINT auiMoudle[MAX_STACK_SIZE];
    UINT uiTop;
}VIEW_STACK_S;

ULONG CLI_InitViewStack(VIEW_STACK_S *pstPara);
ULONG CLI_PushViewStack(VIEW_STACK_S *pstStack, IN CONST VOID *pInBuf, UINT uiNum);
ULONG CLI_PopViewStack(IN VIEW_STACK_S *pstStack, OUT CHAR *pcOutBuf, IN UINT uiBufSize, OUT UINT *uiNum);




#ifdef  __cplusplus
}
#endif

#endif

