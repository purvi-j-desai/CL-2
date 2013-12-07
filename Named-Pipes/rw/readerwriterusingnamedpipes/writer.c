#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>   /* needed for mkfifo */
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define BUFFERSIZE 50
#define CHMOD 0777

int
main (int argc, char **argv)     
{  
    char outbuf[BUFFERSIZE];
    int fifo, j, anzahl;

    if (argc != 2)
    {                            
        printf("Ungültiger Parameter! Bsp.: ./fifow 10\n");  
        return 1;
    }

    anzahl=atoi(argv[1]);

    /* mkfifo fails if the file already exists, which means there's a
     * writer waiting for a reader.  This assures that only one writer
     * will write to the pipe, since it only opens the pipe if it was
     * the one who created it.
     */
    if (mkfifo("namedpipe4", CHMOD) == -1)
    {
        printf("namedpipe4 already exists\n");
        return 1;
    }

    fifo = open("namedpipe4", O_WRONLY);

    for (j = 0; j < anzahl; j++)
    {   
        printf("Writer PID: %d writes record nr. %6d\n", getpid(), j + 1);
        sprintf(outbuf, "Writer PID: %d writes record nr. %6d\n", getpid(), j + 1); 
        write(fifo, outbuf, BUFFERSIZE);       
        remove("namedpipe4");
        sleep(1);
    }

    close(fifo);

    exit(0);
}
