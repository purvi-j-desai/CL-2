#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define max 20


char *ROOT;
char PORT[6];
struct sockaddr_in server_addr, client_addr;

void print_header(int newsockfd)
{
  int n, fd, bytes_read = 0;
  char rdata[1024], MYFILE[200] = "\0";
  int sockfd_clnt;
  strcpy(MYFILE, ROOT);
  strcat(MYFILE, "/index.html");
  printf("In print header %d, file: %s\n", newsockfd, MYFILE);
  n = recv(newsockfd, rdata, 1024, 0);
  rdata[n] = '\0';
  printf("Header:\n\n%s\nEOH..\n", rdata);
  if((fd = open(MYFILE, O_RDONLY)) != -1) {
    while(bytes_read = read(fd, rdata, 1024)) {
      write(newsockfd, rdata, bytes_read);
    }
  }
  shutdown (newsockfd, SHUT_RDWR);   
  close(newsockfd);
  newsockfd = -1;
  
  if((sockfd_clnt = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("error");
    exit(1);
  }
  if(connect(sockfd_clnt, (struct sockaddr *)&client_addr, sizeof(struct sockaddr)) == -1)
    printf("Cannot connect\n");
  else {
    printf("Recieved response");
  }
}

int main()
{
  printf("HTTP Header: ");
  int sockfd, newsockfd, sin_size;
  
  pthread_t client;
  //-------------------
  
  ROOT = getenv("PWD");
  strcpy(PORT, "10000");
  printf("Shall start listening at port no. %s at root %s.....\n", PORT, ROOT);

  //starting to listen on the server--------------------------------------------
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("Socket create error!\n");
    exit(1);
  }
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(10000);
  inet_aton("127.0.0.1", &(server_addr.sin_addr));
  bzero(&(server_addr.sin_zero), 8);
  if(bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
     perror("Socket bind error!\n");
     exit(1);
  }
  if(listen(sockfd, 10000) == -1) {
     perror("Socket listen error!\n");
     exit(1);
  }
  printf("Server listening at port 10000\n");
  //------------------------------------------
  sin_size = sizeof(client_addr);

  while(1) {
    newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
    printf("Got connection at %d from %s:%d\n", newsockfd, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    if(newsockfd > 0) {
      if(fork() == 0) {
	print_header(newsockfd);
	exit(0);
      }
    }
    else {
      perror("Error accept");
      exit(1);
    }
  }
  return 0;

}
