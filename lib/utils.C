// SpeX low level utilities

#include "utils.H"
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>

#define log_file "error.log"

void error(char *err_text)
  // Put error message into log file and exit program
{
  FILE *ferr;
  ferr=fopen(log_file,"ra");
  fprintf(ferr,"%s\n",err_text);
  printf("Error: %s\n",err_text);
  fclose(ferr);
  exit(1);
}

void debug(char *debug_text)
  // Put debug message into log file and resume program
{
  FILE *ferr;
  ferr=fopen(log_file,"ra");
  fprintf(ferr,"%s\n",debug_text);
  printf("Debug: %s\n",debug_text);
  fclose(ferr);
}

float *get_bruker(char *fname, long data_len)
  // fname: file name to be imported
  // data_len: how many float points?
{
  FILE *fin;
  long bytes, n, m, cnt;
  int flag, i;
  int *ip,*ipp;
  float *fl;
  union {
    char ch[4];
    int i;
  } bs;
  char *ca;

  n=data_len/2;
  i=0;
  bytes=sizeof(int)+data_len*sizeof(int);
  if ((ip=(int *)malloc((unsigned)(data_len*sizeof(int))))==NULL)
    debug("get_bruker ! Unable to allocate memory.");
  if ((fin=fopen(fname,"r"))==NULL)
    debug("get_bruker ! Can´t open file for input.");
  cnt=fread((char *)ip,sizeof(int),data_len,fin);
  fclose(fin);
  if (cnt!=data_len)
    debug("get_bruker ! Wrong number of bytes read.");
  ca=(char *)ip;
  ipp=(int *)ip;
  for (m=0; m<data_len; m++)
    {
      bs.ch[3]=*ca++;
      bs.ch[2]=*ca++;
      bs.ch[1]=*ca++;
      bs.ch[0]=*ca++;
      *ipp++=bs.i;
    }
  ca=(char *)ip;
  fl=(float *)ip;
  for (m=0; m<data_len; m++)
    {
      i=*((int *)ca);
      ca+=sizeof(int);
      *fl++=(float)i;
    }
  fl=(float *)ip;
  return fl;
}
