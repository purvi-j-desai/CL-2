/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "ES.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <pthread.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

void *runbaby(void *arg)
{
  int newsockfd = (int)arg;
  char buff[256] = "\0";
  while(1) {
    buff[recv(newsockfd, buff, 256, 0)] = '\0';
    printf("Recd at server: %s\n", buff);
    send(newsockfd, buff, strlen(buff), 0);
  }
}


void *
serverprocess_1_svc(struct input *argp, struct svc_req *rqstp)
{
	static char *result;
	int sockfd, newsockfd, sin_size;
	pthread_t P1;
	struct sockaddr_in server_addr, client_addr;
	char cmd[100] = "\0";
	strcpy(cmd, "echo ");
	strcat(cmd, argp->text);
	system(cmd);
	result = (char *) malloc ( 256 );
	printf("Got text %s\n", argp->text);
	//-------------------------------------
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//--------------------------------------
	server_addr.sin_port = htons(3000);
	inet_aton("127.0.0.1", &(server_addr.sin_addr));
	server_addr.sin_family = AF_INET;
	bzero(&(server_addr.sin_zero), 8);
	//--------------------------------------
	printf("Bind %d\n",bind(sockfd, (struct sockaddr*)(&server_addr), sizeof(server_addr)));
	printf("listen %d\n",listen(sockfd, 25));
	sin_size = sizeof(struct sockaddr);
	//--------------------------------------

	printf("Listening....\n");
	while(1) {
	  newsockfd = accept(sockfd, (struct sockaddr *)(&client_addr), &(sin_size));
	  printf("Got connection at %d\n", newsockfd);
	  pthread_create(&P1, NULL, runbaby, (void *)newsockfd);
	  pthread_detach(P1);
	}
	close(sockfd);
	strcpy(result, argp->text);
	return (void *) &result;
}
