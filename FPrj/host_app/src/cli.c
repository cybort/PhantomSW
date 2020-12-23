/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              cli.c
   Project Code: Test App
   Module Name : CLI
   Date Created: 2020-08-02
   Author      : p21074
   Description : implementation of cli

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
#include <ctype.h>

#include "prv_basedef.h"
#include "cli.h"
#include "utils.h"
#include "log.h"

MOUDLE_INFO_S g_stMoudleInfo;
extern CHAR g_acPrompt[BUF_SIZE_64];

CONST CHAR *g_acCompletionGroup[MAX_COMPLETION_NUM] = {0};
MOUDLE_CIOCTL_CB_S g_astCallBackDB[CLI_MOUDLE_BUTT] = {{USELESS_PARA, NULL},};


CONST CHAR *g_acErrInfo[] = { \
                                " % Incomplete command found at '^' position", \
                                " % Unrecognized command found at '^' position", \
                                " % Wrong parameter found at '^' position, out of range", \
                                " % Unrecognized command found at '^' position, key string exceed maxium length of 80", \
                                " % Wrong parameter found at '^' position, exceed maxium length", \
                                " % Too many parameter found at '^' position",
                                NULL \
                             };

TEST_ELEMENT_S g_stStartEle = {.pcName = "null",
                             .uiFlag = 0,
                             .uiIds = 0,
                             .uiMor = USELESS_PARA,
                             .uiMax = 0,
                             .uiMin = 0,
                             .uiVal = 0,
                             .uiValFlag =0,
                             .pfCheck = NULL,
                            };

 CODE_SECTION("============")
 CODE_SECTION("�ڲ���������")
 CODE_SECTION("============")
 
 STATIC UINT CLI_GetFeatureKey(VOID *pCfg, UINT *puiNo);
 STATIC VOID *CLI_GetFeatureParam(VOID *pCfg, UINT uiIndex, PRASE_PARAM_TYPE_S *pstPara);
 STATIC UINT CLI_PRASE_GetFeatureCliNum(VOID *pCfg);
 STATIC ULONG CLI_PRASE_ParamProc(VOID *pParaInfo, UINT uiBufLen, VOID *pData, PRASE_PARAM_TYPE_S stInfo);
 STATIC UINT CLI_SubClueParse(const CHAR *pcClue);
 STATIC UINT CLI_ClueParse( const CHAR *pcClue, CHAR ucEnd);
 STATIC VOID CLI_InitCmdTree(TEST_TREE_NODE_S *pstTree);
 STATIC TEST_TREE_NODE_S *CLI_CmdTreeFindChild(DTQ_HEAD_S *pstChildList, TEST_ELEMENT_S *pstElement, TEST_TREE_NODE_S **pstSameNode);
 STATIC TEST_TREE_NODE_S *CLI_CmdTreeAddChild(DTQ_HEAD_S *pstChildList, TEST_ELEMENT_S *pstElement, TEST_TREE_NODE_S *pstSameNode);
 STATIC TEST_TREE_NODE_S *CLI_LastTreeNode(TEST_TREE_NODE_S *pstTreeNode, TEST_ELEMENT_S *pstTmp);
 STATIC VOID CLI_SubClueTree(CLI_MODULE_S *pstBash, const CHAR *pcClue, TEST_TREE_NODE_S *pstTree, UINT uiClueLen, UINT uiCmd);
 STATIC VOID CLI_ClueTree( CLI_MODULE_S *pstBash, const CHAR *pcClue, TEST_TREE_NODE_S *pstTree, UINT uiLen, UINT uiCmd);
 STATIC ULONG CLI_SetElement(IN const CHAR *pcName, IN UINT uiNo, IN VOID *pNode, IN VOID *pParam);
 STATIC ELEMENT_LIST_HANDLE CLI_ElementListCreat(IN ELEMENT_LIST_REG_S *pstRegister);
 STATIC ULONG CLI_List_GetNodeByKey(IN CHAR *pcName, IN UINT uiNo, IN VOID *pNodeData, IN VOID *pInArg, OUT VOID *pOutArg);
 STATIC ULONG CLI_List_GetNodeByNo(IN CHAR *pcName, IN UINT uiNo, IN VOID *pNodeData, IN VOID *pInArg, OUT VOID *pOutArg);
 STATIC ULONG CLI_List_IterateNode(IN ELEMENT_LIST_HANDLE hMonList, IN LIST_VISITOR_PF pfVist, IN VOID *pArg, OUT VOID *pOutArg);
 STATIC VOID *CLI_List_FindNodeByKey(IN ELEMENT_LIST_HANDLE hMonList, IN const CHAR *pcKey);
 STATIC VOID *CLI_List_FindNodeByNo(IN ELEMENT_LIST_HANDLE hMonList, IN UINT uiNo);
 STATIC ULONG CLI_List_AddNode(IN ELEMENT_LIST_HANDLE hMonList, IN const CHAR *pcKey, IN VOID *pParam);
 STATIC BOOL_T CLI_IsValue(IN const CHAR *szName, const CHAR *pcName, UINT *puiMin, UINT *puiMax);
 STATIC inline BOOL_T CLI_IsInteger(const CHAR *pcName, UINT *puiMin, UINT *puiMax);
 STATIC inline BOOL_T CLI_IsString(const CHAR *pcName, UINT *puiMin, UINT *puiMax);
 STATIC ULONG CLI_ShowErrInfo(CLI_PRASE_ERROR_E enErrType, BUF_INFO_S *pstBuf, VOID *Data);
 STATIC BOOL_T CLI_FilterWord(IN CONST CHAR *pcName);
 STATIC ULONG CLI_AddCompletionWord(INOUT CONST CHAR **ppList, IN CONST CHAR *pcName);
 STATIC ULONG CLI_CliExc(IN UINT uiCmd, IN VOID *pData);
 STATIC ULONG CLI_FindMoudleCallBack(UINT uiKey, CLI_MOUDLE_CIOCTL_PF *ppMoudleCallBack);

 /*****************************************************************************
  Func Name    : CLI_InitCmdTree
  Date Created : 2020/08/08
  Author       : pengying21074
  Description  : ������������ʼ��
  Input        : TEST_TREE_NODE_S *pstTree      ������ͷ�ڵ�ָ��
  Output       : NONE
  Return       : NONE
  Caution      :
 *****************************************************************************/
 STATIC VOID CLI_InitCmdTree(IN TEST_TREE_NODE_S *pstTree)
{
    DBGASSERT_RETURN_NONE(NULL != pstTree);
    
    DTQ_Init(&pstTree->stChild);
    DTQ_NodeInit(&pstTree->stBrother);
    pstTree->pstElement = &g_stStartEle;
    pstTree->bLeaf = BOOL_FALSE;
    pstTree->uiCmd = USELESS_PARA;
    YNTEST_CLEAR_BUF(pstTree->szStr, sizeof(pstTree->szStr));
    pstTree->pstNext = NULL;
    return;
}

/*****************************************************************************
 Func Name    : CLI_CmdTreeFindChild
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �����������м���ָ�������Ƿ����ָ���Ľڵ�
 Input        : DTQ_HEAD_S *pstChildList        ����ͷָ��
                TEST_ELEMENT_S *pstElement      ָ���ڵ����ݽṹָ��
 Output       : TEST_TREE_NODE_S **pstSameNode  ָ����ָ���ڵ�ͬ����ָ��
 Return       : ���������ҵ��ýڵ��򷵻ظýڵ�,���򷵻�NULL
 Caution      :
*****************************************************************************/
STATIC TEST_TREE_NODE_S *CLI_CmdTreeFindChild(IN DTQ_HEAD_S *pstChildList, IN TEST_ELEMENT_S *pstElement, INOUT TEST_TREE_NODE_S **pstSameNode)
{
    DTQ_NODE_S *pstNode;
    TEST_TREE_NODE_S *pstTreeNode;

    if(NULL == pstChildList || NULL == pstElement || NULL == pstSameNode)
    {
        Log_Print(LOG_LEVEL_ERROR, "null pointer found.\n");
        return NULL;
    }

    *pstSameNode = NULL;
    
    DTQ_FOREACH(pstChildList, pstNode)
    {
        pstTreeNode = container_of(pstNode, TEST_TREE_NODE_S, stBrother);
        if((0==CLI_Strcmp(pstTreeNode->pstElement->pcName, pstElement->pcName)))
        {
            return pstTreeNode;
        }
    }

    return NULL;
}

/*****************************************************************************
 Func Name    : CLI_CmdTreeAddChild
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ��������������ָ�������¹��ؽڵ�
 Input        : DTQ_HEAD_S *pstChildList        ����ͷָ��
                TEST_ELEMENT_S *pstElement      �����ؽڵ����ݽṹָ��
 Output       : TEST_TREE_NODE_S **pstSameNode  ָ����ָ���ڵ�ͬ����ָ��
 Return       : �����¹��ؽڵ�ɹ��򷵻ظýڵ�,���򷵻�NULL
 Caution      :
*****************************************************************************/
STATIC TEST_TREE_NODE_S *CLI_CmdTreeAddChild(IN DTQ_HEAD_S *pstChildList, IN TEST_ELEMENT_S *pstElement, IN TEST_TREE_NODE_S *pstSameNode)
{
    TEST_TREE_NODE_S *pstTreeNode;

    if(NULL == pstChildList || NULL == pstElement)
    {
        Log_Print(LOG_LEVEL_INFO, "null pointer found.\n");
        return NULL;
    }
    
    pstTreeNode = (TEST_TREE_NODE_S *)malloc(sizeof(TEST_TREE_NODE_S));
    if(NULL == pstTreeNode)
    {
        Log_Print(LOG_LEVEL_ERROR,"malloc failed.\n");
        return NULL;
    }

    CLI_InitCmdTree(pstTreeNode);
    pstTreeNode->pstElement = pstElement;
    
    /* �ڱ�β��Ӹýڵ� */
    DTQ_AddTail(pstChildList, &pstTreeNode->stBrother);

    if(NULL != pstSameNode)
    {
        pstTreeNode->pstNext = pstSameNode->pstNext;
        pstSameNode->pstNext = pstTreeNode;
    }
    return pstTreeNode;
}

