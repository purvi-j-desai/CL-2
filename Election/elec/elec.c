#include <stdio.h>
#include <stdlib.h>
#define max 50

struct proc {
  int priority;
  int isalive;
}P[max];

int n;
int CR;


int alldead()
{
  int i;
  for(i = 0; i < n; i++) {
    if(P[i].isalive)
      break;
  }
  if(i==n)
    return 1;
  return 0;
}

void accept()
{
  int i;
  printf("Enter the no. of processes: ");
  scanf("%d", &n);
  for(i = 0; i < n; i++) {
    P[i].priority = i;
    printf("Enter status: ");
    scanf("%d", &P[i].isalive); 
  }
}

void show()
{
  int i;
  for(i = 0;  i < n; i++) {
    printf("P%d - isalive %d\n", i, P[i].isalive);
  }
}

void bully()
{
  int ch, i, pcrash, gen, flag, new_gen = -1;
  while(1) {
    printf("1.crash\n2.make alive\n3.exit\nchoice: ");
    scanf("%d", &ch);
    if(ch == 3)
      break;
    switch(ch) {
    case 1:
      printf("Enter process id to crash: ");
      scanf("%d", &pcrash);
      if(P[pcrash].isalive != 0) {
	P[pcrash].isalive = 0; //crashed
	if(alldead()) {
	  printf("Alldead\n");
	  break;
	}
	printf("Shall start...\n");  
	if(pcrash == CR) {
	  CR = -1;
	  printf("Enter process id for gen: ");
	  scanf("%d", &gen);
	
	  new_gen = gen;
	  while(1) {
	    flag = 0;
	    for(i = gen+1; i < n; i++) {
	      if(P[i].isalive) {
		printf("Sending msg from %d to %d\n", gen, i);
		flag = 1;
		new_gen = i;
		break;
	      }
	    }
	    if(flag) {
	      printf("New generator: %d\n", new_gen);
	      gen = new_gen;
	    }
	    else
		break;
	  }
	  CR = new_gen;
	  printf("new cr: %d\n", CR);
	}
      }
    case 2:
      break;
    }
  }
}






int main()
{
  int ch, i;
  accept();
  show();
  for(i = n-1; i >= 0  ; i--) {
    if(P[i].isalive)
      break;
  }
  if(i >= 0)
    CR = i;
  else
    printf("All are dead...");
  bully();
  // ring();



  return 0;

}
