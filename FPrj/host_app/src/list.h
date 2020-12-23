/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              cli_list.h
   Project Code: Test App
   Module Name : Data struct
   Date Created: 2020-08-02
   Author      : p21074
   Description : 数据结构--链表实现头文件

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#ifndef __CLI_LIST_H__
#define __CLI_LIST_H__

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct tagDTQ_NODE
{
    struct tagDTQ_NODE* pstPrev; /* the previous element */
    struct tagDTQ_NODE* pstNext; /* the next element */
} DTQ_NODE_S;
#define DTQ_ENTRY(ptr, type, member)    (container_of(ptr, type, member))

typedef struct tagDTQ_HEAD
{
    DTQ_NODE_S stHead;   /* stHead.pstNext is the head of list
                            stHead.pstPrev is the tail of list */
} DTQ_HEAD_S;

static inline VOID DTQ_Init(IN DTQ_HEAD_S* pstList);
static inline VOID DTQ_NodeInit(IN DTQ_NODE_S* pstNode);
static inline BOOL_T DTQ_IsEmpty(IN const DTQ_HEAD_S* pstList);
static inline DTQ_NODE_S* DTQ_First(IN const DTQ_HEAD_S* pstList);
static inline DTQ_NODE_S* DTQ_Last(IN const DTQ_HEAD_S* pstList);
static inline BOOL_T DTQ_IsEndOfQ(IN const DTQ_HEAD_S* pstList, IN const DTQ_NODE_S* pstNode);
static inline DTQ_NODE_S* DTQ_Prev(IN const DTQ_NODE_S* pstNode);
static inline DTQ_NODE_S* DTQ_Next(IN const DTQ_NODE_S* pstNode);
static inline VOID DTQ_AddAfter(IN DTQ_NODE_S* pstPrev, IN DTQ_NODE_S* pstInst);
static inline VOID DTQ_AddBefore(IN DTQ_NODE_S* pstNext, IN DTQ_NODE_S* pstInst);
static inline VOID DTQ_Del(IN const DTQ_NODE_S* pstNode);
static inline VOID DTQ_AddHead(IN DTQ_HEAD_S* pstList, IN DTQ_NODE_S* pstNode);
static inline DTQ_NODE_S* DTQ_DelHead(IN const DTQ_HEAD_S* pstList);
static inline VOID DTQ_AddTail(IN DTQ_HEAD_S* pstList, IN DTQ_NODE_S* pstNode);
static inline DTQ_NODE_S* DTQ_DelTail(IN const DTQ_HEAD_S* pstList);
static inline VOID DTQ_Append(IN DTQ_HEAD_S* pstDstList, IN DTQ_HEAD_S* pstSrcList);
static inline VOID DTQ_FreeAll(IN DTQ_HEAD_S *pstList, IN VOID (*pfFree)(VOID *));

/*****************************************************************************
 Func Name   : DTQ_Init
 Description : Initial a doubly-linked tail queue head
 Input       : STQ_HEAD_S* pstList  the doubly-linked tail queue head
 Output      : No output
 Return      : No return
 Caution     :
*****************************************************************************/
static inline VOID DTQ_Init(IN DTQ_HEAD_S* pstList)
{
    pstList->stHead.pstNext = &pstList->stHead;
    pstList->stHead.pstPrev = &pstList->stHead;
    return;
}

/*****************************************************************************
 Func Name   : DTQ_NodeInit
 Description : Initialize a doubly-linked tail queue node
 Input       : IN DTQ_NODE_S* pstList  the pointer to the queue head
 Output      : No output
 Return      : No return
 Caution     :
*****************************************************************************/
static inline VOID DTQ_NodeInit(IN DTQ_NODE_S* pstNode)
{
    pstNode->pstNext = (DTQ_NODE_S*)NULL;
    pstNode->pstPrev = (DTQ_NODE_S*)NULL;
    return;
}

/*****************************************************************************
 Func Name   : DTQ_IsEmpty
 Description : Whether the doubly-linked tail queue is empty
 Input       : STQ_HEAD_S* pstList  the doubly-linked tail queue head
 Output      : No output
 Return      : BOOL_TRUE or BOOL_FLASE
 Caution     :
*****************************************************************************/
static inline BOOL_T DTQ_IsEmpty(IN const DTQ_HEAD_S* pstList)
{
    return (pstList->stHead.pstNext == &pstList->stHead);
}

