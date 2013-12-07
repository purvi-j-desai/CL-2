#include "soapH.h"
#include "calc.nsmap"
#include <math.h>

int main(int argc, char **argv)
{
  int m, s;
  struct soap *soap = soap_new();
  m =  soap_bind(soap, NULL, atoi(argv[1]), 100);
  printf("successful bind: master %d\n", m);
  while(1) {
    s = soap_accept(soap);
    printf("received connection from slave: %d\n", s);
    soap_serve(soap);
    soap_end(soap);
  }
  soap_done(soap);
  free(soap);

  return 0;
}

int ns__add(struct soap *soap, int a, int b, int *result)
{
  *result = a+b;
  return (SOAP_OK);
}
