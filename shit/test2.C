#include <Complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <iomanip.h>

int main()
{
  Complex a[5];
  Complex *cptr;
  float f[]={3,4};
  double d[2];
  cptr=a;
  d[0]=double(f[0]);
  d[1]=double(f[1]);
  memcpy(cptr,d,2*sizeof(double));
  cout << a[0];
  cout << endl;
  cout << sizeof(a[0]) << endl;
  cout << d[0] << " " << d[1]<< endl;
}
