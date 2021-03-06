/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "sort.h"


void sortprog_1(char *host, int n, float array[])
{
	CLIENT *clnt;
	struct output  *result_1;
	struct input  sort_1_arg;
	int i = 0;
#ifndef	DEBUG
	clnt = clnt_create (host, SORTPROG, SORTVERSION, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	//-------------------------------------
	printf("The original array is :\n");
	sort_1_arg.a[0] = n;
	for(i = 0; i < n; i++) {
	  printf ("%f ", array[i]);
	  sort_1_arg.a[i+1] = array[i];
	}
	result_1 = sort_1(&sort_1_arg, clnt);
	if (result_1 == (struct output *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	else {
	  printf("The final sorted array is:\n");
	  for(i = 0; i<n; i++) {
	    printf("%f ", result_1->a[i]);
	  }
	}
	//------------------------------------
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;
	
	int n = 0;
	float array[20];
	int myaccept(float array[]);
	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	n = myaccept(array);
	sortprog_1 (host, n, array);
	exit (0);
}

int myaccept(float array[])
{
  int n = 0, i = 0;
  printf("Enter the no. of numbers to sort");
  scanf("%d", &n);
  for(i = 0; i < n; i++) {
    scanf("%f", &array[i]);
  }
  return n;
}
