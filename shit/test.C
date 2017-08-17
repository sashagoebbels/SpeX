#include <stdio.h>
#include <stdlib.h>
#include "Data2D.H"
#include "utils.H"

int main()
{
  Data2D d;
  fftw_complex t;
  //d=new Data2D(128,141,"ser",LN_BRUKER);
  //printf("%f - %f\n",d->GetReal(0,0),d->GetImag(0,0));
  t=d(0,0);
  printf("%f - %f\n",t.re,t.im);
}
