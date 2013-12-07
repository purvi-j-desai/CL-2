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

    if (mkfifo("chatServ", CHMOD) == -1)
    {
        printf("chatServ already exists\n");
        return 1;
    }
	if (mkfifo("chatCli", CHMOD) == -1)
    {
        printf("chatServ already exists\n");
        return 1;
    }

    while(strcmp(msg, "bye")!=0)
    {   
    	printf("waiting for client..\n");
	    fifo1 = open("chatServ", O_WRONLY);
	    fifo2 = open("chatCli", O_RDONLY);
        read(fifo2, msg, BUFFERSIZE);
        printf("Message from client: %s\n>>", msg);
        bzero(msg, BUFFERSIZE);
        scanf("%s",msg);
        write(fifo1, msg, BUFFERSIZE);
        close(fifo1);
        close(fifo2);        
    }

    exit(0);
}
