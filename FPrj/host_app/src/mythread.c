
#ifdef  __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include "prv_basedef.h"
#include "mythread.h"

typedef VOID *(*Task_StartRoutine)(VOID *);
typedef struct _MUTEX {
   sem_t    semId;
   BOOL_T   bRecursive;
   UINT     uiCnt;
   Thtask   tskId;
} MUTEX;

Thmtx Task_MutexCreate( BOOL_T bRecursive )
{
   MUTEX  *psMutex;

   psMutex = (MUTEX *)malloc(sizeof(MUTEX));
   if (psMutex == NULL )
   {   
      printf("Error in Task_MutexCreate (malloc)\n" );
      return Task_INVALID_MUTEX;
   }
   if (sem_init (&(psMutex->semId), 0, 1) != 0 )
   {
      perror( "Error in Task_MutexCreate (sem_init)");
      free( psMutex );
      return Task_INVALID_MUTEX;
   }
   psMutex->uiCnt = 0;
   psMutex->bRecursive = bRecursive;
   psMutex->tskId = Task_INVALID_TASK;
   return (Thmtx)psMutex ;
}

ULONG Task_MutexDestroy(Thmtx mtxId)
{
   MUTEX   *psMutex;
   
   if ( mtxId != Task_INVALID_MUTEX )
   {
      psMutex = (MUTEX *)mtxId;
      sem_destroy(&(psMutex->semId));
      free( (VOID *)mtxId );
   }
   return ERROR_SUCCESS;
}

ULONG Task_MutexLock(Thmtx mtxId )
{
   INT       iRet;
   Thtask      tskId;
   MUTEX  *psMutex;

   if ( mtxId != Task_INVALID_MUTEX )
   {
      psMutex = (MUTEX *)mtxId;
      if ( ! psMutex->bRecursive) 
      {
         /* binary semaphore */ 
         iRet = sem_wait( (sem_t *)&(psMutex->semId) );
         if ( iRet != 0 )
         {
            perror("Error in Task_MutexLock (sem_wait) ");
            return ERROR_FAILED;
         }
      }
      else
      {
         tskId = Task_GetId();
         if ( tskId == psMutex->tskId )
         {
            psMutex->uiCnt++;
         }
         else
         {
            iRet = sem_wait( (sem_t *)&(psMutex->semId) );
            if ( iRet != 0 )
            {
               perror( "Error in Task_MutexLock (sem_wait) ");
               return ERROR_FAILED;
            }
            psMutex->uiCnt = 1;
            psMutex->tskId = Task_GetId();
         }
      } /* end if recursive */
   }
   else
   {
      printf("Error in Task_MutexLock - invalid mutex\n" );
      return ERROR_FAILED;
   }
   return ERROR_SUCCESS;
}

ULONG Task_MutexUnlock(Thmtx mtxId)
{
   INT       iRet;
   MUTEX     *psMutex;

   if ( mtxId != Task_INVALID_MUTEX )
   {
      psMutex = (MUTEX *)mtxId;
      if ( psMutex->bRecursive) 
      {
         if ( psMutex->uiCnt == 0 )
         {
            printf( "Task_MutexUnlock - counter is already 0\n" );
            return ERROR_FAILED;
         }
         if ( psMutex->tskId != Task_GetId() )
         {
            printf("Task_MutexUnlock - another task id\n" );
            return ERROR_FAILED;
         }
         psMutex->uiCnt--;
         if ( psMutex->uiCnt == 0 )
         {
            psMutex->tskId = Task_INVALID_TASK;
            iRet = sem_post( (sem_t *)&(psMutex->semId) );
            if ( iRet != 0 )
            {
               perror( "Error in Task_MutexUnlock (sem_post) " );
               return ERROR_FAILED;
            }
         }
      }
      else
      {
         iRet = sem_post( (sem_t *)&(psMutex->semId) );
         if ( iRet != 0 )
         {
            perror( "Error in Task_MutexUnlock (sem_post) ");
            return ERROR_FAILED;
         }
      }
   }
   else
   {
      return ERROR_FAILED;
   }

   return ERROR_SUCCESS;
}

/*******************************************************************************************/

Thtask Task_Spawn( const CHAR *pcName, 
                            UINT     uiPri, 
                            UINT     uiStackSize,
                            Task_Spawn_FuncPtr pFun, 
                            VOID     *pArg )
{
   INT          iRetCode;
   pthread_t      *pThread;
   pthread_attr_t sAttr;

   pThread = (pthread_t *)malloc( sizeof(pthread_t));
   if ( pThread == NULL )
   {
      return Task_INVALID_TASK;
   }

   iRetCode = pthread_attr_init( &sAttr );
   
   if ( iRetCode  < 0 )
   {
      perror( "Error in Task_Spawn (pthread_attr_init) " );
      free( pThread );
      return Task_INVALID_TASK;
   }

   iRetCode = pthread_attr_setstacksize( &sAttr, (INT)uiStackSize );

   if ( iRetCode  < 0 )
   {
      perror( "Error in Task_Spawn (pthread_attr_setstacksize) " );
      free( pThread );
      return Task_INVALID_TASK;
   }

   iRetCode = pthread_create( pThread, &sAttr, (Task_StartRoutine) pFun, pArg );

   if ( iRetCode  < 0 )
   {
      perror( "Error in Task_Spawn (pthread_create) " );
      free( pThread );
      return Task_INVALID_TASK;
   }
   
   iRetCode = pthread_attr_destroy( &sAttr );

   if ( iRetCode  < 0 )
   {
      perror( "Error in Task_Spawn (pthread_attr_destroy) " );
      free( pThread );
      return Task_INVALID_TASK;
   }

   return (Thtask) pThread;
}

ULONG Task_Kill( Thtask tTask )
{
   pthread_t sThread;
   INT iRetCode;

   sThread = *(pthread_t *)tTask;
   iRetCode = pthread_cancel( sThread );
   if ( iRetCode == 0 ) 
   {
      free( (pthread_t *)tTask );
      return ERROR_SUCCESS;
   }
   
   return ERROR_FAILED;
}

Thtask Task_GetId( void )
{
   return (Thtask) pthread_self();
}


#ifdef  __cplusplus
}
#endif

