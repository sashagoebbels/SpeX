#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.H"

#define nr 128
#define nc 141
#define pts 36096

void main()
{
  float *r1,**r2,**r3;
  long i,j,k,size;
  size=nr*nc;
  r1=get_bruker("ser",pts);
  r2=new float *[nr];
  r3=new float *[nr];
  r2[0]=new float [size];
  r3[0]=new float [size];
  for (i=1; i<nr; i++)
    {
      r2[i]=r2[i-1]+nc;
      r3[i]=r3[i-1]+nc;
    }
  for (i=0; i<141; i++)
    for (j=0; j<128; j++)
      {
	r2[j][i]=*r1++;
	r3[j][i]=*r1++;
      }
  for (i=0; i<5; i++)
    printf("%f - %f\n",r2[i][0],r3[i][0]);
}
