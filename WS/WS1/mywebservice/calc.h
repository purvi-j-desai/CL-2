//gsoap ns service name: calc
//gsoap ns service namespace: http://www.mysite.com/calc.wsdl
//gsoap ns service location: http://localhost:3000
//gsoap ns schema namespace: urn:calc
int ns__add(double a, double b, double *result);
int ns__sub(double a, double b, double *result);
int ns__mul(double a, double b, double *result);
int ns__sqrt(double a, double *result);
