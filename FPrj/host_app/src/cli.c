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
 CODE_SECTION("内部函数声明")
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
  Description  : 命令线索树初始化
  Input        : TEST_TREE_NODE_S *pstTree      线索树头节点指针
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
 Description  : 命令线索树中检索指定子树是否存在指定的节点
 Input        : DTQ_HEAD_S *pstChildList        子树头指针
                TEST_ELEMENT_S *pstElement      指定节点数据结构指针
 Output       : TEST_TREE_NODE_S **pstSameNode  指向与指定节点同名的指针
 Return       : 在子树中找到该节点则返回该节点,否则返回NULL
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
 Description  : 命令线索树中在指定子树下挂载节点
 Input        : DTQ_HEAD_S *pstChildList        子树头指针
                TEST_ELEMENT_S *pstElement      待挂载节点数据结构指针
 Output       : TEST_TREE_NODE_S **pstSameNode  指向与指定节点同名的指针
 Return       : 子树下挂载节点成功则返回该节点,否则返回NULL
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
    
    /* 在表尾添加该节点 */
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
 Description  : 解析命令格式长度
 Input        : CONST CHAR *pcClue        指向待解析的格式字符串指针
 Output       : NONE
 Return       : 解析出的长度
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
 Description  : 解析命令格式长度
 Input        : CONST CHAR *pcClue        指向待解析的格式字符串指针
                CHAR ucEnd                结束字符
 Output       : NONE
 Return       : 解析出的格式长度
 Caution      :与CLI_SubClueParse不同的是此API需要指定解析时的结束字符,解析到
                结束字符或'\0'会停止解析,CLI_SubClueParse会一直解析直到遇见'\0'
*****************************************************************************/
STATIC UINT CLI_ClueParse( IN CONST CHAR *pcClue, IN CHAR ucEnd)
{
    UINT i =0;
    UINT uiSubLen;
    do
    {
        /* 循环处理'|'分割每一个子句 */
        uiSubLen = CLI_SubClueParse( pcClue+i);
        if(0==uiSubLen)
        {
            Log_Print(LOG_LEVEL_ERROR, "invalid command format. \'%s\'\n", pcClue);
            return 0;
        }

        /* 下一个 */
        i+=uiSubLen;
    }while('|' == pcClue[i-1]);

    /* 句子结尾不对或者句子结尾不是指定字符 */
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
 Description  : 重新挂载遗漏的节点
 Input        : TEST_TREE_NODE_S *pstTreeNode        目标子树头节点指针
                TEST_ELEMENT_S *pstTmp               待挂载节点数据结构指针
 Output       : NONE
 Return       : 子树下挂载节点成功则返回该节点,否则返回NULL
 Caution      :
*****************************************************************************/
STATIC TEST_TREE_NODE_S *CLI_LastTreeNode(IN TEST_TREE_NODE_S *pstTreeNode, IN TEST_ELEMENT_S *pstTmp)
{
    TEST_TREE_NODE_S *pstTreeTmp;
    TEST_TREE_NODE_S *pstSameName;

    DBGASSERT_WITH_RETURN(NULL != pstTreeNode, NULL);
    DBGASSERT_WITH_RETURN(NULL != pstTmp, NULL);
    
    /* 构造树 */
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
 Description  : 解析命令格式构造子树
 Input        : CLI_MODULE_S *pstBash        模块配置空间地址
                CONST CHAR *pcClue           命令格式
                TEST_TREE_NODE_S *pstTree    构造子树头节点指针
                UINT uiClueLen               命令格式长度
                UINT uiCmd                   与命令格式绑定的cmd id
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

        /* 上次错误过滤 */
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

                /* 构造树 */
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

                /* 跳过[]子句 */
                CLI_SubClueTree( pstBash, pcClue+i, pstTreeNode, uiClueLen-i, uiCmd);

                /* 处理[]子句 */                
                CLI_ClueTree( pstBash, pcClue+(i-uiSubLen), pstTreeNode, uiSubLen, uiCmd);

                return;
            case '{':
                uiSubLen = CLI_ClueParse( pcClue+i, '}');
                i += uiSubLen;

                /* 处理{}子句 */                
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
 Description  : 解析命令格式构造子树
 Input        : CLI_MODULE_S *pstBash        模块配置空间地址
                CONST CHAR *pcClue           命令格式
                TEST_TREE_NODE_S *pstTree    构造子树头节点指针
                UINT uiClueLen               命令格式长度
                UINT uiCmd                   与命令格式绑定的cmd id
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
        /* 循环处理'|'分割每一个子句 */
        uiSubLen = CLI_SubClueParse( pcClue+i);

        /* 构造子树 */
        CLI_SubClueTree( pstBash, pcClue+i, pstTree, uiLen-i, uiCmd);

        /* 下一个 */
        i+=uiSubLen;
    }while(i<uiLen);
    
    return;
}

