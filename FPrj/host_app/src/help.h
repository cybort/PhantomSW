/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              help.h
   Project Code: Test App
   Module Name : CLI
   Date Created: 2020-08-02
   Author      : p21074
   Description : header file of help.c which include macro and private variable 
                 type definition

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#ifndef __STRING_H__
#define __STRING_H__

#ifdef  __cplusplus
extern "C" {
#endif

#define STR_BASE    (0x1F000000U)
    /* ∂®“Âstring ID */
#define STR_DEF(a,b) ((STR_BASE + (((a) & 0xFF) << 16)) | ((b) & 0xFFFF))

typedef struct tagSTR_INFO
{
    UINT uiMoudle;
    CHAR **ppcStrGroup;
    BOOL_T bUsed;
    UINT uiSize;
}STR_INFO_S;

typedef enum tagPUBLIC_STRING_ID
{
    PUBLIC_IDS_BEGIN = STR_DEF(CLI_MOUDLE_PUBLIC, 0x0),
    PUBLIC_IDS_DIS,
    PUBLIC_IDS_SET,
    PUBLIC_IDS_MOD,
    PUBLIC_IDS_CONFIG,
    PUBLIC_IDS_VALUE_VAL,
    PUBLIC_IDS_ADDR_VAL,
    PUBLIC_IDS_VALUE,
    PUBLIC_IDS_ADDR,

    PUBLIC_IDS_BUTT,
}PUBLIC_STRING_ID_E;



VOID *CLI_GetHelpString(UINT uiStrId);
ULONG CLI_LoadAllMoudleStr(VOID);

#ifdef  __cplusplus
}
#endif

#endif

