/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              hint.h
   Project Code: Test App
   Module Name : key word hint
   Date Created: 2020-08-08
   Author      : p21074
   Description : 命令关键字联想实现头文件

--------------------------------------------------------------------------------
   Modification History
   DATE        NAME             DESCRIPTION
--------------------------------------------------------------------------------
   YYYY-MM-DD  

*******************************************************************************/

#ifndef __CLI_HINT_H__
#define __CLI_HINT_H__

#ifdef  __cplusplus
extern "C" {
#endif

/* 关键字联想处理方式 */
#define HINT_FROM_HEAD      (0)     /* CLI无输入提示首关键字 */
#define HINT_ERROR          (1)     /* 检测到已输入内容不符合命令格式,不提示 */
#define HINT_FROM_SPEC      (2)     /* 已输入无误,提示下一个可能的关键字 */
#define HINT_COMPLETE       (3)     /* 命令以输入完整,不提示 */
#define HINT_DEFAULT        (0xff)  /* 默认处理 */

#define MAX_INPUT_STR_LEN   (80)    /* 命令关键字包括可能会输入的字符串最大长度限定80 bytes */

extern CHAR *g_acErrInfo[7];
extern CHAR g_acPrompt[BUF_SIZE_64];
extern volatile UINT g_uiMID;

extern char *rl_line_buffer;
extern int rl_point;
extern int rl_end;
extern CHAR *rl_prompt;
extern int rl_already_prompted;
extern rl_voidfunc_t *rl_redisplay_function;

typedef struct tagHINT_ERROR_INFO
{
    CLI_PRASE_ERROR_E enErrType;
    UINT uiParseLen;
}HINT_ERROR_INFO_S;

extern INT test_CmdKeyWordHint(INT iCount, INT Key);




#ifdef  __cplusplus
}
#endif

#endif

