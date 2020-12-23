/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              hint.c
   Project Code: Test App
   Module Name : key word hint
   Date Created: 2020-08-08
   Author      : p21074
   Description : 命令关键字联想实现

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
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "prv_basedef.h"
#include "cli.h"
#include "utils.h"
#include "log.h"
#include "help.h"
#include "hint.h"

STATIC ULONG CLI_HintProcShowErr(IN HINT_ERROR_INFO_S stError, INOUT BUF_INFO_S *pstBuf);
STATIC ULONG CLI_HintPreProc(IN CONST CHAR *pInBuf, INOUT CHAR **ppOutBuf);
STATIC ULONG CLI_HintProc(IN CONST CHAR *pcInBuf, OUT TEST_TREE_NODE_S **ppstLastTreeNode, INOUT UINT *uiKey);
STATIC VOID CLI_RedisplayLine(IN CONST CHAR *line);
STATIC VOID CLI_ShowPossibleNextWord(UINT uiKey, TEST_TREE_NODE_S *pstTreeNode, CONST CHAR *pcLine);

/*****************************************************************************
 Func Name    : CLI_HintProcShowErr
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 错误信息显示
 Input        : HINT_ERROR_INFO_S stError       error类型
                BUF_INFO_S *pstBuf              错误信息缓存区
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
STATIC ULONG CLI_HintProcShowErr(IN HINT_ERROR_INFO_S stError, INOUT BUF_INFO_S *pstBuf)
{
    CHAR pcBuf[512] = {0};

    YNTEST_CHK_PTR_FAILED(pstBuf);
    
    switch(stError.enErrType)
    {
        case CLI_ERROR_NULL:
            bufsprintf(pstBuf, "\nWarning: nullptr detected in function ' CLI_CliParse '\n");
            break;
        case CLI_ERROR_OVERFLOW:
            CLI_FillBufWithSpace(pcBuf, stError.uiParseLen + strlen(g_acPrompt));
            bufsprintf(pstBuf,"\n%s^\n%s\n",pcBuf,g_acErrInfo[3]);
            break;
        case CLI_ERROR_INCMPLETE:
            CLI_FillBufWithSpace(pcBuf, stError.uiParseLen + strlen(g_acPrompt)-1);
            bufsprintf(pstBuf,"\n%s^\n%s\n",pcBuf,g_acErrInfo[0]);
            break;
        case CLI_ERROR_UNDEFINED:
            CLI_FillBufWithSpace(pcBuf, stError.uiParseLen + strlen(g_acPrompt));
            bufsprintf(pstBuf,"\n%s^\n%s\n",pcBuf,g_acErrInfo[1]);
            break;
        case CLI_ERROR_INTEGER:
            CLI_FillBufWithSpace(pcBuf, stError.uiParseLen + strlen(g_acPrompt));
            bufsprintf(pstBuf,"\n%s^\n%s\n",pcBuf,g_acErrInfo[2]);
            break;
        case CLI_ERROR_STRING:
            CLI_FillBufWithSpace(pcBuf, stError.uiParseLen + strlen(g_acPrompt));
            bufsprintf(pstBuf,"\n%s^\n%s\n",pcBuf,g_acErrInfo[4]);
            break;
        case CLI_ERROR_OVERSIZE:
            CLI_FillBufWithSpace(pcBuf, stError.uiParseLen + strlen(g_acPrompt));
            bufsprintf(pstBuf,"\n%s^\n%s\n",pcBuf,g_acErrInfo[5]);
         default: break;
    }
    return ERROR_SUCCESS;
}

/* 命令提示输入行预处理,只对'?'前的字符串进行联想 */
/*****************************************************************************
 Func Name    : CLI_HintPreProc
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 关键字联想输入行预处理
 Input        : CONST CHAR *pInBuf       入Buffer
                
 Output       : CHAR **ppOutBuf          出Buffer
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 命令提示输入行预处理,只对'?'(光标)前的字符串进行联想
*****************************************************************************/
STATIC ULONG CLI_HintPreProc(IN CONST CHAR *pInBuf, INOUT CHAR **ppOutBuf)
{
    CONST CHAR *pcLine;
    CHAR *pcBuffer = NULL;
    UINT uiInputLen = 0;
    UINT uiLoop = 0;
    
    YNTEST_CHK_PTR_FAILED(pInBuf);
    YNTEST_CHK_PTR_FAILED(ppOutBuf);
    
    pcLine = pInBuf;
    uiInputLen = strlen(pcLine);
    pcBuffer = (CHAR *)malloc(uiInputLen + 1);
    YNTEST_CHK_PTR_FAILED(pcBuffer);
    YNTEST_CLEAR_BUF(pcBuffer, uiInputLen+1);

    while((uiLoop < uiInputLen) && (pcLine[uiLoop] != '\0'))
    {
        if(pcLine[uiLoop] == '?')
        break;

        pcBuffer[uiLoop] = pcLine[uiLoop];
        uiLoop++;
    }
    pcBuffer[uiLoop] = '\0';
    *ppOutBuf = pcBuffer;

    return ERROR_SUCCESS;
}

