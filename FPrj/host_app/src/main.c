/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              main.c
   Project Code: Test App
   Module Name : CLI
   Date Created: 2020-08-02
   Author      : p21074
   Description : main entrance of app

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "prv_basedef.h"

#include "cli.h"
#include "mor.h"
#include "stack.h"
#include "utils.h"
#include "help.h"
#include "log.h"
#include "cmds.h"
#include "complete.h"
#include "global.h"
#include "hostserver.h"

#include <readline/readline.h>
#include <readline/history.h>


CHAR g_acPrompt[BUF_SIZE_64] = {"[SEMI] "};

extern VIEW_STACK_S g_stViewInfoStack;
extern MOUDLE_INFO_S g_stMoudleInfo;

extern volatile UINT g_uiMID;
STATIC ULONG CLI_InitAll(VOID);

STATIC ULONG CLI_InitAll(VOID)
{
    ULONG ulRetVal = ERROR_SUCCESS;

    /* log·��,�����ʽ���� */
    ulRetVal = CLI_SetLog("./log",NULL, LOG_LEVEL_ERROR,LOG_FILE);
    YNTEST_CHK_FAILED(ulRetVal, "set log failed.\n");

    /* ��ģ�����ÿռ��ʼ�� */
    ulRetVal = CLI_MoudleInfoInit();
    YNTEST_CHK_FAILED(ulRetVal, "moudle initialize failed.\n");

    /* ���ó�ʼģ����ͼΪPUBLIC */
    g_uiMID = (UINT)CLI_MOUDLE_PUBLIC;

    /* ˽�ж�������ջ��ʼ�� */
    ulRetVal = CLI_InitViewStack(&g_stViewInfoStack);
    YNTEST_CHK_FAILED(ulRetVal, "private statck initialize failed.\n");

    /* ���عؼ���description */
    ulRetVal = CLI_LoadAllMoudleStr();
    YNTEST_CHK_FAILED(ulRetVal, "load string IDS failed.\n");

    /* ��ģ������ע�� */
    ulRetVal = CLI_RegAllCmd();
    YNTEST_CHK_FAILED(ulRetVal, "Register command failed.\n");

    /* ģ��ص�����ע�� */
    ulRetVal = CLI_RegAllCallBack();
    YNTEST_CHK_FAILED(ulRetVal, "Register callback function failed.\n");

    /* key word ��ȫ��ʽ��ʼ�� */
    test_initialize_readline();

    ulRetVal = HostServerInit();
    YNTEST_CHK_FAILED(ulRetVal, "HostServerInit failed.\n");

    return ulRetVal;
}


INT main(VOID)
{
    ULONG ulRetVal = ERROR_SUCCESS;
    CLI_MODULE_S *pstMoudle = NULL;
    CHAR *pcLine = NULL;
    
    /* Initialize begin, this routine must executed before while */
    ulRetVal = CLI_InitAll();
    if(ulRetVal)
    {
        exit(1);
    }
    /* Initialize end */
    printf("\n*************************************************************************\n");
    printf("*                       Formula Software Platform                       *\n");
    printf("*************************************************************************\n\n");
    while(1)
    {
        pcLine = readline(g_acPrompt);
        
        ulRetVal = CLI_CliPreProc((VOID *)pcLine);
        if(ulRetVal)
        {
            free(pcLine);
            continue;
        }
        /* �������룬�����ɻ��� */
        add_history(pcLine);
        
        pstMoudle = CLI_GetMoudleInfo((CLI_MOUDLE_E)g_uiMID);
        if(pstMoudle == NULL)
        {
            Log_Print(LOG_LEVEL_ERROR, "none pointer detect.\n");
        }
        ulRetVal = CLI_CliProc(pcLine, (VOID *)pstMoudle);
        free(pcLine);
    }
    return 0;
}

#ifdef  __cplusplus
}
#endif  /* __cplusplus end */