/* 模块初始化函数，申请内存不释放 */
/*****************************************************************************
 Func Name    : CLI_MoudleInfoInit
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 各模块配置空间初始化
 Input        : NONE
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 初始化过程中为各模块配置空间申请的内存在程序运行期间不释放
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

/* 获取当前操作的模块信息 */
/*****************************************************************************
 Func Name    : CLI_GetMoudleInfo
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 获取模块配置空间信息
 Input        : CLI_MOUDLE_E enMoudle   指定模块ID
 Output       : NONE
 Return       : 指定模块配置空间地址
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
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
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

/* 创建关键字注册表 */
/*****************************************************************************
 Func Name    : CLI_ElementListCreat
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 命令关键字列表创建
 Input        : ELEMENT_LIST_REG_S *pstRegister     创建关键字列表的注册信息
 Output       : NONE
 Return       : 成功返回关键字列表的操作句柄,失败返回NULL
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
 Description  : 从关键字列表中根据关键字名获取关键字信息
 Input        : CHAR *pcName     关键字名
 Output       : VOID *pOutArg    输出缓存空间
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
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
 Description  : 从关键字列表中根据关键字NO.获取关键字信息
 Input        : UINT uiNo       关键字NO.
 Output       : VOID *pOutArg    输出缓存空间
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
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

/* 根据条件遍历表结点 */
/*****************************************************************************
 Func Name    : CLI_List_IterateNode
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 根据条件遍历关键字表的每个节点
 Input        : ELEMENT_LIST_HANDLE hMonList       关键字列表操作句柄.
                LIST_VISITOR_PF pfVist             遍历函数指针
                VOID *pArg                         遍历函数入参数指针
 Output       : VOID *pOutArg                      遍历函数出参数指针
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
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
    
    /* 遍历链表 */
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


/*  根据关键字的key获取指定list node */
/*****************************************************************************
 Func Name    : CLI_List_FindNodeByKey
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 根据Key遍历关键字表的每个节点
 Input        : ELEMENT_LIST_HANDLE hMonList       关键字列表操作句柄.
                CONST CHAR *pcKey                  条件Key
 Output       : NONE
 Return       : 成功返回目标节点,否则返回NULL
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

/* 根据关键字的序号获取指定list node，在关键字表中添加关键字时，序号是根据添加的先后顺序编号 */
/*****************************************************************************
 Func Name    : CLI_List_FindNodeByKey
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 根据关键字的序号获取指定list node,在关键字表中添加关键字时,
                序号是根据添加的先后顺序编号
 Input        : ELEMENT_LIST_HANDLE hMonList       关键字列表操作句柄.
                UINT uiNo                          关键字Node顺序
 Output       : NONE
 Return       : 成功返回目标节点,否则返回NULL
 Caution      : 
*****************************************************************************/
STATIC VOID *CLI_List_FindNodeByNo(IN ELEMENT_LIST_HANDLE hMonList, IN UINT uiNo)
{
    VOID *pData = NULL;
    DBGASSERT_WITH_RETURN(0UL != hMonList, NULL);

    (VOID)CLI_List_IterateNode(hMonList, CLI_List_GetNodeByNo, (VOID *)(ULONG)uiNo, &pData);

    return pData;
}


