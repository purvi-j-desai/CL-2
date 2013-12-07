#include<stdio.h>
#include<stdlib.h>

#define MAX 20

int list[MAX];
int no_proc,CoOrdinator_id;

void display()
{

int i;

printf("\n------List-------");

printf("\nProcess :        ");
for(i=1;i<=no_proc;i++)
{
printf("%2d",i);
}
printf("\nAlive Process :  ");
for(i=1;i<=no_proc;i++)
{
printf("%2d",list[i]);
}
printf("\n\n");
}


void bully()

{int choice=1,crash,activate,genid,i,flag,gen_CoOrdinator;

while(choice<4)
{

printf("\nCurrent Co-Ordinator :%d",CoOrdinator_id);
printf("\n\t1.Crash a Process ");
printf("\n\t2.Activate a Process ");
printf("\n\t3.Display a Process ");
printf("\n\t4.Exit ");
printf("\nEnter the your option:  ");
scanf("%d",&choice);

    switch(choice)
{
  case 1:
         printf("\nEnter a process id to crash : ");
	scanf("%d",& crash);
	list[crash]=0;
	if(crash==CoOrdinator_id)
 {
	printf("\nEnter the generator id: ");
	scanf("%d",& genid);
	printf("\nStarting election algorithm ");
		while(1)
		{
		    flag=0;
	       	    for(i=genid+1;i<=no_proc;i++)
		{ printf("\nSending the election message from %d to %d",genid,i);
		  if(list[i])
		  { flag=1;
		    gen_CoOrdinator=i;
         	  }
       		}
 		if(flag)
		{ genid=gen_CoOrdinator;
		   printf("\nNew Co-Ordinator selected : %d",genid);
		   break;
		}
		else
			break;
		}
	CoOrdinator_id=genid;
}

break;

case 2:

	printf("\nSelect a process to activate : ");
	scanf("%d",&activate);
 	if(list[activate]!=0)
	break;
	list[activate]=1;
	if(activate==no_proc)
	{printf("\nNew Co-Ordinator selected : %d",activate);
	 CoOrdinator_id=activate;
	}
	else
	{printf("\nStarting election algorithm");
	flag=0;
	for(i=activate;i<=no_proc;i++)
	{printf("\nSending ELECTION message from %d to %d",activate,i);
	
	if(list[i])
	{flag=1;
	 gen_CoOrdinator=i;
	}
	}
	if(flag)
	{printf("\n New Co-Ordinator selected : %d",gen_CoOrdinator);
	 CoOrdinator_id=gen_CoOrdinator;

	}
	else
	{ printf("\nAcivated process %d is the new Co-Ordinator  ",activate);
	  CoOrdinator_id=activate;
	}
	}

break;
 
case 3:
		display();
		break;
case 4:	
		break;
}
}
}



void ring()

