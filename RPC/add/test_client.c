/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "test.h"
#include <stdlib.h>


void display(struct OutputInfo *result)
{
  printf("The sum is: %d\n", result->result);



  return;
}


void
test_program_1(char *host, int a, int b, int c)
{
	CLIENT *clnt;
	struct OutputInfo  *result_1;
	struct InputInfo  addnums_1_arg;
	//assignment
	addnums_1_arg.a = a;
	addnums_1_arg.b = b;
	addnums_1_arg.c = c;

#ifndef	DEBUG
	clnt = clnt_create (host, TEST_PROGRAM, TEST_VERSION, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = addnums_1(&addnums_1_arg, clnt);
	if (result_1 == (struct OutputInfo *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	else {
	  display(result_1);
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;
	int m = 0, n = 0, l = 0;
	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	m = atoi(argv[2]);
	n = atoi(argv[3]);
        l = atoi(argv[4]);
	test_program_1 (host, m, n, l);
	exit (0);
}
