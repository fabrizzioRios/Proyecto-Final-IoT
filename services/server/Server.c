#include "com.h"
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "mqtt_frames.h"

#define DEBUG 1

#define CONNECT_PORT 1883 // Port used for the next connection
#define MAXSOCKETS 5      // Limit of sockets.

// Global variables used by ptheads
uint8_t listSocket[MAXSOCKETS] = {0};
int socketIndex;
pthread_mutex_t socketMutex = PTHREAD_MUTEX_INITIALIZER;
int newSocketMember = 0;

void ServerClientThread(void *vpSocketTemp);

int main(int argc, char *argv[]) {
  int32_t dwServerSocket;
  int32_t dwSize;
  int32_t dwCurConnection;
  struct sockaddr_in sServSettings;
  struct sockaddr_in sClient;
  pthread_t ClientT;

  sConnect sReturn;
  sConnACK sAcknowledge;
  sPublish sPublish;
  sSubscribe sSubscribe;
  sUnsubscribe sUnsub;
  sPingReq sRequest;
  sPingRes sResponse;

if(argv[1]){


  printf("argv[] %s, sizeof %d \r\n", argv[1], strlen(argv[1]));

  sReturn = vfnCreateFrame((char *)argv[1], sizeof(argv[1]));

  printf("Server Init\n\r");
  // Set IP information
  sServSettings.sin_family = AF_INET;
  sServSettings.sin_addr.s_addr = INADDR_ANY;
  sServSettings.sin_port = htons(CONNECT_PORT);

  /*int socket(int domain, int type, int protocol);
  AF_INET	= IPv4 Internet protocols
  SOCK_STREAM = Provides sequenced, reliable,
                          two-way, connection-based byte streams.
                          An out-of-band data transmission mechanism may be
  supported. Protocol specifies a particular protocol to be used with the
  socket. Normally only a single protocol exists to support a particular socket
  type within a given protocol family, in which case protocol can be specified
  as 0.
  */
  dwServerSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (dwServerSocket < 0) {
    printf("Error Creating socket\n\r");
  }
  printf("Binding ...\n\r");
  if (bind(dwServerSocket, (struct sockaddr *)&sServSettings,sizeof(sServSettings))) {
    printf("Error Binding\n\r");
  }
  printf("Listening ...\n\r");
  listen(dwServerSocket, 10);
  dwSize = sizeof(struct sockaddr_in);

  pthread_create(&ClientT, NULL, (void *)&ServerClientThread,
                 (void *)&dwCurConnection);
  socketIndex = 0;

  while (1) {
    if ((dwCurConnection = accept(dwServerSocket, (struct sockaddr *)&sClient,(socklen_t *)&dwSize)) < 0) {
      printf("Accepting Error\n\r");
      printf("There was an error trying to accept in the socket, errno:%d\n",
             errno);
      continue;

    } else {
      printf("Connection Accept ...\n\r");
      if(sReturn.bFrameType == 0x10){
        printf("ACK...\n\r");
        sAcknowledge = vfnCreateCONNACK();
        if(sAcknowledge.bFrameType == 0x20){
           sPublish = vfnCreatePUBLISH();
          if(sPublish.bFrameType == 0x30){
            sRequest = vfnCreateREQUEST();
          }else{
            printf("Publish Fallido\n");
          }
        }else{
          printf("Acknowledge Fallido\n");
        }
      }else{
        printf("Frame Invalido\n");
      }
      //sRequest = vfnCreateREQUEST();
    }
    if (listSocket[socketIndex] == 0) {
      listSocket[socketIndex] = dwCurConnection;
      printf("adding new connection listSocket[%d] = %d\n", socketIndex,
             listSocket[socketIndex]);
      socketIndex++;
    } else {
      continue;
    }

    sleep(1);
  }
}else{

	printf("Error en Insercion de Dato\n");

}
  return 0;
}

void ServerClientThread(void *vpSocketTemp) {
  int32_t *dwpSocket;
  uint8_t bNumsocketIndex = 0;
  ssize_t ReadStatus = 0;
  sFrame sFrameInfo;
  dwpSocket = (int32_t *)vpSocketTemp;
  char bpFramePtr[1024] = {0};

  sFrameInfo.bSOF = 0x31;
  sFrameInfo.bCMD = 0x35;

  while (1) {
    pthread_mutex_lock(&socketMutex);
    // Send a messages to all the members connected.
    for (bNumsocketIndex = 0; bNumsocketIndex < 10; bNumsocketIndex++) {
      if (listSocket[bNumsocketIndex] != 0) {
        // Write the message in the socket.
        // ReadStatus = dwfnReadFrame(&sFrameInfo, *dwpSocket);
        ssize_t Readstatus = read(*dwpSocket, bpFramePtr, 1024);
        printf("The data rx %s \r\n", bpFramePtr);
        printf("This is the Rx Frame \r\n");
#if DEBUG == 1
        printf("bNumsocketIndex : %d\n", bNumsocketIndex);
        printf("Reading to: %d\n", listSocket[bNumsocketIndex]);
        printf("ReadStatus : %d\n", ReadStatus);
#endif
        // If there was an error writing to the socket then
        // we shutdown the socket to let other the connection.
        if (ReadStatus < 0) {
          printf("Shuting down a socket of index: %d\n", bNumsocketIndex);
          shutdown(listSocket[socketIndex], SHUT_RDWR);
          listSocket[bNumsocketIndex] = 0;
          //sUnsub = vfnCreateUNSUBSCRIBE(strlen(sUnsubscribe.bPacketIdentifier),(char *)sUnsubscribe.sTopic);
        }
      }
    }
    pthread_mutex_unlock(&socketMutex);
    // This pthread must sleep for 10 seconds.
    sleep(1);
  }
}
