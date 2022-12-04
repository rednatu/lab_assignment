#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>    
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

#define SIM_LENGTH 10 
#define IP_ADDRESS "132.161.33.175" 
#define PORT 1227

int main(void)
{
    int sock; /* socket file descriptor */
    struct sockaddr_in cli_name; /* socket address structure */
    int count;
    int value;

     printf("Client is alive and establishing socket connection.\n");

    sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    { perror ("Error opening channel");
      close(sock);
      exit(1);
    }
     bzero(&cli_name, sizeof(cli_name));
      cli_name.sin_family = AF_INET;
      cli_name.sin_addr.s_addr = inet_addr(IP_ADDRESS);
      cli_name.sin_port = htons(PORT);

        if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)
        { 
            perror ("Error establishing communications");
            close(sock);
            exit(1);
        }
        for (count = 1; count <= SIM_LENGTH; count++)
        {
            read(sock, &value, 4);
            printf("Client has received %d from socket.\n", value);
        }
  printf("Exiting now.\n");

  close(sock); /* close connection to socket */
  exit(0); /* exit with no errors */ 

} 
