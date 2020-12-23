/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              log.c
   Project Code: Test App
   Module Name : LOG
   Date Created: 2020-08-02
   Author      : p21074
   Description : Log���API�ӿ�

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
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include "prv_basedef.h"
#include "log.h"

CHAR g_acLogPath[128] = {0};
CHAR g_acLogFileName[64] = {0};
CONST CHAR g_acDefaultLogName[] = {"test_app_log"};
UINT g_uiLogOutput;
CHAR g_acLogLinePrefix[128];
UINT g_uiLogHighestLevevl = LOG_LEVEL_ERROR;


/* ����log�ļ�·��,Ĭ��·���ǵ�ǰĿ¼ */
/*****************************************************************************
 Func Name    : test_SetLogPath
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : Set the path of log file
 Input        : CONST CHAR *pcPath      path of log file
 Output       : none
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      :
*****************************************************************************/

ULONG CLI_SetLogPath(IN CONST CHAR *pcPath)
{
    CHAR acTempBuf[128] = {0};
    
    if(NULL == pcPath)
    sprintf( g_acLogPath,"%s/","./");
    else
    {
        if(strlen(pcPath) >= 64)
        {
            printf("log path exceed limit length, maximum is 64\n");
            return ERROR_FAILED;
        }
        sprintf( g_acLogPath,"%s/",pcPath);
        sprintf(acTempBuf, "%s%s%s","find ",pcPath," -type d > /dev/null 2>&1");
        if(0 != system(acTempBuf))
        {
            YNTEST_CLEAR_BUF(acTempBuf, 128);
            sprintf(acTempBuf, "%s%s","mkdir -p ",pcPath);
            system(acTempBuf);
        }
    }
    return ERROR_SUCCESS;
}

/* ����log�ļ����������Զ����� */
/*****************************************************************************
 Func Name    : test_SetLogFileNameAuto
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ����log�ļ����������Զ�����
 Input        : none
 Output       : none
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      :
*****************************************************************************/

ULONG CLI_SetLogFileNameAuto(VOID)
{
    struct tm *pstTime;
    time_t Time;

    (void)time(&Time);
    pstTime = localtime(&Time);
    if(pstTime->tm_year > 99)
    {
        pstTime->tm_year = pstTime->tm_year % 100;
    }
    sprintf(g_acLogFileName, "log_20%02d%02d%02d%02d%02d%02d", \
            pstTime->tm_year,pstTime->tm_mon+1, pstTime->tm_mday,pstTime->tm_hour,pstTime->tm_min,pstTime->tm_sec);
            
    return ERROR_SUCCESS;
}

/* ����log����,·�����ļ����������ʽ */
/*****************************************************************************
 Func Name    : test_SetLog
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ����log����:·�����ļ����������ʽ
 Input        : CONST CHAR *pcLogPath       log�ļ����λ��
                CONST CHAR *pcLogName       log�ļ���
                UINT uiMode                 log�������ʽ
 Output       : none
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      :log �����ʽ:LOG_STDOUT-��׼���, LOG_FILE-������ļ�, 
               LOG_STERR-��׼����,Ĭ�Ϸ�ʽ��LOG_STDOUT;
               ���ڶ�����������ΪNULL,���Զ��������������ļ���
*****************************************************************************/

ULONG CLI_SetLog(IN CONST CHAR *pcLogPath, IN CONST CHAR *pcLogName, UINT uiLevel, UINT uiMode)
{
    ULONG ulRetVal = ERROR_SUCCESS;
    
    if(uiMode > 3)
    {
        printf("invalid log out mode.\n");
        return ERROR_FAILED;
    }
    if(uiLevel > LOG_LEVEL_ERROR)
    {
        printf("invalid log level.\n");
        return ERROR_FAILED;
    }

    ulRetVal = CLI_SetLogPath(pcLogPath);
    YNTEST_CHK_FAILED(ulRetVal, "Set log path fail.\n");
    if(NULL == pcLogName)
    {
        ulRetVal = CLI_SetLogFileNameAuto();
        YNTEST_CHK_FAILED(ulRetVal, "Set log name fail.\n");
    }
    else
    {
        if(strlen(pcLogName) > 63)
        {
            printf("the length of log file name exceed limit length,maximum is 64\n");
            return ERROR_FAILED;
        }
        sprintf(g_acLogFileName,"%s",pcLogName);
    }
    strcat(g_acLogPath,g_acLogFileName);

    g_uiLogHighestLevevl = uiLevel;

    g_uiLogOutput = uiMode;
    return ulRetVal;
}

/*****************************************************************************
 Func Name    : Log_SaveSource
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ����log��ӡλ����Ϣ
 Input        : CONST CHAR *pcFile
                CONST CHAR *pFunc
                UINT uiLine
 Output       : none
 Return       : none
 Caution      :
*****************************************************************************/

VOID Log_SaveSource(IN CONST CHAR *pcFile, IN CONST CHAR *pFunc, UINT uiLine)
{
    memset(g_acLogLinePrefix, 0, sizeof(g_acLogLinePrefix));
    sprintf(g_acLogLinePrefix,"in file \'%s\' function \'%s\' line %d :",pcFile,pFunc,uiLine);
    return;
}

/* log��ӡ�ӿ� */
/*****************************************************************************
 Func Name    : test_LogPrintf
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : log��ӡ�ӿ�,�����ط���Ҫ��¼log��Ӧʹ�ô˽ӿ�,��Log_Printf��
 Input        : CONST CHAR *pcFormat        ��ʽ���ַ���
                ...                         ���
 Output       : none
 Return       : ��ӡ�ַ�ͳ��
 Caution      :
*****************************************************************************/

UINT CLI_LogPrintf(IN UINT uiLevel, IN CONST CHAR *pcFormat,...)
{
    VA_LIST vaArg;
    FILE *pfFileStream = NULL;
    INT iSize;

    /* log ����������õ���߼��𽫲���ӡlog */
    if(uiLevel > g_uiLogHighestLevevl)
    {
        return 0;
    }

    switch(uiLevel)
    {
        case LOG_LEVEL_WARNING:
        case LOG_LEVEL_TRACE:
        {
            pfFileStream = (FILE *)stdout;
            break;
        }
        case LOG_LEVEL_INFO:
        case LOG_LEVEL_DEBUG:
        case LOG_LEVEL_ERROR:
        default:
        {
            pfFileStream = fopen(g_acLogPath,"a");
            if(NULL == pfFileStream)
            {
                printf("open log file fail, file name:%s\n",g_acLogPath);
                exit(0);
            }
            break;
        }
    }
    
    fprintf(pfFileStream,"%s",g_acLogLinePrefix);
    VA_START(vaArg,pcFormat);
    iSize = vfprintf(pfFileStream,pcFormat,vaArg);
    VA_END(vaArg);
    if(fflush(pfFileStream) < 0)
    printf("Error in fflush - %s\n",strerror(errno));
    if(LOG_LEVEL_INFO == uiLevel || LOG_LEVEL_DEBUG == uiLevel || LOG_LEVEL_ERROR == uiLevel)
    {
        fclose(pfFileStream);
    }

    if((uiLevel >> LOG_MASK_BITS))
    {
        fprintf((FILE *)stdout,"%s",g_acLogLinePrefix);
        VA_START(vaArg,pcFormat);
        iSize = vfprintf((FILE *)stdout,pcFormat,vaArg);
        VA_END(vaArg);
        if(fflush((FILE *)stdout) < 0)
        printf("Error in fflush - %s\n",strerror(errno));
    }
    
    return (UINT)iSize;
}

#ifdef  __cplusplus
}
#endif  /* __cplusplus end */

