#ifndef __CLI_MOR_H__
#define __CLI_MOR_H__

#ifdef  __cplusplus
extern "C" {
#endif

#include "global.h"

#define MOR_BASE    (0x0F000000U)
    
    /* ∂®“ÂCommand ID */
#define MOR_DEF(a,b) ((MOR_BASE + (((a) & 0xFF) << 16)) | ((b) & 0xFFFF))
#define INNER_DEF(a,b) ((((a) & 0xFF) << 8) | ((b) & 0xFF))

typedef enum tagPUBLIC_PROC_ID
{
    PUBLIC_BEGIN = 0,
    PUBLIC_DISPLAY,
    PUBLIC_SET,

    PUBLIC_BUTT,
}PUBLIC_PROC_ID_E;


#define MOR_PUBLIC_DIS_MOD          MOR_DEF(CLI_MOUDLE_PUBLIC, INNER_DEF(PUBLIC_DISPLAY, 1))
#define MOR_PUBLIC_DIS_CONFIG       MOR_DEF(CLI_MOUDLE_PUBLIC, INNER_DEF(PUBLIC_DISPLAY, 2))
#define MOR_PUBLIC_DIS_VALUE        MOR_DEF(CLI_MOUDLE_PUBLIC, INNER_DEF(PUBLIC_DISPLAY, 3))
#define MOR_PUBLIC_DIS_ADDR         MOR_DEF(CLI_MOUDLE_PUBLIC, INNER_DEF(PUBLIC_DISPLAY, 4))


#ifdef  __cplusplus
}
#endif

#endif

