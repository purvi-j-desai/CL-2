//rem. DO NOT DETACH SHM BEFORE USING IT! :P


#include<stdio.h>
#include<sys/shm.h>
#include<sys/types.h>
#define KEY 200

int main(){

	int shmid;
	void *shmAddr;
	int value;
	shmid=shmget(KEY,500,IPC_CREAT | 0666);	//use IPC_CREAT | 0666 for first call, only 0666 for other calls, even between diff. execs. of the prog.
					//if not, we get the errror as shmget failed: No such file or directory
					// keep IPC_CREAT. dosent matter.
	if(shmid==-1){
		perror("shmget failed");
		return(-1);
	}
	shmAddr=shmat(shmid,NULL,0);
	if(*(int*)shmAddr==-1){
		perror("shmat failed");
		return(-2);
	}
				//ithe detach lihila hota me. kiti bavlatpana!!
	
	printf("\nenter a value: ");
	scanf("%d",&value);
	if(value==1){
		printf("\nfirst word of shm: %d",*(int*)(shmAddr));
	}
	else{
	 	(*(int*)(shmAddr))=value;
		scanf("%d",&value);
		printf("\nshared memory first word: %d",*(int*)(shmAddr));
	}

	if(shmdt(shmAddr)==-1){
		perror("shmdt failed");
		return(-3);
	}
	return 0;
}

/*** OUTPUT

bash: /usr/local/lib: is a directory
bash: /usr/local/lib: is a directory
rutvik@Rutvik-PC:~$ cd b4Exam/sharedMem/
rutvik@Rutvik-PC:~/b4Exam/sharedMem$ cd basic/
rutvik@Rutvik-PC:~/b4Exam/sharedMem/basic$ cc client.c
rutvik@Rutvik-PC:~/b4Exam/sharedMem/basic$ ./a.out
shmget failed: No such file or directory
rutvik@Rutvik-PC:~/b4Exam/sharedMem/basic$ cc client.c
rutvik@Rutvik-PC:~/b4Exam/sharedMem/basic$ ./a.out

enter a value: 34

***************************in another tab...(tab2)

bash: /usr/local/lib: is a directory
bash: /usr/local/lib: is a directory
rutvik@Rutvik-PC:~/b4Exam/sharedMem/basic$ ./client.out
bash: ./client.out: No such file or directory
rutvik@Rutvik-PC:~/b4Exam/sharedMem/basic$ ./a.out

enter a value: 32


***************************again in tab1....
1

shared memory first word: 32

***************************and in tab2....
5

shared memory first word: 32
*/

//standalone:

/**TAB 1

rutvik@Rutvik-PC:~$ cd b4Exam/sharedMem/
rutvik@Rutvik-PC:~/b4Exam/sharedMem$ cd basic/
rutvik@Rutvik-PC:~/b4Exam/sharedMem/basic$ cc client.c
rutvik@Rutvik-PC:~/b4Exam/sharedMem/basic$ ./a.out
shmget failed: No such file or directory
rutvik@Rutvik-PC:~/b4Exam/sharedMem/basic$ cc client.c
rutvik@Rutvik-PC:~/b4Exam/sharedMem/basic$ ./a.out

enter a value: 34
1

shared memory first word: 32rutvik@Rutvik-PC:~/b4Exam/sharedMem/basic$ 

**/
/**TAB 2
rutvik@Rutvik-PC:~/b4Exam/sharedMem/basic$ ./client.out
bash: ./client.out: No such file or directory
rutvik@Rutvik-PC:~/b4Exam/sharedMem/basic$ ./a.out

enter a value: 32
5

shared memory first word: 32rutvik@Rutvik-PC:~/b4Exam/sharedMem/basic$ 

**/