/*****************************************************************************
 Func Name   : DTQ_First
 Description : Whether the doubly-linked tail queue is empty
 Input       : DTQ_HEAD_S* pstList  the doubly-linked tail queue head
 Output      : No output
 Return      : the pointer to first element of the doubly-linked tail queue
               NULL if the list is empty
 Caution     :
*****************************************************************************/
static inline DTQ_NODE_S* DTQ_First(IN const DTQ_HEAD_S* pstList)
{   
    DTQ_NODE_S* pstNode = pstList->stHead.pstNext;
    if(pstNode == &(pstList->stHead))
    {
       return (DTQ_NODE_S*) NULL;
    }
    return pstNode;
}

/*****************************************************************************
 Func Name   : DTQ_Last
 Description : Get the last element of a doubly-linked tail queue
 Input       : DTQ_HEAD_S* pstList  the doubly-linked tail queue head
 Output      : No output
 Return      : the pointer to last element of the doubly-linked tail queue
               NULL if the list is empty
 Caution     :
*****************************************************************************/
static inline DTQ_NODE_S* DTQ_Last(IN const DTQ_HEAD_S* pstList)
{
    DTQ_NODE_S* pstNode = pstList->stHead.pstPrev;
    if(pstNode == &pstList->stHead)
    {
        return (DTQ_NODE_S *) NULL;
    }
    return pstNode;
}

/*****************************************************************************
 Func Name   : DTQ_IsEndOfQ
 Description : Wether the node is the end of the queue
 Input       : DTQ_HEAD_S* pstList  the doubly-linked tail queue head
               DTQ_NODE_S* pstNode  the pointer to the node
 Output      : No output
 Return      : BOOL_TURE if is end of the queue, BOOL_FALSE is not
 Caution     :
*****************************************************************************/
static inline BOOL_T DTQ_IsEndOfQ(IN const DTQ_HEAD_S* pstList, IN const DTQ_NODE_S* pstNode)
{
    if (DTQ_IsEmpty(pstList))
    {
        return BOOL_TRUE;
    }
    if (NULL == pstNode)
    {
        return BOOL_TRUE;
    }
    return (pstNode == &pstList->stHead);
}

/*****************************************************************************
 Func Name   : DTQ_Prev
 Description : Get the previous element of current one
 Input       : DTQ_NODE_S* pstNode  the pointer to current element
 Output      : No output
 Return      : the pointer to previous element of current element
               NULL if the current element is the last one
 Caution     :
*****************************************************************************/
static inline DTQ_NODE_S* DTQ_Prev(IN const DTQ_NODE_S* pstNode)
{
    return (pstNode->pstPrev);
}

/*****************************************************************************
 Func Name   : DTQ_Next
 Description : Get the next element of current one
 Input       : DTQ_NODE_S* pstNode  the pointer to current element
 Output      : No output
 Return      : the pointer to next element of current element
               NULL if the current element is the last one
 Caution     :
*****************************************************************************/
static inline DTQ_NODE_S* DTQ_Next(IN const DTQ_NODE_S* pstNode)
{
    return (pstNode->pstNext);
}

/*****************************************************************************
 Func Name   : DTQ_AddAfter
 Description : Add an element after another one
 Input       : DTQ_NODE_S* pstPrev  pointer to the previous element
               DTQ_NODE_S* pstInst  pointer to the element to be added
 Output      : No output
 Return      : NONE
 Caution     :
*****************************************************************************/
static inline VOID DTQ_AddAfter(IN DTQ_NODE_S* pstPrev, IN DTQ_NODE_S* pstInst)
{
    pstInst->pstPrev = pstPrev;
    pstInst->pstNext = pstPrev->pstNext;
    pstPrev->pstNext = pstInst;
    pstInst->pstNext->pstPrev = pstInst;

    return;
}

/*****************************************************************************
 Func Name   : DTQ_AddBefore
 Description : Add an element before another one
 Input       : DTQ_NODE_S* pstPrev  pointer to the previous element
               DTQ_NODE_S* pstInst  pointer to the element to be added
 Output      : No output
 Return      : NONE
 Caution     :
*****************************************************************************/
static inline VOID DTQ_AddBefore(IN DTQ_NODE_S* pstNext, IN DTQ_NODE_S* pstInst)
{
    pstInst->pstPrev = pstNext->pstPrev;
    pstInst->pstNext = pstNext;
    pstInst->pstPrev->pstNext = pstInst;
    pstInst->pstNext->pstPrev = pstInst;

    return;
}

