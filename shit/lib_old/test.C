#include <stdlib.h>
#include <stdio.h>
#include "Data.H"

void main()
{
  float r1,i1;
  int i;
  Data d(141,"ser");
  d.RealDump();
  printf("\n");
  d.ImagDump();
  printf("\nDone.\n",r1,i1);
}