/*****************************************************************************
 Func Name    : CLI_SubClueParse
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ���������ʽ����
 Input        : CONST CHAR *pcClue        ָ��������ĸ�ʽ�ַ���ָ��
 Output       : NONE
 Return       : �������ĳ���
 Caution      :
*****************************************************************************/
STATIC UINT CLI_SubClueParse(IN CONST CHAR *pcClue)
{
    UINT i = 0;
    UINT uiLen;
    UINT uiSubLen;
    UINT uiNo;

    if(NULL == pcClue)
    {
        Log_Print(LOG_LEVEL_ERROR, "null pointer found.\n");
        return 0;
    }

    uiLen = strlen(pcClue)+1;
    while(i<uiLen)
    {
        if(' ' != pcClue[i++])
        {
            Log_Print(LOG_LEVEL_ERROR, "invalid command format. \'%s\'\n", pcClue);
            return 0;
        }
        
        switch(pcClue[i++])
        {
            case '$':
                uiSubLen = CLI_Str2dec(pcClue+i, &uiNo);
                if(0 == uiSubLen)
                {
                    Log_Print(LOG_LEVEL_ERROR, "invalid command format. \'%s\'\n", pcClue);
                    return 0;
                }
                uiNo -= 1;
                i += uiSubLen;

                break;
            case '[':
                uiSubLen = CLI_ClueParse( pcClue+i, ']');
                if(0 == uiSubLen)
                {
                    Log_Print(LOG_LEVEL_ERROR, "invalid command format. \'%s\'\n", pcClue);
                    return 0;
                }
                
                i += uiSubLen;

                break;
            case '{':
                uiSubLen = CLI_ClueParse( pcClue+i, '}');
                if(0 == uiSubLen)
                {
                    Log_Print(LOG_LEVEL_ERROR, "invalid command format. \'%s\'\n", pcClue);
                    return 0;
                }
                
                i += uiSubLen;

                break;
            case '}':
            case ']':
            case '|':
            case '\0':
                return i;  
            default:
                return 0;        
        }
    }

    return 0;
}

/*****************************************************************************
 Func Name    : CLI_ClueParse
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ���������ʽ����
 Input        : CONST CHAR *pcClue        ָ��������ĸ�ʽ�ַ���ָ��
                CHAR ucEnd                �����ַ�
 Output       : NONE
 Return       : �������ĸ�ʽ����
 Caution      :��CLI_SubClueParse��ͬ���Ǵ�API��Ҫָ������ʱ�Ľ����ַ�,������
                �����ַ���'\0'��ֹͣ����,CLI_SubClueParse��һֱ����ֱ������'\0'
*****************************************************************************/
STATIC UINT CLI_ClueParse( IN CONST CHAR *pcClue, IN CHAR ucEnd)
{
    UINT i =0;
    UINT uiSubLen;
    do
    {
        /* ѭ������'|'�ָ�ÿһ���Ӿ� */
        uiSubLen = CLI_SubClueParse( pcClue+i);
        if(0==uiSubLen)
        {
            Log_Print(LOG_LEVEL_ERROR, "invalid command format. \'%s\'\n", pcClue);
            return 0;
        }

        /* ��һ�� */
        i+=uiSubLen;
    }while('|' == pcClue[i-1]);

    /* ���ӽ�β���Ի��߾��ӽ�β����ָ���ַ� */
    if(-1 == ucEnd)
    {
        if(('}' != pcClue[i-1]) && (']' != pcClue[i-1]) && ('\0' != pcClue[i-1]))
        {
            Log_Print(LOG_LEVEL_ERROR, 
                      "invalid command format, end without specific character \'%c\'. p1=\'%s\' p2=\'%c\'\n", 
                      ucEnd, pcClue, pcClue[i-1]);
            return 0;
        }
    }
    else if(ucEnd != pcClue[i-1])
    {
        Log_Print(LOG_LEVEL_ERROR, 
                      "invalid command format, end without specific character \'%c\'. p1=\'%s\' p2=\'%c\'\n", 
                      ucEnd, pcClue, pcClue[i-1]);
        return 0;
    }

    return i;
}

/*****************************************************************************
 Func Name    : CLI_LastTreeNode
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ���¹�����©�Ľڵ�
 Input        : TEST_TREE_NODE_S *pstTreeNode        Ŀ������ͷ�ڵ�ָ��
                TEST_ELEMENT_S *pstTmp               �����ؽڵ����ݽṹָ��
 Output       : NONE
 Return       : �����¹��ؽڵ�ɹ��򷵻ظýڵ�,���򷵻�NULL
 Caution      :
*****************************************************************************/
STATIC TEST_TREE_NODE_S *CLI_LastTreeNode(IN TEST_TREE_NODE_S *pstTreeNode, IN TEST_ELEMENT_S *pstTmp)
{
    TEST_TREE_NODE_S *pstTreeTmp;
    TEST_TREE_NODE_S *pstSameName;

    DBGASSERT_WITH_RETURN(NULL != pstTreeNode, NULL);
    DBGASSERT_WITH_RETURN(NULL != pstTmp, NULL);
    
    /* ������ */
    pstTreeTmp = CLI_CmdTreeFindChild(&pstTreeNode->stChild, pstTmp, &pstSameName);
    if(NULL == pstTreeTmp)
    {
        pstTreeTmp = CLI_CmdTreeAddChild(&pstTreeNode->stChild, pstTmp, pstSameName);
    }

    if(NULL == pstTreeTmp)
    {
        Log_Print(LOG_LEVEL_ERROR, "command tree add child failed.\n");
        return NULL;
    }

    pstTreeNode = pstTreeTmp;

    return pstTreeTmp;
}

/*****************************************************************************
 Func Name    : CLI_SubClueTree
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ���������ʽ��������
 Input        : CLI_MODULE_S *pstBash        ģ�����ÿռ��ַ
                CONST CHAR *pcClue           �����ʽ
                TEST_TREE_NODE_S *pstTree    ��������ͷ�ڵ�ָ��
                UINT uiClueLen               �����ʽ����
                UINT uiCmd                   �������ʽ�󶨵�cmd id
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
STATIC VOID CLI_SubClueTree(IN CLI_MODULE_S *pstBash, IN CONST CHAR *pcClue, IN TEST_TREE_NODE_S *pstTree, IN UINT uiClueLen, IN UINT uiCmd)
{
    UINT i = 0;
    UINT uiLen;
    UINT uiSubLen;
    UINT uiNo = 0;
    TEST_TREE_NODE_S *pstTreeTmp;
    TEST_TREE_NODE_S *pstTreeNode;
    TEST_ELEMENT_S *pstEle;
    TEST_ELEMENT_S *pstTmp = NULL;
    TEST_TREE_NODE_S *pstSameName;

    DBGASSERT_RETURN_NONE(NULL != pstBash);
    DBGASSERT_RETURN_NONE(NULL != pcClue);
    DBGASSERT_RETURN_NONE(NULL != pstTree);

    uiLen = strlen(pcClue)+1;
    pstTreeNode = pstTree;

    while(i<uiLen)
    {
        i++;

        /* �ϴδ������ */
        if(('$' != pcClue[i])&&(NULL != pstTmp))
        {
            pstTreeNode = CLI_LastTreeNode(pstTreeNode, pstTmp);
            if(NULL == pstTreeNode)
            {
                return;
            }
            pstTmp = NULL;
        }
        
        switch(pcClue[i++])
        {
            case '$':
                uiSubLen = CLI_Str2dec(pcClue+i, &uiNo);
                uiNo -= 1;
                pstEle = CLI_List_FindNodeByNo(pstBash->hCurList, uiNo);
                i+=uiSubLen;

                /* ������ */
                pstTreeTmp = CLI_CmdTreeFindChild(&pstTreeNode->stChild, pstEle, &pstSameName);
                if(NULL == pstTreeTmp)
                {
                    pstTreeTmp = CLI_CmdTreeAddChild(&pstTreeNode->stChild, pstEle, pstSameName);
                }

                if(NULL == pstTreeTmp)
                {
                    return;
                }

                pstTreeNode = pstTreeTmp;
                break;
            case '[':
                uiSubLen = CLI_ClueParse( pcClue+i, ']');
                i += uiSubLen;

                /* ����[]�Ӿ� */
                CLI_SubClueTree( pstBash, pcClue+i, pstTreeNode, uiClueLen-i, uiCmd);

                /* ����[]�Ӿ� */                
                CLI_ClueTree( pstBash, pcClue+(i-uiSubLen), pstTreeNode, uiSubLen, uiCmd);

                return;
            case '{':
                uiSubLen = CLI_ClueParse( pcClue+i, '}');
                i += uiSubLen;

                /* ����{}�Ӿ� */                
                CLI_ClueTree( pstBash, pcClue+(i-uiSubLen), pstTreeNode, uiSubLen, uiCmd);

                return;

            case '}':
            case ']':
                break;
            case '|':
                uiSubLen = CLI_ClueParse( pcClue+i, -1);
                i += uiSubLen;
                break;  
            case '\0':
                pstTreeNode->bLeaf = BOOL_TRUE;
                pstTreeNode->uiCmd = uiCmd;
            default:
                break;        
        }
    }

    if(uiLen == i)
    {
        pstTreeNode->bLeaf = BOOL_TRUE;
        pstTreeNode->uiCmd = uiCmd;
    }

    return;
}

/*****************************************************************************
 Func Name    : CLI_ClueTree
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ���������ʽ��������
 Input        : CLI_MODULE_S *pstBash        ģ�����ÿռ��ַ
                CONST CHAR *pcClue           �����ʽ
                TEST_TREE_NODE_S *pstTree    ��������ͷ�ڵ�ָ��
                UINT uiClueLen               �����ʽ����
                UINT uiCmd                   �������ʽ�󶨵�cmd id
 Output       : NONE
 Return       : NONE
 Caution      :
*****************************************************************************/
STATIC VOID CLI_ClueTree( CLI_MODULE_S *pstBash, const CHAR *pcClue, TEST_TREE_NODE_S *pstTree, UINT uiLen, UINT uiCmd)
{
    UINT i = 0;
    UINT uiSubLen;

    DBGASSERT_RETURN_NONE(NULL!= pstBash);
    DBGASSERT_RETURN_NONE(NULL!= pcClue);
    DBGASSERT_RETURN_NONE(NULL!= pstTree);
    
    do
    {
        /* ѭ������'|'�ָ�ÿһ���Ӿ� */
        uiSubLen = CLI_SubClueParse( pcClue+i);

        /* �������� */
        CLI_SubClueTree( pstBash, pcClue+i, pstTree, uiLen-i, uiCmd);

        /* ��һ�� */
        i+=uiSubLen;
    }while(i<uiLen);
    
    return;
}

