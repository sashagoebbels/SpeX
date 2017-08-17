// NMR data base class header file

#ifndef MODULE_DATA2D
#define MODULE_DATA2D

#include <string.h>
#include <stdio.h>
#include <fftw.h>

class Data2D
{
  int Domain;                // Which domain? 0-> time, 1-> frequency
  int Dims[2];               // exact dimension
  long AllSize;              // over all size in bytes
  fftw_complex **Data;       // the actual data array
  fftwnd_plan plan;          // FFT plan
public:
  // Simple empty constructor
  Data2D(int d1, int d2);
  // Constructor from BRUKER file content
  Data2D(int d1, int d2,char *fname, int file_type);
  // Standard destructor
  ~Data2D(void);
  // Access functions
  float GetReal(int i, int j);
  float GetImag(int i, int j);
  fftw_complex GetValue(int i, int j);
  void SetReal(int i, int j, float &val);
  void SetImag(int i, int j, float &val);
  void SetValue(int i, int j, fftw_complex &val);
  // FFT routines
  void DoFFT(void);
  // Service routines
  void RealDump();
  void ImagDump();
};

#endif MODULE_DATA2D
