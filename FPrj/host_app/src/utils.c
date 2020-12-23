/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              utils.c
   Project Code: Test App
   Module Name : Pubic utils
   Date Created: 2020-08-02
   Author      : p21074
   Description : �������ܺ����ӿ�

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
#include <stdlib.h>
#include <stdarg.h>

#include "prv_basedef.h"
#include "log.h"
#include "utils.h"

#define vsnprintf(buf, size, fmt, args) vsprintf(buf, fmt, args)

STATIC ULONG CLI_ProcessPrefix(IN CONST      CHAR *pcInBuf, OUT CHAR *pcOutBuf, IN UINT uiSize);
STATIC BOOL_T CLI_ParamIsHex(IN CONST CHAR *pcInBuf);

/*****************************************************************************
 Func Name    : strlcpy
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �ַ������� 
 Input        : char *strSrc                   Ŀ�ĵ�ַ
                const char *strDst             Դ��ַ
                size_t uiSize                  ��Ҫ�������ַ�������
 Output       : none
 Return       : �����ɹ����ַ�������
 Caution      : �˽ӿ�Ϊ�ַ��������İ�ȫ���ýӿ�
*****************************************************************************/

size_t strlcpy(char *strSrc, const char *strDst, size_t uiSize)
{
    size_t size = strlen(strDst);
    size = (size > uiSize - 1)? uiSize - 1 : size;
    CLI_Memcpy(strSrc, strDst, size);
    strSrc[size] = '\0';

    return size;
}

 /*****************************************************************************
  Func Name    : scnprintf
  Date Created : 2020/08/08
  Author       : pengying21074
  Description  : ��ʽ����� 
  Input        : char *buf                   �����������ַ
                 size_t size                 size of out buffer
  Output       : none
  Return       : �����ɹ����ַ�������
  Caution      : �˽ӿ�Ϊ�ַ��������İ�ȫ���ýӿ�
 *****************************************************************************/

 int scnprintf(char * buf, size_t size, const char *fmt, ...)
{
    va_list args;
    unsigned int i;

    va_start(args, fmt);
    i = vsnprintf(buf, size, fmt, args);
    va_end(args);
    return (i >= size) ? (size - 1) : i;
}


/* �Ƚ������ַ����Ƿ���� */
/*****************************************************************************
 Func Name    : CLI_Strcmp
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �Ƚ������ַ����Ƿ���� 
 Input        : CONST CHAR *pStr1                   ���Ƚϵ��ַ���1
                CONST CHAR *pStr2                 ���Ƚϵ��ַ���2
 Output       : none
 Return       : 0 - ���; ��0 - �����
 Caution      : 
*****************************************************************************/

INT CLI_Strcmp(IN CONST CHAR *pStr1, IN CONST CHAR *pStr2)
{
    UINT    uiStrLen1,uiStrLen2;
    if((NULL == pStr1) || (NULL == pStr2))
    {
        return -1;
    }
    uiStrLen1 = strlen(pStr1);
    uiStrLen2 = strlen(pStr2);
    if(uiStrLen1 != uiStrLen2)
    {
        return -1;
    }
    else
    {
        return (strcmp(pStr1,pStr2));
    }
}
/*****************************************************************************
     Func Name    : CLI_ParamIsHex
     Date Created : 2019/12/20
     Author       : pengying 21074
     Description  : �ж���������Ƿ���ʮ������
     Input        : CHAR *pcInBuf       ��Buffer
     Output       : NONE
     Return       : ʮ�����Ʋ�����          BOOL_TRUE 
                    ��ʮ�����Ʋ����� BOOL_FALSE
     Caution      :
*****************************************************************************/

