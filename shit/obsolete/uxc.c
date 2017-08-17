/*****************************************
 *       uxc - uxnmr convert             *
 *    (c) 1997 by V.M. Goebbels          *
 *                                       *
 * Usage:                                *
 *  uxc INFILE TD OUTFILE FLAG           *
 *  INFILE: input file to be converted   *
 *  TD: total number of real points      *
 *      = td*dim1*dim2...                *
 *  OUTFILE: resulting output            *
 *  FLAG: = 1 convert to pure data       *
 *        = 2 convert to unform. FORTRAN *
 *        = 3 convert to ascii (sure??)  *
 *****************************************/

#include <stdio.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>

void main(int argc, char **argv)
{
  FILE *fin;
  FILE *fout;
  struct stat sb;
  long td, bytes, n, m, cnt;
  int flag, i;
  int *ip,*ipp;
  float *fl;
  union {
    char ch[4];
    int i;
  } bs;
  char *ca;

  printf("\nUXC - the magic is Broken!\n\n");
  if (argc != 5)
    {
      printf("Wrong number of arguments.\n\n");
      printf("Usage: uxc INFILE TD OUTFILE FLAG\n");
      printf("         INFILE:  input file to be converted\n");
      printf("         TD:      total number of real points\n");
      printf("                  = td*dim1*dim2...\n");
      printf("         OUTFILE: resulting output\n");
      printf("         FLAG:    = 1 convert to pure data\n");
      printf("                  = 2 convert to unform. FORTRAN\n");
      printf("                  = 3 convert to ascii (not recommended!)\n");
      exit(1);
    }
  td=atol(argv[2]);
  flag=atoi(argv[4]);
  n=td/2;
  i=0;
  bytes=sizeof(int)+td*sizeof(int);
  if ((ip=(int *)malloc((unsigned)(td*sizeof(int))))==NULL)
    {
      printf("Unable to allocate memory.\n");
      exit(1);
    }
  if (flag==1) printf("Converting to raw float binary data\n");
  if (flag==2) printf("Converting to unformatted FORTRAN style.\n");
  if (flag==3)
    {
      printf("Converting to ascii data ... shit, you wanted it\n");
      printf("Prepare to blast your hard disk!\n");
    }
  if (stat(argv[1], &sb)==-1)
    {
      printf("Can´t stat file %s\n\n",argv[1]);
      exit(1);
    }
  if (sb.st_size<td*sizeof(int))
    {
      printf("Wrong byte count entered: %d bytes\n",td*sizeof(int));
      printf("            file size is: %d bytes\n",sb.st_size);
      exit(1);
    }
  if ((fin=fopen(argv[1],"r"))==NULL)
    {
      printf("Can´t open file %s for input.\n",argv[1]);
      exit(1);
    }
  if (flag<3)
    {
      if ((fout=fopen(argv[3],"w"))==NULL)
	{
	  printf("Can´t open file %s for output.\n",argv[3]);
	  exit(1);
	}
    }
  else
    {
      if ((fout=fopen(argv[3],"wt"))==NULL)
	{
	  printf("Can´t open file %s for output.\n",argv[3]);
	  exit(1);
	}
    }
  cnt=fread((char *)ip,sizeof(int),td,fin);
  if (cnt!=td)
    {
      printf("Wrong number of bytes read.\n");
      exit(1);
    }
  ca=(char *)ip;
  ipp=(int *)ip;
  for (m=0; m<td; m++)
    {
      bs.ch[3]=*ca++;
      bs.ch[2]=*ca++;
      bs.ch[1]=*ca++;
      bs.ch[0]=*ca++;
      *ipp++=bs.i;
    }
  ca=(char *)ip;
  fl=(float *)ip;
  for (m=0; m<td; m++)
    {
      i=*((int *)ca);
      ca+=sizeof(int);
      *fl++=(float)i;
    }
  fl=(float *)ip;
  printf("--> %f\n",*fl);
  if (flag==1)
    {
      fwrite((char *)ip,sizeof(int),td,fout);
    }
  if (flag==2)
    {
      fwrite((char *)&bytes,sizeof(int),1,fout);
      fwrite((char *)&n,sizeof(int),1,fout);
      fwrite((char *)ip,sizeof(int),td,fout);
      fwrite((char *)&bytes,sizeof(int),1,fout);
    }
  if (flag==3)
    {
      fl=(float *)ip;
      for (m=0; m<n; m+=2)
	{
	  fprintf(fout,"%f %f\n",*fl++,*fl++);
	}
    }
  fclose(fin);
  fclose(fout);
}
