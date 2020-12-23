/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              cmds.h
   Project Code: Test App
   Module Name : CLI
   Date Created: 2020-08-02
   Author      : p21074
   Description : header file of cmds.c which include macro and private variable 
                 type definition

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#ifndef __COMMAND_H__
#define __COMMAND_H__

#ifdef  __cplusplus
extern "C" {
#endif

#if 0

typedef enum tagSUB_IF_TYPE
{
    SUB_IF_ETH = 0,
    SUB_IF_ILK,
    SUB_IF_ILK_A,
    SUB_IF_BUTT,
}SUB_IF_TYPE_E;

typedef enum tagIF_TYPE
{
    IF_TYPE_ETH_GE = 0,
    IF_TYPE_ETH_10GE,
    IF_TYPE_ETH_25GE,
    IF_TYPE_ETH_40GE,
    IF_TYPE_ETH_50GEGAUI1,
    IF_TYPE_ETH_50GEGAUI2,
    IF_TYPE_ETH_100GECAUI2,
    IF_TYPE_ETH_100GECAUI4,
    IF_TYPE_ETH_100GECAUI10,
    IF_TYPE_ETH_200GE,
    IF_TYPE_ETH_400GE,
    IF_TYPE_ETH_BUTT,
    
    IF_TYPE_ILKN = IF_TYPE_ETH_BUTT,
    IF_TYPE_ILKN_LA,
    
    IF_TYPE_BUTT
}IF_TYPE_E;

typedef struct tagIF_SUB_VIEW
{
    UINT uiSubType;
    CHAR szInfo[64];
}IF_SUB_VIEW_S;

typedef struct tagETH_TYPE_INFO
{
    UINT uiCode;
    CHAR szName[16];
}ETH_TYPE_INFO_S;

typedef struct tagIF_TYPE_INFO
{
    IF_TYPE_E enType;
    UINT uiChip;
    UINT uiSide;
    UINT uiEngine;
    UINT uiIFNum;
}IF_TYPE_INFO_S;



#define GETNAME_BYCODE_IFTYPE(_code) \
    CLI_GetSubIFName((_code), g_astEthTypeInfo)



ULONG CLI_SystemView(IN VOID *pData);
ULONG CLI_ChangeView2IF(IN CONST VOID *pINTBuf, IN CONST VOID *pSTRBuf);
ULONG CLI_ChangeView2SubIF(IN VOID *pData);
ULONG CLI_Exit2LastView(IN      VOID *pData);
ULONG CLI_ChangeView2TM(IN VOID *pData);
ULONG CLI_AGT_CreatAgt(VOID *pData);
#endif

#ifdef  __cplusplus
}
#endif

#endif

