#include "calc.nsmap"
#include "soapcalcProxy.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
int main()
{
  calc c;
  int ch;
  double a,b,result;
  cout<<"Enter operation\n";
  cout<<"1.ADD\n2.SUB\n3.MUL\n4.SQRT\nChoice: ";
  cin>>ch;
  switch(ch) {
  case 1:
    cin>>a>>b;
    if(c.ns__add(a,b,&result) == SOAP_OK)
      cout<<"Answer :"<<result<<endl;
    else 
      soap_print_fault(c.soap, stderr);
    break;
  case 2:
    cin>>a>>b;
    if(c.ns__sub(a,b,&result) == SOAP_OK)
      cout<<"Answer :"<<result<<endl;
    else 
      soap_print_fault(c.soap, stderr);
    break;
  case 3:
    cin>>a>>b;
    if(c.ns__mul(a,b,&result) == SOAP_OK)
      cout<<"Answer :"<<result<<endl;
    else 
      soap_print_fault(c.soap, stderr);
    break;
  case 4:
    cin>>a>>b;
    if(c.ns__sqrt(a, &result) == SOAP_OK)
      cout<<"Answer :"<<result<<endl;
    else 
      soap_print_fault(c.soap, stderr);
    break;
  
  }
  
  return(0);
}
