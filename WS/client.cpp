#include "soapcalcProxy.h"
#include "calc.nsmap"
#include "strings.h"
#include "iostream"
using namespace std;


int main()
{
  calc c;
  int x, y, n;
  cout<<"Enter 2 numbers to add:";
  cin>>x>>y;
  if(c.ns__add(x, y, &n) == SOAP_OK) {
    cout<<"Addition"<<": "<<n<<endl;
  }
  return 0;
}
