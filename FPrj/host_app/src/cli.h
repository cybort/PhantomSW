/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              cli.h
   Project Code: Test App
   Module Name : CLI
   Date Created: 2020-08-02
   Author      : p21074
   Description : header file of cli.c which include macro and private variable 
                 type definition

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#ifndef __CLI_CLI_H__
#define __CLI_CLI_H__

#ifdef  __cplusplus
extern "C" {
#endif

#include "list.h"
#include "global.h"



/* �ؼ��ֲ������Ͷ��� */
#define ELEMENT_NONE    (0)       /* �ǲ��� */
#define ELEMENT_INT     (1)       /* INTEGER ���Ͳ��� */
#define ELEMENT_STR     (2)       /* STRING ���Ͳ��� */

/* ���տɱ����ʱ�Ľ�����־ */
#define CLI_PARA_END    (0xFFAAFFAAU)

/* �ؼ��ֱ����Ƿ�Ϊ������־���� */
#define ELEMENT_VALUED  (0xF0000000U)       /* �ؼ��ֱ����ǲ�����־ */
#define ELEMENT_NOT_VALUED  (0xF1111111U)   /* �ؼ��ֱ����ǲ�����־ */

#define MAX_COMPLETION_NUM  (1024)  /* ��ȫ�ֵ���������� */

#define MAX_VAR_PARAM       (3) /* CLI ע��ɽ��ܵ����ɱ������ */


/* ������ע�Ὺʼ����ָ������ģ�� */
#define CLI_BEGIN(__enMoudle)\
    ULONG ulRet = ERROR_SUCCESS; \
    CLI_MOUDLE_E enMoudle = (__enMoudle); \
    CLI_MOUDLE_INIT(enMoudle)

#define CLI_END return ulRet

/* ����ؼ���ע��ʱӦ�ô˺궨��,��һ�����������ڴ�����ֻ����ʾ���� */
#define CLI_DEF_ELEMENT(szDec, szElementName,uiHelpStrId,arg...) \
    ((ulRet) += CLI_Reg_DefElement(szElementName, enMoudle, uiHelpStrId, ##arg,CLI_PARA_END))

/* �����ʽע��ʱӦ�ô˺궨�� */
#define CLI_DEF_CMD(__szFormat, __uiCmd) \
    ((ulRet) +=CLI_Reg_DefCli(enMoudle, (__szFormat), (__uiCmd)))

#define bufsprintf(__pstBuf, __args...) \
        (((__pstBuf)->uiUsedSize) += (UINT)scnprintf(((__pstBuf)->pcBuf) + ((__pstBuf)->uiUsedSize), ((size_t)((__pstBuf)->uiMaxSize) - (size_t)((__pstBuf)->uiUsedSize)), ## __args))


#define test_Malloc(__pstMem, __uiSize, __Type) \
    { \
        (__pstMem)->pMem = (__Type *)malloc(__uiSize); \
        if(NULL == (__pstMem)->pMem) \
        { \
            (__pstMem)->bRet = BOOL_FALSE;\
        } \
        else \
        { \
            (__pstMem)->bRet = BOOL_TRUE; \
            (__pstMem)->uiAllocatedSize += (__uiSize); \
        } \
    }

#define test_Realloc(__pstMem, __uiSize, __Type) \
    (__pstMem)->pMem = (__Type *)realloc((__pstMem)->pMem, (__pstMem)->uiAllocatedSize + __uiSize); \
    if(NULL == (__pstMem)->pMem) \
    { \
        (__pstMem)->bRet = BOOL_FALSE;\
    } \
    else \
    { \
        (__pstMem)->bRet = BOOL_TRUE; \
        (__pstMem)->uiAllocatedSize += (__uiSize); \
    }


typedef ULONG ELEMENT_LIST_HANDLE;

typedef INT (*ELEMENT_LIST_CMP_NODE)(IN const CHAR *pcName, IN UINT uiNo, IN VOID *pNode1, IN VOID *pNode2);/* pNode1�Ƿ����pNode2 */
typedef ULONG (*ELEMENT_LIST_SET_NODE)(IN const CHAR *pcName, IN UINT uiNo, IN VOID *pNode, IN VOID *pParam);
typedef ULONG (*ELEMENT_LIST_VISITOR_PF)(IN CHAR *pcName, IN UINT uiNo, IN VOID *pNodeData, IN VOID *pInArg, OUT VOID *pOutArg);
typedef ULONG (*LIST_VISITOR_PF)(IN CHAR *pcName, IN UINT uiNo, IN VOID *pNodeData, IN VOID *pInArg, OUT VOID *pOutArg);
typedef ULONG (*ELEMENT_CHECK_PF)(IN CONST CHAR *pcName);
typedef ULONG (* CLI_CIOCTL_PF)(IN VOID *pData);
typedef ULONG (* CLI_MOUDLE_CIOCTL_PF)(IN UINT uiKey, IN VOID *pData);

typedef struct tagMOUDLE_CIOCTL_CB
{
    UINT uiKey;
    CLI_MOUDLE_CIOCTL_PF pfMoudlCallBack;
}MOUDLE_CIOCTL_CB_S;

/* ģ���ڲ�callback�����ṹ */
typedef struct tagCLI_CIOCTL_CB
{
    UINT uiKey;                 /* ģ������ID,��ģ���Լ����� */
    CLI_CIOCTL_PF pfCallBack;   /* callback API��� */
}CLI_CIOCTL_CB_S;

typedef struct tagELEMENT_LIST_REG
{
    UINT uiNodeLen;
    ELEMENT_LIST_CMP_NODE pfCmpNode;
    ELEMENT_LIST_SET_NODE pfSetNode;
}ELEMENT_LIST_REG_S;

typedef enum tagCLI_PRASE_ERROR
{
    CLI_ERROR_NONE = 0,
    CLI_ERROR_INCMPLETE,
    CLI_ERROR_UNDEFINED,
    CLI_ERROR_INTEGER,
    CLI_ERROR_STRING,
    CLI_ERROR_NULL,
    CLI_ERROR_OVERFLOW,
    CLI_ERROR_OVERSIZE,
    CLI_ERROR_BUTT,
}CLI_PRASE_ERROR_E;

/* ע��Ĺؼ������ݽṹ���� */
typedef struct tagTEST_ELEMENT
{
    CONST CHAR *pcName;     /* �ؼ����� */
    UINT        uiValFlag;  /* �ؼ����Ƿ񱻸�ֵ��־ */
    UINT        uiMor;      /* ��Ҫ������Mor,������ΪĬ��ֵ */
    UINT        uiIds;      /* �ؼ�����ʾ�ַ�ID */
    UINT        uiVal;      /* �ؼ��ֱ���Я����ֵ */
    UINT        uiMin;      /* �ؼ���ΪINTEGERʱ����Сֵ(��STRINGʱ����С����,��С���Ȳ��ܵ���1) */
    UINT        uiMax;      /* �ؼ���ΪINTEGERʱ�����ֵ(��STRINGʱ����󳤶�) */
    UINT        uiFlag;   /* �ؼ������ͱ�־��integer/string/�� */
    ELEMENT_CHECK_PF pfCheck;
}TEST_ELEMENT_S;

/* �����������ڵ����ݽṹ���� */
typedef struct tagTEST_TREE_NODE
{
    DTQ_NODE_S stBrother;   /* brother�ڵ������� */
    DTQ_HEAD_S stChild;     /* child�ڵ������� */
    TEST_ELEMENT_S *pstElement; /* ָ��ýڵ��ŵĹؼ��� */
    struct tagTEST_TREE_NODE *pstNext;  /* ָ��ͬ���Ľڵ� */
    UINT uiCmd;
    CHAR szStr[64];
    BOOL_T bLeaf;  /* ָʾ�ýڵ��Ƿ�ΪҶ�ӽڵ� */
}TEST_TREE_NODE_S;


/* ģ�����ݽṹ���� */
typedef struct tagCLI_MODULE
{
    UINT  uiMId;
    ELEMENT_LIST_HANDLE hElementList[MAX_SUB_MOUDLE];  /* ע���ڸ�ģ���µ�����ؼ��ֱ���ͬ�ı��п�������ͬ�Ĺؼ��� */
    ELEMENT_LIST_HANDLE hCurList;
    TEST_TREE_NODE_S stTree;  /* ��ģ��ҽӵ�������������ע���ڸ�ģ���µ����� */
    TEST_TREE_NODE_S *pstErrorNode;
    VOID *apstCurCli[32];
    VOID *apstCurTree[32];
    UINT uiCurCliNum;
    UINT uiNo;
    UINT uiCmd;
    UINT uiParsedLen;
    CLI_PRASE_ERROR_E enErrType;
}CLI_MODULE_S;

typedef struct tagMOUDLE_INFO
{
    CLI_MODULE_S *pstMoudle[CLI_MOUDLE_BUTT];
}MOUDLE_INFO_S;

/* ����ؼ��ֱ����ݽṹ���� */
typedef struct tagELEMENT_LIST
{
    DTQ_HEAD_S stLink;
    DTQ_HEAD_S stDelLink;
    UINT uiCount;
    UINT uiNodeLen;
    BOOL_T bDel;
    ELEMENT_LIST_CMP_NODE pfCmpNode;
    ELEMENT_LIST_SET_NODE pfSetNode;
}ELEMENT_LIST_S;

/* ����ؼ��ֱ��йؼ��ֽڵ����ݽṹ���� */
typedef struct tagELEMENT_LIST_NODE
{
    DTQ_NODE_S stNode;
    CHAR szKey[32];
    VOID *pElementData;
}ELEMENT_LIST_NODE_S;

/* buffer ���ݽṹ���� */
typedef struct tagBUF_INFO
{
    CHAR *pcBuf;        /* ָ��Ŀ�껺���� */
    UINT uiMaxSize;     /* Ŀ�껺������󳤶� */
    UINT uiUsedSize;    /* ��ʹ�ó��� */
}BUF_INFO_S;

typedef struct tagMEM_INFO
{
    BYTE *pMem;
    UINT uiAllocatedSize;  /* �ѷ�����ڴ��С */
    UINT uiUsedSize;    /* ��ʹ�õķ����ڴ� */
    BOOL_T bRet;
} MEM_INFO_S;

/* ��������ʱʹ�ô˽ṹ */
typedef struct tagCLI_PARAM_PRASE
{
    UINT        uiKey;      /* ����key */
    VOID        *pData;     /* ��Ž������Ĳ��������� */
    UINT        uiBufLen;   /* ������size */
}CLI_PARAM_PRASE_S;

typedef struct tagPRASE_PARAM_TYPE
{
    BOOL_T bIsVal;
    UINT uiVal;
    UINT uiType;
}PRASE_PARAM_TYPE_S;

typedef enum tagAGT_OPT
{
    AGT_OPT_DISABLE = 0,
    AGT_OPT_ENABLE,
    AGT_OPT_BUTT,
}AGT_OPT_E;



CODE_SECTION("============")
CODE_SECTION("�ⲿ��������")
CODE_SECTION("============")

ULONG CLI_PRASE_ParamPrase(IN VOID *pCfg, INOUT CLI_PARAM_PRASE_S *pstParam, IN UINT uiNum);
ULONG CLI_RegCallBack(IN UINT uiKey, IN CLI_MOUDLE_CIOCTL_PF pfFunc);
ULONG CLI_CliProc( IN CONST CHAR *pcInBuf, IN VOID *pCfg);
ULONG CLI_CliPreProc(INOUT     VOID *pInBuf);
TEST_TREE_NODE_S *CLI_Tree_FindSameName(TEST_TREE_NODE_S *pstTree, CHAR *pcName, UINT *uiErrCode);
UINT CLI_SubCliParse(IN CONST CHAR *pcInBuf, OUT CHAR *pcString, IN UINT uiSize, OUT UINT *uiErrCode);
VOID *CLI_CliParamsProc(CLI_MODULE_S *pstMoudle, BYTE *pOutBuf, UINT uiOutBufSize);
VOID CLI_AllocateInit(MEM_INFO_S *pstMem);
UINT CLI_CheckPraseRes(INOUT CHAR *pcBuf, UINT uiSize, VOID *Data);
UINT CLI_FillBufWithSpace(IN CHAR *pcInBuf, IN UINT uiSize);
ULONG CLI_CliParse(IN CONST     CHAR *pcInput, const char * const *arg_value, void *data);
ULONG CLI_Reg_DefCli(IN CLI_MOUDLE_E enMoudle, IN const CHAR *pcClue, IN UINT uiCmd);
UINT CLI_BufGetSize(IN CONST BUF_INFO_S *pstIBuf);
ULONG CLI_Reg_DefElement(IN const CHAR *pcName, IN CLI_MOUDLE_E enMoudle, IN UINT uiHelpStrId, ...);
VOID CLI_BufInit(IN BUF_INFO_S *pstIBuf, IN CHAR *pcBuf, IN UINT uiBufLen, IN UINT uiUsedLen);
VOID CLI_MOUDLE_INIT(CLI_MOUDLE_E enMoudle);
CLI_MODULE_S *CLI_GetMoudleInfo(CLI_MOUDLE_E enMoudle);
ULONG CLI_MoudleInfoInit(VOID);


#pragma pack(4)
typedef struct tagTEST_STRUCT
{
    UINT uiParam1;
    UINT uiParam2;
    UINT uiParam3;
    UINT uiParam4;
    CHAR uiParam5[32];
}TEST_STRUCT_S;

typedef struct tagAGT_PARAM
{
    UINT uiOpt;
}AGT_PARAM_S;



#ifdef  __cplusplus
}
#endif

#endif

