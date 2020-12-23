/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              complete.h
   Project Code: Test App
   Module Name : CLI
   Date Created: 2020-08-02
   Author      : p21074
   Description : header file of complete.c which include macro and private variable 
                 type definition

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#ifndef __CLI_COMPLETE_H__
#define __CLI_COMPLETE_H__

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct tagFIND_NODE
{
    TEST_TREE_NODE_S *pstTreeNode;
    DTQ_NODE_S *pstClidNode;
    DTQ_HEAD_S *pstClidList;
}FIND_NODE_S;

typedef struct tagCOMPLETE_SAVE
{
    ELEMENT_LIST_HANDLE hCurrentList;
    DTQ_NODE_S *pstCurrentNode;
    DTQ_NODE_S *pstListHead;
    UINT uiNum;
    BOOL_T bIs1st;
}COMPLETE_SAVE_S;

VOID test_initialize_readline (VOID);
CHAR **test_command_completion(const char *pcText, int iStart, int iEnd);
CHAR *test_command_generator(const CHAR *pcText, INT iState);
CHAR *DupPointer(CONST CHAR *pcPtr);



#ifdef  __cplusplus
}
#endif

#endif

