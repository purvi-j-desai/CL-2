#include <stdio.h>
#include <pthread.h>
#include <sys/stat.h>

pthread_t P1, P2, P3;
int t1 = 0, t2 = 0, t3 = 0;
pthread_mutex_t M;
int flag;

void *inc_t1(void *interval)
{
  while(1) {
    sleep(2);
    t1 += (int)interval;
    printf("Counter 1: %d----------------------------------------------\n", t1);
  }
}

void *inc_t2(void *interval)
{
  while(1) {
    sleep(2);
    t2 += (int)interval;
    printf("-------------------------Counter 2: %d----------------------\n", t2);
  }
}

void *inc_t3(void *interval)
{
  while(1) {
    sleep(2);
    t3 += (int)interval;
    printf("------------------------------------------------Counter 3: %d\n", t3);
  }
}

//-----------------------------------------------------
void *clock1(void *interval)
{
  pthread_t id1;
  pthread_create(&id1, NULL, inc_t1, interval);
  while(1) {
    sleep(5);
    pthread_mutex_lock(&M);
    printf("P1 received msg from P%d at interval %d\n", flag, t1);
    if(flag == 2 && t2 > t1)
      t1 = t2 + 1;
    else if(flag ==3 && t3 > t1)
      t1 = t3 + 1;
    flag = 1;
    printf("P1 updated its count to %d\n", t1);
    printf("P1 sends msg at interval %d\n", t1);
    pthread_mutex_unlock(&M);
  }
  pthread_join(id1, NULL);
}
//-------------------------------------------------------
void *clock2(void *interval)
{
  pthread_t id2;
  pthread_create(&id2, NULL, inc_t2, interval);
  while(1) {
    sleep(5);
    pthread_mutex_lock(&M);
    printf("P2 received msg from P%d at interval %d\n", flag, t2);
    if(flag == 1 && t1 > t2)
      t2 = t1 + 1;
    else if(flag ==3 && t3 > t2)
      t2 = t3 + 1;
    flag = 2;
    printf("P2 updated its count to %d\n", t2);
    printf("P2 sends msg at interval %d\n", t2);
    pthread_mutex_unlock(&M);
    sleep(5);
  }
  pthread_join(id2, NULL);
  pthread_join(P2, NULL);
  
}
//-------------------------------------------------------
void *clock3(void *interval)
{
  pthread_t id3;
  pthread_create(&id3, NULL, inc_t3, interval);
  while(1) {
    sleep(5);
    pthread_mutex_lock(&M);
    printf("P3 received msg from P%d at interval %d\n", flag, t3);
    if(flag == 2 && t2 > t3)
      t3 = t2 + 1;
    else if(flag == 1 && t1 > t3)
      t3 = t1 + 1;
    flag = 3;
    printf("P3 updated its count to %d\n", t3);
    printf("P3 sends msg at interval %d\n", t3);
    pthread_mutex_unlock(&M);
    sleep(3);
  }
  pthread_join(id3, NULL);
  pthread_join(P3, NULL);
}



int main()
{
  pthread_mutex_init(&M, NULL);
  int int1 = 5, int2 = 10, int3 = 8;
  printf("Enter start process: (1,2,3):- ");
  scanf("%d", &flag);
  pthread_create(&P1, NULL, clock1, (void *)int1);
  pthread_create(&P2, NULL, clock2, (void *)int2);
  pthread_create(&P3, NULL, clock3, (void *)int3);
  pthread_join(P1, NULL);
  return 0;
}
