#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#define SHMSZ 100
int main()
{
int shmid;
key_t key;
key=1234;
char *shm,*s;
if((shmid=shmget(key,SHMSZ,IPC_CREAT|0660))<0)
{
perror("shget");
exit(1);
}
//attach the process2 to this shm
if((shm=shmat(shmid,NULL,0))==(char*)-1)
{
perror("shget");
exit(1);
}

//read from shm
printf("The process2 is reading from shm");
for(s=shm;*s!='\0';s++)
{
putchar(*s);
}

return(0);
}
