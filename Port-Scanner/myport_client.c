/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "myport.h"
#include <stdlib.h>
#include <string.h>
void
portscanner_1(char *host, char *myhost, int start, int end)
{
	CLIENT *clnt;
	struct output  *result_1;
	struct input  getstatus_1_arg;
	int i = 0;
#ifndef	DEBUG
	clnt = clnt_create (host, portscanner, portver, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	strcpy(getstatus_1_arg.myhost, myhost);
	getstatus_1_arg.start = start;
	getstatus_1_arg.end = end;
	printf("Sending %d, %d\n", start, end);
	result_1 = getstatus_1(&getstatus_1_arg, clnt);
	if (result_1 == (struct output *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	else {
	  printf("Open ports are: \n");
	  for(i = 0; i < result_1->total; i++) {
	    printf("%d\n", result_1->openports[i]);
	  }
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;
	char *myhost;
	int s, e;
	if (argc < 5) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	myhost = argv[2];
	s = atoi(argv[3]);
	e = atoi(argv[4]);
	portscanner_1 (host, myhost, s, e);
exit (0);
}