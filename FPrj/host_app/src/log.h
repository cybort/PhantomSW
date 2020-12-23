/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              cli_log.h
   Project Code: Test App
   Module Name : LOG
   Date Created: 2020-08-02
   Author      : p21074
   Description : Log 实现头文件

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/


#ifndef __CLI_LOG_H__
#define __CLI_LOG_H__

#ifdef  __cplusplus
extern "C" {
#endif

#define LOG_STDOUT          (0)
#define LOG_FILE            (1)
#define LOG_STERR           (2)

#define LOG_LEVEL_NONE      0x00000000U
#define LOG_LEVEL_INFO      0x00000001U
#define LOG_LEVEL_WARNING   0x00000010U
#define LOG_LEVEL_TRACE     0x00000100U
#define LOG_LEVEL_DEBUG     0x00001000U
#define LOG_LEVEL_ERROR     0x00010000U
#define LOG_LEVEL_MAX_NUM   5
#define LOG_MASK_BITS       3

#define Log_Print \
            Log_SaveSource(__FILE__,__func__,__LINE__);CLI_LogPrintf

ULONG CLI_SetLogPath(IN CONST CHAR *pcPath);
ULONG CLI_SetLogFileNameAuto(VOID);
ULONG CLI_SetLog(IN CONST CHAR *pcLogPath, IN CONST CHAR *pcLogName, UINT uiLevel, UINT uiMode);
VOID Log_SaveSource(IN CONST CHAR *pcFile, IN CONST CHAR *pFunc, UINT uiLine);
UINT CLI_LogPrintf(IN UINT uiLevel, IN CONST CHAR *pcFormat,...);


#ifdef  __cplusplus
}
#endif

#endif

