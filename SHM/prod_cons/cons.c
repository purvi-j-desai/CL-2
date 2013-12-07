#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/shm.h>
#include "myshm.h"
#define shmsz 1024

int shmid;
char *shm, *s;
sem_t *full;
sem_t *empty;
sem_t *M;

int main()
{
  struct buffer *B;
  if((shmid = shmget((key_t)1234, sizeof(struct buffer), IPC_CREAT | 0666)) == -1 && errno != EEXIST) {
    perror("error get: ");
    exit(1);
  }
  if((shm = shmat(shmid, NULL, 0)) == (char *)-1) {
    perror("error attach: ");
    exit(1);
  }
  
  B = (struct buffer *)shm;
  full = sem_open("/full", O_CREAT, 0666, 0);
  M = sem_open("/mut", O_CREAT, 0666, 1);
  empty = sem_open("/emp", O_CREAT, 0666, 10);
  while(1) {
    /* while(B->produced <= 0);
    if(B->produced) {
      printf("Count: %d\n", B->produced);
      printf("Consuming %d\n", B->buff[(B->produced)--]);
      sleep(rand() % 4);
      }*/
    sleep(1);
    sem_wait(full);
    sem_wait(M);
    printf("counsumed: %d, count %d\n", B->buff[(B->produced)], B->produced);
    (B->produced)--;
    sem_post(M);
    sem_post(empty);
  }
  sem_unlink("/full");
  sem_unlink("/mut");
  sem_unlink("/emp");
  if(shmdt(shm) == -1) {
    perror("error");
    exit(1);
  }
  return 0;
}
