/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "test.h"

struct OutputInfo *
addnums_1_svc(struct InputInfo *argp, struct svc_req *rqstp)
{
	static struct OutputInfo  result;
	printf("Connection done!!\n");
	result.result = argp->a + argp->b + argp->c;

	return &result;
}
