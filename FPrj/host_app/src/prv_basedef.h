/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              yntest_basetype.h
   Project Code: Test App
   Module Name : test app public module
   Date Created: 2019-12-12
   Author      : pengying21074
   Description : test app 公共头文件

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#ifndef _YNTEST_BASETYPE_H
#define _YNTEST_BASETYPE_H

#ifdef _cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <ctype.h>
#include <stddef.h>
#include <stdarg.h>


/************************************
      data type definition here
************************************/
#ifndef _SYS_BASETYPE_H_  
typedef unsigned long long UINT64;  /*!< 64 bit unsigned type */
typedef unsigned int       UINT32;  /*!< 32 bit unsigned type */
typedef unsigned short     UINT16;  /*!< 16 bit unsigned type */
typedef unsigned char      UINT8;   /*!< 8 bit unsigned type */
#endif  

#ifndef _SYS_BASETYPE_H_  
typedef signed long long INT64; /*!< 64 bit signed type */
typedef signed int       INT32; /*!< 32 bit signed type */
typedef signed short     INT16; /*!< 16 bit signed type */
typedef signed char      INT8;  /*!< 8 bit signed type */ 

typedef float      FLOAT;  /*!< 32 bit floating point type */
typedef double     DOUBLE; /*!< 64 bit floating point type */
#endif

#ifdef _UT_
#ifdef STATIC
#undef STATIC
#endif
#define STATIC
#else
#ifndef STATIC
#define STATIC    static
#endif
#endif

#ifndef CONST
#define CONST    const
#endif

    
#ifndef INLINE
#define INLINE    inline
#endif
    
#ifndef VOID
#define VOID    void
#endif
    
#ifndef CHAR
#define CHAR    char
#endif
    
#ifndef UCHAR
#define UCHAR   unsigned char
#endif
    
#ifndef SHORT
#define SHORT   short
#endif
    
#ifndef USHORT
#define USHORT  unsigned short
#endif
    
#ifndef LONG
#define LONG    long
#endif
    
#ifndef ULONG
#define ULONG   unsigned long
#endif
    
#ifndef UINT
#define UINT    unsigned int
#endif
    
#ifndef IF_INDEX
#define IF_INDEX unsigned int
#endif
    
#ifndef INT
#define INT     int
#endif
    
#ifndef BOOL_T
typedef USHORT    BOOL_T;
#endif

#ifndef BOOL
typedef UINT    BOOL;
#endif

    
#ifndef FLOAT
#define FLOAT   float
#endif
    
#ifndef DOUBLE
#define DOUBLE  double
#endif
    
    
#ifndef INT8
#define INT8    CHAR
#endif
    
#ifndef UINT8
#define UINT8   UCHAR
#endif
    
#ifndef INT16
#define INT16   SHORT
#endif
    
#ifndef UINT16
#define UINT16  USHORT
#endif
    
#ifndef INT32
#define INT32   INT
#endif
    
#ifndef UINT32
#define UINT32  UINT
#endif
    
#ifndef VRF_INDEX
#define VRF_INDEX USHORT
#endif
    
#ifndef MT_INDEX
#define MT_INDEX USHORT
#endif
    
#ifndef VRF_ANY
#define VRF_ANY (VRF_INDEX)0xffff
#endif
    
#ifndef LIP_ADDR
#define LIP_ADDR USHORT
#endif
    
#ifndef ZONE_ID
#define ZONE_ID USHORT
#endif
    
#ifndef UCM_USERLABEL
#define UCM_USERLABEL UINT32
#endif

typedef char BYTE;
typedef void * LPVOID;    
#if 0
typedef unsigned long long __attribute__((aligned(8)))    UINT64;
typedef long long __attribute__((aligned(8)))            INT64;
#endif    

#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif
                                                
#ifdef __cplusplus
#define container_of(ptr, type, member) ({ \
    (type *)( (char *)ptr - offsetof(type,member) );})