{	int choice=1,crash,activate,genid,i,flag,temp,message[MAX],mid=0,maxid;

while(choice<4)
	{
	printf("\nCurrent Co-Ordinator :%d",CoOrdinator_id);
	printf("\n1.Crash a Process ");
	printf("\n2.Activate a Process ");
	printf("\n3.Display a Process ");
	printf("\n4.Exit ");
	printf("\nEnter the your option:  ");
	scanf("%d",&choice);
	printf("\n");

  switch(choice)
	{
	  case 1:
           printf("\nEnter a process id to crash : ");
      	   scanf("%d",&crash);
	   list[crash]=0;
	   if(crash==CoOrdinator_id)
 	{
	printf("\nEnter the generator id: ");
	scanf("%d",&genid);
	printf("\nStarting election algorithm ");	
	mid=1;
	message[mid]=genid;
	for(i=(genid+1)%no_proc;i!=genid;i=(i+1)%no_proc)
	{ if(list[i])
            {
		printf("\nSending the election message  to %d",i);
		message[++mid]=i;
	     }
	}
	temp=0;
	for(i=1;i<=mid;i++)
	{if(message[i]>temp)
		 { temp=message[i];
		   maxid=temp;	
		}
	}
	printf("\n New CoOrdinator Selected : %d ",maxid);
        for(i=(genid+1)%no_proc;i!=genid;i=(i+1)%no_proc)
	 { if(list[i])
	  {printf("\nCoOrdinator message delivered to %d",i);
	  }
	 }
	CoOrdinator_id=maxid;
	}
break;

case 2:

	printf("\nSelect a process to activate : ");

	scanf("%d",&activate);
 	if(list[activate]!=0)
	break;
	list[activate]=1;
	if(activate==no_proc)
	{printf("\nNew Co-Ordinator selected : %d",activate);
	 CoOrdinator_id=activate;
	}
	else
	{printf("\nStarting election algorithm");
	mid=1;
	message[mid]=activate;	
	
	for(i=(activate+1)%no_proc;i!=activate;i=(i+1)%no_proc)
	 { if(list[i])
	  {printf("\nMessage Forwareded  to %d",i);
		message[++mid]=i;
                 if(i=CoOrdinator_id)
		 break;
	   }
	}

	temp=0;
	for(i=1;i<=mid;i++)
	{if(message[i]>temp)
	   {temp=message[i];
	     maxid=temp;
	    }
	}
	printf("\n New Co-Ordinator selected : %d",maxid);
	for(i=(genid+1)%no_proc;i!=genid;i=(i+1)%no_proc)
	{if(list[i])
	  { printf("\nCo-Ordinator message delivered to %d ",i);
	  }
	}
	CoOrdinator_id=maxid;
 	}

break;
 
	case 3:
		display();
		break;
	case 4:	
		break;
	}
    }
}


int main()
{
	int i,choice=1;
	printf("\nEnter the number of the processes : ");
	scanf("%d",& no_proc);
	for(i=1;i<=no_proc;i++)
	{printf("\nProcess id = %1d is alive ?(0/1)  : ",i);
	 scanf("%d ",&list[i]);
         }
 	 CoOrdinator_id=no_proc;
	 display();
	while(choice<3)
	{
	      printf("\n---------Election Algorithm----------");
	printf("\n\t1. Bully Algorithm ");
	printf("\n\t2. Ring Algorithm ");
	printf("\n\t3. Exit Algorithm ");
	printf("\nEnter the your choice : ");
	scanf("%d",&choice);
	printf("\n");
	switch(choice)
{
case 1:
 	  bully();break;
case 2:
 	  ring();break;
case 3:
 	  exit(0);break;

}

}
return 0;
}

/*output

[oslab@ws203-021 elect]$ gcc elect.c
[oslab@ws203-021 elect]$ ./a.out

 Enter the number of the processes : 5

Process id = 1 ...... is alive ?(0/1)  :1

Process id = 2 ...... is alive ?(0/1)  :1

Process id = 3 ...... is alive ?(0/1)  :1

Process id = 4 ...... is alive ?(0/1)  :1

Process id = 5 ...... is alive ?(0/1)  :1

------List-------
Process :   1 2 3 4 5
Alive Process :   1 1 1 1 1
---------Election Algorithm----------
 1. Bully Algorithm 
 2. Ring Algorithm 
 3. Exit Algorithm 
Enter the your choice : 1

Current Co-Ordinator :5
 1.Crash a Process 
 2.Activate a Process 
 3.Display a Process 
 4.Exit 
 Enter the your option:  1

Enter a process id to crash : 5

Enter the generator id: 2

Starting election algorithm 
Sending the election message from 2 to 3
Sending the election message from 2 to 4
Sending the election message from 2 to 5
New Co-Ordinator selected : 4
Current Co-Ordinator :4
 1.Crash a Process 
 2.Activate a Process 
 3.Display a Process 
 4.Exit 
 Enter the your option:  2

Select a process to activate : 5

New Co-Ordinator selected : 5
Current Co-Ordinator :5
 1.Crash a Process 
 2.Activate a Process 
 3.Display a Process 
 4.Exit 
 Enter the your option:  3

------List-------
Process :   1 2 3 4 5
Alive Process :   1 1 1 1 1
Current Co-Ordinator :5
 1.Crash a Process 
 2.Activate a Process 
 3.Display a Process 
 4.Exit 
 Enter the your option: 

*/
