#include "soapH.h"
#include "calc.nsmap"
#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
  int s, m, n;
  struct soap *soap = soap_new();
  m = soap_bind(soap, NULL, atoi(argv[1]), 100);
  printf("Master bound at %d\n", m);
  while(1) {
    s = soap_accept(soap);
    printf("Got connection at %d\n", s);
    soap_serve(soap);
    soap_end(soap);
  }
  soap_done(soap);
  free(soap);
  return 0;
}

int ns__add(struct soap *soap, double a, double b, double *res)
{
  *res = a+b;
  return SOAP_OK;
}
