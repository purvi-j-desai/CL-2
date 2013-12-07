#include <stdio.h>
#include<pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/shm.h>
#define shmsz 1024
#include "myshm.h"
int shmid;
char *shm, *s;

sem_t *full;
sem_t *empty;
sem_t *M;
int main()
{
  
  pthread_t producer;
  int running = 1;
  struct buffer *B;
  if((shmid = shmget((key_t)1234, sizeof(struct buffer), IPC_CREAT | 0666 )) == -1 && errno != EEXIST) {
    perror("Error");
    exit(1);
  }
  if((shm = shmat(shmid, NULL, 0)) == (char *)-1) {
    perror("Error");
    exit(1);
  }
  printf("Shared seg acquired and attached\n");
  B = (struct buffer *)shm;
  //pthread_create(&producer, NULL, produce, NULL);
  B->produced = 0;
  full = sem_open("/full", O_CREAT, 0666, 0);
  M = sem_open("/mut", O_CREAT, 0666, 1);
  empty = sem_open("/emp", O_CREAT, 0666, 10);
  while(running) {
    /* if(B->produced >=  10) {
      sleep(1);
      printf("waiting for consumer to consume...\n");
    }
    else {
      sleep(1);
      B->buff[(B->produced)] = rand() %100;
      printf("Produced: %d, count %d\n", B->buff[(B->produced)], B->produced);
      (B->produced)++;
      }*/
    sem_wait(empty);
    sem_wait(M);
    B->buff[(B->produced)] = rand() %100;
    printf("Produced: %d, count %d\n", B->buff[(B->produced)], B->produced);
    (B->produced)++;
    sem_post(M);
    sem_post(full);
    sleep(1);
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
