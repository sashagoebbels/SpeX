#include "parampars.H"

ParamSet *parse_param_files_bruker(String fpath)
{
  ParamSet *indata=new ParamSet;
  Regex Delims="=";
  int num_words,indims=1;
  String fname=fpath;
  String in_line;
  String Words[3],Hstr;
  // first dim parameter file
  fname+=par1d;
  ifstream *in_file=new ifstream((const char*)fname,ios::in);
  while(*in_file>>in_line)
    {
      if (in_line.contains("$TD=")>0)
	{
	  if(num_words=split(in_line,Words,3,Delims)>1)
	    indata->d1=atoi((const char*)Words[1]);
	}
      if (in_line.contains("$NS=")>0)
	{
	  if(num_words=split(in_line,Words,3,Delims)>1)
	    indata->ns=atoi((const char*)Words[1]);
	}
      if (in_line.contains("$SW_h=")>0)
	{
	  if(num_words=split(in_line,Words,3,Delims)>1)
	    indata->swh=atof((const char*)Words[1]);
	}
      if (in_line.contains("$O1=")>0)
	{
	  if(num_words=split(in_line,Words,3,Delims)>1)
	    indata->o1=atof((const char*)Words[1]);
	}
      if (in_line.contains("$BYTORDA=")>0)
	{
	  if(num_words=split(in_line,Words,3,Delims)>1)
	    indata->bytorda=atoi((const char*)Words[1]);
	}
      if (in_line.contains("$PULPROG=")>0)
	{
	  if(num_words=split(in_line,Words,3,Delims)>1)
	    {
	      Hstr=Words[1].after("<");
	      indata->pp=Hstr.before(">");
	    }
	}
      if (in_line.contains("$GRDPROG=")>0)
	{
	  if(num_words=split(in_line,Words,3,Delims)>1)
	    {
	      Hstr=Words[1].after("<");
	      indata->gp=Hstr.before(">");
	    }
	}
      if (in_line.contains("$PARMODE=")>0)
	{
	  if(num_words=split(in_line,Words,3,Delims)>1)
	    indata->parmode=atoi((const char*)Words[1]);
	}
    }
  delete in_file;
  // second dim parameter file
  fname=fpath;
  fname+=par2d;
  in_file=new ifstream((const char*)fname,ios::in);
  if (*in_file!=NULL)
    {
      indims++;
      while(*in_file>>in_line)
	{
	  if (in_line.contains("$TD=")>0)
	    {
	      if(num_words=split(in_line,Words,3,Delims)>1)
		indata->d2=atoi((const char*)Words[1]);
	    }
	}
      delete in_file;
    }
  else
    indata->d2=0;
  // third dim parameter file
  if (indims>1)
    {
      fname=fpath;
      fname+=par3d;
      in_file=new ifstream((const char*)fname,ios::in);      
      if (*in_file!=NULL)
	{
	  indims++;
	  while(*in_file>>in_line)
	    {
	      if (in_line.contains("$TD=")>0)
		{
		  if(num_words=split(in_line,Words,3,Delims)>1)
		    indata->d3=atoi((const char*)Words[1]);
		}
	    }
	  delete in_file;
	}
    }
  else
    indata->d3=0;      
  // return results
  return indata;
}
