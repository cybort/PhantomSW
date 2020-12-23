/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              global.c
   Project Code: Test App
   Module Name : GLOBAL 
   Date Created: 2020-08-02
   Author      : p21074
   Description : global project file for other moudle

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#include "prv_basedef.h"
#include "global.h"
#include "cli.h"
#include "example.h"

/*****************************************************************************
 Func Name    : CLI_RegAllCmd
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 其他模块的命令注册放此函数中
 Input        : NONE
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
ULONG CLI_RegAllCmd(VOID)
{
    ULONG ulRetVal = ERROR_SUCCESS;

    ulRetVal += CLI_CmdRegister();



    return ulRetVal;
}

/*****************************************************************************
 Func Name    : CLI_RegAllCallBack
 Date Created : 2020/08/08
 Author       : pengying21074
 Description  : 各模块的callback函数统一放此函数中
 Input        : NONE
 Output       : NONE
 Return       : ERROR_SUCCESS: 操作成功
                ERROR_FAILED : 操作失败
 Caution      : 
*****************************************************************************/
ULONG CLI_RegAllCallBack(VOID)
{
    ULONG ulRetVal = ERROR_SUCCESS;

    ulRetVal += CLI_RegCallBack( CLI_MOUDLE_PUBLIC, CLI_PUBLIC_CallBack);

    return ulRetVal;
}


#ifdef  __cplusplus
}
#endif  /* __cplusplus end */

