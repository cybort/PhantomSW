#ifndef _MYSOCKET_H_
#define _MYSOCKET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/ipc.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <netdb.h>

#ifdef  __cplusplus
extern "C" {
#endif

typedef UINT    SOCK;

#define SOCKET_PROTOCOL_STREAM      (0)
#define SOCKET_PROTOCOL_DGRAM       (1)

#define SOCKET_SD_RECEIVE    0
#define SOCKET_SD_SEND       1
#define SOCKET_SD_BOTH       2
#define Socket_INVALID      ((SOCK)-1)

SOCK Socket_Create(UINT uiProtocol );
ULONG Socket_Close(SOCK sockId);
ULONG Socket_Shutdown( SOCK sockId, UINT uiHow );
SOCK Socket_Accept( SOCK sockServerId );
ULONG Socket_AutoListen( SOCK  sockServerId,
                       UINT  uiPortAddr,
                       UINT  *puiRealPortAddr,
                       UINT  uiNumberOfConnections);
ULONG Socket_Listen( SOCK  sockServerId,
                        UINT  uiPortAddr,
                        UINT  uiNumberOfConnections);
ULONG Socket_Send(SOCK    sockId,
                     VOID *pBuffer,
                     UINT  uiSize );
ULONG Socket_Recv( SOCK sockId,
                      VOID *pBuffer,
                      UINT uiSize);
ULONG Socket_Connect(SOCK     sockId,
                         CONST CHAR *pcCompName,
                         UINT uiPortAddr);
ULONG Socket_Wait( SOCK sockId, UINT uiTimeOutMS);
ULONG Socket_WaitMulti( UINT  uiNumberOfSockets, 
                          SOCK  *asSockId, UINT *uiNum,
                          UINT  uiTimeout);



#ifdef  __cplusplus
}
#endif

#endif