/*****************************************************************************
 Func Name    : CLI_HintProc
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 关键字联想输入行处理
 Input        : CONST CHAR *pInBuf       入Buffer
                
 Output       : TEST_TREE_NODE_S **ppstLastTreeNode  指向需要联想的关键字节点
                UINT *uiKey     联想方式
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
STATIC ULONG CLI_HintProc(IN CONST CHAR *pcInBuf, OUT TEST_TREE_NODE_S **ppstLastTreeNode, INOUT UINT *uiKey)
{
    ULONG ulRet = ERROR_SUCCESS;
    CONST CHAR *pcTmp = NULL;
    CHAR *pcPraseLine = NULL;
    HINT_ERROR_INFO_S stError = {.enErrType = CLI_ERROR_NONE, .uiParseLen = 0};
    UINT uiLen;
    UINT uiSubLen = 0;
    UINT uiTotal = 0;
    CHAR acArgName[MAX_INPUT_STR_LEN] = {0}; /* 命令关键字包括可能会输入的字符串最大长度限定80 bytes */
    UINT uiErrCode = 0;
    TEST_TREE_NODE_S *pstTree = NULL;
    TEST_TREE_NODE_S *pstTmpTree;
    CLI_MODULE_S *pstMoudle = CLI_GetMoudleInfo(g_uiMID);
    CHAR acShowBuf[BUF_SIZE_512] = {0};
    BUF_INFO_S stBuf;

    YNTEST_CHK_PTR_FAILED(pcInBuf);
    YNTEST_CHK_PTR_FAILED(ppstLastTreeNode);
    
    pstMoudle = CLI_GetMoudleInfo(g_uiMID);
    YNTEST_CHK_PTR_FAILED(pstMoudle);
    
    pcTmp = pcInBuf;
    pstTree = &pstMoudle->stTree;
    ulRet = CLI_HintPreProc(pcTmp, (CHAR **)&pcPraseLine);
    if(ulRet)
    {
        if(NULL != pcPraseLine)
        free(pcPraseLine);
        Log_Print(LOG_LEVEL_ERROR, "CLI_HintPreProc : failed.\n");
        return ulRet;
    }
    uiLen = strlen(pcPraseLine);
    
    /* 联想下一个可能的命令关键字前, 先检查当前已输入的内容是否符合命令格式的定义,
       否则将不会进行后续的关键字联想 */
    while(uiTotal < uiLen)
    {
        YNTEST_CLEAR_BUF(acArgName, sizeof(acArgName));
        uiSubLen = CLI_SubCliParse(pcPraseLine + uiTotal, acArgName, sizeof(acArgName), (UINT *)&uiErrCode);
        uiTotal += uiSubLen;
        
        if(uiErrCode)
        {
            stError.enErrType = (CLI_PRASE_ERROR_E)uiErrCode;
            stError.uiParseLen = uiTotal - uiSubLen;
            break;
        }
        /* 预处理没有处理行末的空格, 若解析出的字符串没有内容则认为所有的关键字都已检查完*/
        if(acArgName[0] == '\0')
        {
            break;
        }
        /* 若当前子树节点已经是leaf节点需要判断后面输入是否为多余输入,
           尽管当前节点被标记为leaf节点,如果检查到该节点下挂载有子树,则该节点并不是真的leaf节点
         */
        if((pstTree->bLeaf) && (pstTree->stChild.stHead.pstNext == &pstTree->stChild.stHead))
        {
            stError.enErrType = CLI_ERROR_OVERSIZE;
            stError.uiParseLen = uiTotal - uiSubLen;
            *uiKey = HINT_ERROR;
            break;
        }
        pstTmpTree = CLI_Tree_FindSameName(pstTree, acArgName, (UINT *)&uiErrCode);
        if(NULL == pstTmpTree)
        {
            if(uiErrCode)
            {
                stError.enErrType = (CLI_PRASE_ERROR_E)uiErrCode;
                stError.uiParseLen = uiTotal - uiSubLen;
                break;
            }
            else
            {
                stError.enErrType = CLI_ERROR_UNDEFINED;
                stError.uiParseLen = uiTotal - uiSubLen;
                break;
            }
        }
        else
        {
            pstTree = pstTmpTree;
        }
    }
    /* 解析完,释放临时分配的内存 */
    if(NULL != pcPraseLine)
    {
        free(pcPraseLine);
    }
    /* 若当前输入已经是完整的命令行内容，则不进行后续的联想 */
    if(pstTree && pstTree->bLeaf && \
    (pstTree->stChild.stHead.pstNext == &pstTree->stChild.stHead))
    {
        /* 若前面已经*uiKey赋值，这将不在赋值 */
        if(*uiKey == HINT_DEFAULT)
        {
            *uiKey = HINT_COMPLETE;
        }
    }
    /* 检查到当前输入有错 */
    if(stError.enErrType)
    {
        CLI_BufInit(&stBuf, acShowBuf, sizeof(acShowBuf), 0);
        ulRet = CLI_HintProcShowErr(stError, &stBuf);
        YNTEST_CHK_FAILED(ulRet, "test_HintProcShowErr : Process failed.\n");
        if(CLI_BufGetSize(&stBuf))
        {
            printf("%s",acShowBuf);
        }
        *ppstLastTreeNode = NULL;
        return ERROR_FAILED;
    }

    /* 记录需要联想提示的关键字所在结点信息 */
    *ppstLastTreeNode = pstTree;
    return ERROR_SUCCESS;
}

