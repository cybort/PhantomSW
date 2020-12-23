/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              hint.c
   Project Code: Test App
   Module Name : key word hint
   Date Created: 2020-08-08
   Author      : p21074
   Description : ����ؼ�������ʵ��

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
 Description  : ������Ϣ��ʾ
 Input        : HINT_ERROR_INFO_S stError       error����
                BUF_INFO_S *pstBuf              ������Ϣ������
 Output       : NONE
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
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

/* ������ʾ������Ԥ����,ֻ��'?'ǰ���ַ����������� */
/*****************************************************************************
 Func Name    : CLI_HintPreProc
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �ؼ�������������Ԥ����
 Input        : CONST CHAR *pInBuf       ��Buffer
                
 Output       : CHAR **ppOutBuf          ��Buffer
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : ������ʾ������Ԥ����,ֻ��'?'(���)ǰ���ַ�����������
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
 Description  : �ؼ������������д���
 Input        : CONST CHAR *pInBuf       ��Buffer
                
 Output       : TEST_TREE_NODE_S **ppstLastTreeNode  ָ����Ҫ����Ĺؼ��ֽڵ�
                UINT *uiKey     ���뷽ʽ
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
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
    CHAR acArgName[MAX_INPUT_STR_LEN] = {0}; /* ����ؼ��ְ������ܻ�������ַ�����󳤶��޶�80 bytes */
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
    
    /* ������һ�����ܵ�����ؼ���ǰ, �ȼ�鵱ǰ������������Ƿ���������ʽ�Ķ���,
       ���򽫲�����к����Ĺؼ������� */
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
        /* Ԥ����û�д�����ĩ�Ŀո�, �����������ַ���û����������Ϊ���еĹؼ��ֶ��Ѽ����*/
        if(acArgName[0] == '\0')
        {
            break;
        }
        /* ����ǰ�����ڵ��Ѿ���leaf�ڵ���Ҫ�жϺ��������Ƿ�Ϊ��������,
           ���ܵ�ǰ�ڵ㱻���Ϊleaf�ڵ�,�����鵽�ýڵ��¹���������,��ýڵ㲢�������leaf�ڵ�
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
    /* ������,�ͷ���ʱ������ڴ� */
    if(NULL != pcPraseLine)
    {
        free(pcPraseLine);
    }
    /* ����ǰ�����Ѿ������������������ݣ��򲻽��к��������� */
    if(pstTree && pstTree->bLeaf && \
    (pstTree->stChild.stHead.pstNext == &pstTree->stChild.stHead))
    {
        /* ��ǰ���Ѿ�*uiKey��ֵ���⽫���ڸ�ֵ */
        if(*uiKey == HINT_DEFAULT)
        {
            *uiKey = HINT_COMPLETE;
        }
    }
    /* ��鵽��ǰ�����д� */
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

    /* ��¼��Ҫ������ʾ�Ĺؼ������ڽ����Ϣ */
    *ppstLastTreeNode = pstTree;
    return ERROR_SUCCESS;
}

/* ��ʾ����������� */
/*****************************************************************************
 Func Name    : CLI_RedisplayLine
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �ؼ���������ɸ���������
 Input        : CONST CHAR *line       ��Buffer
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

    /* �����������е�'?'���� */
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
            /* ����'?'֮ǰ�����ݵ������� */
            CLI_Memcpy(pcTemp, line, uiCpyLen);
            pcTemp[uiCpyLen] = '\0';

            /* '?'����������,����ĩ */
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
 Description  : ��ʾ���ܹؼ�����Ϣ
 Input        : UINT uiKey                      ���뷽ʽ
                TEST_TREE_NODE_S *pstTreeNode   ָ����Ҫ����Ĺؼ��ֽڵ�
                CONST CHAR *pcLine              ��Buffer
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
        /* û������ */
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
        /* �������� */
        case HINT_ERROR:
        {
            CLI_RedisplayLine(pcLine);
            break;
        }
        /* ���������������� */
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
            
            /* ��⵽��ǰ�ڵ�Ϊĳ������leaf�ڵ� */
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
        /* �Ѿ����������������ʽ */
        case HINT_COMPLETE:
        {
            printf("\n%% You have already entered complete commandline, please press \'ENTER\' and continue.\n");
            CLI_RedisplayLine(pcLine);
            break;
        }
        default: break;
    }
}

/* ����ؼ������봦���� */
/*****************************************************************************
 Func Name    : test_CmdKeyWordHint
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �ؼ�������ʵ����ں���
 Input        : INT iCount                      ���뷽ʽ
                INT Key                         �밴���󶨵�keymap
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

    /* �ն����ַ����� */
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
        /* ����'�ո�' ��Ϊ��Ч����,�ȼ���Ƿ�Ϊ�հ�����(�հ�����Ҳ�����ַ�����Ľ��) */
        while(YNTEST_WHITESPACE(pcInput[uiCount]) && (pcInput[uiCount] != '\0'))
        {
            uiCount++;
        }

        /* ��⵽�����ַ�ȫΪ�հ��ַ�(' '��'\t') */
        if(++uiCount == strlen(pcInput))
        {
            uiKey = HINT_FROM_HEAD;
        }
        else
        {
            /* �Ѿ�����Ч�ַ����룬����ʽ */
            ulRetVal = CLI_HintProc(pcInput, &pstTreeNode, &uiKey);

            /* �������д������йؼ������� */
            if(ulRetVal)
            {
                uiKey = HINT_ERROR;
            }
            else
            {
                /* �����������û�д��� */
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