/* ģ���ʼ�������������ڴ治�ͷ� */
/*****************************************************************************
 Func Name    : CLI_MoudleInfoInit
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ��ģ�����ÿռ��ʼ��
 Input        : NONE
 Output       : NONE
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : ��ʼ��������Ϊ��ģ�����ÿռ�������ڴ��ڳ��������ڼ䲻�ͷ�
*****************************************************************************/
ULONG CLI_MoudleInfoInit(VOID)
{
    UINT uiLoop;
    CLI_MODULE_S *pstMoudle = NULL;
    
    for(uiLoop = CLI_MOUDLE_PUBLIC; uiLoop < CLI_MOUDLE_BUTT; uiLoop++)
    {
        pstMoudle = (CLI_MODULE_S *)malloc(sizeof(CLI_MODULE_S));
        if(NULL == pstMoudle)
        {
            Log_Print(LOG_LEVEL_ERROR, "malloc failed.\n");
            return ERROR_FAILED;
        }
        pstMoudle->uiMId = uiLoop;
        CLI_InitCmdTree(&pstMoudle->stTree);
        pstMoudle->hCurList = 0UL;
        memset(pstMoudle->hElementList, 0, sizeof(pstMoudle->hElementList));
        pstMoudle->uiCurCliNum = 0;
        pstMoudle->uiNo = 0;
        pstMoudle->uiCmd = USELESS_PARA;
        pstMoudle->enErrType = CLI_ERROR_NONE;
        pstMoudle->uiParsedLen = 0;

        g_stMoudleInfo.pstMoudle[uiLoop] = pstMoudle;
    }
    return ERROR_SUCCESS;
}

/* ��ȡ��ǰ������ģ����Ϣ */
/*****************************************************************************
 Func Name    : CLI_GetMoudleInfo
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ��ȡģ�����ÿռ���Ϣ
 Input        : CLI_MOUDLE_E enMoudle   ָ��ģ��ID
 Output       : NONE
 Return       : ָ��ģ�����ÿռ��ַ
 Caution      : 
*****************************************************************************/
CLI_MODULE_S *CLI_GetMoudleInfo(IN CLI_MOUDLE_E enMoudle)
{
    DBGASSERT_WITH_RETURN(enMoudle < CLI_MOUDLE_BUTT, NULL);
    
    return g_stMoudleInfo.pstMoudle[enMoudle];
}

/*****************************************************************************
 Func Name    : CLI_SetElement
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 
 Input        : 
 Output       : NONE
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : 
*****************************************************************************/
STATIC ULONG CLI_SetElement(IN const CHAR *pcName, IN UINT uiNo, IN VOID *pNode, IN VOID *pParam)
{
    TEST_ELEMENT_S *pstElement;

    DBGASSERT(NULL != pcName);
    DBGASSERT(NULL != pNode);
    DBGASSERT(NULL != pParam);

    pstElement = (TEST_ELEMENT_S *)pNode;
    memcpy(pstElement, pParam, sizeof(TEST_ELEMENT_S));
    
    return ERROR_SUCCESS;
}

/* �����ؼ���ע��� */
/*****************************************************************************
 Func Name    : CLI_ElementListCreat
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ����ؼ����б���
 Input        : ELEMENT_LIST_REG_S *pstRegister     �����ؼ����б��ע����Ϣ
 Output       : NONE
 Return       : �ɹ����عؼ����б�Ĳ������,ʧ�ܷ���NULL
 Caution      : 
*****************************************************************************/
STATIC ELEMENT_LIST_HANDLE CLI_ElementListCreat(IN ELEMENT_LIST_REG_S *pstRegister)
{
    ELEMENT_LIST_S *pstMonList;

    DBGASSERT_WITH_RETURN(NULL != pstRegister, (ELEMENT_LIST_HANDLE)NULL);
    
    pstMonList = (ELEMENT_LIST_S *)malloc(sizeof(ELEMENT_LIST_S));
    if(NULL == pstMonList)
    {
        Log_Print(LOG_LEVEL_ERROR, "malloc failed.\n");
        return (ELEMENT_LIST_HANDLE)NULL;
    }
    
    DTQ_Init(&pstMonList->stLink);
    DTQ_Init(&pstMonList->stDelLink);
    pstMonList->uiNodeLen = pstRegister->uiNodeLen;
    pstMonList->pfCmpNode = pstRegister->pfCmpNode;
    pstMonList->pfSetNode = pstRegister->pfSetNode;

    return (ELEMENT_LIST_HANDLE)pstMonList;
}

/*****************************************************************************
 Func Name    : CLI_List_GetNodeByKey
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �ӹؼ����б��и��ݹؼ�������ȡ�ؼ�����Ϣ
 Input        : CHAR *pcName     �ؼ�����
 Output       : VOID *pOutArg    �������ռ�
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : 
*****************************************************************************/
STATIC ULONG CLI_List_GetNodeByKey(IN CHAR *pcName, IN UINT uiNo, IN VOID *pNodeData, IN VOID *pInArg, OUT VOID *pOutArg)
{
    DBGASSERT(NULL != pcName);
    DBGASSERT(NULL != pNodeData);
    DBGASSERT(NULL != pInArg);
    DBGASSERT(NULL != pOutArg);
    IGNORE_PARAM(uiNo);
    
    if(0 == strcmp(pcName, (CHAR *)pInArg))
    {
        *(VOID **)pOutArg = pNodeData;
        return ERROR_SUCCESS;
    }
    *(VOID **)pOutArg = NULL;

    return ERROR_FAILED;
}

/*****************************************************************************
 Func Name    : CLI_List_GetNodeByNo
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �ӹؼ����б��и��ݹؼ���NO.��ȡ�ؼ�����Ϣ
 Input        : UINT uiNo       �ؼ���NO.
 Output       : VOID *pOutArg    �������ռ�
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : 
*****************************************************************************/
STATIC ULONG CLI_List_GetNodeByNo(IN CHAR *pcName, IN UINT uiNo, IN VOID *pNodeData, IN VOID *pInArg, OUT VOID *pOutArg)
{
    DBGASSERT(NULL != pNodeData);
    DBGASSERT(NULL != pOutArg);
    IGNORE_PARAM(pcName);
    
    if(uiNo == (UINT)(ULONG)pInArg)
    {
        *(VOID **)pOutArg = pNodeData;
        return ERROR_SUCCESS;
    }

    *(VOID **)pOutArg = NULL;

    return ERROR_FAILED;
}

/* ���������������� */
/*****************************************************************************
 Func Name    : CLI_List_IterateNode
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �������������ؼ��ֱ��ÿ���ڵ�
 Input        : ELEMENT_LIST_HANDLE hMonList       �ؼ����б�������.
                LIST_VISITOR_PF pfVist             ��������ָ��
                VOID *pArg                         �������������ָ��
 Output       : VOID *pOutArg                      ��������������ָ��
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : 
*****************************************************************************/
STATIC ULONG CLI_List_IterateNode(IN ELEMENT_LIST_HANDLE hMonList, IN LIST_VISITOR_PF pfVist, IN VOID *pArg, OUT VOID *pOutArg)
{
    ELEMENT_LIST_S *pstMonList;
    ELEMENT_LIST_NODE_S *pstListNode;
    DTQ_NODE_S *pstNode;
    UINT uiLoop;
    ULONG ulRet;

    DBGASSERT(0UL != hMonList);
    DBGASSERT(NULL != pOutArg);
    DBGASSERT(NULL != pfVist)

    pstMonList = (ELEMENT_LIST_S *)hMonList;
    
    /* �������� */
    uiLoop = 0;
    DTQ_FOREACH(&pstMonList->stLink, pstNode)
    {
        pstListNode = container_of(pstNode, ELEMENT_LIST_NODE_S, stNode);

        ulRet = pfVist(pstListNode->szKey, uiLoop, pstListNode->pElementData, pArg, pOutArg);
        if(ERROR_SUCCESS == ulRet)
        {
            break;
        }
        
        uiLoop++;
    }
    return ERROR_SUCCESS;
}


/*  ���ݹؼ��ֵ�key��ȡָ��list node */
/*****************************************************************************
 Func Name    : CLI_List_FindNodeByKey
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ����Key�����ؼ��ֱ��ÿ���ڵ�
 Input        : ELEMENT_LIST_HANDLE hMonList       �ؼ����б�������.
                CONST CHAR *pcKey                  ����Key
 Output       : NONE
 Return       : �ɹ�����Ŀ��ڵ�,���򷵻�NULL
 Caution      : 
*****************************************************************************/
STATIC VOID *CLI_List_FindNodeByKey(IN ELEMENT_LIST_HANDLE hMonList, IN CONST CHAR *pcKey)
{
    VOID *pData = NULL;
    
    DBGASSERT_WITH_RETURN(0UL != hMonList, NULL);
    DBGASSERT_WITH_RETURN(NULL != pcKey, NULL);

    (VOID)CLI_List_IterateNode(hMonList, CLI_List_GetNodeByKey, (VOID *)pcKey, &pData);

    return pData;
}

/* ���ݹؼ��ֵ���Ż�ȡָ��list node���ڹؼ��ֱ�����ӹؼ���ʱ������Ǹ�����ӵ��Ⱥ�˳���� */
/*****************************************************************************
 Func Name    : CLI_List_FindNodeByKey
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ���ݹؼ��ֵ���Ż�ȡָ��list node,�ڹؼ��ֱ�����ӹؼ���ʱ,
                ����Ǹ�����ӵ��Ⱥ�˳����
 Input        : ELEMENT_LIST_HANDLE hMonList       �ؼ����б�������.
                UINT uiNo                          �ؼ���Node˳��
 Output       : NONE
 Return       : �ɹ�����Ŀ��ڵ�,���򷵻�NULL
 Caution      : 
*****************************************************************************/
STATIC VOID *CLI_List_FindNodeByNo(IN ELEMENT_LIST_HANDLE hMonList, IN UINT uiNo)
{
    VOID *pData = NULL;
    DBGASSERT_WITH_RETURN(0UL != hMonList, NULL);

    (VOID)CLI_List_IterateNode(hMonList, CLI_List_GetNodeByNo, (VOID *)(ULONG)uiNo, &pData);

    return pData;
}