/* 显示已输入的内容 */
/*****************************************************************************
 Func Name    : CLI_RedisplayLine
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 关键字联想完成更新输入行
 Input        : CONST CHAR *line       入Buffer
 Output       : NONE
 Return       : NONE
 Caution      : 
*****************************************************************************/

STATIC VOID CLI_RedisplayLine(IN CONST CHAR *line)
{
    UINT uiLen;
    CHAR *pcTemp = NULL;
    CHAR *pcCurPos = NULL;
    UINT uiCpyLen = 0;
    
    CHAR acString[] = {""};

    /* 处理输入行中的'?'符号 */
    uiLen = strlen(line);
    pcTemp = (CHAR *)malloc(uiLen + 1);
    if(NULL == pcTemp)
    {
        Log_Print(LOG_LEVEL_ERROR," malloc failed.\n");
        return;
    }
    YNTEST_CLEAR_BUF(pcTemp, uiLen+1);
    pcCurPos = strchr(line, '?');
    if(pcCurPos)
    {
        uiCpyLen = pcCurPos - line;
        if(uiCpyLen)
        {
            /* 拷贝'?'之前的内容到缓存区 */
            CLI_Memcpy(pcTemp, line, uiCpyLen);
            pcTemp[uiCpyLen] = '\0';

            /* '?'出现在行中,非行末 */
            if(line[uiCpyLen + 1] != '\0')
            {
                strcat(pcTemp, line+uiCpyLen+1);
            }
        }
        else
        {
            strcat(pcTemp, acString);
        }
    }
    else
    {
        strncpy(pcTemp,line,uiLen);
    }
    
    if (rl_prompt && rl_already_prompted)
    {
        rl_on_new_line_with_prompt ();
    }
    else
    {
        rl_on_new_line ();
    }
    (*rl_redisplay_function) ();

    
    rl_replace_line(pcTemp,0);
    free(pcTemp);
    rl_point = rl_end;

    return;
}

