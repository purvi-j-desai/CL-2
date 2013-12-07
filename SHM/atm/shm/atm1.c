#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<string.h>
#define SHMSZ 100
int main()
{
int shmid;
char ch;
key_t key;
key=1234;
//create segment
 if((shmid=shmget(key,SHMSZ,IPC_CREAT|0660))<0)
 {
   perror("shmget");
   exit(1);
 }
char *shm,*s;
//attach the segment created to local address of this process
   if((shm=shmat(shmid,NULL,0))==(char*)-1)
   {
     perror("shmat");
     exit(1);
   }
s=shm;
//now write the data to be read
printf("\nEnter the the total amount in atm");
fgets(s,100,stdin);//read fro standard i/o and store in s i.e shm
printf("\nDo you want to knw the balance:");
scanf("%c",&ch);
if(ch=='y')
{
printf("The balance is:%s",s);
}
return(0);
}
