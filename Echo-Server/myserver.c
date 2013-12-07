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

void *serverprocess(void *arg)
{
  int newsockfd = (int)arg;
  char buff[256];
  while(1) {
    buff[recv(newsockfd, buff, 256, 0)] = '\0';
   
    
    if(strcmp(buff, "q") == 0) {
      //send(newsockfd, buff, strlen(buff), 0);
      printf("Terminated connection : %d\n", newsockfd);
      close(newsockfd);
      break;
    }
    else {
      printf("Received message: %s from %d\n", buff, newsockfd);
      send(newsockfd, buff, strlen(buff), 0);
    }
  }
  sem_post(&S);
}


int main()
{
  int sockfd, newsockfd;
  int sin_size;
  struct sockaddr_in server_addr, client_addr;
  char buff[256];
  int nbytes = 0;
  sem_init(&S, 0, 5);
  //---------------------
  if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1) {
    perror("Error");
    exit(1);
  }
  server_addr.sin_port = htons(5000);
  inet_aton("127.0.0.1", &(server_addr.sin_addr));
  server_addr.sin_family = AF_INET;
  bzero(&(server_addr.sin_zero), 8);

  if(bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
    perror("Error");
    exit(1);
  }
  if(listen(sockfd, 15) == -1) {
    perror("Error");
    exit(1);
  }
  sin_size = sizeof(client_addr);
  printf("Listening....\n");
  //-------------------
  while(1) {
    newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
    printf("Accepted\n");
    if(sem_trywait(&S) == 0) {
      send(newsockfd, "$", strlen("$"), 0);
      printf("Got connection at %d form %s:%d\n", newsockfd, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
      pthread_create(&tid, NULL, serverprocess, (void *)newsockfd);
      pthread_detach(tid);
    }
    else {
      printf("Server overloaded..\n");
      send(newsockfd, "^", strlen("^"), 0);
      close(newsockfd);
      break;
    }
  }
  close(sockfd);
  return 0;
}