STATIC BOOL_T CLI_ParamIsHex(IN CONST CHAR *pcInBuf)
{
    CONST CHAR *pcTmp = NULL;
    UINT uiSize = 0;
    
    DBGASSERT_WITH_RETURN(NULL != pcInBuf, BOOL_FALSE);
    
    pcTmp = pcInBuf;
    uiSize = strlen(pcTmp);
    if(1 >= uiSize)
    {
        return BOOL_FALSE;
    }
    else
    {
        if( (pcTmp[0] == '0' && pcTmp[1] == 'x') || (pcTmp[0] == '0' && pcTmp[1] == 'X'))
        {
            return BOOL_TRUE;
        }
        else
        {
            return BOOL_FALSE;
        }
    }
}
/*****************************************************************************
 Func Name    : CLI_ProcessPrefix
 Date Created : 2020/01/08
 Author       : pengying 21074
 Description  : ȥ��ʮ�����Ʋ����ַ���ǰ�ı�ʶ
 Input        : CHAR *pcInBuf       Input buffer
                UINT uiSize         ��buffer����
 Output       : CHAR *pcOutBuf      ��buffer
 Return       : ERROR_SUCCESS: �����ɹ�
                ERROR_FAILED : ����ʧ��
 Caution      :
*****************************************************************************/

STATIC ULONG CLI_ProcessPrefix(IN CONST      CHAR *pcInBuf, OUT CHAR *pcOutBuf, IN UINT uiSize)
{
    
    CONST CHAR *pcTmp = NULL;
    CHAR *pcCurPos = NULL;

    DBGASSERT(NULL != pcInBuf);
    DBGASSERT(NULL != pcOutBuf);
    
    YNTEST_CLEAR_BUF(pcOutBuf, uiSize);
    pcTmp = pcInBuf;
    pcCurPos = strstr(pcTmp, "0");
    if(NULL != pcCurPos)
    {
        pcCurPos++;
        if('x' == *pcCurPos || 'X' == *pcCurPos)
        {
            pcCurPos++;
            strlcpy(pcOutBuf, pcCurPos, uiSize);
            return ERROR_SUCCESS;
        }
    }
    return ERROR_FAILED;
}

/*****************************************************************************
 Func Name    : CLI_Str2dec
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ʮ�����ַ���תʮ������ 
 Input        : CONST CHAR *pStr                   ��ת�����ַ���
 Output       : UINT *puiNo                        ת��������
 Return       : ����ת��������ַ�������
 Caution      : 
*****************************************************************************/

UINT CLI_Str2dec(IN CONST CHAR *pcStr, INOUT UINT *puiNo)
{
    UINT i=0;
    UINT uiPower=1;
    UINT uiVal = 0;
    UINT uiLen;
    ULONG ulRetVal = ERROR_SUCCESS;
    CHAR *pcTmp = NULL;
    UINT uiBitNum;
    CHAR cChTmp;

    DBGASSERT_WITH_RETURN(NULL != pcStr, 0);
    DBGASSERT_WITH_RETURN(NULL != puiNo, 0);

    /* ������ʮ�����Ʋ��� */
    if(CLI_ParamIsHex(pcStr))
    {
        pcTmp = malloc(strlen(pcStr));
        if(NULL == pcTmp)
        {
            Log_Print(LOG_LEVEL_ERROR, "malloc failed.\n");
            return 0;
        }
        YNTEST_CLEAR_BUF(pcTmp,strlen(pcStr));
        ulRetVal = CLI_ProcessPrefix(pcStr, pcTmp, strlen(pcStr));
        if(ulRetVal)
        {
            Log_Print(LOG_LEVEL_ERROR,"Process parameter string prefix failed. p= %s\n",pcStr);
            return 0;
        }
        while(pcTmp[i] != '\0' )
        {
            if(isdigit(pcTmp[i]))
            {
                i++;
            }
            else if(isalpha(pcTmp[i]))
            {
                i++;
            }
            else
            {
                Log_Print(LOG_LEVEL_ERROR,"invalid parameter character found. p = %s\n",pcStr);
                return 0;
            }
            if(pcTmp[i] == ' ' || pcTmp[i] == '-')
            {
                break;
            }
        }
        if(0 == i)
        {
            return 0;
        }
        uiLen = i +2 ;
        while(0 != i)
        {
            --i;
            if(isalpha(pcTmp[i]))
            {
                cChTmp = toupper(pcTmp[i]);
                if(cChTmp < 'A' || cChTmp > 'Z')
                {
                    Log_Print(LOG_LEVEL_ERROR,"invalid parameter character found. p = %s\n",pcStr);
                    return 0;
                }
                else
                {
                    uiBitNum = cChTmp - 'A' + 10;
                }
            }
            else
            {
                uiBitNum = pcTmp[i] - '0';
            }
            uiVal += uiBitNum * uiPower;
            uiPower = uiPower * 16;
        }
        free(pcTmp);
    }
    /* ��ʮ������������ */
    else
    {
        while((i<10) && (pcStr[i]>='0') && (pcStr[i]<='9'))
        {
            i++;
        }

        if(0 == i)
        {
            return 0;
        }

        uiLen = i;

        while(0!=i)
        {
            --i;
            uiVal += (pcStr[i] - '0') * uiPower;
            uiPower = uiPower * 10;
        }
    }
    *puiNo = uiVal;
    
    return uiLen;
}