/*****************************************************************************
 Func Name    : CLI_ShowPossibleNextWord
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 显示可能关键字信息
 Input        : UINT uiKey                      联想方式
                TEST_TREE_NODE_S *pstTreeNode   指向需要联想的关键字节点
                CONST CHAR *pcLine              入Buffer
 Output       : NONE
 Return       : NONE
 Caution      : 
*****************************************************************************/
STATIC VOID CLI_ShowPossibleNextWord(UINT uiKey, TEST_TREE_NODE_S *pstTreeNode, CONST CHAR *pcLine)
{
    DTQ_HEAD_S *pstChildList;
    DTQ_NODE_S *pstNode;
    CLI_MODULE_S *pstMoudle ;
    TEST_TREE_NODE_S *pstTmpNode = NULL;
    CHAR *pcHelpStr = NULL;
    UINT uiCurPos = 0;
    CHAR *pcShowBuf;
    UINT uiLen = 4 * BUF_SIZE_1K;
    
    pcShowBuf = (CHAR *)malloc(uiLen);
    if(NULL == pcShowBuf )
    {
        return;
    }
    YNTEST_CLEAR_BUF(pcShowBuf, uiLen);
    switch(uiKey)
    {
        /* 没有输入 */
        case HINT_FROM_HEAD:
        {
            pstMoudle = CLI_GetMoudleInfo(g_uiMID);
            pstChildList = &pstMoudle->stTree.stChild;
            yntest_ssprintf(uiCurPos, pcShowBuf, uiLen, "\n >/User command view:\n");
            DTQ_FOREACH(pstChildList, pstNode)
            {
                pstTmpNode = container_of(pstNode, TEST_TREE_NODE_S, stBrother);
                if(uiCurPos + BUF_SIZE_128 > uiLen)
                {
                    pcShowBuf = realloc(pcShowBuf, (uiLen += BUF_SIZE_1K));
                    if(NULL == pcShowBuf)
                    {
                        free(pcShowBuf);
                        return;
                    }
                    
                    YNTEST_CLEAR_BUF(pcShowBuf+uiLen-BUF_SIZE_1K, BUF_SIZE_1K);
                }
                pcHelpStr = CLI_GetHelpString(pstTmpNode->pstElement->uiIds);
                if(NULL == pcHelpStr)
                {
                    yntest_ssprintf(uiCurPos, pcShowBuf, uiLen, "  %-20s%s\n",pstTmpNode->pstElement->pcName,"Not defined");
                }
                else
                {
                    yntest_ssprintf(uiCurPos, pcShowBuf, uiLen, "  %-20s%s\n",pstTmpNode->pstElement->pcName,pcHelpStr);
                }    
            }
            printf("%s\n",pcShowBuf);
            free(pcShowBuf);
        }
        /* 输入有误 */
        case HINT_ERROR:
        {
            CLI_RedisplayLine(pcLine);
            break;
        }
        /* 有输入且输入无误 */
        case HINT_FROM_SPEC:
        {
            if(!pstTreeNode)
            {
                free(pcShowBuf);
                CLI_RedisplayLine(pcLine);
                return;
            }
            pstChildList = &pstTreeNode->stChild;
            yntest_ssprintf(uiCurPos, pcShowBuf, uiLen, "\n >/Possible next word:\n");
            
            /* 检测到当前节点为某子树的leaf节点 */
            if(pstTreeNode->bLeaf)
            {
                yntest_ssprintf(uiCurPos, pcShowBuf, uiLen, "  %-20s%s\n","<cr>","Execute current input line");
            }
            DTQ_FOREACH(pstChildList, pstNode)
            {
                pstTmpNode = container_of(pstNode, TEST_TREE_NODE_S, stBrother);
                if(uiCurPos + BUF_SIZE_128 > uiLen)
                {
                    pcShowBuf = realloc(pcShowBuf, (uiLen += BUF_SIZE_1K));
                    if(NULL == pcShowBuf)
                    {
                        free(pcShowBuf);
                        return;
                    }
                    YNTEST_CLEAR_BUF(pcShowBuf+uiLen-BUF_SIZE_1K, BUF_SIZE_1K);
                }
                
                pcHelpStr = CLI_GetHelpString(pstTmpNode->pstElement->uiIds);
                if(NULL == pcHelpStr)
                {
                    yntest_ssprintf(uiCurPos, pcShowBuf, uiLen, "  %-20s%s\n",pstTmpNode->pstElement->pcName,"Not defined");
                }
                else
                {
                    yntest_ssprintf(uiCurPos, pcShowBuf, uiLen, "  %-20s%s\n",pstTmpNode->pstElement->pcName,pcHelpStr);
                }
            }
            printf("%s\n",pcShowBuf);
            free(pcShowBuf);
            CLI_RedisplayLine(pcLine);
            break;
        }
        /* 已经输入完整的命令格式 */
        case HINT_COMPLETE:
        {
            printf("\n%% You have already entered complete commandline, please press \'ENTER\' and continue.\n");
            CLI_RedisplayLine(pcLine);
            break;
        }
        default: break;
    }
}