/* 向关键字表中增加新注册的关键字 */
/*****************************************************************************
 Func Name    : CLI_List_AddNode
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 关键字列表添加新的节点
 Input        : ELEMENT_LIST_HANDLE hMonList       关键字列表操作句柄.
                const CHAR *pcKey                  关键字key
                VOID *pParam                       指向节点具体数据结构的指针
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
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

    /* 已经存在 */
    if(NULL != CLI_List_FindNodeByKey(hMonList, pcKey))
    {
        return ERROR_SUCCESS;
    }

    /* 节点分配 */
    pstListNode = (ELEMENT_LIST_NODE_S *)malloc(sizeof(ELEMENT_LIST_NODE_S)+pstMonList->uiNodeLen);
    if(NULL == pstListNode)
    {
        Log_Print(LOG_LEVEL_ERROR,"malloc failed.\n");
        return ERROR_FAILED;
    }
    memset(pstListNode,0,sizeof(ELEMENT_LIST_NODE_S)+pstMonList->uiNodeLen);

    /* 信息设置 */
    pstListNode->pElementData = (VOID *)(pstListNode+1);
    (VOID)strlcpy(pstListNode->szKey, pcKey, sizeof(pstListNode->szKey));
    if((NULL != pstMonList->pfSetNode)&&(ERROR_SUCCESS != pstMonList->pfSetNode(pcKey, pstMonList->uiCount, pstListNode->pElementData, pParam)))
    {
        free(pstListNode);
        Log_Print(LOG_LEVEL_ERROR,"set node failed.\n");
        return ERROR_FAILED;
    }

    /* 在表尾添加新的关键字 */
    DTQ_AddTail(&pstMonList->stLink, &pstListNode->stNode);

    /* 更新此表中注册的关键字个数 */
    pstMonList->uiCount++;

    
    return ERROR_SUCCESS;
}


/* 注册命令关键字时，指定模块初始化 */
/*****************************************************************************
 Func Name    : CLI_List_AddNode
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  :  注册命令关键字时,指定模块初始化
 Input        : CLI_MOUDLE_E enMoudle   模块ID
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
 Description  : buffer 初始化
 Input        : BUF_INFO_S *pstIBuf   保存buffer信息指针
                CHAR *pcBuf          目标buffer
                UINT uiBufLen        buffer size
                UINT uiUsedLen       已使用size
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
 Description  : 获取buffer已使用size
 Input        : BUF_INFO_S *pstIBuf   保存buffer信息指针
 Output       : NONE
 Return       : NONE
 Caution      : 
*****************************************************************************/
UINT CLI_BufGetSize(IN CONST BUF_INFO_S *pstIBuf)
{
    DBGASSERT_WITH_RETURN(pstIBuf != NULL, 0xfffffff);
    return pstIBuf->uiUsedSize;
}

/* 此函数判断该命令关键字所在cli的位置是否是参数，参数类型有整数、字符串和无参数 */
/*****************************************************************************
 Func Name    : CLI_IsValue
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 此函数判断该命令关键字所在cli的位置是否是参数,并与指定类型参数比较
                是否为该类型参数
 Input        : const CHAR *szName   指定参数类型
                const CHAR *pcName   关键字名
                UINT *puiMin         指向参数范围最小值的指针
                UINT *puiMax         指向参数范围最大值的指针
 Output       : NONE
 Return       : BOOL_TRUE            关键字是参数
                BOOL_FALSE           关键字非参数
 Caution      : 当参数类型为INTEGER时,最小值为0
                当参数类型为STRING时,参数范围为字符串长度范围,最小值为1
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
 Description  : 此函数判断该命令关键字所在cli的位置是否是整型参数
 Input        : const CHAR *pcName   关键字名
                UINT *puiMin         指向参数范围最小值的指针
                UINT *puiMax         指向参数范围最大值的指针
 Output       : NONE
 Return       : BOOL_TRUE            关键字是整型参数
                BOOL_FALSE           关键字非整型参数
 Caution      : 当参数类型为INTEGER时,最小值为0
                当参数类型为STRING时,参数范围为字符串长度范围,最小值为1
*****************************************************************************/
STATIC inline BOOL_T CLI_IsInteger(const CHAR *pcName, UINT *puiMin, UINT *puiMax)
{
    return CLI_IsValue("INTEGER", pcName, puiMin, puiMax);
}

