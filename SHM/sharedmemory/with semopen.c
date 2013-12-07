//rem. DO NOT DETACH SHM BEFORE USING IT! :P


#include<stdio.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/types.h>
#include<semaphore.h>
#include<fcntl.h>

#define KEY 200

sem_t * semBufferLock;

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

	semBufferLock=sem_open("/semBufferLock",O_CREAT, 0666, 1);

	
	printf("\nenter a value: ");
	scanf("%d",&value);

	sem_wait(semBufferLock);

	if(value==1){
		printf("\nfirst word of shm: %d",*(int*)(shmAddr));
	}
	else{
	 	(*(int*)(shmAddr))=value;
		scanf("%d",&value);
		printf("\nshared memory first word: %d",*(int*)(shmAddr));
	}

	sem_post(semBufferLock);	

	if(shmdt(shmAddr)==-1){
		perror("shmdt failed");
		return(-3);
	}

	sem_unlink("/semBufferLock");

	return 0;
}

