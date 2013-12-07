/* Write a simple chat program using named pipe */
//Rutvik karve 4232

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(){

	int fd;
	char buff[100];
	if(mkfifo("/home/oslab/chatPipe",0666 )==0){

		printf("\nFifo created");	
		fd=open("/home/oslab/chatPipe",O_RDWR);	
//		fd2=open("/home/oslab/chatPipe2",O_RDWR);
		printf("\nFifo opened for RD/WR\n");
		while(strcmp(buff,"exit")){
			
			read(fd,buff,100);
			printf("\nOther end says: %s",buff);
			printf("\nI say: ");
			gets(buff);
			write(fd,buff,100);
		}

	}
	else if(fopen("/home/oslab/chatPipe","r")){
		fd=open("/home/oslab/chatPipe",O_RDWR);
		printf("\nFifo opened for RD/WR\n");
		while(strcmp(buff,"exit")){
			
			printf("\nI say: ");
			gets(buff);
			write(fd,buff,100);
			read(fd,buff,100);
			printf("\nOther end says: %s",buff);
		}
	}
	else{
		printf("\nunable to attach to fifo");
		return -1;
	}
	return 0;

}
