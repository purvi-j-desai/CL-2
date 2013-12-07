/* soapcalcProxy.h
   Generated by gSOAP 2.8.3 from calc.h

Copyright(C) 2000-2011, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapcalcProxy_H
#define soapcalcProxy_H
#include "soapH.h"
class calc
{   public:
	/// Runtime engine context allocated in constructor
	struct soap *soap;
	/// Endpoint URL of service 'calc' (change as needed)
	const char *endpoint;
	/// Constructor allocates soap engine context, sets default endpoint URL, and sets namespace mapping table
	calc()
	{ soap = soap_new(); endpoint = "http://localhost:3000"; if (soap && !soap->namespaces) { static const struct Namespace namespaces[] = 
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns", "urn:calc", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap->namespaces = namespaces; } };
	/// Destructor frees deserialized data and soap engine context
	virtual ~calc() { if (soap) { soap_destroy(soap); soap_end(soap); soap_free(soap); } };
	/// Invoke 'add' of service 'calc' and return error code (or SOAP_OK)
	virtual int ns__add(double a, double b, double *result) { return soap ? soap_call_ns__add(soap, endpoint, NULL, a, b, result) : SOAP_EOM; };
	/// Invoke 'sub' of service 'calc' and return error code (or SOAP_OK)
	virtual int ns__sub(double a, double b, double *result) { return soap ? soap_call_ns__sub(soap, endpoint, NULL, a, b, result) : SOAP_EOM; };
	/// Invoke 'mul' of service 'calc' and return error code (or SOAP_OK)
	virtual int ns__mul(double a, double b, double *result) { return soap ? soap_call_ns__mul(soap, endpoint, NULL, a, b, result) : SOAP_EOM; };
	/// Invoke 'sqrt' of service 'calc' and return error code (or SOAP_OK)
	virtual int ns__sqrt(double a, double *result) { return soap ? soap_call_ns__sqrt(soap, endpoint, NULL, a, result) : SOAP_EOM; };
};
#endif
