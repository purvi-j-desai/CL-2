#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMSZ 20

int main()
{
  int shmid;
  char *shm, *s, c;
  key_t key;
  key  = 5678;
  // create the segment
  if((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
    perror(" you are so doomed!");
    exit(1);
  }
  //attach the segment
  if((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
    perror("You are so doomed");
    exit(1);
  }
  //shm is the shared seg address
  s = shm;
  for(c='a'; c<='z'; c++) {
    *s++ = c;
  }
  *s = '\0';
  while(*shm != '*') {
    sleep(1);
  }
  printf("Who changed me ?!?!\n");
  return 0;
}