/*****************************************************************************
 Func Name    : CLI_IsString
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 此函数判断该命令关键字所在cli的位置是否是字符型参数
 Input        : const CHAR *pcName   关键字名
                UINT *puiMin         指向参数范围最小值的指针
                UINT *puiMax         指向参数范围最大值的指针
 Output       : NONE
 Return       : BOOL_TRUE            关键字是字符型参数
                BOOL_FALSE           关键字非字符型参数
 Caution      : 当参数类型为INTEGER时,最小值为0
                当参数类型为STRING时,参数范围为字符串长度范围,最小值为1
*****************************************************************************/
STATIC inline BOOL_T CLI_IsString(const CHAR *pcName, UINT *puiMin, UINT *puiMax)
{
    return CLI_IsValue("STRING", pcName, puiMin, puiMax);
}

/*****************************************************************************
 Func Name    : CLI_Reg_DefElement
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 注册关键字API函数
 Input        : CONST CHAR *pcName       指向关键字名的指针
                CLI_MOUDLE_E enMoudle    模块id
               UINT uiHelpStrId          关键字解释字符串索引
               ...                       可变参数
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 注册关键字时不直接使用此API函数,应该使用宏CLI_DEF_ELEMENT来
                完成关键字注册;可变参数最多能接受3个,多余3个将不再接收；
                1个变参:MOR
                2个变参:MOR + value
                3个变参:暂未使用
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

    /* 变参处理 */
    VA_START( varArg, uiHelpStrId );
    while(CLI_PARA_END != (uiVarParaVal = VA_ARG(varArg,UINT)))
    {
        auiVarPara[i++] = uiVarParaVal;
        /* 可变参数最多只有3个，超过3个将不接受多余参数 */
        if(MAX_VAR_PARAM == i)
        {
            break;
        }
    }
    VA_END(varArg);

    /* 当有变参时第一个可变参数在传入时必须是MOR，
       故这里可以用auiVarPara[0]是否为0来判断是否有变参 */
       
    /* 无变参传入 */
    if(0 == i)
    {
        stElement.uiValFlag = ELEMENT_NOT_VALUED;
    }
    /* 有变参传入 */
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
    
    /* 判断关键字类型 */
    if(CLI_IsInteger(pcName, &stElement.uiMin, &stElement.uiMax))
    {
        stElement.uiFlag = ELEMENT_INT;
    }
    else if(CLI_IsString(pcName, &stElement.uiMin, &stElement.uiMax))/* min不能为０ */
    {
        stElement.uiFlag = ELEMENT_STR;
    }
    else
    {
        stElement.uiFlag = ELEMENT_NONE;
    }
    /* 关键字列表中添加该关键字 */
    ulRetVal = CLI_List_AddNode(pstMoudle->hCurList, (const CHAR *)szName, (VOID *)&stElement);
    YNTEST_CHK_FAILED(ulRetVal,"add word to key word list failed. word = %s\n",pcName);

    /* 将该关键字添加到g_acCompletionGroup对应的组中 */
    ulRetVal = CLI_AddCompletionWord(g_acCompletionGroup, pcName);
    YNTEST_CHK_FAILED(ulRetVal,"add word to completion group failed. word = %s\n",pcName);

    return ERROR_SUCCESS;
}

/*****************************************************************************
 Func Name    : CLI_FilterWord
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 判断关键字是否需要过滤
 Input        : const CHAR *pcName   关键字名
 Output       : NONE
 Return       : BOOL_TRUE: 过滤
                BOOL_FALSE: 不过滤
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
 Description  : 将注册的关键字添加到单词补全列表
 Input        : CONST CHAR **ppList       单词补全列表指针
                CONST CHAR *pcName        指向待添加的关键字的指针
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
STATIC ULONG CLI_AddCompletionWord(INOUT CONST CHAR **ppList, IN CONST CHAR *pcName)
{
    ULONG ulRetVal = ERROR_SUCCESS;
    UINT i = 0;
    CHAR *pcTemp = NULL;

    DBGASSERT(NULL != ppList);
    DBGASSERT(NULL != pcName);

    /* 过滤INTEGER  /STRING 和已添加的关键字*/
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


