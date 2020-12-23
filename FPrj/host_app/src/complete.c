/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              complete.c
   Project Code: Test App
   Module Name : CLI
   Date Created: 2020-08-02
   Author      : p21074
   Description : keyword自动补全实现

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
#include "complete.h"
#include <readline/readline.h>
#include <readline/history.h>


extern CONST CHAR *g_acCompletionGroup[MAX_COMPLETION_NUM];


VOID test_initialize_readline (VOID)
{
    rl_readline_name = "Test_App";
    rl_attempted_completion_function = test_command_completion;
}

CHAR **test_command_completion(const char *pcText, int iStart, int iEnd)
{
    char **ppcMatch;
    ppcMatch = (char **)NULL;

    ppcMatch = rl_completion_matches (pcText, test_command_generator);

    return (ppcMatch);
}

CHAR *test_command_generator(const CHAR *pcText, INT iState)
{
    STATIC UINT uiLen,uiIndex;
    CONST CHAR *pcName;

    if(NULL == pcText)
    {
        return ((CHAR *)NULL);
    }
    if(!iState)
    {
        uiLen = strlen(pcText);
        uiIndex = 0;
    }
    while((uiIndex < MAX_COMPLETION_NUM) && (NULL != g_acCompletionGroup[uiIndex]))
    {
        pcName = g_acCompletionGroup[uiIndex];
        uiIndex++;
        if(0 == strncmp(pcName,pcText,uiLen))
        {
            return DupPointer(pcName);
        }
    }
    return NULL;
}

CHAR *DupPointer(IN CONST CHAR *pcPtr)
{
    CHAR    *pcTem;
    DBGASSERT_WITH_RETURN(NULL != pcPtr, NULL);
    
    pcTem = (CHAR *)malloc(strlen(pcPtr) + 1);
    if(NULL == pcTem)
    {
        return NULL;
    }
    strcpy(pcTem, pcPtr);
    return pcTem;
}


#ifdef  __cplusplus
}
#endif  /* __cplusplus end */

