#include <sys/shm.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <semaphore.h>

sem_t *Sm;
sem_t *M;

int main()
{
  int shmid, ch;
  char *shm, *s;
  int *balance, debit = 0, credit = 0;
  //get shm chunk
  if((shmid = shmget((key_t)1234, sizeof(int), IPC_CREAT|0666)) == -1 && errno != EEXIST) {
    perror("Error");
    exit(1);
  }
  if((shm = shmat(shmid, NULL, 0)) == (char *)-1) {
    perror("Error");
    exit(1);
  }
  printf("Got and attached\n");
  balance = (int *)shm;
  //sem_unlink("/sem4");
  //sem_unlink("/mut1");
  //-------------------------------------
  Sm = sem_open("/sem4", O_CREAT, 0666, 4);
  M = sem_open("/mut1", O_CREAT, 0666, 1);
  //--------------------------------------
  printf("semaphores opened\n");
  if(sem_trywait(Sm) == 0) {
    while(1) {
      printf("1.Credit\n2.Debit\n3.View\n4.Exit\nChoice: ");
      scanf("%d", &ch);
      if(ch == 4) {
	sem_post(Sm);
	break;
      }
      switch(ch) {
      case 1:
 
	sem_wait(M);
	printf("Enter amount to credit: ");
	scanf("%d", &credit);
	*balance += credit;
	printf("New balance: %d\n", *balance);
	sem_post(M);
	break;
      case 2:
	sem_wait(M);
	printf("Enter amount to debit: ");
	scanf("%d", &debit);
	*balance -= debit;
	if(*balance < 0) {
	  *balance += debit;
	  printf("Sorry unable to debit\n");
	  sem_post(M);
	  break;
	}
	printf("New balance: %d\n", *balance);
	sem_post(M);
	break;
      case 3:
	sem_wait(M);
	printf("Current balance: %d\n", *balance);
	sem_post(M);
	break;
      }
    }
  }
  //sem_unlink("/sem4");
  //sem_unlink("/mut1");


  return 0;
}
