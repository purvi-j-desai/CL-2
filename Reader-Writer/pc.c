#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#define SIZE 10

pthread_mutex_t mutex;
pthread_t tid;
int buffer[SIZE];
int count;
sem_t full,empty;

void *producer(void *param);
void *consumer(void *param);
int removeitm();
void insert(int);
 
 void initialised()
 {
 	pthread_mutex_init(&mutex,NULL);
 	sem_init(&full,0,0);
 	sem_init(&empty,0,SIZE);
 	count=0;
 }
 
 void insert(int item)
 {
 	buffer[count]=item;
 	count++;
 }
 
 int removeitm()
 {
 	return(buffer[--count]);
 }
 
 void *producer(void *param)
 {
 	int item,waittime;
 	while(1)
 	{
 		waittime=rand()%5;
 		sleep(waittime);
 		item=rand()%1000;
 		sem_wait(&empty);
 		pthread_mutex_lock(&mutex);
 		insert(item);
 		printf("\nProducer...%d ",item);
 		pthread_mutex_unlock(&mutex);
		sem_post(&full); 	
 	}
 	
 }
 void *consumer(void *param)
 {
 	int item,waittime;
 	while(1)
 	{
 		waittime=rand()%5;
 		sleep(waittime);
 		sem_wait(&full);
 		pthread_mutex_lock(&mutex);
 		item=removeitm();
 		printf("\nConsumer....%d ",item);
 		pthread_mutex_unlock(&mutex);
 		sem_post(&empty);
 	}
 }
 int main()
 {
 	initialised();
 	pthread_create(&tid,NULL,producer,NULL);
 	pthread_create(&tid,NULL,consumer,NULL);
 	pthread_join(tid,NULL);
	return 0;
 }
