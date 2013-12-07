#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>   /* needed for mkfifo */
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define BUFFERSIZE 50
#define CHMOD 0777

int main (int argc, char **argv)     
{  
    char msg[BUFFERSIZE];
    int fifo1, fifo2;

    while(strcmp(msg, "bye")!=0)
    {   
    	printf("opening fifo...\n");
	    fifo1 = open("chatServ", O_RDONLY);
	    fifo2 = open("chatCli", O_WRONLY);
	    printf(">> ");
	    scanf("%s",msg);
        write(fifo2, msg, BUFFERSIZE);
        bzero(msg, BUFFERSIZE);
        read(fifo1, msg, BUFFERSIZE);
        printf("Message from server: %s\n>>", msg);
        close(fifo1);
        close(fifo2);        
    }

    exit(0);
}
