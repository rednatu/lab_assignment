#include <iostream>
#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h> /* socket command libraries needed by some compilers */
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
using namespace std;

#define SIM_LENGTH 10 /* number of integers to be written and read */
#define PORT 1227 /* local port on which connection will be established */


void clean_up(int cond, int *sock)
{ cout<<"Exiting now.\n";
  close(*sock); 
  exit(cond);
} 


int main(){
    int sock; 
    int connect_sock;
    struct sockaddr_in serv_name;
     /* socket address structure 
     struct sockaddr_in {
     short	sin_family;
     u_short	sin_port;
     struct in_addr	sin_addr;
     char	sin_zero[8];
    };
    */
    size_t len; /* variable for the size of the socket address structure */
    int count;

     /* set socket descriptor */ 
     sock = socket(AF_INET, SOCK_STREAM, 0);  //#defined	AF_INET = 2 and SOCK_STREAM = 1, socket => int socket(int, int, int) ...in the socket.h library
    if (sock < 0)
     { 
        perror ("Error opening channel");
        clean_up(1, &sock);
     }
     bzero(&serv_name, sizeof(serv_name)); //The bzero() function erases the data in the n bytes of the memory starting at the location pointed to by s, by writing zeros (bytes containing '\0') to that area.
    serv_name.sin_family = AF_INET;
    serv_name.sin_port = htons(PORT); //The htons() function translates a short integer from host byte order to network byte order. The unsigned short integer to be put into network byte order.
      if (bind(sock, (struct sockaddr *)&serv_name, sizeof(serv_name)) < 0) //int	bind(int, const struct sockaddr *, socklen_t) __DARWIN_ALIAS(bind)
        { 
            perror ("Error naming channel");
            clean_up(1, &sock);
        }
     len = sizeof(serv_name);
     connect_sock = accept(sock, (struct sockaddr *)&serv_name, &len); //int	accept(int, struct sockaddr * __restrict, socklen_t * __restrict) __DARWIN_ALIAS_C(accept);
     
}   