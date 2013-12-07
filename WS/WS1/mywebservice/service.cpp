#include "soapH.h"
#include "calc.nsmap"
#include <stdio.h>
#include <math.h>
int main(int agrc, char **argv)
{
  struct soap *soap = soap_new();
  int m,n,s;
  m = soap_bind(soap, NULL, atoi(argv[1]), 100);
  printf("Successful: master %d\n", m);
  while(1) {
    s = soap_accept(soap);
    printf("Got slave connection %d\n", s);
    soap_serve(soap);
    soap_end(soap);
  }
  soap_done(soap);
  free(soap);
  return 0;
}

int ns__add(struct soap *soap, double a, double b, double *result)
{
  *result = a + b;
  return SOAP_OK;
}
int ns__sub(struct soap *soap, double a, double b, double *result)
{
  *result = a-b;
  return SOAP_OK;
}
int ns__mul(struct soap *soap, double a, double b, double *result)
{
  *result = a*b;
  return SOAP_OK;
}
int ns__sqrt(struct soap *soap, double a, double *result)
{
  *result = sqrt(a);
  return SOAP_OK;
}