/* ��ؼ��ֱ���������ע��Ĺؼ��� */
/*****************************************************************************
 Func Name    : CLI_List_AddNode
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �ؼ����б�����µĽڵ�
 Input        : ELEMENT_LIST_HANDLE hMonList       �ؼ����б�������.
                const CHAR *pcKey                  �ؼ���key
                VOID *pParam                       ָ��ڵ�������ݽṹ��ָ��
 Output       : NONE
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : 
*****************************************************************************/
STATIC ULONG CLI_List_AddNode(IN ELEMENT_LIST_HANDLE hMonList, IN const CHAR *pcKey, IN VOID *pParam)
{
    ELEMENT_LIST_S *pstMonList;
    ELEMENT_LIST_NODE_S *pstListNode;

    DBGASSERT(0UL != hMonList);
    DBGASSERT(NULL != pcKey);
    DBGASSERT(NULL != pParam);

    pstMonList = (ELEMENT_LIST_S *)hMonList;

    /* �Ѿ����� */
    if(NULL != CLI_List_FindNodeByKey(hMonList, pcKey))
    {
        return ERROR_SUCCESS;
    }

    /* �ڵ���� */
    pstListNode = (ELEMENT_LIST_NODE_S *)malloc(sizeof(ELEMENT_LIST_NODE_S)+pstMonList->uiNodeLen);
    if(NULL == pstListNode)
    {
        Log_Print(LOG_LEVEL_ERROR,"malloc failed.\n");
        return ERROR_FAILED;
    }
    memset(pstListNode,0,sizeof(ELEMENT_LIST_NODE_S)+pstMonList->uiNodeLen);

    /* ��Ϣ���� */
    pstListNode->pElementData = (VOID *)(pstListNode+1);
    (VOID)strlcpy(pstListNode->szKey, pcKey, sizeof(pstListNode->szKey));
    if((NULL != pstMonList->pfSetNode)&&(ERROR_SUCCESS != pstMonList->pfSetNode(pcKey, pstMonList->uiCount, pstListNode->pElementData, pParam)))
    {
        free(pstListNode);
        Log_Print(LOG_LEVEL_ERROR,"set node failed.\n");
        return ERROR_FAILED;
    }

    /* �ڱ�β����µĹؼ��� */
    DTQ_AddTail(&pstMonList->stLink, &pstListNode->stNode);

    /* ���´˱���ע��Ĺؼ��ָ��� */
    pstMonList->uiCount++;

    
    return ERROR_SUCCESS;
}


/* ע������ؼ���ʱ��ָ��ģ���ʼ�� */
/*****************************************************************************
 Func Name    : CLI_List_AddNode
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  :  ע������ؼ���ʱ,ָ��ģ���ʼ��
 Input        : CLI_MOUDLE_E enMoudle   ģ��ID
 Output       : NONE
 Return       : NONE
 Caution      : 
*****************************************************************************/
VOID CLI_MOUDLE_INIT(CLI_MOUDLE_E enMoudle)
{
    CLI_MODULE_S *pstMoudle;
    ELEMENT_LIST_REG_S stListReg ;
    UINT i;

    if(enMoudle >= CLI_MOUDLE_BUTT)
    {
        Log_Print(LOG_LEVEL_ERROR,"moudle id exceed maximum moudle.\n");
        return;
    }

    pstMoudle = CLI_GetMoudleInfo(enMoudle);
    if(pstMoudle == NULL)
    {
        Log_Print(LOG_LEVEL_ERROR,"none pointer detect.\n");
        return;
    }

    for(i=0; i<MAX_SUB_MOUDLE; i++)
    {
        if(0UL == pstMoudle->hElementList[i])
        {
            break;
        }
    }
    if( MAX_SUB_MOUDLE == i)
    {
        Log_Print(LOG_LEVEL_ERROR, "exceed maximum sub-modle, p = %u\n",i);
        return;
    }
    stListReg.uiNodeLen = sizeof(TEST_ELEMENT_S);
    stListReg.pfSetNode = CLI_SetElement;
    stListReg.pfCmpNode = NULL;
    pstMoudle->hElementList[i] = CLI_ElementListCreat(&stListReg);
    pstMoudle->hCurList = pstMoudle->hElementList[i];
    pstMoudle->uiNo = 0;
    return;
}

/*****************************************************************************
 Func Name    : CLI_BufInit
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : buffer ��ʼ��
 Input        : BUF_INFO_S *pstIBuf   ����buffer��Ϣָ��
                CHAR *pcBuf          Ŀ��buffer
                UINT uiBufLen        buffer size
                UINT uiUsedLen       ��ʹ��size
 Output       : NONE
 Return       : NONE
 Caution      : 
*****************************************************************************/
VOID CLI_BufInit(IN BUF_INFO_S *pstIBuf, IN CHAR *pcBuf, IN UINT uiBufLen, IN UINT uiUsedLen)
{
    DBGASSERT_RETURN_NONE(NULL != pstIBuf);
    DBGASSERT_RETURN_NONE(NULL != pcBuf);
    pstIBuf->pcBuf  = pcBuf;
    pstIBuf->uiMaxSize  = uiBufLen;
    pstIBuf->uiUsedSize = uiUsedLen;
    return;
}

/*****************************************************************************
 Func Name    : CLI_BufGetSize
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ��ȡbuffer��ʹ��size
 Input        : BUF_INFO_S *pstIBuf   ����buffer��Ϣָ��
 Output       : NONE
 Return       : NONE
 Caution      : 
*****************************************************************************/
UINT CLI_BufGetSize(IN CONST BUF_INFO_S *pstIBuf)
{
    DBGASSERT_WITH_RETURN(pstIBuf != NULL, 0xfffffff);
    return pstIBuf->uiUsedSize;
}

/* �˺����жϸ�����ؼ�������cli��λ���Ƿ��ǲ����������������������ַ������޲��� */
/*****************************************************************************
 Func Name    : CLI_IsValue
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �˺����жϸ�����ؼ�������cli��λ���Ƿ��ǲ���,����ָ�����Ͳ����Ƚ�
                �Ƿ�Ϊ�����Ͳ���
 Input        : const CHAR *szName   ָ����������
                const CHAR *pcName   �ؼ�����
                UINT *puiMin         ָ�������Χ��Сֵ��ָ��
                UINT *puiMax         ָ�������Χ���ֵ��ָ��
 Output       : NONE
 Return       : BOOL_TRUE            �ؼ����ǲ���
                BOOL_FALSE           �ؼ��ַǲ���
 Caution      : ����������ΪINTEGERʱ,��СֵΪ0
                ����������ΪSTRINGʱ,������ΧΪ�ַ������ȷ�Χ,��СֵΪ1
*****************************************************************************/
STATIC BOOL_T CLI_IsValue(IN const CHAR *szName, const CHAR *pcName, UINT *puiMin, UINT *puiMax)
{
    UINT i;
    UINT uiStrLen;
    UINT uiTypeLen;

    DBGASSERT_WITH_RETURN(NULL != szName, BOOL_FALSE);
    DBGASSERT_WITH_RETURN(NULL != pcName, BOOL_FALSE);
    DBGASSERT_WITH_RETURN(NULL != puiMax, BOOL_FALSE);
    DBGASSERT_WITH_RETURN(NULL != puiMin, BOOL_FALSE);

    uiTypeLen = strlen(szName);
    for(i=0; i<uiTypeLen; i++)
    {
        if(szName[i] != pcName[i])
        {
            break;
        }
    }

    if(i<uiTypeLen)
    {
        return BOOL_FALSE;
    }

    if('\0'==pcName[i])
    {
        *puiMin = 0;
        *puiMax = 0xFFFFFFFFUL;
        return BOOL_TRUE;
    }

    if('<'!=pcName[i])
    {
        return BOOL_FALSE;
    }
    
    i++;
    uiStrLen= CLI_Str2dec(pcName+i, puiMin);
    if(0==uiStrLen)
    {
        return BOOL_FALSE;
    }

    i+=uiStrLen;
    if('-'!=pcName[i++])
    {
        return BOOL_FALSE;
    }
    
    uiStrLen= CLI_Str2dec(pcName+i, puiMax);
    if(0==uiStrLen)
    {
        return BOOL_FALSE;
    }
    i+=uiStrLen;
    if('>'!=pcName[i++])
    {
        return BOOL_FALSE;
    }

    if('\0'!=pcName[i])
    {
        return BOOL_FALSE;
    }

    return BOOL_TRUE;
}

/*****************************************************************************
 Func Name    : CLI_IsInteger
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �˺����жϸ�����ؼ�������cli��λ���Ƿ������Ͳ���
 Input        : const CHAR *pcName   �ؼ�����
                UINT *puiMin         ָ�������Χ��Сֵ��ָ��
                UINT *puiMax         ָ�������Χ���ֵ��ָ��
 Output       : NONE
 Return       : BOOL_TRUE            �ؼ��������Ͳ���
                BOOL_FALSE           �ؼ��ַ����Ͳ���
 Caution      : ����������ΪINTEGERʱ,��СֵΪ0
                ����������ΪSTRINGʱ,������ΧΪ�ַ������ȷ�Χ,��СֵΪ1
*****************************************************************************/
STATIC inline BOOL_T CLI_IsInteger(const CHAR *pcName, UINT *puiMin, UINT *puiMax)
{
    return CLI_IsValue("INTEGER", pcName, puiMin, puiMax);
}

/*****************************************************************************
 Func Name    : CLI_IsString
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �˺����жϸ�����ؼ�������cli��λ���Ƿ����ַ��Ͳ���
 Input        : const CHAR *pcName   �ؼ�����
                UINT *puiMin         ָ�������Χ��Сֵ��ָ��
                UINT *puiMax         ָ�������Χ���ֵ��ָ��
 Output       : NONE
 Return       : BOOL_TRUE            �ؼ������ַ��Ͳ���
                BOOL_FALSE           �ؼ��ַ��ַ��Ͳ���
 Caution      : ����������ΪINTEGERʱ,��СֵΪ0
                ����������ΪSTRINGʱ,������ΧΪ�ַ������ȷ�Χ,��СֵΪ1
*****************************************************************************/
STATIC inline BOOL_T CLI_IsString(const CHAR *pcName, UINT *puiMin, UINT *puiMax)
{
    return CLI_IsValue("STRING", pcName, puiMin, puiMax);
}

