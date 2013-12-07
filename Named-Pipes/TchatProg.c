
/* Write a simple chat program using named pipe */
//Rutvik karve 4232

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>
#include<string.h>

pthread_t readerthread;
pthread_t writerthread;

int fd;

void * reader(){
	
	char buff[100];	
	int no_bytes;
	printf("\nreader thread initialized");
	while(strcmp(buff,"exit")){
		no_bytes = read(fd,buff,100);
		if(no_bytes!=0){
			printf("\nThe other end says: %s",buff);
		}
	}		

}	
void * writer(){

	char buff[100];
	printf("\nwriter thread initialized");
	while(strcmp(buff,"exit")){
		printf("\nI say: ");
		gets(buff);
		write(fd,buff,strlen(buff));
	}

}
int main(){

	//int fd;
	char buff[100];
	if(mkfifo("chatPipe",0666)==0){

		printf("\nFifo created");	
		fd=open("chatPipe",O_RDWR);
		printf("\nFifo opened for RD/WR\n");

		pthread_create(&readerthread,NULL,(void*)&reader,NULL);
		pthread_create(&writerthread,NULL,(void*)&writer,NULL);

		pthread_join(readerthread,NULL);
		pthread_join(writerthread,NULL);
		/*while(strcmp(buff,"exit")){
			
			read(fd,buff,100);
			printf("\nOther end says: %s",buff);
			printf("\nI say: ");
			gets(buff);
			write(fd,buff,100);
		}*/

	}
	else if(fopen("chatPipe","r")){
		fd=open("chatPipe",O_RDWR);
		printf("\nFifo opened for RD/WR\n");
		
		pthread_create(&readerthread,NULL,(void*)&reader,NULL);
		pthread_create(&writerthread,NULL,(void*)&writer,NULL);

		pthread_join(readerthread,NULL);


		pthread_join(writerthread,NULL);

	
	}
	else{
		printf("\nunable to attach to fifo\n");
		return -1;
	}
	return 0;

}
