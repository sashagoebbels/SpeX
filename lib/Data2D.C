// NMR data base class

#include "Data2D.H"
#include "utils.H"
#include <fftw.h>

// Simple empty constructors

Data2D::Data2D(int d1, int d2)
{
  long i,size;

  AllSize=2*d1*d2*sizeof(float);
  Domain=0;
  Dims[0]=d1-1;
  Dims[1]=d2-1;
  size=d1*d2;
  Data=new fftw_complex *[d1];
  Data[0]=new fftw_complex [size];
  for (i=1; i<d1; i++)
    {
      Data[i]=Data[i-1]+d2;
      memset(Data[i],0,d2*sizeof(fftw_complex));
    }
  plan=fftw2d_create_plan(d1,d2,FFTW_FORWARD,FFTW_ESTIMATE|FFTW_IN_PLACE);
}

// Constructors from file content

Data2D::Data2D(int d1, int d2, char *fname, int file_type)
{
  float *tmp;
  long i,j,size;

  AllSize=2*d1*d2*sizeof(float);
  Domain=0;
  Dims[0]=d1-1;
  Dims[1]=d2-1;
  size=d1*d2;
  Data=new fftw_complex *[d1];
  Data[0]=new fftw_complex [size];
  for (i=1; i<d1; i++)
    {
      Data[i]=Data[i-1]+d2;
    }
  if (file_type == LN_BRUKER)
    tmp=get_bruker(fname,d1*d2*2);
  for (i=0; i<d2; i++)
    for (j=0; j<d1; j++)
      {
	Data[j][i].re=*tmp++;
	Data[j][i].im=*tmp++;
      }
  plan=fftw2d_create_plan(d1,d2,FFTW_FORWARD,FFTW_ESTIMATE|FFTW_IN_PLACE);
}

// Standard destructor
Data2D::~Data2D(void)
{
  if (Data == 0) return;
  delete Data[0];
  delete Data;
}

// Access functions
float Data2D::GetReal(int i, int j)
{
  return Data[i][j].re;
}

float Data2D::GetImag(int i, int j)
{
  return Data[i][j].im;
}

fftw_complex Data2D::GetValue(int i, int j)
{
  return Data[i][j];
}

void Data2D::SetReal(int i, int j, float &val)
{
  Data[i][j].re=val;
}

void Data2D::SetImag(int i, int j, float &val)
{
  Data[i][j].im=val;
}

void Data2D::SetValue(int i, int j, fftw_complex &val)
{
  Data[i][j]=val;
}

// FFT routines
void Data2D::DoFFT(void)
{
  fftwnd_one(plan,&Data[0][0],NULL);
}


// Service routines
void Data2D::RealDump()
{
  for (int i=0; i<=Dims[0]; i++) 
    for (int j=0; j<=Dims[1]; j++)
      printf("%f\n",Data[i][j]);
}

void Data2D::ImagDump()
{
  for (int i=0; i<=Dims[0]; i++) 
    for (int j=0; j<=Dims[1]; j++)
      printf("%f\n",Data[i][j]);
}

