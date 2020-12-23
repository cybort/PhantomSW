/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                             utils.h
   Project Code: Test App
   Module Name : Pubic utils
   Date Created: 2020-08-02
   Author      : p21074
   Description : 公共功能函数实现头文件

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/


#ifndef __CLI_UTILS_H__
#define __CLI_UTILS_H__

#ifdef  __cplusplus
extern "C" {
#endif

size_t strlcpy(char *strSrc, const char *strDst, size_t uiSize);
int scnprintf(char * buf, size_t size, const char *fmt, ...);
INT CLI_Strcmp(IN CONST CHAR *pStr1, IN CONST CHAR *pStr2);
UINT CLI_Str2dec(IN CONST CHAR *pcStr, INOUT UINT *puiNo);
VOID *CLI_Memcpy(VOID *dest, const VOID *src, UINT len);
VOID CLI_ShowMem(BYTE *pStart, UINT uiSize);
VOID AssertHandler(const char *pcExpression,
                            unsigned int uiLine,
                          const char *pcFunction);




#ifdef  __cplusplus
}
#endif

#endif

