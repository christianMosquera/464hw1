#include "pincrack.h"

#define SERVER_PORT     3005
#define BUFFER_LENGTH    250
#define FALSE              0
#define SERVER_NAME     "localhost"
#define MAX_HOST_NAME_LENGTH 20

int pincrack(char *hash, int hashLength) {

/* Here you will implement all logic: 
socket creation, communication with the server and returning 
the value to the caller of this function. 
*/
   int    sd=-1, rc, bytesReceived;
   char   buffer[hashLength];
   char   server[MAX_HOST_NAME_LENGTH];
   int    num;
   struct sockaddr_in serveraddr;
   struct hostent *hostp;

   
   sd = socket(AF_INET, SOCK_STREAM, 0);
   //test error sd < 0

   memset(&serveraddr, 0, sizeof(serveraddr));
   serveraddr.sin_family      = AF_INET;
   serveraddr.sin_port        = htons(SERVER_PORT);
   serveraddr.sin_addr.s_addr = inet_addr(server);

   if (serveraddr.sin_addr.s_addr == (unsigned long)INADDR_NONE)      {
      hostp = gethostbyname(SERVER_NAME);
      if (hostp == (struct hostent *)NULL) {
         printf("Host not found --> ");
         return -1;
      }

      memcpy(&serveraddr.sin_addr,
               hostp->h_addr,
               sizeof(serveraddr.sin_addr));
   }

    rc = connect(sd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    // test error rc < 0

    rc = send(sd, hash, hashLength + 1, 0);
    rc = recv(sd, &num, sizeof(int), 0);
    

//    shutdown(sd, SHUT_RDWR);

    if (sd != -1)
      close(sd);

    return num;
}