/*****************************************************************************
 Func Name   : DTQ_Del
 Description : Delete an element from the tail queue
 Input       : DTQ_NODE_S* pstNode  the pointer to the element to be deleted
 Output      : No output
 Return      : NONE
 Caution     :
*****************************************************************************/
static inline VOID DTQ_Del(IN const DTQ_NODE_S* pstNode)
{
    pstNode->pstPrev->pstNext = pstNode->pstNext;
    pstNode->pstNext->pstPrev = pstNode->pstPrev;

    return;
}

/*****************************************************************************
 Func Name   : DTQ_AddHead
 Description : Add an element to the head of the queue
 Input       : DTQ_HEAD_S* pstList  the pointer to the queue head
               DTQ_NODE_S* pstNode  the pointer to the element to be added
 Output      : No output
 Return      : NONE
 Caution     :
*****************************************************************************/
static inline VOID DTQ_AddHead(IN DTQ_HEAD_S* pstList, IN DTQ_NODE_S* pstNode)
{
    DTQ_AddAfter (&pstList->stHead, pstNode);

    return;
}

/*****************************************************************************
 Func Name   : DTQ_AddTail
 Description : Add an element to the tail of the queue
 Input       : DTQ_HEAD_S* pstList  the pointer to the queue head
               DTQ_NODE_S* pstNode  the pointer to the element to be added
 Output      : No output
 Return      : NONE
 Caution     :
*****************************************************************************/
static inline VOID DTQ_AddTail(IN DTQ_HEAD_S* pstList, IN DTQ_NODE_S* pstNode)
{
    DTQ_AddBefore (&pstList->stHead, pstNode);
    return;
}

/*****************************************************************************
 Func Name   : DTQ_DelHead
 Description : Delete the first element from the queue
 Input       : DTQ_HEAD_S* pstList  the pointer to the queue head
               
 Output      : No output
 Return      : the pointer to the deleted element, NULL if no element is deleted
 Caution     : This function only delete the element from the list, and does
               NOT free the memory of the element.
*****************************************************************************/
static inline DTQ_NODE_S* DTQ_DelHead(IN const DTQ_HEAD_S* pstList)
{
    DTQ_NODE_S* pstNode = DTQ_First(pstList);

    if (DTQ_IsEndOfQ(pstList, pstNode))
    {
        pstNode = (DTQ_NODE_S*)NULL;
    }
    else
    {
        DTQ_Del (pstNode);
    }

    return pstNode;
}

/*****************************************************************************
 Func Name   : DTQ_DelTail
 Description : Delete the last element from the queue
 Input       : DTQ_HEAD_S* pstList  the pointer to the queue head
               
 Output      : No output
 Return      : the pointer to the deleted element, NULL if no element is deleted
 Caution     : This function only delete the element from the list, and does
               NOT free the memory of the element.
*****************************************************************************/
static inline DTQ_NODE_S* DTQ_DelTail(IN const DTQ_HEAD_S* pstList)
{
    DTQ_NODE_S* pstNode = DTQ_Last (pstList);

    if (DTQ_IsEndOfQ(pstList, pstNode))
    {
        pstNode = (DTQ_NODE_S*)NULL;
    }
    else
    {
        DTQ_Del (pstNode);
    }

    return pstNode;
}

/* macro for walk the doubly-linked tail queue */
#define DTQ_FOREACH(pstList, pstNode) \
    for ((pstNode) = (pstList)->stHead.pstNext; \
         ((pstNode) != &((pstList)->stHead)); \
         (pstNode) = DTQ_Next(pstNode))

#define DTQ_FOREACH_SAFE(pstList, pstNode, pstNextNode) \
    for ((pstNode) = (pstList)->stHead.pstNext; \
         (((pstNode) != &((pstList)->stHead)) && \
         ({(pstNextNode) = DTQ_Next(pstNode); BOOL_TRUE;})); \
         (pstNode) = (pstNextNode))
         
#define DTQ_FOREACH_REVERSE(pstList, pstNode) \
    for ((pstNode) = DTQ_Last(pstList); \
         (BOOL_TRUE != DTQ_IsEndOfQ(pstList, pstNode)); \
         (pstNode) = DTQ_Prev(pstNode))

