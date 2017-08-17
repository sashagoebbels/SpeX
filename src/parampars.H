// Header file for parameter parsing module

#ifndef MODULE_PARAM
#define MODULE_PARAM

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream.h>
#include <iomanip.h>
#include <String.h>
#include <Regex.h>
#include "lib/utils.H"

#define rx_ok 0
#define rx_limlow 1
#define rx_limhigh 2
#define rx_limboth 3
#define rx_exit 4

// Bruker parameter file names
#define par1d "/acqu"
#define par2d "/acqu2"
#define par3d "/acqu3"

// Define some alignment flags
#define label_align FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE

struct ParamSet {
  int d1;                // Dim. 1
  int d2;                // Dim. 2
  int d3;                // Dim. 3
  int dims;              // dimensionality of data
  int ns;                // No. of scans
  float swh;             // sweep width in Hz
  float o1;              // frequency offset
  int bytorda;           // byte order
  String pp;             // name of pulse program
  String gp;             // name of gradient program
  int parmode;           // parameter mode
};

ParamSet *parse_param_files_bruker(String fpath);

#endif MODULE_PARAM
