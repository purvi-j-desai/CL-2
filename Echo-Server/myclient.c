#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <pthread.h>
#include<stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <netdb.h>
#include <strings.h>
#include<string.h>
pthread_t tid;
sem_t S;


int main()
{
  int sockfd, newsockfd;
  int sin_size;
  struct sockaddr_in server_addr, client_addr;
  char buff[256];
  int nbytes = 0;
  //---------------------
  if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1) {
    perror("Error");
    exit(1);
  }
  server_addr.sin_port = htons(5000);
  inet_aton("127.0.0.1", &(server_addr.sin_addr));
  server_addr.sin_family = AF_INET;
  bzero(&(server_addr.sin_zero), 8);

  if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
    perror("Error");
    exit(1);
  }
  
  sin_size = sizeof(client_addr);
  buff[recv(sockfd, buff, 256, 0)] = '\0';
  if(strcmp(buff, "^") == 0) {
    printf("Server is overloaded...\n");
    close(sockfd);
    exit(1);
  }
  else {
    while(1) {
      printf("Send data: ");
      gets(buff);
      if(strcmp(buff,"q") == 0) {
	send(sockfd, buff, strlen(buff), 0);
	break;
      }
      else
	send(sockfd, buff, strlen(buff), 0);
      buff[recv(sockfd, buff, 256, 0)] = '\0';
      if(strcmp(buff, "q") == 0) 
	break;
      else 
	printf("Echo: %s\n", buff);
    }
  }
  close(sockfd);
  return 0;
}
