#include<stdio.h>
#include<semaphore.h>
pthread_mutex_t x;
pthread_t t1[10],t2[10];
sem_t db;
int rc;
void init()
{
	pthread_mutex_init(&x,NULL);
	sem_init(&db,1,1);
	rc=0;
}
void reader()
{
	printf("\nReader trying to enter ");
	pthread_mutex_lock(&x);
	rc++;
	if(rc==1)
		sem_wait(&db);
	printf("\n%d reader inside",rc);
	pthread_mutex_unlock(&x);

	sleep(3);

	pthread_mutex_lock(&x);
	if(rc==0)
		sem_post(&db);
	printf("\n%d Reader leaving",rc--);
	pthread_mutex_unlock(&x);
}
void writer()
{
	printf("\nWriter trying to enter ");
	sem_wait(&db);
	printf("\nWriter inside");
	sleep(3);	
	sem_post(&db);
	printf("\nWriter leaving");
}
void main()
{
	int nr,nw,i,j;
	printf("\nREADER WRITER (READER'S PRIORITY)");
	printf("\n---------------------------------");	
	init();
	printf("\nEnter the number of readers :\t");
	scanf("%d",&nr);	

	printf("Enter the number of writers :\t");
	scanf("%d",&nw);	

	for(i=0;i<nr;i++)
		pthread_create(&t1[i],NULL,reader,NULL);
	
	for(j=0;j<nw;j++)
		pthread_create(&t2[j],NULL,writer,NULL);
	

	for(i=0;i<nr;i++)
		pthread_join(t1[i],NULL);
	
	for(j=0;j<nw;j++)
		pthread_join(t2[j],NULL);
	printf("\n\n");
}
