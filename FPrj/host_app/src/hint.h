/*******************************************************************************
Copyright (c) 2012, Hangzhou H3C Technologies Co., Ltd. All rights reserved.
--------------------------------------------------------------------------------
                              hint.h
   Project Code: Test App
   Module Name : key word hint
   Date Created: 2020-08-08
   Author      : p21074
   Description : ����ؼ�������ʵ��ͷ�ļ�

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

/* �ؼ������봦��ʽ */
#define HINT_FROM_HEAD      (0)     /* CLI��������ʾ�׹ؼ��� */
#define HINT_ERROR          (1)     /* ��⵽���������ݲ����������ʽ,����ʾ */
#define HINT_FROM_SPEC      (2)     /* ����������,��ʾ��һ�����ܵĹؼ��� */
#define HINT_COMPLETE       (3)     /* ��������������,����ʾ */
#define HINT_DEFAULT        (0xff)  /* Ĭ�ϴ��� */

#define MAX_INPUT_STR_LEN   (80)    /* ����ؼ��ְ������ܻ�������ַ�����󳤶��޶�80 bytes */

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

