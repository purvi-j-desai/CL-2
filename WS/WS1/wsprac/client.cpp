#include "calc.nsmap"
#include "soapcalcProxy.h"
#include <stdio.h>
#include "iostream"
using namespace std;
int main()
{
  calc c;
  double a,b,res;
  cout<<"Enter 2 numbers: ";
  cin>>a>>b;
  if(c.ns__add(a,b,&res) == SOAP_OK) {
    cout<<"Adition: "<<res<<endl;
  }
  else
    printf("error");
  return 0;
}
