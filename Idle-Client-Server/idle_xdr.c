/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "idle.h"

bool_t
xdr_input (XDR *xdrs, input *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->m))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->n))
		 return FALSE;
	return TRUE;
}
