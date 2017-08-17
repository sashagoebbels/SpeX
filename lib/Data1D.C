// NMR data base class

#include "Data1D.H"
#include "utils.H"
#include <fftw.h>
#include <math.h>

// Simple empty constructors

Data1D::Data1D(int d1)
{
  AllSize=2*d1*sizeof(float);
  Domain=0;
  Dims=d1-1;
  Data=new fftw_complex[d1];
  memset(Data,0,d1*sizeof(fftw_complex));
  plan=fftw_create_plan(d1,FFTW_FORWARD,FFTW_ESTIMATE|FFTW_IN_PLACE);
}

// Constructors from BRUKER file content

Data1D::Data1D(int d1, char *fname, int file_type)
{
  float *tmp;
  long i;

  AllSize=2*d1*sizeof(float);
  Domain=0;
  Dims=d1-1;
  Data=new fftw_complex[d1];
  if (file_type == LN_BRUKER)
    tmp=get_bruker(fname,d1);
  for (i=0; i<d1; i++)
    {
      Data[i].re=*tmp++;
      Data[i].im=*tmp++;
    }
  plan=fftw_create_plan(d1,FFTW_FORWARD,FFTW_ESTIMATE|FFTW_IN_PLACE);
}

// Standard destructor
Data1D::~Data1D(void)
{
  if (Data == 0) return;
  delete Data;
}

// Access functions
float Data1D::GetReal(int i)
{
  return Data[i].re;
}

float Data1D::GetImag(int i)
{
  return Data[i].im;
}

fftw_complex Data1D::GetValue(int i)
{
  return Data[i];
}

void Data1D::SetReal(int i, float &val)
{
  Data[i].re=val;
}

void Data1D::SetImag(int i, float &val)
{
  Data[i].im=val;
}

void Data1D::SetValue(int i, fftw_complex &val)
{
  Data[i]=val;
}

// Recall data for ploting
int Data1D::GetDim()
{
  return Dims+1;
}

float *Data1D::ExtractData(int type)
{
  int i;
  float *XData=new float[Dims+1];

  switch (type)
    {
    case LN_REAL:
      for (i=0; i<=Dims; i++)
	{
	  XData[i]=Data[i].re;
	}
      break;
    case LN_IMAG:
      for (i=0; i<=Dims; i++)
	{
	  XData[i]=Data[i].im;
	}
      break;
    case LN_MAGN:
      for (i=0; i<=Dims; i++)
	{
	  XData[i]=sqrt(Data[i].re*Data[i].re+Data[i].im*Data[i].im);
	}
      break;
    default:
      break;
    }
  return XData;
}

// FFT routines
void Data1D::DoFFT(void)
{
  fftw_one(plan,Data,NULL);
}

// Service routines
void Data1D::RealDump()
{
  for (int i=0; i<=Dims; i++) printf("%f\n",Data[i].re);
}

void Data1D::ImagDump()
{
  for (int i=0; i<=Dims; i++) printf("%f\n",Data[i].im);
}