#else
#define container_of(ptr, type, member) ({  \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})
#endif /* inner cplusplus */

/* 返回类型定义 */
#define ERROR_SEVERITY_SUCCESS          0x0
#define ERROR_SEVERITY_INFO             0x1
#define ERROR_SEVERITY_WARNING          0x2
#define ERROR_SEVERITY_ERROR            0x3
#define ERROR_GET_MODULEFACILITY(ulMID) (((ulMID)>>16)&0xfff)
#define ERROR_COMMON_FACILITY                 ERROR_GET_MODULEFACILITY(0x00010000UL)
#define ERROR_DEFINE(sev,fac,code)      ((ULONG)(((ULONG)((sev)&3)<<29) | \
                                                ((ULONG)((fac)& 0x0FFF)<<16)    | \
                                                ((ULONG)((code)&0xFFFF))))    
#define ERROR_SUCCESS                         0x0000UL
#define ERROR_FAILED                          ERROR_DEFINE(ERROR_SEVERITY_WARNING, ERROR_COMMON_FACILITY, 0x1UL)
#define ERROR_INVALID_PARAMETER               ERROR_DEFINE(ERROR_SEVERITY_INFO,    ERROR_COMMON_FACILITY, 0x2UL)
#define ERROR_NO_ENOUGH_RESOURCE              ERROR_DEFINE(ERROR_SEVERITY_WARNING, ERROR_COMMON_FACILITY, 0xBUL)
#define ERROR_NOT_FOUND                       ERROR_DEFINE(ERROR_SEVERITY_WARNING, ERROR_COMMON_FACILITY, 0x5UL)
#define ERROR_TIMEOUT                         ERROR_DEFINE(ERROR_SEVERITY_WARNING, ERROR_COMMON_FACILITY, 0x3UL)

#define BOOL_TRUE   ((BOOL_T)1)
#define BOOL_FALSE  ((BOOL_T)0)
    
#define ENABLE    1
#define DISABLE   2

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE  0
#endif

#if 0
#ifndef ERROR_SUCCESS
#define ERROR_SUCCESS 0x0000UL
#endif

#ifndef ERROR_FAILED
#define ERROR_FAILED  0x40010001UL
#endif
#endif

#ifndef IN
#define IN
#endif
    
#ifndef OUT
#define OUT
#endif
    
#ifndef INOUT
#define INOUT
#endif

#ifdef __KERNEL__
#define YNTEST_Print printk
#else
#define YNTEST_Print printf
#endif

#define MAC_ADDR_LEN 6
    
#define  IGNORE_PARAM(x)     ((x) = (x))
    
#pragma pack()
    
#ifndef BIT_TEST
#define BIT_TEST(f, b)  (0 != ((f) & (b)))
#endif
    
#ifndef BIT_SET
#define BIT_SET(f, b)   ((f) |= (b))
#endif
    
#ifndef BIT_RESET
#define BIT_RESET(f, b) ((f) &= ~(b))
#endif
    
#ifndef BIT_MATCH
#define BIT_MATCH(f,b)          (((f) & (b)) == (b))
#endif
    
#ifndef BIT_COMPARE
#define BIT_COMPARE(f,b1,b2)    (((f) & (b1)) == (b2))
#endif
    
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof (a) / sizeof ((a)[0]))
#endif

#define VA_LIST va_list 
#define VA_START(a,b) va_start((a),(b))
#define VA_ARG(a,b) va_arg(a,b)
#define VA_END(a) va_end((a))

/*  #ifndef __FUNCTION__
#define __FUNCTION__ ">"
#endif */

#if 0
#define DBGASSERT(n)    \
{                                  \
    if (!(n))             \
    {                              \
        printf("FILE=%s,ERROR:FUNC=%s,Line=%d.\n", __FILE__, __FUNCTION__, __LINE__);    \
        return ERROR_FAILED;         \
    }                              \
}
#endif

