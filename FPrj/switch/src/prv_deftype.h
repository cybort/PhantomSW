/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              prv_deftype.h
   Project Code: F-Switch
   Module Name : public module
   Date Created: 2020-11-12
   Author      : pengying21074
   Description : 公共头文件

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#ifndef _PRV_TYPEDEF_H_
#define _PRV_TYPEDEF_H_

#ifdef _cplusplus
#include <cstdarg>
#include <cstddef>
#else
#include <stdarg.h>
#include <stddef.h>
#endif

/************************************
      data type definition here
************************************/
#ifndef _SYS_BASETYPE_H_  
typedef unsigned long long   UINT64;        /*!< 64 bit unsigned type */
typedef unsigned int        UINT32;         /*!< 32 bit unsigned type */
typedef unsigned short      UINT16;         /*!< 16 bit unsigned type */
typedef unsigned char       UINT8;          /*!< 8 bit unsigned type */
typedef signed long long    INT64;          /*!< 64 bit signed type */
typedef signed int          INT32;          /*!< 32 bit signed type */
typedef signed short        INT16; /*!< 16 bit signed type */
typedef signed char         INT8;  /*!< 8 bit signed type */ 
typedef float               FLOAT;  /*!< 32 bit floating point type */
typedef double              DOUBLE; /*!< 64 bit floating point type */
#endif

#ifndef STATIC
#define STATIC    static
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

#define BOOL_TRUE   ((BOOL_T)1)
#define BOOL_FALSE  ((BOOL_T)0)
#ifndef TRUE
#define TRUE  1
#endif
    
#ifndef FALSE
#define FALSE  0
#endif

//#undef NULL
#ifndef NULL
#ifdef _UT_
#define NULL    ((ULONG)0)
#else
#define NULL    ((void *)0)
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

#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif
                                                
#ifdef __cplusplus
#define container_of(ptr, type, member) ({  \
    (type *)( (char *)ptr - offsetof(type,member) );})
#else
#define container_of(ptr, type, member) ({  \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})
#endif /* inner cplusplus */

/* 返回类型定义 */
#if 0
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
#endif
#define  IGNORE_PARAM(x)     ((x) = (x))

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof (a) / sizeof ((a)[0]))
#endif

#define VA_LIST va_list 
#define VA_START(a,b) va_start((a),(b))
#define VA_ARG(a,b) va_arg(a,b)
#define VA_END(a) va_end((a))

#ifndef true
#define true 	(1==1)
#endif
#ifndef false
#define false 	(0)
#endif

#define MAX_FIFO_SIZE   100

#define UNICAST     (0U)
#define MULTCAST    (1U)
#define EMPTY       (2U)


#endif