/*****************************************************************************
 Func Name    : CLI_Memcpy
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : �ڴ濽���İ�ȫ�ӿ� 
 Input        : VOID *dest                   pointer to destination
                const VOID *src              pointer to source
 Output       : none
 Return       : destination address
 Caution      : 
*****************************************************************************/

VOID *CLI_Memcpy(VOID *dest, const VOID *src, UINT len)
{
    CHAR *pctemp;
    const CHAR *pcsrc;
    if(dest == NULL || src == NULL)
    {
        return NULL;
    }
    pctemp = (CHAR *)dest;
    pcsrc = ( const CHAR *)src;
    if((pctemp +len) < pcsrc || pctemp >= (pcsrc + len))
    {
        while(len--)
        {
            *pctemp++ = *pcsrc++;
        }
    }

    else if(pctemp < pcsrc)
    {
        while(len--)
        {
            *pctemp++ = *pcsrc++;
        }
    }
    else
    {
        while(len--)
        {
            *(pctemp + len) = *(pcsrc + len);
        }
    }
    return dest;
}

/*****************************************************************************
 Func Name    : CLI_ShowMem
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : ��ʾ�ڴ����� 
 Input        : BYTE *pStart                   pointer to start
                UINT uiSize                    the size that will be shown
 Output       : none
 Return       : void
 Caution      : �˽ӿڽ������������Բ鿴�ڴ浥Ԫ
*****************************************************************************/

VOID CLI_ShowMem(BYTE *pStart, UINT uiSize)
{
    UINT uiLoop;
    UINT uiCnt = 0;
    UINT uiTotal = 0;
    for(uiLoop = 0; uiLoop < uiSize; uiLoop++)
    {
        if(uiCnt == 0) 
        {
            if(uiTotal +12 < uiSize)
            printf(" %p - %p :",pStart+uiLoop, pStart+uiLoop+12);
            else
            printf(" %p - %p :",pStart+uiLoop, pStart+uiSize);
        }
        printf("%X ",pStart[uiLoop]);
        uiCnt++;
        uiTotal++;
        if(uiCnt == 12)
        {
            printf("\n");
            uiCnt = 0;
        }
    }
    printf("\n");
    return;
}

void AssertHandler(const char *pcExpression,
                            unsigned int uiLine,
                          const char *pcFunction)
{
    CHAR acAssertBuf[256] = {0};
    UINT uiBufLen = 0;

    yntest_ssprintf(uiBufLen, acAssertBuf, 255, "assertion failed:(%s). Line:%d :%s",
                    pcExpression, uiLine, pcFunction);
    printf("%s\n",acAssertBuf);
    return;
}


#ifdef  __cplusplus
}
#endif  /* __cplusplus end */

