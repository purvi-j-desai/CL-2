#include <stdio.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int wrfd, n = 0, i;
  int retval;
  char buff[256];
  retval = mkfifo("NP1", 0666);
  if(retval == -1 && errno != EEXIST) {
    perror("Error");
    exit(1);
  }
  wrfd = open("NP1", O_WRONLY);
  printf("pipe opened\n");
  //n = atoi(argv[1]);
  for(i = 0; i < 10; i++) {
    printf("Writer: %d wrote rec no. %d\n", getpid(), i+1);
    sprintf(buff, "Writer: %d wrote rec no. %d\n", getpid(), i+1);
    write(wrfd, buff, strlen(buff));
    remove("NP1");
    sleep(1);
  }
  close(wrfd);
  return 0;
}