#define CODE_SECTION(Desc)

#define GFP_ATOMIC 0
#define GFP_KERNEL 0

#define cond_resched()     0

#define yntest_ssprintf(uiCurPos, pcBuf, uiBufLen, args...) \
        ((uiCurPos) += (UINT)scnprintf((pcBuf) + (uiCurPos), ((size_t)(uiBufLen) - (size_t)(uiCurPos)), ## args))

#define MY_LF ("\n")
#define YNTEST_BOOL2STR_YESNO(Expr)    ((BOOL_TRUE == (Expr)) ? "Yes"     : "No")
#define YNTEST_BOOL2STR_DISEN(Expr)    ((BOOL_TRUE == (Expr)) ? "Enable"  : "Disable")
#define YNTEST_BOOL2STR_TF(Expr)       ((BOOL_TRUE == (Expr)) ? "TRUE"    : "FALSE")

#define INVALID_DBG_UCHAR       0xffU
#define INVALID_DBG_USHORT      0xffffU
#define INVALID_DBG_UINT        0xffffffffU
#define INVALID_DBG_UINT64      0xffffffffffffffffU
#define INVALID_DBG_ULONG       ~0UL

#define YNTEST_EZVERSION                           (EZapiCP_Version_Latest)
#define YNTEST_EZCP_ST_INIT(_stEZcp_)   \
        memset(&(_stEZcp_), 0, sizeof(_stEZcp_));   \
        (_stEZcp_).eVersion = (EZapiCP_Version)YNTEST_EZVERSION;

#define YNDEBUG_EZCP_ST_INIT(_stEZcp_)   \
    memset(&(_stEZcp_), 0, sizeof(_stEZcp_));   \
    (_stEZcp_).eVersion = (EZapiCP_Version)YNTEST_EZVERSION;


#define YNTEST_FREE(ptr)\
        {\
            if(NULL != ptr)\
            {\
                free(ptr);\
                ptr = (VOID *)NULL;\
            }\
        }

#define YNTEST_CONTINUE_IF(_expr) \
    {                                   \
        if (_expr)                       \
        {                               \
            continue;                   \
        }                               \
    }
    
#define YNTEST_DIAG_MON(szStringFmt, args...) \
    { \
        { \
            YNTEST_Print((szStringFmt), ## args); \
        } \
    }
    
#define YNTEST_LOG_MON(szStringFmt, args...) \
    { \
        { \
            YNTEST_Print((szStringFmt), ## args); \
        } \
    }
    
#define YNTEST_CHK_FAILED(Expr, szStringFmt, args...) \
    { \
        if (Expr) \
        { \
            Log_Print(LOG_LEVEL_ERROR,(szStringFmt), ## args); \
            return ERROR_FAILED; \
        } \
    }
    
#define YNTEST_CHK_FALSE(Expr, szStringFmt, args...) \
    { \
        if (Expr) \
        { \
            YNTEST_Print((szStringFmt), ## args); \
            return BOOL_FALSE; \
        } \
    }
    
#define YNTEST_PTR_ASSERT_FAILED(pPointer) \
    { \
        if (NULL == (pPointer)) \
        { \
            YNTEST_Print("null pointer"); \
            return ERROR_FAILED; \
        } \
    }

#define YNTEST_CONVERT_TO_EZRET(_ulRet) \
    (ERROR_SUCCESS == (_ulRet) ? EZok : EZerror)

#define YNTEST_CONVERT_FROM_EZRET(_uiStatus)   \
    ((((_uiStatus) & EZrc_ERROR_MASK) != EZrc_ERROR_MASK) ? ERROR_SUCCESS : ERROR_FAILED)

#define YNTEST_CHK_PTR_FAILED(pPointer) \
    YNTEST_CHK_FAILED(NULL == (pPointer), "%s", "Null pointer")


#define YNTEST_CHK_RET_FALSE(ulRet, szStringFmt, args...) \
    YNTEST_CHK_FALSE(ERROR_SUCCESS != (ulRet), szStringFmt, ## args)


#define YNTEST_CHK_RET_FAILED(ulRet, szStringFmt, args...) \
    YNTEST_CHK_FAILED(ERROR_SUCCESS != (ulRet), szStringFmt, ## args)

/* 宏: EZcp返回值检查, 这里的变量不能加括号, 否则编译不过 */
#define YNTEST_CHK_EZRET_FAILED(_uiStatus, _szStringFmt, _args...) \
    YNTEST_CHK_RET_FAILED(YNTEST_CONVERT_FROM_EZRET(_uiStatus), _szStringFmt"\t[0x%08x]", ## _args, (_uiStatus))

#define YNTEST_CHK_EZRET_FALSE(_uiStatus, _szStringFmt, _args...) \
    YNTEST_CHK_RET_FALSE(YNTEST_CONVERT_FROM_EZRET(_uiStatus), _szStringFmt"\t[0x%08x]", ## _args, (_uiStatus))

#define YNTEST_CLEAR_BUF(pPointer, uiSize) \
        memset((pPointer), 0, (uiSize))

#define STRUCT_INIT(pPointer, uiSize) \
        memset((pPointer), 0, (uiSize))

#define YNTEST_ALIGN_UINTLEN(_Length)\
    ((USHORT)((USHORT)(((_Length) + 3) / sizeof(UINT)) * sizeof(UINT)))

#ifndef true
#define true 	(1==1)
#endif
#ifndef false
#define false 	(0)
#endif

#define YNTEST_WHITESPACE(c) (((c) ==' ') || ((c) == '\t'))
#define YNTEST_ISALPHABET(c) (isalpha((c)) ? true : false)
#define YNTEST_ISDIGIT(c)     (isdigit((c)) ? true : false)

#define DEFAULT_INT_VALUE    (0xFFFFFFFF)
#define DEFAULT_LONG_VALUE    (0xFFFFFFFFFFFFFFFF)

#define BUF_SIZE_32     (32)
#define BUF_SIZE_64     (64)
#define BUF_SIZE_128    (128)
#define BUF_SIZE_256    (256)
#define BUF_SIZE_512    (512)
#define BUF_SIZE_1K     (1024)


#ifndef __kernel__
#ifndef likely
#define likely(x)    __builtin_expect(!!(x), 1)
#endif
#ifndef unlikely
#define unlikely(x)  __builtin_expect(!!(x), 0)
#endif
#endif


#define ASSERT_VERSION 1
#ifdef ASSERT_VERSION
extern void AssertHandler(const char *pcExpression,
                            unsigned int uiLine,
                          const char *pcFunction);
/* 断言失败返回默认值，ERROR_FAILED */
#define DBGASSERT(expression) \
{ \
    do \
    {\
        if (unlikely(!(expression))) \
        {\
            AssertHandler(#expression, __LINE__, __FUNCTION__); \
        return ERROR_FAILED; \
        }\
    }while(0); \
}

/* 断言失败返回指定type认值 */
#define DBGASSERT_WITH_RETURN(expression,re_type) \
            { \
                do \
                {\
                    if (unlikely(!(expression))) \
                    {\
                        AssertHandler(#expression, __LINE__, __FUNCTION__); \
                        return (re_type); \
                    }\
                }while(0); \
            }

/* 断言失败返回VOID */
#define DBGASSERT_RETURN_NONE(expression) \
            { \
                do \
                {\
                    if (unlikely(!(expression))) \
                    {\
                        AssertHandler(#expression, __LINE__, __FUNCTION__); \
                        return; \
                    }\
                }while(0); \
            }

#else
#define DBGASSERT(expression) 
#define DBGASSERT_WITH_RETURN(expression, re_type) 
#define DBGASSERT_RETURN_NONE(expression) 
#endif

#include "log.h"


#ifdef _cplusplus
}
#endif

#endif

