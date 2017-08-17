// NMR data base class header file

#ifndef MODULE_DATA1D
#define MODULE_DATA1D

#include <string.h>
#include <stdio.h>
#include <fftw.h>

class Data1D
{
  int Domain;                // Which domain? 0-> time, 1-> frequency
  int Dims;                  // exact dimension
  long AllSize;              // over all size in bytes
  fftw_complex *Data;        // the actual data array
  fftw_plan plan;            // fft plan
public:
  // Simple empty constructor
  Data1D(int d1);
  // Constructor from file content
  Data1D(int d1, char *fname, int file_type);
  // Standard destructor
  ~Data1D(void);
  // Access functions
  float GetReal(int i);
  float GetImag(int i);
  fftw_complex GetValue(int i);
  void SetReal(int i, float &val);
  void SetImag(int i, float &val);
  void SetValue(int i, fftw_complex &val);
  // Recall data for ploting
  int GetDim();
  float *ExtractData(int type);
  // FFT routines
  void DoFFT(void);
  // Service routines
  void RealDump();
  void ImagDump();
};

#endif MODULE_DATA1D
