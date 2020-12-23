

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "prv_basedef.h"
#include "mysocket.h"


#define INVALID_SOCKET   -1
#define SOCKET_ERROR     -1




SOCK Socket_Create(UINT uiProtocol )
{
   SOCK    sockId;
   UINT   uiCompatibleProtocol;

   switch ( uiProtocol )
   {
   case SOCKET_PROTOCOL_STREAM:
      uiCompatibleProtocol = SOCK_STREAM;
      break;
   case SOCKET_PROTOCOL_DGRAM:
      uiCompatibleProtocol = SOCK_DGRAM;
      break;
   default:
      return INVALID_SOCKET;
   }

   sockId = socket (AF_INET , (INT)uiCompatibleProtocol , 0 );
   if ( sockId == (SOCK)INVALID_SOCKET ) 
   {
      perror("Socket_Create");
   }
   return ( sockId == (SOCK)INVALID_SOCKET )? Socket_INVALID : sockId;;
}

ULONG Socket_Close(SOCK sockId)
{
    close(sockId);
    return ERROR_SUCCESS;
}

ULONG Socket_Shutdown( SOCK sockId, UINT uiHow )
{
   UINT  uiCompatibleHow;

   switch (uiHow)
   {
   case SOCKET_SD_RECEIVE:
      uiCompatibleHow = 0;
      break;
   case SOCKET_SD_SEND:
      uiCompatibleHow = 1;
      break;
   case SOCKET_SD_BOTH:
   default:
      uiCompatibleHow = 2;
      break;
   }
   shutdown(sockId, (INT)uiCompatibleHow );
   return ERROR_SUCCESS;
}

SOCK Socket_Accept( SOCK sockServerId )
{
   UINT   uiPar;
   SOCK   sockId;
   sockId = accept(sockServerId, NULL , NULL);
   if ( sockId == (SOCK)INVALID_SOCKET ) 
   {
      perror("Socket_Accept ");
      return Socket_INVALID;
   }
   uiPar = 1;
   
   if ( setsockopt(sockId, IPPROTO_TCP, TCP_NODELAY  , (CHAR *)&uiPar, sizeof(uiPar)) == SOCKET_ERROR )
   {
      perror("Error in EZosSocket_Accept (setsockopt)");
      return Socket_INVALID;
   }

   return sockId;
}

ULONG Socket_AutoListen( SOCK  sockServerId,
                               UINT  uiPortAddr,
                               UINT  *puiRealPortAddr,
                               UINT  uiNumberOfConnections)
{
   struct sockaddr_in sockAddr;
   UINT             uiOptval;
   UINT             uiLen;
   ULONG ulRetVal = ERROR_SUCCESS;

   memset(&sockAddr,0,sizeof(sockAddr));

   sockAddr.sin_family = AF_INET;

   sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

   sockAddr.sin_port = htons((USHORT)uiPortAddr);

   uiOptval = TRUE;

   if ( setsockopt( sockServerId , SOL_SOCKET , SO_REUSEADDR , (CHAR *)&uiOptval, sizeof( uiOptval ) ) == SOCKET_ERROR )
   {
      perror("Socket_AutoListen (setsockopt)");
      return ERROR_FAILED;
   }

   if ( bind(sockServerId , (struct sockaddr *)&sockAddr, sizeof (struct sockaddr)) == SOCKET_ERROR)
   {
      perror("Socket_AutoListen (bind)");
      return ERROR_FAILED;
   }

   if (listen(sockServerId,uiNumberOfConnections ) == SOCKET_ERROR)
   {
      perror("Socket_AutoListen (listen)");
      return ERROR_FAILED;
   }

   if ( puiRealPortAddr )
   {
      uiLen = sizeof( sockAddr );

      if ( getsockname( sockServerId, (struct sockaddr *)&sockAddr, &uiLen ) == SOCKET_ERROR )
      {
         perror("Socket_AutoListen (getsockname) ");
         return ERROR_FAILED;
      }

      *puiRealPortAddr = ntohs(sockAddr.sin_port);
   }

   return ulRetVal;
}

ULONG Socket_Listen( SOCK  sockServerId,
                        UINT  uiPortAddr,
                        UINT  uiNumberOfConnections)
{
   return Socket_AutoListen( sockServerId, uiPortAddr, NULL, uiNumberOfConnections );
}

ULONG Socket_Send(SOCK    sockId,
                     VOID *pBuffer,
                     UINT  uiSize )
{
   INT    iSendedBytes;
   UINT   uiCurOffset;
   UCHAR  *pucBuffer = (UCHAR *)pBuffer;
   ULONG  ulRetVal = ERROR_SUCCESS;

   uiCurOffset = 0;
   while ( uiCurOffset < uiSize)
   {
      if ( ( iSendedBytes = send (sockId , (pucBuffer+uiCurOffset), uiSize-uiCurOffset, 0) )  < 1)
      {
         perror("Socket_Send ");
         return ERROR_FAILED;
      }
      uiCurOffset += iSendedBytes;
   }
   return ulRetVal;
}

