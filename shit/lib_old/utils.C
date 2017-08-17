// SpeX low level utilities

#include "utils.H"
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>

#define log_file "error.log"

void error(char *err_text)
{
  FILE *ferr;
  ferr=fopen(log_file,"ra");
  fprintf(ferr,"%s\n",err_text);
  printf("Error: %s\n",err_text);
  fclose(ferr);
  exit(1);
}

void debug(char *debug_text)
{
  FILE *ferr;
  ferr=fopen(log_file,"ra");
  fprintf(ferr,"%s\n",debug_text);
  printf("Debug: %s\n",debug_text);
  fclose(ferr);
  exit(1);
}

