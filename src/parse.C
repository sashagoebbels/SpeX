// Command parsing module

#include "parse.H"

/* void load_dialog(String fname)
   {
   load_window->show();
   } */

int load_wrapper(String fname)
{
  char *lfn=new char(100);
  char *lfn2=new char(100);
  char *cpath;
  String full_name,file_name;
  int result=0,f_valid=0;
  
  cpath=getcwd(NULL,0);
  full_name=cpath;
  full_name+="/";
  // was it called with a valid file name?
  if (fname.length()==0)
    {
      lfn=fl_file_chooser("Select a file to load",NULL,NULL);
      file_name=lfn;
      if (file_name.length()>0)
	{
	  full_name+=file_name;
	  f_valid=1;
	}
    }
  else
    {
      full_name+=fname;
      f_valid=1;
    }
  // so query some parameters
  if (f_valid)
    {
      load_window->show();
      //load_dialog(full_name);
    }
  return result;
}

void parse_command(String line, Parse_Result *pr)
{
  int result=rx_ok,meta;
  String argu[5];
  // regular expressions for the commands
  Regex rx_quit="^quit$";
  Regex rx_load="^load";
  Regex rx_limit="^limit";
  // parse the input line
  if (line.contains(rx_quit)>0)
    result=rx_exit;
  if (line.contains(rx_load)>0)
    {
      meta=split(line,argu,5,RXwhite);
      if (load_wrapper(argu[1])!=0)
	error("! Parse Command ! Error opening file.");
    }
  pr->result=result;
}
