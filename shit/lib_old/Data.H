// NMR data base class header file

#include <string.h>
#include <stdio.h>

class Data
{
  int Dim_no;                // How many dimensions? max is three
  int Domain;                // Which domain? 0-> time, 1-> frequency
  int Dims[3];               // exact dimensions, Dims[0]-> first dimension ..., max is three
  long AllSize;              // over all size in bytes
  float *RealData;           // real part of data
  float *ImagData;           // imaginary part of data
public:
  // Simple empty constructors
  Data(int d1);
  Data(int d1, int d2);
  Data(int d1, int d2, int d3);
  // Constructors from BRUKER file content
  Data(int d1, char *fname);
  Data(int d1, int d2, char *fname);
  Data(int d1, int d2, int d3, char *fname);
  // Access functions
  float GetReal(int i);
  float GetReal(int i, int j);
  float GetReal(int i, int j, int k);
  float GetImag(int i);
  float GetImag(int i, int j);
  float GetImag(int i, int j, int k);
  void SetReal(int i, float &val);
  void SetReal(int i, int j, float &val);
  void SetReal(int i, int j, int k, float &val);
  void SetImag(int i, float &val);
  void SetImag(int i, int j, float &val);
  void SetImag(int i, int j, int k, float &val);
  // Service routines
  void RealDump();
  void ImagDump();
};
