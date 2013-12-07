//server.c
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "chatprog.h"

int main()
{
  int rdfd, wrfd;
  char buff[MAX];
  //create named pipes if not created
  if(mkfifo(NP1, 0666) == -1 && errno != EEXIST) {
    perror("Error creating pipe");
    exit(1);
  }
  if(mkfifo(NP2, 0666) == -1 && errno != EEXIST) {
    perror("Error creating pipe");
    exit(1);
  }
  //open NP1 for readonly
  rdfd = open(NP1, O_RDONLY);
  //open NP2 for writeonly
  wrfd = open(NP2, O_WRONLY);
  while(1) {
    //read from NP1 and output to stdout
    buff[read(rdfd, buff, MAX)] = '\0';
    if(strcmp(buff, "quit"))
      printf("Client: %s\n", buff);
    else 
      break;
  
    //write back to the server
    printf("Me: ");
    strcpy(buff, "\0");
    gets(buff);
    write(wrfd, buff, strlen(buff));
    if(strcmp(buff, "quit") == 0)
      break;
  }
  return 0;
}
