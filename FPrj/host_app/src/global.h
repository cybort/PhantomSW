/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              global.h
   Project Code: Test App
   Module Name : CLI
   Date Created: 2020-08-02
   Author      : p21074
   Description : header file of global.c which include macro and private variable 
                 type definition

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#ifndef __CLI_GLOBAL_H__
#define __CLI_GLOBAL_H__

#ifdef  __cplusplus
extern "C" {
#endif

#define MAX_NAME_LEN    (32)      /* 关键字最大长度 */
#define MAX_MOUDLE      (32)      /* 当前框架支持注册的最大模块 */
#define MAX_SUB_MOUDLE  (16)      /* 每个模块的命令可分的注册次数 */

#define USELESS_PARA    (0xFFFFFFFFU)

/* command id base 定义 */
#define CMD_BASE    (0x2F000000U)
/* 定义command ID */
#define CMD_DEF(a,b) ((CMD_BASE + (((a) & 0xFF) << 16)) | ((b) & 0xFFFF))
#define DE_CMD(a) ((((a) - CMD_BASE) >> 16) & 0xFF)

/* 模块ID定义 */
typedef enum tagCLI_MOUDLE
{
    CLI_MOUDLE_PUBLIC = 0,

    /* 新增模块添加在上面 */
    CLI_MOUDLE_BUTT
}CLI_MOUDLE_E;

/* 模块Command ID定义 */
#define PUBLIC_CMD_DIS   CMD_DEF(CLI_MOUDLE_PUBLIC, 0x00)
#define PUBLIC_CMD_SET   CMD_DEF(CLI_MOUDLE_PUBLIC, 0x01)



ULONG CLI_RegAllCmd(VOID);
ULONG CLI_RegAllCallBack(VOID);


#ifdef  __cplusplus
}
#endif

#endif