/*****************************************************************************
 Func Name    : CLI_Reg_DefElement
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ע��ؼ���API����
 Input        : CONST CHAR *pcName       ָ��ؼ�������ָ��
                CLI_MOUDLE_E enMoudle    ģ��id
               UINT uiHelpStrId          �ؼ��ֽ����ַ�������
               ...                       �ɱ����
 Output       : NONE
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : ע��ؼ���ʱ��ֱ��ʹ�ô�API����,Ӧ��ʹ�ú�CLI_DEF_ELEMENT��
                ��ɹؼ���ע��;�ɱ��������ܽ���3��,����3�������ٽ��գ�
                1�����:MOR
                2�����:MOR + value
                3�����:��δʹ��
*****************************************************************************/
ULONG CLI_Reg_DefElement(IN CONST CHAR *pcName,
                                  IN CLI_MOUDLE_E enMoudle,
                                  IN UINT uiHelpStrId,
                                  ...)
{
    TEST_ELEMENT_S stElement ;
    ULONG ulRetVal = ERROR_SUCCESS;
    CLI_MODULE_S *pstMoudle;
    CHAR szName[BUF_SIZE_32];
    BUF_INFO_S stBufInfo;
    VA_LIST varArg;
    UINT auiVarPara[MAX_VAR_PARAM] = {0};
    UINT uiVarParaVal;
    UINT i = 0;
    UINT uiMor = USELESS_PARA;
    UINT uiVal = USELESS_PARA;

    DBGASSERT(NULL != pcName);
    DBGASSERT(enMoudle < CLI_MOUDLE_BUTT);
    
    pstMoudle = CLI_GetMoudleInfo(enMoudle);
    YNTEST_CHK_PTR_FAILED(pstMoudle);
    
    memset(&stElement, 0, sizeof(stElement));
    stElement.pcName = pcName;
    stElement.uiIds = uiHelpStrId;

    /* ��δ��� */
    VA_START( varArg, uiHelpStrId );
    while(CLI_PARA_END != (uiVarParaVal = VA_ARG(varArg,UINT)))
    {
        auiVarPara[i++] = uiVarParaVal;
        /* �ɱ�������ֻ��3��������3���������ܶ������ */
        if(MAX_VAR_PARAM == i)
        {
            break;
        }
    }
    VA_END(varArg);

    /* ���б��ʱ��һ���ɱ�����ڴ���ʱ������MOR��
       �����������auiVarPara[0]�Ƿ�Ϊ0���ж��Ƿ��б�� */
       
    /* �ޱ�δ��� */
    if(0 == i)
    {
        stElement.uiValFlag = ELEMENT_NOT_VALUED;
    }
    /* �б�δ��� */
    else
    {
        stElement.uiValFlag = ELEMENT_VALUED;
        uiMor = auiVarPara[0];
        if(i > 1)
        {
            uiVal = auiVarPara[1];
        }
    }
    stElement.uiMor = uiMor;
    stElement.uiVal = uiVal;

    CLI_BufInit(&stBufInfo, szName, sizeof(szName), 0);
    bufsprintf(&stBufInfo, "$%d", ++pstMoudle->uiNo);
    
    /* �жϹؼ������� */
    if(CLI_IsInteger(pcName, &stElement.uiMin, &stElement.uiMax))
    {
        stElement.uiFlag = ELEMENT_INT;
    }
    else if(CLI_IsString(pcName, &stElement.uiMin, &stElement.uiMax))/* min����Ϊ�� */
    {
        stElement.uiFlag = ELEMENT_STR;
    }
    else
    {
        stElement.uiFlag = ELEMENT_NONE;
    }
    /* �ؼ����б�����Ӹùؼ��� */
    ulRetVal = CLI_List_AddNode(pstMoudle->hCurList, (const CHAR *)szName, (VOID *)&stElement);
    YNTEST_CHK_FAILED(ulRetVal,"add word to key word list failed. word = %s\n",pcName);

    /* ���ùؼ�����ӵ�g_acCompletionGroup��Ӧ������ */
    ulRetVal = CLI_AddCompletionWord(g_acCompletionGroup, pcName);
    YNTEST_CHK_FAILED(ulRetVal,"add word to completion group failed. word = %s\n",pcName);

    return ERROR_SUCCESS;
}

/*****************************************************************************
 Func Name    : CLI_FilterWord
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �жϹؼ����Ƿ���Ҫ����
 Input        : const CHAR *pcName   �ؼ�����
 Output       : NONE
 Return       : BOOL_TRUE: ����
                BOOL_FALSE: ������
 Caution      : 
*****************************************************************************/
STATIC BOOL_T CLI_FilterWord(IN CONST CHAR *pcName)
{
    UINT uiLoop = 0;

    DBGASSERT_WITH_RETURN(NULL != pcName, BOOL_TRUE);

    if(NULL != strstr(pcName, "INTEGER"))
    {
        return BOOL_TRUE;
    }
    if(NULL != strstr(pcName, "STRING"))
    {
        return BOOL_TRUE;
    }

    while(uiLoop < MAX_COMPLETION_NUM && g_acCompletionGroup[uiLoop] != NULL)
    {
        if(0 == CLI_Strcmp(pcName, g_acCompletionGroup[uiLoop]))
        {
            return BOOL_TRUE;
        }
        uiLoop++;
    }
    return BOOL_FALSE;
}

/*****************************************************************************
 Func Name    : CLI_AddCompletionWord
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ��ע��Ĺؼ�����ӵ����ʲ�ȫ�б�
 Input        : CONST CHAR **ppList       ���ʲ�ȫ�б�ָ��
                CONST CHAR *pcName        ָ�����ӵĹؼ��ֵ�ָ��
 Output       : NONE
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : 
*****************************************************************************/
STATIC ULONG CLI_AddCompletionWord(INOUT CONST CHAR **ppList, IN CONST CHAR *pcName)
{
    ULONG ulRetVal = ERROR_SUCCESS;
    UINT i = 0;
    CHAR *pcTemp = NULL;

    DBGASSERT(NULL != ppList);
    DBGASSERT(NULL != pcName);

    /* ����INTEGER  /STRING ������ӵĹؼ���*/
    if(CLI_FilterWord(pcName))
    {
        return ERROR_SUCCESS;
    }
    
    while(i < MAX_COMPLETION_NUM && (ppList[i] != NULL))
    {
        i++;
    }
    YNTEST_CHK_FAILED(MAX_COMPLETION_NUM == i, "Completion group over size.\n");

    pcTemp = (CHAR *)malloc(strlen(pcName) + 1);
    YNTEST_CHK_FAILED(NULL == pcTemp, "malloc failed.\n");
    
    (VOID)strlcpy(pcTemp, pcName, strlen(pcName) + 1);
    ppList[i] = pcTemp;

    return ulRetVal;
}


/* Cli �����ʽ���� */
/*****************************************************************************
 Func Name    : CLI_Reg_DefCli
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : CLI �����ʽ����API
 Input        : CLI_MOUDLE_E enMoudle       ģ��ID
                CONST CHAR *pcClue          �����ʽ
                UINT uiCmd                  �������ʽ�󶨵�id
 Output       : NONE
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : �ڶ��������ʽʱ��Ӧ�ô�API,Ӧ�ú�CLI_DEF_CMD
*****************************************************************************/
ULONG CLI_Reg_DefCli(IN CLI_MOUDLE_E enMoudle, IN CONST CHAR *pcClue, IN UINT uiCmd)
{
    CLI_MODULE_S *pstMoudle;
    UINT uiStrLen;

    DBGASSERT(enMoudle < CLI_MOUDLE_BUTT);
    DBGASSERT(NULL != pcClue);

    pstMoudle = CLI_GetMoudleInfo(enMoudle);
    YNTEST_CHK_PTR_FAILED(pstMoudle);
    
    uiStrLen = CLI_ClueParse( pcClue, '\0');
    
    /* ����������Ӧ��һ���ؼ��֣��ؼ���ǰ����һ��'�ո�' */
    if(uiStrLen < 4)
    {
        Log_Print(LOG_LEVEL_ERROR, "invalid command format. \'%s\'\n",pcClue);
        return ERROR_FAILED;
    }
    CLI_ClueTree(pstMoudle, pcClue, &pstMoudle->stTree, uiStrLen, uiCmd);

    return ERROR_SUCCESS;
}

/*****************************************************************************
 Func Name    : CLI_Tree_FindChildByName
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �����������и��ݹؼ��������������ڵ�
 Input        : DTQ_HEAD_S *pstChildList    ����ͷ�ڵ�ָ��
                CHAR *pcName                �ؼ�����
 Output       : UINT *uiErrCode             �������
 Return       : ���ҳɹ��򷵻ظýڵ�, ���򷵻�NULL
 Caution      : 
*****************************************************************************/
STATIC TEST_TREE_NODE_S *CLI_Tree_FindChildByName(DTQ_HEAD_S *pstChildList, CHAR *pcName, UINT *uiErrCode)
{
    DTQ_NODE_S *pstNode;
    TEST_TREE_NODE_S *pstTreeNode;
    UINT uiNo;
    UINT uiStrLen;
    *uiErrCode = CLI_ERROR_NONE;

    DBGASSERT_WITH_RETURN(NULL != pstChildList, NULL);
    DBGASSERT_WITH_RETURN(NULL != pcName, NULL);

    DTQ_FOREACH(pstChildList, pstNode)
    {
        pstTreeNode = container_of(pstNode, TEST_TREE_NODE_S, stBrother);

        switch(pstTreeNode->pstElement->uiFlag)
        {
            case ELEMENT_NONE:
                if(0 == strcmp(pstTreeNode->pstElement->pcName, pcName))
                {
                    pstTreeNode->szStr[0] = 0;
                    return pstTreeNode;
                }
                break;
            case ELEMENT_INT:
                uiStrLen = CLI_Str2dec((const CHAR *)pcName, &uiNo);
                if((0 != uiStrLen)&&('\0'==pcName[uiStrLen])&&
                (pstTreeNode->pstElement->uiMin <= uiNo)&&
                (pstTreeNode->pstElement->uiMax >= uiNo))
                {
                    if(pstTreeNode->pstElement->pfCheck)
                    {
                        if(ERROR_SUCCESS != pstTreeNode->pstElement->pfCheck(pcName))
                        {
                            break;
                        }
                    }
                    strcpy(pstTreeNode->szStr, pcName);
                    return pstTreeNode;
                }
                else
                {
                    *uiErrCode = CLI_ERROR_INTEGER;
                    return NULL;
                }
            case ELEMENT_STR:
                uiStrLen = strlen(pcName);
                if((pstTreeNode->pstElement->uiMin <= uiStrLen)&&(pstTreeNode->pstElement->uiMax >= uiStrLen))
                {
                    if(pstTreeNode->pstElement->pfCheck)
                    {
                        if(ERROR_SUCCESS != pstTreeNode->pstElement->pfCheck(pcName))
                        {
                            break;
                        }
                    }

                    strcpy(pstTreeNode->szStr, pcName);
                    return pstTreeNode;
                }
                else
                {
                    *uiErrCode = CLI_ERROR_STRING;
                    return NULL;
                }
            default:
                break;
        }
    }

    return NULL;
}