#define DTQ_FOREACH_REVERSE_SAFE(pstList, pstNode, pstPrev) \
    for ((pstNode) = DTQ_Last(pstList); \
         (BOOL_TRUE != DTQ_IsEndOfQ(pstList, pstNode)) && \
         ({(pstPrev) = DTQ_Prev(pstNode); BOOL_TRUE;}); \
         (pstNode) = (pstPrev))

#define DTQ_ENTRY_FIRST(pstList, type, member) \
        ({DTQ_NODE_S *pstNode__Tmp__Mx = DTQ_First(pstList); \
         (NULL == pstNode__Tmp__Mx) ? NULL : DTQ_ENTRY(pstNode__Tmp__Mx, type, member);})
#define DTQ_ENTRY_LAST(pstList, type, member) \
        ({DTQ_NODE_S *pstNode__Tmp__Mx = DTQ_Last(pstList); \
         (NULL == pstNode__Tmp__Mx) ? NULL : DTQ_ENTRY(pstNode__Tmp__Mx, type, member);})
#define DTQ_ENTRY_NEXT(pstList, pstEntry, member) \
    (DTQ_IsEndOfQ(pstList, (NULL == (pstEntry) ? NULL : DTQ_Next(&((pstEntry)->member)))) ? \
        NULL : \
        DTQ_ENTRY(DTQ_Next(&((pstEntry)->member)), typeof(*(pstEntry)), member))

#define DTQ_ENTRY_PREV(pstList, pstEntry, member) \
    (DTQ_IsEndOfQ(pstList, (NULL == (pstEntry) ? NULL : DTQ_Prev(&((pstEntry)->member)))) ? \
        NULL : \
        DTQ_ENTRY(DTQ_Prev(&((pstEntry)->member)), typeof(*(pstEntry)), member))

#define DTQ_FOREACH_ENTRY(pstList, pstEntry, member) \
    for ((pstEntry) = DTQ_ENTRY((pstList)->stHead.pstNext, typeof(*(pstEntry)), member); \
         ((&(pstEntry)->member != &(pstList)->stHead) || ({pstEntry = NULL; BOOL_FALSE;})); \
         (pstEntry) = DTQ_ENTRY((pstEntry)->member.pstNext, typeof(*(pstEntry)), member))

#define DTQ_FOREACH_ENTRY_SAFE(pstList, pstEntry, pstNextEntry, member) \
    for ((pstEntry) = DTQ_ENTRY((pstList)->stHead.pstNext, typeof(*(pstEntry)), member); \
         (((&(pstEntry)->member != &(pstList)->stHead) &&\
         ({(pstNextEntry) = DTQ_ENTRY((pstEntry)->member.pstNext, typeof(*(pstEntry)), member); BOOL_TRUE;})) || \
         ({pstEntry = NULL; BOOL_FALSE;})); \
         (pstEntry) = (pstNextEntry))
         
#define DTQ_FOREACH_ENTRY_REVERSE(pstList, pstEntry, member) \
    for ((pstEntry) = DTQ_ENTRY_LAST(pstList, typeof(*(pstEntry)), member); \
         NULL != (pstEntry); \
         (pstEntry) = DTQ_ENTRY_PREV(pstList, pstEntry, member))

#define DTQ_FOREACH_ENTRY_REVERSE_SAFE(pstList, pstEntry, pstPrevEntry, member) \
    for ((pstEntry) = DTQ_ENTRY_LAST(pstList, typeof(*(pstEntry)), member); \
         (NULL != (pstEntry)) && \
         ({(pstPrevEntry) = DTQ_ENTRY_PREV(pstList, pstEntry, member); BOOL_TRUE;}); \
         (pstEntry) = (pstPrevEntry))


/*****************************************************************************
 Func Name   : DTQ_FreeAll
 Description : Remove and free all nodes from DTQ list
 Input       : DTQ_HEAD_S* pstList  the pointer to the queue head
               pfFree  function pointer which point the free function
 Output      : No output
 Return      : NONE
 Caution     : 
*****************************************************************************/
static inline VOID DTQ_FreeAll(IN DTQ_HEAD_S *pstList, IN VOID (*pfFree)(VOID *))
{
    DTQ_NODE_S *pstCurNode;
    DTQ_NODE_S *pstNextNode;

    /* Free all node from list */
    DTQ_FOREACH_SAFE(pstList, pstCurNode, pstNextNode)
    {
        pfFree(pstCurNode);
    }

    DTQ_Init(pstList);
    return;
}



#ifdef  __cplusplus
}
#endif

#endif

