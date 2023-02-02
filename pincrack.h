#include <sys/select.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>   // gethostbyname()
#include <arpa/inet.h>

/* This function takes as arguments a SHA-1 hash and the length of it.
This function returns a 4 digit PIN code that has a SHA-1 hash equal to that provided
This function returns -1 if no 4 digit PIN code is found.
*/
 
int pincrack(char *hash, int hashLength);

