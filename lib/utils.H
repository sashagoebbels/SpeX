// SpeX low level utilities

#include <stdio.h>
#include <stdlib.h>

// define some possible NMR data file types for import
#define LN_BRUKER 0
#define LN_VARIAN 1
#define LN_JEOL 2

// define types of recall data
#define LN_REAL 0
#define LN_IMAG 1
#define LN_MAGN 2

// define states of data (data domain)
#define LN_TIME 0
#define LN_FREQ 1

void error(char *err_text);
void debug(char *debug_text);
float *get_bruker(char *fname, long data_len);