/* Cli 命令格式定义 */
/*****************************************************************************
 Func Name    : CLI_Reg_DefCli
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : CLI 命令格式定义API
 Input        : CLI_MOUDLE_E enMoudle       模块ID
                CONST CHAR *pcClue          命令格式
                UINT uiCmd                  与命令格式绑定的id
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 在定义命令格式时不应用此API,应用宏CLI_DEF_CMD
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
    
    /* 命令行至少应有一个关键字，关键字前后有一个'空格' */
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
 Description  : 命令线索树中根据关键字名查找子树节点
 Input        : DTQ_HEAD_S *pstChildList    子树头节点指针
                CHAR *pcName                关键字名
 Output       : UINT *uiErrCode             错误代码
 Return       : 查找成功则返回该节点, 否则返回NULL
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


/* 根据名字查找命令线索树中的结点 */
/*****************************************************************************
 Func Name    : CLI_Tree_FindSameName
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 命令线索树中根据关键字名查找子树节点
 Input        : DTQ_HEAD_S *pstChildList    子树根节点指针
                CHAR *pcName                关键字名
 Output       : UINT *uiErrCode             错误代码
 Return       : 查找成功则返回该节点, 否则返回NULL
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
            break;/* 找到 */
        }

        if(NULL == pstLast->pstNext)
        {
            break;
        }

        pstLast = pstLast->pstNext;
    }while(1);

    return pstTmpTree;
}

/* 从输入命令行中每次解析一个关键字或参数 */
/*****************************************************************************
 Func Name    : CLI_SubCliParse
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 从输入命令行中每次解析一个关键字或参数
 Input        : CONST CHAR *pcInBuf    入buffer
                UINT uiSize            出Buffer size
 Output       : UINT *uiErrCode        错误代码
                CHAR *pcString         出Buffer
 Return       : 本次解析的长度
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
    /* 跳过输入命令行开始的空白 */
    while(YNTEST_WHITESPACE(pcInBuf[uiParsedLen]))
    {
        uiParsedLen++;
    }
    
    /* 记录关键字开始位置 */
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