/* �������ֲ��������������еĽ�� */
/*****************************************************************************
 Func Name    : CLI_Tree_FindSameName
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �����������и��ݹؼ��������������ڵ�
 Input        : DTQ_HEAD_S *pstChildList    �������ڵ�ָ��
                CHAR *pcName                �ؼ�����
 Output       : UINT *uiErrCode             �������
 Return       : ���ҳɹ��򷵻ظýڵ�, ���򷵻�NULL
 Caution      : 
*****************************************************************************/
TEST_TREE_NODE_S *CLI_Tree_FindSameName(TEST_TREE_NODE_S *pstTree, CHAR *pcName, UINT *uiErrCode)
{
    TEST_TREE_NODE_S *pstTmpTree = NULL;
    TEST_TREE_NODE_S *pstLast;

    DBGASSERT_WITH_RETURN(NULL != pstTree, NULL);
    DBGASSERT_WITH_RETURN(NULL != pcName, NULL);

    pstLast = pstTree;
    do
    {
        pstTmpTree = CLI_Tree_FindChildByName(&pstLast->stChild, pcName, uiErrCode);

        if(NULL != pstTmpTree)
        {
            break;/* �ҵ� */
        }

        if(NULL == pstLast->pstNext)
        {
            break;
        }

        pstLast = pstLast->pstNext;
    }while(1);

    return pstTmpTree;
}

/* ��������������ÿ�ν���һ���ؼ��ֻ���� */
/*****************************************************************************
 Func Name    : CLI_SubCliParse
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ��������������ÿ�ν���һ���ؼ��ֻ����
 Input        : CONST CHAR *pcInBuf    ��buffer
                UINT uiSize            ��Buffer size
 Output       : UINT *uiErrCode        �������
                CHAR *pcString         ��Buffer
 Return       : ���ν����ĳ���
 Caution      : 
*****************************************************************************/
UINT CLI_SubCliParse(IN CONST CHAR *pcInBuf, OUT CHAR *pcString, IN UINT uiSize, OUT UINT *uiErrCode)
{
    UINT uiParsedLen = 0;
    UINT uiStrLen;
    UINT uiStartPos = 0;
    UINT uiEndPos = 0;

    if((NULL == pcInBuf) || (NULL == pcString))
    {
        *uiErrCode = (UINT)CLI_ERROR_NULL;
        return 0;
    }

    memset(pcString, 0, uiSize);
    /* �������������п�ʼ�Ŀհ� */
    while(YNTEST_WHITESPACE(pcInBuf[uiParsedLen]))
    {
        uiParsedLen++;
    }
    
    /* ��¼�ؼ��ֿ�ʼλ�� */
    uiStartPos = uiParsedLen;
    while(!YNTEST_WHITESPACE(pcInBuf[uiParsedLen]) && (pcInBuf[uiParsedLen] != '\0'))
    {
        uiParsedLen++;
    }
    uiEndPos = uiParsedLen;
    uiStrLen = uiEndPos - uiStartPos;
    
    if(0 == uiStrLen)
    {
        pcString[uiStrLen] = '\0';
        return ++uiParsedLen;
    }
    else if(uiStrLen < uiSize)
    {
        memcpy(pcString, pcInBuf + uiStartPos, uiStrLen);
        pcString[uiStrLen] = '\0';
    }
    else
    {
        *uiErrCode = (UINT)CLI_ERROR_OVERFLOW;
    }
    return ++uiParsedLen;
}

/* ������� */
/*****************************************************************************
 Func Name    : CLI_CliParse
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : CLI �������API
 Input        : CONST CHAR *pcInput             ��Buffer
                CONST CHAR * CONST *ppcArg      
                VOID *pData                     ָ�����ò�����ָ��
 Output       : NONE
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : 
*****************************************************************************/
ULONG CLI_CliParse(IN CONST      CHAR *pcInput, CONST CHAR * CONST *ppcArg, VOID *pData)
{
    UINT i = 0;
    UINT uiNum = 0;
    UINT uiSubLen = 0;
    UINT uiErrCode = 0;
    TEST_TREE_NODE_S *pstTree;
    TEST_TREE_NODE_S *pstTmpTree;
    CLI_MODULE_S *pstBash;
    CHAR acArgName[80] = {0};
    UINT uiLen;

    DBGASSERT(NULL != pcInput);
    DBGASSERT(NULL != pData);
    
    IGNORE_PARAM(ppcArg);
    pstBash = (CLI_MODULE_S *)pData;
    uiLen = strlen(pcInput);

    pstTree = &pstBash->stTree;
    pstBash->enErrType = CLI_ERROR_NONE;
    pstBash->pstErrorNode = NULL;
    while(i < uiLen)
    {
        uiSubLen = CLI_SubCliParse(pcInput + i, acArgName, 80, &uiErrCode);
        i += uiSubLen;
        if(uiErrCode)
        {
            pstBash->enErrType = (CLI_PRASE_ERROR_E)uiErrCode;
            pstBash->uiParsedLen = i-uiSubLen;
            pstBash->pstErrorNode = pstTree;
            return ERROR_FAILED;
        }

        /* �Ѿ������������ʽ�����һ���ؼ��֣����������ж����򲻽��н��� */
        if(pstTree->bLeaf && (pstTree->stChild.stHead.pstNext == &pstTree->stChild.stHead))
        {
            pstBash->enErrType = CLI_ERROR_OVERSIZE;
            pstBash->uiParsedLen = i-uiSubLen;
            pstBash->pstErrorNode = pstTree;
            return ERROR_FAILED;
        }
        pstTmpTree = CLI_Tree_FindSameName(pstTree, (CHAR *)acArgName, &uiErrCode);

        /* ����������ʱ�������ʽ����ȷ����¼�´�ʱ��λ�ý�㣬���˳����� */
        if(NULL == pstTmpTree)
        {
            /* �����Ĺؼ����ǲ��� */
            if(uiErrCode)
            {
                pstBash->pstErrorNode = pstTree;
                pstBash->uiCurCliNum = uiNum;
                pstBash->enErrType = (CLI_PRASE_ERROR_E)uiErrCode;
                pstBash->uiParsedLen = i-uiSubLen;
                return ERROR_FAILED;
            }
            else
            {
                pstBash->pstErrorNode = pstTree;
                pstBash->uiCurCliNum = uiNum;
                pstBash->enErrType = CLI_ERROR_UNDEFINED;
                pstBash->uiParsedLen = i-uiSubLen;
                return ERROR_FAILED;
            }
        }

        pstBash->apstCurCli[uiNum] = pstTmpTree->pstElement;
        pstBash->apstCurTree[uiNum] = pstTmpTree;
        uiNum++;

        pstTree = pstTmpTree;
    }

    pstBash->uiCurCliNum = uiNum;

    /* ����������ʽ����������¼���������Ľ�� */
    if(!pstTree->bLeaf)
    {
        pstBash->pstErrorNode = pstTree;
        pstBash->enErrType = CLI_ERROR_INCMPLETE;
        pstBash->uiParsedLen = i;
        return ERROR_FAILED;
    }
    /* ���������и�ʽ��ȷ����¼�´������ж�Ӧ��uiCmd */
    else
    {
        pstBash->uiCmd = pstTree->uiCmd;
    }
    
    /* return i; */
    return ERROR_SUCCESS;
}

/*****************************************************************************
 Func Name    : CLI_CheckPraseRes
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �������������
 Input        : UINT uiSize             ��Buffer size
                VOID *pData             ָ�����ò�����ָ��
 Output       : CHAR *pcBuf             ��Buffer
 Return       : 0: ��������
                ��0: ��������д�
 Caution      : 
*****************************************************************************/
UINT CLI_CheckPraseRes(INOUT CHAR *pcBuf, IN UINT uiSize, IN VOID *pData)
{
    CLI_MODULE_S *pstBash;
    BUF_INFO_S stIBuf;

    if(NULL == pcBuf || NULL == pData)
    {
        return 0;
    }
    pstBash = (CLI_MODULE_S *)pData;

    CLI_BufInit(&stIBuf, pcBuf, uiSize, 0);

    if((NULL != pstBash->pstErrorNode) || (CLI_ERROR_NONE != pstBash->enErrType))
    {
        CLI_ShowErrInfo(pstBash->enErrType, &stIBuf, pstBash);
        return CLI_BufGetSize(&stIBuf);
    }

    return 0;

}

/*****************************************************************************
 Func Name    : CLI_ShowErrInfo
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ��ӡ������ϢAPI
 Input        : CLI_PRASE_ERROR_E enErrType     ��������
                BUF_INFO_S *pstBuf              ��Ŵ�����Ϣ�ĵ�ַ
                VOID *pData                     ָ�����ò�����ָ��
 Output       : NONE
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : 
*****************************************************************************/
STATIC ULONG CLI_ShowErrInfo(CLI_PRASE_ERROR_E enErrType, BUF_INFO_S *pstBuf, VOID *pData)
{
    CLI_MODULE_S *pstBash;
    CHAR pcBuf[BUF_SIZE_256] = {0};

    DBGASSERT(NULL != pstBuf);
    DBGASSERT(NULL != pData);

    pstBash = (CLI_MODULE_S *)pData;
    switch(enErrType)
    {
        case CLI_ERROR_NULL:
            bufsprintf(pstBuf, "Warning: nullptr detected in function ' test_CliParse '\n");
            break;
        case CLI_ERROR_OVERFLOW:
            CLI_FillBufWithSpace(pcBuf, pstBash->uiParsedLen + strlen(g_acPrompt));
            bufsprintf(pstBuf,"%s^\n%s\n",pcBuf,g_acErrInfo[3]);
            break;
        case CLI_ERROR_INCMPLETE:
            CLI_FillBufWithSpace(pcBuf, pstBash->uiParsedLen + strlen(g_acPrompt)-1);
            bufsprintf(pstBuf,"%s^\n%s\n",pcBuf,g_acErrInfo[0]);
            break;
        case CLI_ERROR_UNDEFINED:
            CLI_FillBufWithSpace(pcBuf, pstBash->uiParsedLen + strlen(g_acPrompt));
            bufsprintf(pstBuf,"%s^\n%s\n",pcBuf,g_acErrInfo[1]);
            break;
        case CLI_ERROR_INTEGER:
            CLI_FillBufWithSpace(pcBuf, pstBash->uiParsedLen + strlen(g_acPrompt));
            bufsprintf(pstBuf,"%s^\n%s\n",pcBuf,g_acErrInfo[2]);
            break;
        case CLI_ERROR_STRING:
             CLI_FillBufWithSpace(pcBuf, pstBash->uiParsedLen + strlen(g_acPrompt));
             bufsprintf(pstBuf,"%s^\n%s\n",pcBuf,g_acErrInfo[4]);
         break;
        case CLI_ERROR_OVERSIZE:
             CLI_FillBufWithSpace(pcBuf, pstBash->uiParsedLen + strlen(g_acPrompt));
             bufsprintf(pstBuf,"%s^\n%s\n",pcBuf,g_acErrInfo[5]);
             
         default: break;
    }
    return ERROR_SUCCESS;
}

