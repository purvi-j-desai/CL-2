#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#define SHMSZ 20

int main()
{
  key_t key;
  int shmid;
  char *shm, *s;
  
  //get shmid
  key = 5678;
  if((shmid = shmget(key, SHMSZ, 0666)) < 0) {
    perror("exit");
    exit(1);
  }
  //attach
  if((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
    perror("exit");
    exit(1);
  }
  
  for(s = shm ; *s != '\0'; s++) {
    putchar(*s);
  }
  putchar('\n');
  
  s = shm;
  *s = '*'; //shared mem tampered..should reflect on the server side

  return 0;
}
