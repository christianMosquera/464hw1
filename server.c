#include <sys/select.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>    
#include <netinet/in.h>
#include <unistd.h>
#include <openssl/sha.h>

#define SERVER_PORT     3005
#define BUFFER_LENGTH    250
#define FALSE              0

typedef unsigned char byte;

int crack_code(const char* buffer) {
      SHA_CTX         shactx;
      unsigned char   digest[SHA_DIGEST_LENGTH];
      unsigned char   hash[SHA_DIGEST_LENGTH*2];

      // cracking code
      for (int i = 0; i < 10000; i++) {

         // compute hash
         SHA1_Init(&shactx);
         SHA1_Update(&shactx, &i, 4);
         SHA1_Final(digest, &shactx);

         // make hash human readable
         for (int j=0; j < SHA_DIGEST_LENGTH; j++) {
            sprintf((char*)&(hash[j*2]), "%02x", digest[j]);
         }

         // compare the two hash values
         if (strcmp(hash, buffer) == 0) {
            return i;
         }
      }

      // if not found
      return -1;
}

int  main() {
   int    sd=-1, sd2=-1;
   int    rc, length, on=1;
   int    optval = 1;
   unsigned char   buffer[SHA_DIGEST_LENGTH*2];

   fd_set read_fd;
   struct timeval timeout;
   struct sockaddr_in serveraddr;

   if (sd = socket(AF_INET, SOCK_STREAM, 0) < -1) {
      return -1;
   }

   memset(&serveraddr, 0, sizeof(serveraddr));
   serveraddr.sin_family      = AF_INET;
   serveraddr.sin_port        = htons(SERVER_PORT);
   serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

   if (rc = bind(sd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == < 0) {
      return -1;
   }

   if(rc = listen(sd, 10) < 0) {
      return -1;
   }

   printf("Ready for client connect().\n");

   do {

      sd2 = accept(sd, NULL, NULL);
      // test error sd2 < 0

      timeout.tv_sec  = 0;
      timeout.tv_usec = 0;

      FD_ZERO(&read_fd);
      FD_SET(sd2, &read_fd);

      if (rc = select(1, &read_fd, NULL, NULL, &timeout) < 0) {
         return -1;
      }
 
      rc = recv(sd2, buffer, SHA_DIGEST_LENGTH*2 + 1, 0);

      printf("server received %d bytes\n", rc);      

      // cracking code
      int i = crack_code(buffer);

      rc = send(sd2, &i, sizeof(int), 0);

   } while (1);

   if (sd != -1)
      close(sd);
   if (sd2 != -1)
      close(sd2);
}


