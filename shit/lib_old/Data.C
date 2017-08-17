// NMR data base class

#include "Data.H"
#include "utils.H"

// Simple empty constructors

// 1D constructor
Data::Data(int d1)
{
  AllSize=2*d1*sizeof(float);
  Domain=0;
  Dim_no=1;
  Dims[0]=d1-1;
  Dims[1]=0;
  Dims[2]=0;
  RealData=new float[d1];
  ImagData=new float[d1];
  memset(RealData,0,d1*sizeof(float));
  memset(ImagData,0,d1*sizeof(float));
}

// 2D constructor
Data::Data(int d1, int d2)
{
  AllSize=2*d1*d2*sizeof(float);
  Domain=0;
  Dim_no=2;
  Dims[0]=d1-1;
  Dims[1]=d2-1;
  Dims[2]=0;
  RealData=new float[d1*d2];
  ImagData=new float[d1*d2];
  memset(RealData,0,d1*d2*sizeof(float));
  memset(ImagData,0,d1*d2*sizeof(float));
}

// 3D constructor
Data::Data(int d1, int d2, int d3)
{
  AllSize=2*d1*d2*d3*sizeof(float);
  Domain=0;
  Dim_no=3;
  Dims[0]=d1-1;
  Dims[1]=d2-1;
  Dims[2]=d3-1;
  RealData=new float[d1*d2*d3];
  ImagData=new float[d1*d2*d3];
  memset(RealData,0,d1*d2*d3*sizeof(float));
  memset(ImagData,0,d1*d2*d3*sizeof(float));
}

// Constructors from BRUKER file content

// 1D constructor
Data::Data(int d1, char *fname)
{
  FILE *fin;
  long cnt,m;
  int *ip,*ipp;
  union {
    char ch[4];
    int i;
  } bs;
  char *ca;
  int i;

  AllSize=2*d1*sizeof(float);
  Domain=0;
  Dim_no=1;
  Dims[0]=d1-1;
  Dims[1]=0;
  Dims[2]=0;
  RealData=new float[d1];
  ImagData=new float[d1];
  ip=new int[2*d1];
  fin=fopen(fname,"rb");
  cnt=fread((char *)ip,sizeof(int),d1,fin);
  fclose(fin);
  if (cnt!=d1) error("! BRUKER 1D constructor ! Wrong byte number read.");
  ca=(char *)ip;
  ipp=(int *)ip;
  for (m=0; m<cnt; m++)
    {
      bs.ch[3]=*ca++;
      bs.ch[2]=*ca++;
      bs.ch[1]=*ca++;
      bs.ch[0]=*ca++;
      *ipp++=bs.i;
    }
  ca=(char *)ip;
  for (m=0; m<(cnt/2); m++)
    {
      i=*((int *)ca);
      ca+=sizeof(int);
      *RealData++=(float)i;
      i=*((int *)ca);
      ca+=sizeof(int);
      *ImagData++=(float)i;
    }
  free(ip);
}

// 2D constructor
Data::Data(int d1, int d2, char *fname)
{
    FILE *fin;
  long cnt,m;
  int *ip,*ipp;
  union {
    char ch[4];
    int i;
  } bs;
  char *ca;
  int i;

  AllSize=2*d1*d2*sizeof(double);
  Domain=0;
  Dim_no=2;
  Dims[0]=d1-1;
  Dims[1]=d2-1;
  Dims[2]=0;
  RealData=new float[d1*d2];
  ImagData=new float[d1*d2];
  ip=new int[2*d1*d2];
  fin=fopen(fname,"rb");
  cnt=fread((char *)ip,sizeof(int),(d1*d2),fin);
  fclose(fin);
  if (cnt!=(d1*d2)) error("! BRUKER 2D constructor ! Wrong byte number read.");
  ca=(char *)ip;
  ipp=(int *)ip;
  for (m=0; m<cnt; m++)
    {
      bs.ch[3]=*ca++;
      bs.ch[2]=*ca++;
      bs.ch[1]=*ca++;
      bs.ch[0]=*ca++;
      *ipp++=bs.i;
    }
  ca=(char *)ip;
  for (m=0; m<(cnt/2); m++)
    {
      i=*((int *)ca);
      ca+=sizeof(int);
      *RealData++=(float)i;
      i=*((int *)ca);
      ca+=sizeof(int);
      *ImagData++=(float)i;
    }
  free(ip);
}

// 3D constructor
Data::Data(int d1, int d2, int d3, char *fname)
{
  FILE *fin;
  long cnt,m;
  int *ip,*ipp;
  union {
    char ch[4];
    int i;
  } bs;
  char *ca;
  int i;

  AllSize=2*d1*d2*d3*sizeof(double);
  Domain=0;
  Dim_no=3;
  Dims[0]=d1-1;
  Dims[1]=d2-1;
  Dims[2]=d3-1;
  RealData=new float[d1*d2*d3];
  ImagData=new float[d1*d2*d3];
  ip=new int[2*d1*d2*d3];
  fin=fopen(fname,"rb");
  cnt=fread((char *)ip,sizeof(int),(d1*d2*d3),fin);
  fclose(fin);
  if (cnt!=(d1*d2*d3)) error("! BRUKER 3D constructor ! Wrong byte number read.");
  ca=(char *)ip;
  ipp=(int *)ip;
  for (m=0; m<cnt; m++)
    {
      bs.ch[3]=*ca++;
      bs.ch[2]=*ca++;
      bs.ch[1]=*ca++;
      bs.ch[0]=*ca++;
      *ipp++=bs.i;
    }
  ca=(char *)ip;
  
  for (m=0; m<(cnt/2); m++)
    {
      i=*((int *)ca);
      ca+=sizeof(int);
      *RealData++=(float)i;
      i=*((int *)ca);
      ca+=sizeof(int);
      *ImagData++=(float)i;
    }
  free(ip);
}

// Access functions
float Data::GetReal(int i)
{
  return RealData[i];
}

float Data::GetReal(int i, int j)
{
  return RealData[i+j*Dims[0]];
}

float Data::GetReal(int i, int j, int k)
{
  return RealData[i+j*Dims[0]+k*Dims[1]*Dims[0]];
}

float Data::GetImag(int i)
{
  return ImagData[i];
}

float Data::GetImag(int i, int j)
{
  return ImagData[i+j*Dims[0]];
}

float Data::GetImag(int i, int j, int k)
{
  return ImagData[i+j*Dims[0]+k*Dims[1]*Dims[0]];
}

void Data::SetReal(int i, float &val)
{
  RealData[i]=val;
}

void Data::SetReal(int i, int j, float &val)
{
  RealData[i+j*Dims[0]]=val;
}

void Data::SetReal(int i, int j, int k, float &val)
{
  RealData[i+j*Dims[0]+k*Dims[1]*Dims[0]]=val;
}

void Data::SetImag(int i, float &val)
{
  ImagData[i]=val;
}

void Data::SetImag(int i, int j, float &val)
{
  ImagData[i+j*Dims[0]]=val;
}

void Data::SetImag(int i, int j, int k, float &val)
{
  ImagData[i+j*Dims[0]+k*Dims[1]*Dims[0]]=val;
}

// Service routines
void Data::RealDump()
{
  if (Dim_no==1)
    for (int i=0; i<=Dims[0]; i++) printf("%f\n",RealData[i]);
}

void Data::ImagDump()
{
  if (Dim_no==1)
    for (int i=0; i<=Dims[0]; i++) printf("%f\n",ImagData[i]);
}

