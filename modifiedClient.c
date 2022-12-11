/* Author: Pete Broadwell
           Grinnell College

   This program uses streaming Internet sockets to simulate the readers-writers
   problem. This is the client/reader portion of the simulation.
*/

#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>     /* socket command libraries needed by some compilers */
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define SIM_LENGTH 10 /* number of integers to be written and read */
//#define IP_ADDRESS "132.161.33.175" /* Internet address of server */
#define PORT 1227 /* local port on which the server establishes connection */

int main(int argc, char* argv[])
{ /* processing for client */
  int sock; /* socket file descriptor */
//   struct sockaddr_in cli_name; /* socket address structure */
  int count;
  int value; /* variable for number read from socket */

  struct addrinfo* res;
  char* hostname;
  char* hostaddr;
  struct sockaddr_in* saddr;

  if (argc != 2) {
    perror("Usage: hostnamelookup <hostname>\n");
    exit(1);
  }

  hostname = argv[1];

  /* Resolve the hostname to an addrinfo structure */
  if (0 != getaddrinfo(hostname, NULL, NULL, &res)) {
    fprintf(stderr, "Error in resolving hostname %s\n", hostname);
    exit(1);
  }

  /* Extract the sockaddr and cast to sockaddr_in */
  saddr = (struct sockaddr_in*)res->ai_addr;

  /* Convert the address to numbers-and-dots notation (a char * string)
   * (This is only necessary if a human being will read the address.)
   * Note that the string returned comes from a static memory area.
   */
  hostaddr = inet_ntoa(saddr->sin_addr);

  printf("Address for %s is %s\n", hostname, hostaddr);
  exit(0);

  printf("Client is alive and establishing socket connection.\n");
  
  /* set the socket descriptor */
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    { perror ("Error opening channel");
      close(sock);
      exit(1);
    }
      
  /* set the physical address (cli_name) of the socket descriptor */
  bzero(&saddr, sizeof(saddr)); /* initializes the address structure */
  saddr->sin_family = AF_INET; /* socket family will be AF_INET (Internet) */
  saddr->sin_addr.s_addr = inet_addr(hostaddr); /* sets the Internet
						       Protocol (IP) address
						       of the server */
  saddr->sin_port = htons(PORT); /* sets the port on which the server will
				      establish the socket connection */

  /* connect to the socket */
  if (connect(sock, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    { perror ("Error establishing communications");
      close(sock);
      exit(1);
    }

  /* read integers from the socket */
  for (count = 1; count <= SIM_LENGTH; count++)
    { read(sock, &value, 4);
      printf("Client has received %d from socket.\n", value);
    }

  printf("Exiting now.\n");

  close(sock); /* close connection to socket */
  exit(0); /* exit with no errors */ 

} /* end of main */
