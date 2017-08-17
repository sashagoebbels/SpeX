#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "preferences.H"
#include "lib/utils.H"

// this function reads in the preferences file
void load_prefs(void)
{
  FILE *prefs;
  char *in_line, *tokenizer, *tok_label, *tok_item, *tail;
  in_line=new char[81];
  tokenizer=new char[81];
  tok_label=new char[81];
  tok_item=new char[81];
  tail=new char[81];
  if ((prefs=fopen(preferences_file,"r"))==NULL)
      {
	error("load_prefs ! Can´t open config file.");
      }
  regex_t *pr_comm=new regex_t;
  regex_t *pr_back=new regex_t;
  regex_t *pr_norm=new regex_t;
  regex_t *pr_real=new regex_t;
  regex_t *pr_imag=new regex_t;
  regex_t *pr_intg=new regex_t;
  if (regcomp(pr_comm,"^#",0)!=0)
    error("! load_prefs ! Error in comm regex.");
  if (regcomp(pr_back,"^back$",0)!=0)
    error("! load_prefs ! Error in back regex.");
  if (regcomp(pr_norm,"^norm$",0)!=0)
    error("! load_prefs ! Error in norm regex.");
  if (regcomp(pr_real,"^real$",0)!=0)
    error("! load_prefs ! Error in real regex.");
  if (regcomp(pr_imag,"^imag$",0)!=0)
    error("! load_prefs ! Error in imag regex.");
  if (regcomp(pr_intg,"^intg$",0)!=0)
    error("! load_prefs ! Error in intg regex.");
  while(!feof(prefs))
    {
      fgets(in_line,80,prefs);
      // check for comment lines
      if (regexec(pr_comm,in_line,0,NULL,0)!=0)
	{
	  strcpy(tokenizer,in_line);
	  tok_label=strtok(tokenizer," ");
	  tok_item=strtok(NULL," ");
	  if (regexec(pr_back,tok_label,0,NULL,0)==0)
	    gen_prefs.back_color=int(strtol(tok_item,&tail,0));
	  if (regexec(pr_norm,tok_label,0,NULL,0)==0)
	    gen_prefs.norm_color=int(strtol(tok_item,&tail,0));
	  if (regexec(pr_real,tok_label,0,NULL,0)==0)
	    gen_prefs.real_color=int(strtol(tok_item,&tail,0));
	  if (regexec(pr_imag,tok_label,0,NULL,0)==0)
	    gen_prefs.imag_color=int(strtol(tok_item,&tail,0));
	  if (regexec(pr_intg,tok_label,0,NULL,0)==0)
	    gen_prefs.intg_color=int(strtol(tok_item,&tail,0));
	}
    }
};

void save_prefs(void)
{

};