/* ���������' ' */
/*****************************************************************************
 Func Name    : CLI_FillBufWithSpace
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : Buffer�����ָ�����ȵ�' '�ַ�
 Input        : CHAR *pcInBuf     ��Buffer
                UINT uiSize       ��Ҫ���ĳ���
 Output       : NONE
 Return       : ���ĳ���
 Caution      : 
*****************************************************************************/
UINT CLI_FillBufWithSpace(IN CHAR *pcInBuf, IN UINT uiSize)
{
    UINT uiLen;

    DBGASSERT_WITH_RETURN(NULL != pcInBuf, 0);

    /* �ڲ�������ָֹ��Խ�� */
    uiLen = (uiSize <= 255) ? uiSize : 255;
    memset(pcInBuf, ' ', uiLen);
    pcInBuf[uiLen] = '\0';
    return strlen(pcInBuf);
}

/*****************************************************************************
 Func Name    : CLI_AllocateInit
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �����ڴ���Ϣ�����ݽṹ��ʼ��
 Input        : MEM_INFO_S *pstMem     ָ�򱣴��ڴ���Ϣ���ݽṹ��ָ��
 Output       : NONE
 Return       : NONE
 Caution      : 
*****************************************************************************/
VOID CLI_AllocateInit(IN MEM_INFO_S *pstMem)
{
    DBGASSERT_RETURN_NONE(NULL != pstMem)

    pstMem->pMem = NULL;
    pstMem->uiAllocatedSize = 0;
    pstMem->uiUsedSize = 0;
    pstMem->bRet = BOOL_FALSE;
    return;
}

/* �����в��������� */
/*****************************************************************************
 Func Name    : CLI_CliParamsProc
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �����ڴ���Ϣ�����ݽṹ��ʼ��
 Input        : CLI_MODULE_S *pstMoudle     ģ������
                UINT uiOutBufSize           �� Buffer size
 Output       : BYTE *pOutBuf               ��Buffer
 Return       : VOID *
 Caution      : 
*****************************************************************************/
VOID *CLI_CliParamsProc(IN CLI_MODULE_S *pstMoudle, INOUT BYTE *pOutBuf, IN UINT uiOutBufSize)
{
    UINT uiNum;
    UINT uiLoop = 0;
    TEST_ELEMENT_S *pstEle;
    TEST_TREE_NODE_S *pstTmpTree;
    UINT uiParamTmp;
    MEM_INFO_S stMemInfo;
    BUF_INFO_S stBufInfo;

    DBGASSERT_WITH_RETURN(NULL != pstMoudle, NULL);
    DBGASSERT_WITH_RETURN(NULL != pOutBuf, NULL);
    
    uiNum = pstMoudle->uiCurCliNum;
    /* ����buf��ʼ�� */
    CLI_BufInit(&stBufInfo, pOutBuf, uiOutBufSize, 0);
    YNTEST_CLEAR_BUF(stBufInfo.pcBuf, stBufInfo.uiMaxSize);

    CLI_AllocateInit(&stMemInfo);
    test_Malloc(&stMemInfo, BUF_SIZE_64, BYTE);
    if(!stMemInfo.bRet)
    {
        Log_Print(LOG_LEVEL_ERROR, "Allocte memory failed! %d \n");
        if(stMemInfo.pMem != NULL)
        free(stMemInfo.pMem);
        return NULL;
    }
    YNTEST_CLEAR_BUF(stMemInfo.pMem, BUF_SIZE_64);
    for(uiLoop = 0; uiLoop < uiNum; uiLoop++)
    {
        pstEle = (TEST_ELEMENT_S *)pstMoudle->apstCurCli[uiLoop];
        switch(pstEle->uiFlag)
        {
            case ELEMENT_NONE:
                if(pstEle->uiValFlag == ELEMENT_VALUED)
                {
                    uiParamTmp = pstEle->uiVal;
                    CLI_Memcpy(stBufInfo.pcBuf + stBufInfo.uiUsedSize, &uiParamTmp, sizeof(uiParamTmp));
                    stBufInfo.uiUsedSize += sizeof(uiParamTmp);
                }
                break;
            case ELEMENT_INT:
                pstTmpTree = (TEST_TREE_NODE_S *)(pstMoudle->apstCurTree[uiLoop]);
                (VOID)CLI_Str2dec(pstTmpTree->szStr, &uiParamTmp);
                
                CLI_Memcpy(stBufInfo.pcBuf + stBufInfo.uiUsedSize, &uiParamTmp, sizeof(uiParamTmp));
                stBufInfo.uiUsedSize += sizeof(uiParamTmp);
                break;
            case ELEMENT_STR:
                pstTmpTree = (TEST_TREE_NODE_S *)(pstMoudle->apstCurTree[uiLoop]);
                if((stMemInfo.uiUsedSize + strlen(pstTmpTree->szStr)) >= stMemInfo.uiAllocatedSize)
                {
                    test_Realloc(&stMemInfo, BUF_SIZE_64, BYTE);
                    if(!stMemInfo.bRet)
                    {
                        Log_Print(LOG_LEVEL_ERROR, "Allocte memory failed! %d \n");
                        return NULL;
                    }
                    YNTEST_CLEAR_BUF(stMemInfo.pMem + (stMemInfo.uiAllocatedSize - BUF_SIZE_64), BUF_SIZE_64);
                }
                CLI_Memcpy(stMemInfo.pMem + stMemInfo.uiUsedSize, pstTmpTree->szStr, strlen(pstTmpTree->szStr));
                stMemInfo.uiUsedSize += strlen(pstTmpTree->szStr);
                CLI_Memcpy(stMemInfo.pMem + stMemInfo.uiUsedSize, "#", 1);
                stMemInfo.uiUsedSize += 1;
                break;

            default: break;
        }
    }
    *(stMemInfo.pMem + stMemInfo.uiUsedSize) = '\0';
    return stMemInfo.pMem;
}

/* ��ȡ���� */
/*****************************************************************************
 Func Name    : CLI_GetFeatureKey
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ��ȡ��������
 Input        : VOID *pCfg
                
 Output       : UINT *puiNo
 Return       : UINT
 Caution      : 
*****************************************************************************/
STATIC UINT CLI_GetFeatureKey(VOID *pCfg, UINT *puiNo)
{
    CLI_MODULE_S *pstData;
    UINT uiTemp = *puiNo;
    UINT uiKey = USELESS_PARA;

    DBGASSERT_WITH_RETURN(pCfg != NULL, USELESS_PARA);
    DBGASSERT_WITH_RETURN(puiNo != NULL, USELESS_PARA);

    pstData = (CLI_MODULE_S *)pCfg;
    if(uiTemp >= pstData->uiCurCliNum)
    {
        return USELESS_PARA;
    }
    do
    {
        if(NULL != ((TEST_ELEMENT_S *)pstData->apstCurCli[uiTemp]))
        {
            uiKey = ((TEST_ELEMENT_S *)pstData->apstCurCli[uiTemp])->uiMor;
        }
        else
        {
            Log_Print(LOG_LEVEL_ERROR,"null pointer found.\n");
        }
        uiTemp++;
        /* ���в����Ѿ������� */
        if(uiTemp >= pstData->uiCurCliNum)
        {
            break;
        }
    }while(USELESS_PARA == uiKey);

    *puiNo = uiTemp - 1;
    return uiKey;
}

/*****************************************************************************
 Func Name    : CLI_GetFeatureParam
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ��ȡ��������
 Input        : VOID *pCfg
                UINT uiIndex
                PRASE_PARAM_TYPE_S *pstPara
 Output       : NONE
 Return       : VOID *
 Caution      : 
*****************************************************************************/
STATIC VOID *CLI_GetFeatureParam(VOID *pCfg, UINT uiIndex, PRASE_PARAM_TYPE_S *pstPara)
{
    CLI_MODULE_S *pstData;
    TEST_ELEMENT_S *pstEle = NULL;

    DBGASSERT_WITH_RETURN(NULL != pCfg, NULL);
    DBGASSERT_WITH_RETURN(NULL != pstPara, NULL);

    pstData = (CLI_MODULE_S *)pCfg;
    if(uiIndex >= pstData->uiCurCliNum)
    {
        Log_Print(LOG_LEVEL_ERROR, "invalid parameter index. index = %u\n",uiIndex);
        return NULL;
    }
    pstEle = ((TEST_TREE_NODE_S *)pstData->apstCurTree[uiIndex])->pstElement;
    if(pstEle->uiValFlag == ELEMENT_VALUED)
    {
        pstPara->bIsVal = BOOL_TRUE;
        pstPara->uiVal = pstEle->uiVal;
    }
    else
    {
        pstPara->bIsVal = BOOL_FALSE;
        pstPara->uiVal = USELESS_PARA;
    }
    pstPara->uiType = pstEle->uiFlag;
    if(NULL != ((TEST_TREE_NODE_S *)pstData->apstCurTree[uiIndex])->szStr)
    {
        return ((TEST_TREE_NODE_S *)pstData->apstCurTree[uiIndex])->szStr;
    }
    else
    {
        return NULL;
    }
}

/*****************************************************************************
 Func Name    : CLI_GetFeatureParam
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ��ȡ�������ø���
 Input        : VOID *pCfg
 Output       : NONE
 Return       : UINT
 Caution      : 
*****************************************************************************/
STATIC UINT CLI_PRASE_GetFeatureCliNum(VOID *pCfg)
{
    CLI_MODULE_S *pstData;

    DBGASSERT_WITH_RETURN(NULL != pCfg, 0);

    pstData = (CLI_MODULE_S *)pCfg;
    return pstData->uiCurCliNum;
}

