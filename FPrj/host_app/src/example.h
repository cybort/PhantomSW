#ifndef __CLI_EXAMPLE_H__
#define __CLI_EXAMPLE_H__

#ifdef  __cplusplus
extern "C" {
#endif


ULONG CLI_CmdRegister(VOID);

STATIC ULONG CLI_PublicCliGetCallBack(UINT uiKey, CLI_CIOCTL_PF *ppCallBack);
ULONG CLI_PUBLIC_CallBack(IN UINT uiCmd, IN VOID *pData);

#ifdef  __cplusplus
}
#endif

#endif

