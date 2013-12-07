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
s=shm;
//read from shm
char *amt;
int amount,debit;
amount=atoi(s);
printf("The amount in the atm is:%d",amount);
if(amount>20)
{
 printf("Enter the amount to debit:");
 //read from terminal
 scanf("%d",&debit);
 amount=amount-debit;
 printf("the amount remaining is %d",amount);
 //stor in shm
 printf("Enter amount left");
 fgets(s,40,stdin);
 
}
/*for(s=shm;*s!='\0';s++)
{
putchar(*s);
}
*/

return(0);
}
