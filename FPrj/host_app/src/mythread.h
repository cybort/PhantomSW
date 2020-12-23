#ifndef _MY_THREAD_H_
#define _MY_THREAD_H_

#ifdef  __cplusplus
extern "C" {
#endif



typedef unsigned long Thtask;
typedef unsigned long Thsem;
typedef unsigned long Thmtx;

typedef UINT (*Task_Spawn_FuncPtr)( VOID *pArg );


#define Task_HIGHEST_PRIORITY            0
#define Task_ABOVE_NORMAL                99
#define Task_NORMAL_PRIORITY             102
#define Task_BELOW_NORMAL                110
#define Task_LOWEST_PRIORITY             255
    
#define Task_INVALID_SEMAPHORE           (Thsem)0
#define Task_INVALID_MUTEX               (Thmtx)0
#define Task_INVALID_TASK                (Thtask)0

Thmtx Task_MutexCreate( BOOL_T bRecursive );
ULONG Task_MutexDestroy(Thmtx mtxId);
ULONG Task_MutexLock(Thmtx mtxId );
ULONG Task_MutexUnlock(Thmtx mtxId);
Thtask Task_Spawn( const CHAR *pcName, 
                        UINT     uiPri, 
                        UINT     uiStackSize,
                        Task_Spawn_FuncPtr pFun, 
                        VOID     *pArg );
ULONG Task_Kill( Thtask tTask );
Thtask Task_GetId( void );


#ifdef  __cplusplus
}
#endif

#endif