/*****************************************************************************
 Func Name    : CLI_PRASE_ParamPrase
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �����û����������Ĳ���
 Input        : VOID *pCfg      ģ������
                UINT uiNum      ��������
 Output       : CLI_PARAM_PRASE_S *pstParam     �������Ĳ���������
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : 
*****************************************************************************/
ULONG CLI_PRASE_ParamPrase(IN VOID *pCfg, INOUT CLI_PARAM_PRASE_S *pstParam, IN UINT uiNum)
{
    UINT  uiLoop = 0;
    UINT  uiKey  = 0;
    UINT  uiBlkSeqNo = 0;
    VOID *pParaInfo  = NULL;
    UINT uiMaxNum = 0;
    PRASE_PARAM_TYPE_S stParam;
    ULONG ulRet = ERROR_SUCCESS;
    CLI_PARAM_PRASE_S *pstCurParam = NULL;

    DBGASSERT((NULL != pCfg) && (NULL != pstParam) && (0 != uiNum));

    uiMaxNum = CLI_PRASE_GetFeatureCliNum(pCfg);
    while(uiBlkSeqNo < uiMaxNum )
    {
        YNTEST_CLEAR_BUF(&stParam, sizeof(stParam));
        uiKey = CLI_GetFeatureKey(pCfg, &uiBlkSeqNo);
        pParaInfo = CLI_GetFeatureParam(pCfg, uiBlkSeqNo, &stParam);
        uiBlkSeqNo++;
        for(uiLoop = 0; uiLoop < uiNum; uiLoop++)
        {
            pstCurParam = pstParam + uiLoop;
            if(uiKey == pstCurParam->uiKey)
            {
                if(pstCurParam->pData != NULL)
                {
                    ulRet = CLI_PRASE_ParamProc(pParaInfo, pstCurParam->uiBufLen, pstCurParam->pData, stParam);
                    if(ulRet)
                    {
                        return ulRet;
                    }
                    /* �ò����Ǳ��ν�Ҫ�����Ĳ���,��������˳�����ѭ�� */
                    break;
                }
            }
        }
    }
    return ulRet;
}

/*****************************************************************************
 Func Name    : CLI_PRASE_ParamProc
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �����û�ָ���Ĳ���
 Input        : VOID *pParaInfo      ������Ϣ
                UINT uiBufLen        �����������buffer����
                PRASE_PARAM_TYPE_S stInfo �������Ĳ���������Ϣ
 Output       : VOID *pData          �������Ĳ���������
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : 
*****************************************************************************/
STATIC ULONG CLI_PRASE_ParamProc(VOID *pParaInfo, UINT uiBufLen, VOID *pData, PRASE_PARAM_TYPE_S stInfo)
{
    CHAR *pcTmp ;
    UINT uiVal = stInfo.uiVal;
    
    DBGASSERT(NULL != pParaInfo);
    DBGASSERT(NULL != pData);

    pcTmp = (CHAR *)pParaInfo;
    switch(stInfo.uiType)
    {
        case ELEMENT_NONE:
        /* �˴��жϳ�����������ELEMENT_NONE��ֱ��ȷ���ؼ���Я��������Ϣ */
        /* ���ݴ����Buff�����жϲ���������,�˴�ֱ��ת��Ϊָ��������,�����ɲ���ת�� */
        if (sizeof(UCHAR) == uiBufLen)
            {
                *(UCHAR *)pData = (UCHAR)uiVal;
            }
            else if (sizeof(USHORT) == uiBufLen)
            {
                *(USHORT *)pData = (USHORT)uiVal;
            }
            else if (sizeof(ULONG) == uiBufLen)
            {
                *(ULONG *)pData = (ULONG)uiVal;
            }
            /* Я����������Ĭ��ΪUINT�� */
            else
            {
                *(UINT *)pData = uiVal;
            }
            break;

         case ELEMENT_INT:
         /* Ҫ�����Ĳ�������ΪINT�͵Ĵ��� */
         (VOID)CLI_Str2dec(pcTmp, &uiVal);
         if (sizeof(UCHAR) == uiBufLen)
            {
                *(UCHAR *)pData = (UCHAR)uiVal;
            }
            else if (sizeof(USHORT) == uiBufLen)
            {
                *(USHORT *)pData = (USHORT)uiVal;
            }
            else if (sizeof(ULONG) == uiBufLen)
            {
                *(ULONG *)pData = (ULONG)uiVal;
            }
            /* Я����������Ĭ��ΪUINT�� */
            else
            {
                *(UINT *)pData = uiVal;
            }
            break;

        case ELEMENT_STR:
        (VOID)strlcpy(pData, pcTmp, uiBufLen);
        break;
        default: break;
    }
    
    return ERROR_SUCCESS;
}

/*****************************************************************************
 Func Name    : CLI_RegCallBack
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ģ��CallBack����ע��
 Input        : UINT uiKey          ģ��id
                CLI_CIOCTL_PF *ppMoudleCallBack �ص�API��ַ
                CONST CHAR *pcDes               ģ������
 Output       : 
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : 
*****************************************************************************/
ULONG CLI_RegCallBack(IN UINT uiKey, IN CLI_MOUDLE_CIOCTL_PF pfFunc)
{
    ULONG ulRetVal = ERROR_SUCCESS;
    UINT uiLoop = 0;

    DBGASSERT(NULL != pfFunc);

    if(uiKey >= CLI_MOUDLE_BUTT)
    {
        Log_Print(LOG_LEVEL_ERROR, "exceed maximum moudle id, maximum is %d, but current moudle is %d.\n",CLI_MOUDLE_BUTT, uiKey);
        return ERROR_FAILED;
    }
    while(g_astCallBackDB[uiLoop].pfMoudlCallBack != NULL)
    {
        uiLoop++;
        YNTEST_CHK_FAILED(uiLoop == CLI_MOUDLE_BUTT, "g_astCallBackDB oversize, current moudle is %d\n",uiKey);
    }

    g_astCallBackDB[uiLoop].pfMoudlCallBack = pfFunc;
    g_astCallBackDB[uiLoop].uiKey = uiKey;

    return ulRetVal;
}

/*****************************************************************************
 Func Name    : CLI_FindMoudleCallBack
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ģ��callback API����
 Input        : UINT uiKey          ģ��id
 Output       : CLI_CIOCTL_PF *ppMoudleCallBack �ص�API��ַ
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : 
*****************************************************************************/
STATIC ULONG CLI_FindMoudleCallBack(UINT uiKey, CLI_MOUDLE_CIOCTL_PF *ppMoudleCallBack)
{
    UINT uiLoop;

    DBGASSERT(NULL != ppMoudleCallBack);
    if(uiKey >= CLI_MOUDLE_BUTT)
    {
        Log_Print(LOG_LEVEL_ERROR, 
        "exceed maximum moudle id, maximum is %d, but current moudle is %d.\n",
        CLI_MOUDLE_BUTT, uiKey);
        return ERROR_FAILED;
    }
    
    for(uiLoop=0; uiLoop < ARRAY_SIZE(g_astCallBackDB); uiLoop++)
    {
        if((uiKey == g_astCallBackDB[uiLoop].uiKey ) &&
            (NULL != g_astCallBackDB[uiLoop].pfMoudlCallBack))
        {
            *ppMoudleCallBack = g_astCallBackDB[uiLoop].pfMoudlCallBack;
            return ERROR_SUCCESS;
        }
    }
    Log_Print(LOG_LEVEL_ERROR, "find moudle callback failed.\n");
    return ERROR_FAILED;

}

/*****************************************************************************
 Func Name    : CLI_CliExc
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ��������ID��ִ�ж�Ӧ������ܺ���
 Input        : UINT uiCmd      ����id
                VOID *pData     ���ò���
 Output       : NONE
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : 
*****************************************************************************/
STATIC ULONG CLI_CliExc(IN UINT uiCmd, IN VOID *pData)
{
    CLI_MOUDLE_CIOCTL_PF pfCmdProc = NULL;
    ULONG ulRetVal = ERROR_SUCCESS;
    UINT uiKey = DE_CMD(uiCmd);

    DBGASSERT(pData != NULL);
    
    ulRetVal = CLI_FindMoudleCallBack(uiKey, &pfCmdProc);
    YNTEST_CHK_FAILED(ulRetVal, "get moudle callback failed.\n");
    return pfCmdProc(uiCmd, pData);
}

/* ������Ԥ���� */
/*****************************************************************************
 Func Name    : CLI_CliPreProc
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �������Ԥ����API
 Input        : VOID *pInBuf      ��Buffer
 Output       : VOID *pInBuf      ��Buffer
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : 
*****************************************************************************/
ULONG CLI_CliPreProc(INOUT     VOID *pInBuf)
{
    CHAR *pcLine;
    UINT uiInputLen = 0;
    
    DBGASSERT(NULL != pInBuf);
    
    pcLine = (CHAR *)pInBuf;
    uiInputLen = strlen(pcLine);
    /* ����������ĩ�Ŀո��ַ� */
    while((0 != uiInputLen) && (pcLine[--uiInputLen] == ' '));

    uiInputLen++;

    pcLine[uiInputLen] = '\0';

    if((0 == strlen(pcLine)) || ((pcLine[0] == ' ') && (uiInputLen == 1)))
    {
        return ERROR_FAILED;
    }
    return ERROR_SUCCESS;
}

/*****************************************************************************
 Func Name    : CLI_CliProc
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �������API����
 Input        : VOID *pCfg      ģ������
                CONST CHAR *pcInBuf      ��Buffer
 Output       : NONE
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      : 
*****************************************************************************/
ULONG CLI_CliProc( IN CONST CHAR *pcInBuf, IN VOID *pCfg)
{
    CLI_MODULE_S *pstMoudle;
    ULONG ulRetVal = ERROR_SUCCESS;
    CHAR acShowBuf[BUF_SIZE_512] = {0};
    
    DBGASSERT(NULL != pCfg);
    DBGASSERT(NULL != pcInBuf);

    pstMoudle = (CLI_MODULE_S *)pCfg;

    ulRetVal = CLI_CliParse( pcInBuf, NULL, (VOID *)pstMoudle);
    if(ulRetVal)
    {
        CLI_CheckPraseRes(acShowBuf, BUF_SIZE_512, (VOID *)pstMoudle);
        printf("%s",acShowBuf);
        return ERROR_FAILED;
    }
    ulRetVal = CLI_CliExc(pstMoudle->uiCmd, (VOID *)pstMoudle);
    YNTEST_CHK_FAILED(ulRetVal, "Execute command filed. Cmd = %x\n",pstMoudle->uiCmd);

    return ERROR_SUCCESS;
}

#ifdef _cplusplus
}
#endif /* end of __cplusplus */

