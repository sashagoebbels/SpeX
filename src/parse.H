// Header file for command parsing module

#ifndef MODULE_PARSE
#define MODULE_PARSE

#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <String.h>
#include <Regex.h>
#include <iostream.h>
#include <iomanip.h>

#include "lib/utils.H"
#include "lib/Data1D.H"
#include "lib/Data2D.H"
#include "StatusBox.H"
#include <FL/Fl.H>
#include <FL/fl_file_chooser.H>
#include <FL/filename.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>

#define rx_ok 0
#define rx_limlow 1
#define rx_limhigh 2
#define rx_limboth 3
#define rx_exit 4

// Define some alignment flags
#define label_align FL_ALIGN_TOP_LEFT|FL_ALIGN_INSIDE

// These come from main.C
extern Data1D *act1d;
extern Data2D *act2d;
extern Fl_Window *load_window;

struct Parse_Result {
  int result;
  int argument1,argument2;
  char *str_argument;
};

// void load_dialog(String fname);
int  load_wrapper(String fname);
void parse_command(String line, Parse_Result *pr);

#endif MODULE_PARSE