/* 输入解析 */
/*****************************************************************************
 Func Name    : CLI_CliParse
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : CLI 输入解析API
 Input        : CONST CHAR *pcInput             入Buffer
                CONST CHAR * CONST *ppcArg      
                VOID *pData                     指向配置参数的指针
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
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

        /* 已经解析到命令格式的最后一个关键字，若后续还有多余则不进行解析 */
        if(pstTree->bLeaf && (pstTree->stChild.stHead.pstNext == &pstTree->stChild.stHead))
        {
            pstBash->enErrType = CLI_ERROR_OVERSIZE;
            pstBash->uiParsedLen = i-uiSubLen;
            pstBash->pstErrorNode = pstTree;
            return ERROR_FAILED;
        }
        pstTmpTree = CLI_Tree_FindSameName(pstTree, (CHAR *)acArgName, &uiErrCode);

        /* 解析命令行时，输入格式不正确，记录下此时的位置结点，并退出解析 */
        if(NULL == pstTmpTree)
        {
            /* 解析的关键字是参数 */
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

    /* 输入的命令格式不完整，记录下最后输入的结点 */
    if(!pstTree->bLeaf)
    {
        pstBash->pstErrorNode = pstTree;
        pstBash->enErrType = CLI_ERROR_INCMPLETE;
        pstBash->uiParsedLen = i;
        return ERROR_FAILED;
    }
    /* 输入命令行格式正确，记录下此命令行对应的uiCmd */
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
 Description  : 输入解析结果检查
 Input        : UINT uiSize             出Buffer size
                VOID *pData             指向配置参数的指针
 Output       : CHAR *pcBuf             出Buffer
 Return       : 0: 解析无误
                非0: 解析结果有错
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
 Description  : 打印错误信息API
 Input        : CLI_PRASE_ERROR_E enErrType     错误类型
                BUF_INFO_S *pstBuf              存放错误信息的地址
                VOID *pData                     指向配置参数的指针
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
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

/* 缓存区填充' ' */
/*****************************************************************************
 Func Name    : CLI_FillBufWithSpace
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : Buffer中填充指定长度的' '字符
 Input        : CHAR *pcInBuf     入Buffer
                UINT uiSize       将要填充的长度
 Output       : NONE
 Return       : 填充的长度
 Caution      : 
*****************************************************************************/
UINT CLI_FillBufWithSpace(IN CHAR *pcInBuf, IN UINT uiSize)
{
    UINT uiLen;

    DBGASSERT_WITH_RETURN(NULL != pcInBuf, 0);

    /* 内部保护防止指针越界 */
    uiLen = (uiSize <= 255) ? uiSize : 255;
    memset(pcInBuf, ' ', uiLen);
    pcInBuf[uiLen] = '\0';
    return strlen(pcInBuf);
}

/*****************************************************************************
 Func Name    : CLI_AllocateInit
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 保存内存信息的数据结构初始化
 Input        : MEM_INFO_S *pstMem     指向保存内存信息数据结构的指针
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

/* 命令行参数处理函数 */
/*****************************************************************************
 Func Name    : CLI_CliParamsProc
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 保存内存信息的数据结构初始化
 Input        : CLI_MODULE_S *pstMoudle     模块配置
                UINT uiOutBufSize           出 Buffer size
 Output       : BYTE *pOutBuf               出Buffer
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
    /* 参数buf初始化 */
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

/* 获取配置 */
/*****************************************************************************
 Func Name    : CLI_GetFeatureKey
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 获取参数配置
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
        /* 所有参数已经遍历完 */
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
 Description  : 获取参数配置
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
 Description  : 获取参数配置个数
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
 Description  : 解析用户期望解析的参数
 Input        : VOID *pCfg      模块配置
                UINT uiNum      参数个数
 Output       : CLI_PARAM_PRASE_S *pstParam     解析出的参数缓存区
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
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
                    /* 该参数是本次将要解析的参数,解析完成退出本次循环 */
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
 Description  : 解析用户指定的参数
 Input        : VOID *pParaInfo      参数信息
                UINT uiBufLen        参数输出缓存buffer长度
                PRASE_PARAM_TYPE_S stInfo 带解析的参数类型信息
 Output       : VOID *pData          解析出的参数缓存区
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
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
        /* 此处判断出参数类型是ELEMENT_NONE可直接确定关键字携带参数信息 */
        /* 根据传入的Buff长度判断参数的类型,此处直接转换为指定的类型,后续可不再转换 */
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
            /* 携带参数类型默认为UINT型 */
            else
            {
                *(UINT *)pData = uiVal;
            }
            break;

         case ELEMENT_INT:
         /* 要解析的参数类型为INT型的处理 */
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
            /* 携带参数类型默认为UINT型 */
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
 Description  : 模块CallBack函数注册
 Input        : UINT uiKey          模块id
                CLI_CIOCTL_PF *ppMoudleCallBack 回调API地址
                CONST CHAR *pcDes               模块描述
 Output       : 
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
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
 Description  : 模块callback API索引
 Input        : UINT uiKey          模块id
 Output       : CLI_CIOCTL_PF *ppMoudleCallBack 回调API地址
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
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
 Description  : 解析命令ID并执行对应的命令功能函数
 Input        : UINT uiCmd      命令id
                VOID *pData     配置参数
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
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

/* 命令行预处理 */
/*****************************************************************************
 Func Name    : CLI_CliPreProc
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 输入解析预处理API
 Input        : VOID *pInBuf      入Buffer
 Output       : VOID *pInBuf      出Buffer
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
ULONG CLI_CliPreProc(INOUT     VOID *pInBuf)
{
    CHAR *pcLine;
    UINT uiInputLen = 0;
    
    DBGASSERT(NULL != pInBuf);
    
    pcLine = (CHAR *)pInBuf;
    uiInputLen = strlen(pcLine);
    /* 处理输入行末的空格字符 */
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
 Description  : 输入解析API函数
 Input        : VOID *pCfg      模块配置
                CONST CHAR *pcInBuf      入Buffer
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
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

