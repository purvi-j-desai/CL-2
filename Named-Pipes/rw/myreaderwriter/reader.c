#include <stdio.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>


int main()
{
  int rdfd, n;
  char buff[256];
  while(1) {
    while((rdfd = open("NP1", O_RDONLY)) == -1) {
      printf("Cannot read yet \n");
      sleep(1);
    }
    if(flock(rdfd, LOCK_EX | LOCK_NB)  == 0) 
      break;
    close(rdfd);
  }
  remove("NP1");
  while((n = read(rdfd, buff, 256)) > 0) {
    buff[n] = '\0';
    printf("Read buffer %s\n", buff);
  }
  close(rdfd);
  return 0;
}
