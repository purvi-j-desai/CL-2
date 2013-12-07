#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>   /* for flock */
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define BUFFERSIZE 50

int
main (int argc, char **argv)      
{  
    char inbuf[BUFFERSIZE];
    int fifo, var;

    printf("\n Waiting for a Pipe....\n");

    /* There are *two* ways the open can fail: the pipe doesn't exist
     * yet, *or* it succeeded, but a different writer already opened
     * it but didn't yet remove it.
     */
    while (1)
    {
        while ((fifo = open("namedpipe4", O_RDONLY)) == -1)
        {
            /* Since you didn't specify O_CREAT in the call to open, there
             * is no way that namedpipe4 would have been created by the
             * reader.  If there *is* now a namedpipe4, a remove here
             * would delete the one the writer created!
             */
            sleep(1);
        }    

        /* Get an exclusive lock on the file, failing if we can't get
         * it immediately.  Only one reader will succeed.
         */
        if (flock (fifo, LOCK_EX | LOCK_NB) == 0)
            break;

        /* We lost the race to another reader.  Give up and wait for
         * the next writer.
         */
        close (fifo);
    }

    /* We are definitely the only reader.
     */

    /* *Here* we delete the pipe, now that we've locked it and thus
     * know that we "own" the pipe.  If we delete before locking,
     * there's a race where after we opened the pipe, a different
     * reader also opened, deleted, and locked the file, and a new
     * writer created a new pipe; in that case, we'd be deleting the
     * wrong pipe.
     */
    remove("namedpipe4");

    while ((var = read(fifo, inbuf, BUFFERSIZE)) > 0)
    {    
        printf("Reader PID: %d reads  record: %s\n", getpid(), inbuf);
        /* No need to sleep; we'll consume input as it becomes
         * available.
         */
    }

    close(fifo);
    printf("\n EOF..\n");
    exit(0);
}