/* 命令关键字联想处理函数 */
/*****************************************************************************
 Func Name    : test_CmdKeyWordHint
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 关键字联想实现入口函数
 Input        : INT iCount                      联想方式
                INT Key                         与按键绑定的keymap
 Output       : NONE
 Return       : int
 Caution      : 
*****************************************************************************/
INT test_CmdKeyWordHint(INT iCount, INT Key)
{
    CHAR *pcInput = NULL;
    UINT uiSaveLen;
    UINT uiCount = 0;
    ULONG ulRetVal = ERROR_SUCCESS;
    TEST_TREE_NODE_S *pstTreeNode = NULL;
    UINT uiKey = HINT_DEFAULT;

    rl_insert(iCount, Key);
    uiSaveLen = (rl_point < rl_end) ? rl_end : rl_point;

    /* 终端有字符输入 */
    if(uiSaveLen > 0)
    {
        pcInput = (CHAR *)malloc(uiSaveLen + 1);
        if(pcInput == NULL)
        {
            return -1;
        }
        else
        {
            CLI_Memcpy(pcInput,rl_line_buffer, uiSaveLen);
            pcInput[uiSaveLen] = '\0';
        }
        /* 输入'空格' 视为无效输入,先检查是否为空白输入(空白输入也是有字符输入的结果) */
        while(YNTEST_WHITESPACE(pcInput[uiCount]) && (pcInput[uiCount] != '\0'))
        {
            uiCount++;
        }

        /* 检测到输入字符全为空白字符(' '或'\t') */
        if(++uiCount == strlen(pcInput))
        {
            uiKey = HINT_FROM_HEAD;
        }
        else
        {
            /* 已经有有效字符输入，处理方式 */
            ulRetVal = CLI_HintProc(pcInput, &pstTreeNode, &uiKey);

            /* 输入行有错将不进行关键字联想 */
            if(ulRetVal)
            {
                uiKey = HINT_ERROR;
            }
            else
            {
                /* 已输入的内容没有错误 */
                uiKey = (HINT_DEFAULT != uiKey) ? uiKey : HINT_FROM_SPEC;
            }
        }
    }
    /* no input detected */
    else
    {
        uiKey = HINT_FROM_HEAD;
    }
    CLI_ShowPossibleNextWord(uiKey, pstTreeNode, pcInput);
    free(pcInput);
    return 0;
    
}


#ifdef  __cplusplus
}
#endif  /* __cplusplus end */