ULONG    Socket_Recv( SOCK sockId,
                         VOID *pBuffer,
                         UINT uiSize)
{
   INT    iRecvBytes;
   UINT   uiCurOffset;
   UCHAR  *pucBuffer = (UCHAR *)pBuffer;

   uiCurOffset = 0;

   while (uiCurOffset < uiSize)
   {
      if ( ( iRecvBytes = recv( sockId , (pucBuffer+uiCurOffset), uiSize-uiCurOffset, 0 ) ) < 1)
      {
         perror("Socket_Recv");
         return ERROR_FAILED;
      }
      uiCurOffset += iRecvBytes;
   }
   return ERROR_SUCCESS;
}

ULONG    Socket_Connect(SOCK     sockId,
                            CONST CHAR *pcCompName,
                            UINT uiPortAddr)
{
   INT iRes;
   UINT   uiPar;
   struct hostent *lphost;
   struct sockaddr_in sockAddr;
   ULONG  ulRetVal = ERROR_SUCCESS;

   lphost = gethostbyname(pcCompName);
   if (lphost == NULL)
   {
      perror("Socket_Connect (gethostbyname)");
      return ERROR_FAILED;
   }

   memset( &sockAddr, 0, sizeof(sockAddr) );

   sockAddr.sin_family = AF_INET;
   sockAddr.sin_port = htons((USHORT)uiPortAddr);

   sockAddr.sin_addr = *((struct in_addr *)lphost->h_addr_list[0]);

   iRes =  connect ( sockId , (struct sockaddr *) &sockAddr , sizeof (struct sockaddr));
   if (iRes == SOCKET_ERROR)
   {
      perror("Socket_Connect (connect) ");
      return ERROR_FAILED;
   }
   uiPar = TRUE;

   if ( setsockopt( sockId, IPPROTO_TCP, TCP_NODELAY  , (CHAR *)&uiPar, sizeof(uiPar)) == SOCKET_ERROR )
   {
      perror("Socket_Connect (setsockopt) ");
      return ERROR_FAILED;
   }

   return ulRetVal;
}

ULONG Socket_Wait( SOCK sockId, UINT uiTimeOutMS)
{
   INT    iRet;
   fd_set   read_fds;
   struct   timeval  timev;
   ULONG    ulRetVal = ERROR_SUCCESS;

   if ( sockId == Socket_INVALID )
   {
      printf("Error in Socket_Wait - invalid socket to set\n" );
      return ERROR_FAILED;
   }

   FD_ZERO( &read_fds );
   FD_SET( sockId, &read_fds);

    if( 0 == uiTimeOutMS)
    {
        iRet = select( sockId+1, &read_fds, NULL, NULL, NULL );
    }
    else
    {
        timev.tv_sec = uiTimeOutMS / 1000;
        timev.tv_usec = (uiTimeOutMS % 1000) * 1000;
        iRet = select( sockId+1, &read_fds, NULL, NULL, &timev );
    }

    switch(iRet)
    {
        case SOCKET_ERROR:
        perror("Socket_Wait (select) ");
        ulRetVal = ERROR_FAILED;
        break;

        case 0:
        ulRetVal = ERROR_TIMEOUT;
        break;

        default:
        FD_CLR(sockId,&read_fds);
        ulRetVal = ERROR_SUCCESS;
    }
    return ulRetVal;
}

ULONG Socket_WaitMulti( UINT  uiNumberOfSockets, 
                          SOCK  *asSockId, UINT *uiNum,
                          UINT  uiTimeout)
{
    INT iRetVal;
    UINT   uiInd, uiFlag;
    UINT    vMax;
    fd_set   read_fds;
    struct   timeval  timev;

    FD_ZERO(&read_fds);

    uiFlag = 0;
    vMax = 0;
    for ( uiInd = 0; uiInd < uiNumberOfSockets; uiInd++ )
    {
        if ( asSockId[uiInd] != Socket_INVALID )
        {
            FD_SET ( asSockId[uiInd] ,&read_fds);
            uiFlag++;
            if ( vMax < asSockId[uiInd]) 
            {
                vMax = asSockId[uiInd];
            }
        }
    }

    if ( uiFlag == 0)
    {
        return ERROR_FAILED;
    }

    timev.tv_sec = uiTimeout / 1000;
    timev.tv_usec = (uiTimeout % 1000) *1000;

    iRetVal = select( vMax+1, &read_fds, NULL, NULL, &timev);
    if (iRetVal == SOCKET_ERROR)
    {
        perror("Socket_WaitMulti (select) ");
        return -1;
    }

    if ( iRetVal == 0 )
    {
        return ERROR_TIMEOUT;
    }

    uiFlag = 0;

    for (uiInd = 0;uiInd < uiNumberOfSockets ; uiInd++)
    {
        if (FD_ISSET ( asSockId[uiInd] ,&read_fds ))
        {
            uiFlag++;
        }
        else
        {
            asSockId[uiInd] = Socket_INVALID;

        }
    }
    *uiNum = uiFlag;
    FD_ZERO(&read_fds);
    return ERROR_SUCCESS;
}


#ifdef  __cplusplus
}
#endif


