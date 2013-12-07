#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/stat.h>


int t1 =  0, t2 = 0, t3 = 0, flag;
pthread_mutex_t M;
pthread_t P1, P2, P3;

void *increment1(void *arg)
{
  int interval = (int)arg;
  while(1) {
    t1 += interval;
    printf("Count1: %d--------\n", t1);
    
    sleep(2);
  }
}


void *increment2(void *arg)
{
  int interval = (int)arg;
  while(1) {
     t2 += interval;
    printf("--------------Count2: %d--------\n", t2);
   
    sleep(2);
  }
}


void *increment3(void *arg)
{
  int interval = (int)arg;
  while(1) {
     t3 += interval;
    printf("----------------Count3: %d\n", t3);
   
    sleep(2);
  }
}

void *clock1(void *arg)
{
  pthread_t id1;
  pthread_create(&id1, NULL, increment1, arg);
  while(1) {
    sleep(5);
    pthread_mutex_lock(&M);
    printf("P1 recd msg from P%d at time %d\n", flag, t1);
    if(flag == 2 && t2 > t1) 
      t1 = t2 + 1;
    if(flag == 3 && t3 > t1)
      t1 = t3+1;
    flag = 1;
    printf("P1 updated count to %d\n", t1);
    printf("P1 sends msg at %d\n", t1);
    pthread_mutex_unlock(&M);
    sleep(5);
  }
  pthread_join(id1, NULL);
}

void *clock2(void *arg)
{
  pthread_t id2;
  pthread_create(&id2, NULL, increment2, arg);
  while(1) {
    sleep(5);
    pthread_mutex_lock(&M);
    printf("P2 recd msg from P%d at time %d\n", flag, t2);
    if(flag == 1 && t1 > t2) 
      t2 = t1 + 1;
    if(flag == 3 && t3 > t2)
      t2 = t3+1;
    flag = 2;
    printf("P2 updated count to %d\n", t2);
    printf("P2 sends msg at %d\n", t2);
    pthread_mutex_unlock(&M);
    sleep(5);
  }
  pthread_join(id2, NULL);
  pthread_join(P2, NULL);
}

void *clock3(void *arg)
{
  pthread_t id3;
  pthread_create(&id3, NULL, increment3, arg);
  while(1) {
    sleep(5);
    pthread_mutex_lock(&M);
    printf("P3 recd msg from P%d at time %d\n", flag, t3);
    if(flag == 1 && t1 > t3) 
      t3 = t1 + 1;
    if(flag == 2 && t2 > t3)
      t3 = t2+1;
    flag = 3;
    printf("P3 updated count to %d\n", t3);
    printf("P3 sends msg at %d\n", t3);
    pthread_mutex_unlock(&M);
    sleep(5);
  }
  pthread_join(id3, NULL);
  pthread_join(P3, NULL);
}

int main()
{
  pthread_mutex_init(&M, NULL);
  int int1 = 5, int2 = 10, int3 = 8;
  printf("Enter the flag: ");
  scanf("%d", &flag);
  pthread_create(&P1, NULL, clock1, (void *)int1);
  pthread_create(&P2, NULL, clock2, (void *)int2);
  pthread_create(&P3, NULL, clock3, (void *)int3);
  pthread_join(P1, NULL);
  return 0;
}
