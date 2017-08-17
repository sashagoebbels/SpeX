// Global includes
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <String.h>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Hor_Value_Slider.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Toggle_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Pixmap.H>
#include <FL/fl_file_chooser.H>
#include <FL/filename.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_ToggleTree.H>
#include <FL/gl.h>
#include <FL/Fl_Roller.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Choice.H>
#include <FL/file_small.xpm>

// Local includes
#include "parse.H"
#include "preferences.H"
#include "color_defs.H"
#include "StatusBox.H"
#include "lib/Data1D.H"
#include "lib/Data2D.H"

// includes for GUI elements
#include "pref_dialog.H"

// test spectrum settings
#define Pi 3.14159265           // just for testing
#define pts 128                 // No. of points
#define max_y 2                 // max. size (-1..+1) for sin
#define scl_y 0.7               // scaling factor
#define ofs_y 1                 // offset (-1..1)->(0..2)

// General settings
#define spex_vers "SpeX V 0.10    (c) 1998 by BlazerSoft"
#define stat_ok 0               // status flag OK
#define stat_error 1            // status flag for error
#define stat_info 2             // status flag for info level
#define stat_font 1             // helvetica bold font for status line

// Settings for screen geometry
#define gen_size_x 1000         // main screen size x
#define gen_size_y 655          // main screen size y
#define tree_width 200          // width of data tree
#define draw_width 750          // width of drawing area     \ these two are reduced by
#define draw_height 520         // Height of drawing area    / 20 pixels for wheel controls
#define inner_width 980         // inner width of status and input line
#define inner_height 540        // inner height of elemnts
#define but_height 30           // height of a button
#define spacer 10               // spacing between elements
#define stat_height 25          // height of status line
#define stat_spacer 5           // spacing between status line and command input line
#define roller_height 180       // height of a roller element
#define roller_width 20         // width of a roller element
#define roller_spacer 5         // spacing between rollers and other elements
#define sub_width 300           // width of a subwindow
#define sub_height 350          // height of a subwindow
#define tab_height 20           // height of the tab buttons
#define sub_spacer 20           // spacing for subwindows
#define but_bar 50              // height of a button bar at the foot of a subwindow
#define sub_label_width 110     // length of a label in subwindow
#define sub_label_height 25     // height of a label in subwindow
#define sub_tab 90              // space between choice widget and left border
#define sub_item_spacing 30     // spacing between items

// Needed Prototypes ... ugly but necessary
void test_exit()
{
  if (fl_ask("Do you really want to quit?")==1) exit(0);
}

void menu_quit_cb(Fl_Widget *, void *)
{
  test_exit();
}

void prefs_cb(Fl_Widget *ob, void *ptr);
void load_file_cb(Fl_Widget *ob, void *ptr);

double points[pts][2];
int zoom1,zoom2;          // left and right zoom limits
pref_type gen_prefs;
Fl_Input *com_line;
Fl_Box *stat_line;
Fl_Scroll *scroll;
Fl_ToggleTree *tree;
Fl_ToggleNode *root_node;
Fl_Roller *ver_roll, *hor_roll;
Fl_Window *prefs_window, *load_window;
Fl_Int_Input *data_len;

Data1D *act1d;
float *act1f,xslval=1.0,yslval=1.0;
float minv,maxv;
Data2D *act2d;

Fl_Menu_Item menutable[] = {
  {"&File",0,0,0,FL_SUBMENU},
  {"&Load", FL_ALT+'l', load_file_cb, 0},
  {"&Close", FL_ALT+'c', 0, 0, FL_MENU_DIVIDER},
  {"&Quit", FL_ALT+'q', menu_quit_cb, 0},
  {0},
  {"&Edit",0,0,0,FL_SUBMENU},
  {"&Preferences", 0, prefs_cb, 0},
  {0},
  {"&Plot",0,0,0,FL_SUBMENU},
  {"&2 D Mode",	FL_ALT+'2', 0},
  {"&3 D Mode",	FL_ALT+'3', 0, 0, FL_MENU_DIVIDER},
  {"&Autoscale", FL_ALT+'a', 0},
  {"Zoom in", FL_ALT+'+', 0},
  {"Zoom out", FL_ALT+'-', 0},
  {"Clear", 0, 0, 0, FL_MENU_DIVIDER},
  {"Options",0, 0},
  {0},
  {0}
};

Fl_Menu_Item back_pull[] = {
  {pref_xcolors[0],0},
  {pref_xcolors[1],0},
  {pref_xcolors[2],0},
  {pref_xcolors[3],0},
  {pref_xcolors[4],0},
  {pref_xcolors[5],0},
  {pref_xcolors[6],0},
  {0}
};

Fl_Menu_Item norm_pull[] = {
  {"black",0},
  {"red",0},
  {"green",0},
  {"blue",0},
  {0}
};

Fl_Menu_Item real_pull[] = {
  {"black",0},
  {"red",0},
  {"green",0},
  {"blue",0},
  {0}
};

Fl_Menu_Item imag_pull[] = {
  {"black",0},
  {"red",0},
  {"green",0},
  {"blue",0},
  {0}
};

Fl_Menu_Item intg_pull[] = {
  {"black",0},
  {"red",0},
  {"green",0},
  {"blue",0},
  {0}
};

Fl_Menu_* menus[6];

// load test spectrum
void load_it()
{
  act1d=new Data1D(2048,"/home/vmg/SpeX/data/fid",LN_BRUKER);
  act1d->DoFFT();
  int n=act1d->GetDim();
  act1f=new float(n);
  act1f=act1d->ExtractData(LN_REAL);
  for (int i=0; i<n; i++)
    {
      if (act1f[i]<minv)
	minv=act1f[i];
      if (act1f[i]>maxv)
	maxv=act1f[i];
    }
  StatusBox::Instance()->status("min: %d max: %d\n",minv,maxv);
}

// Here the GUI magic begins :*)

class spec_box : public Fl_Gl_Window {
  void draw();
public:
  double size;
  double speed;
  spec_box(int x,int y,int w,int h,const char *l=0)
    : Fl_Gl_Window(x,y,w,h,l) {}
};

spec_box *canvas;

void drawspec()
{
  minv=0.0;
  maxv=0.0;
  int n=act1d->GetDim();
  int i;
  for (i=0; i<n; i++)
    {
      if (act1f[i]<minv)
	minv=act1f[i];
      if (act1f[i]>maxv)
	maxv=act1f[i];
    }
  glOrtho(0,float(n),minv,maxv,-1.0,1.0);
  glScalef(xslval,yslval,1);
  glColor3f(0.0,0.0,0.0);
  glBegin(GL_LINE_STRIP);
  StatusBox::Instance()->status("Drawing ...");
  for (i=0; i<n; i++)
    {
      glVertex3f(float(i),act1f[i],0.0);
    }
  glEnd();
  StatusBox::Instance()->status("Done.");
}

void spec_box::draw() {
  int n=act1d->GetDim();
  if (!valid()) {
    valid(1);
    glLoadIdentity();
    glViewport(0,0,w(),h());
    glEnable(GL_DEPTH_TEST);
    glClearColor(pref_fcolors[gen_prefs.back_color][0],pref_fcolors[gen_prefs.back_color][1],
		 pref_fcolors[gen_prefs.back_color][2],0);
    //glFrustum(0,n,minv,maxv,-1,1);
    //glTranslatef(0,0,0);
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //glPushMatrix();
  //glRotatef(float(lasttime*1.6),0,0,1);
  //glRotatef(float(lasttime*4.2),1,0,0);
  //glRotatef(float(lasttime*2.3),0,1,0);
  //glTranslatef(-1.0, 1.2f, -1.5);
  glScalef(xslval,xslval,xslval);
  drawspec();
  //glPopMatrix();
}

// print status with priority prior (which determines the color of the text)
void do_status(int prior, char *stat_text)
{
  stat_line->align(FL_ALIGN_INSIDE|FL_ALIGN_WRAP|FL_ALIGN_LEFT);
  stat_line->labelfont(stat_font);
  if (prior==3) // Error or emergency -> red
    stat_line->labelcolor(FL_RED);
  if (prior==2) // Info -> green
    stat_line->labelcolor(FL_GREEN);
  if (prior==1) // Subroutine status -> blue
    stat_line->labelcolor(FL_BLUE);
  if (prior==0) // All ok -> Black
    stat_line->labelcolor(FL_BLACK);
  stat_line->label(stat_text);
}

void cl_cb(Fl_Widget *ob)
{
  int result;
  int arg1,arg2;
  char stat[80];
  //char cur_com[100];
  String cur_com;
  Parse_Result *p_res=new Parse_Result;
  // parse command line
  //sprintf(cur_com,"%s",((Fl_Input*)ob)->value());
  cur_com=((Fl_Input*)ob)->value();
  parse_command(cur_com,p_res);
  result=p_res->result;
  arg1=p_res->argument1;
  arg2=p_res->argument2;
  // check for the results
  if (result==rx_exit) test_exit();
  if (result==rx_limlow)
    {
      zoom1=arg1;
      sprintf(stat,"Lower limit set to %d",zoom1);
      do_status(1,stat);
    }
  if (result==rx_limhigh)
    {
      zoom2=arg1;
      sprintf(stat,"Upper limit set to %d",zoom2);
      do_status(1,stat);
    }
  if (result==rx_limboth)
    {
      zoom1=arg1;
      zoom2=arg2;
      sprintf(stat,"Limits set from %d to %d",zoom1,zoom2);
      do_status(1,stat);
    }
  // reset line
  ((Fl_Input*)ob)->value("");
}

void quit_cb(Fl_Widget *ob)
{
  test_exit();
}

void menu_cb(Fl_Widget* w, void*) {
  Fl_Menu_* mw = (Fl_Menu_*)w;
  const Fl_Menu_Item* m = mw->mvalue();
  char ttt[30];
  sprintf(ttt,"Menu: %s",m->label());
  if (m)
    {
      do_status(2,ttt);
    }
}

void tree_cb(Fl_Widget* w,void* ptr)
{
  Fl_ToggleTree* t=(Fl_ToggleTree*) w;
}

// Callback for edit->preferences
void prefs_cb(Fl_Widget *ob, void *ptr)
{
  //prefs_window->show();
  preferences_window();
}

void load_file_cb(Fl_Widget *ob, void *ptr)
{
  load_wrapper("");
}

void load_button_cb(Fl_Widget *ob, void *ptr)
{
  load_window->hide();
  StatusBox::Instance()->status("Load button pressed");
}

void cancel_button_cb(Fl_Widget *ob, void *ptr)
{
  load_window->hide();
}

void vroll_cb(Fl_Roller* o, void*) {
  yslval=o->value();
  canvas->redraw();
}

void hroll_cb(Fl_Roller* o, void*) {
  xslval=o->value();
  canvas->redraw();
}

// SpeX main routine
int main(int argc, char** argv) 
{
  int line_cnt;
  load_prefs();
  zoom1=0;
  zoom2=pts;
  load_it();
  Fl_Pixmap* filesmall  =new Fl_Pixmap(file_small);
  // BEGIN main window
  Fl_Double_Window window(gen_size_x,gen_size_y);
  window.label(spex_vers);
  scroll=new Fl_Scroll(spacer,but_height+spacer,tree_width,inner_height);
  scroll->type(Fl_Scroll::VERTICAL_ALWAYS);
  tree=new Fl_ToggleTree(spacer,but_height+spacer,tree_width-scroll->scrollbar.w(),inner_height);
  scroll->end();
  Fl_TreeBuilder tree_build(root_node=new Fl_ToggleNode("Main Data",1,filesmall));
  tree->start(root_node);
  tree_build.sub(root_node=new Fl_ToggleNode("Parameters",1,filesmall));
  Fl_Menu_Bar menubar(0,0,gen_size_x,but_height);
  menubar.menu(menutable);
  menus[0]= &menubar;
  menubar.callback(menu_cb);
  canvas=new spec_box(tree_width+2*spacer,but_height+spacer,draw_width,draw_height,NULL);
  ver_roll=new Fl_Roller(tree_width+draw_width+2*spacer+roller_spacer,
			 but_height+spacer+(inner_height/2)-(roller_height/2),
			 roller_width, roller_height,NULL);
  ver_roll->callback((Fl_Callback*)vroll_cb);
  ver_roll->range(0.1,5.0);
  ver_roll->value(1.0);
  hor_roll=new Fl_Roller(tree_width+(draw_width/2)+2*spacer-(roller_height/2),
			 but_height+draw_height+spacer+roller_spacer,
			 roller_height, roller_width,NULL);
  hor_roll->type(1);
  hor_roll->range(0.1,5.0);
  hor_roll->callback((Fl_Callback*)hroll_cb);
  hor_roll->value(1.0);
  com_line=new Fl_Input(spacer,but_height+2*spacer+inner_height,inner_width,but_height);
  com_line->when(FL_WHEN_ENTER_KEY);
  com_line->callback(cl_cb);
  stat_line=new Fl_Box(FL_FRAME_BOX,spacer,2*but_height+2*spacer+stat_spacer+inner_height,
		       inner_width,stat_height,"Status: ok");
  stat_line->align(FL_ALIGN_INSIDE|FL_ALIGN_WRAP|FL_ALIGN_LEFT);
  stat_line->labelfont(stat_font);
  stat_line->labelcolor(FL_BLACK);
  tree->update_height();
  window.end();
  // END main window
  // BEGIN prefs_window
  //   prefs_window=new Fl_Window(sub_width,sub_height,"Preferences");
  //   {
  //     Fl_Tabs *tabs=new Fl_Tabs(spacer,spacer,sub_width-sub_spacer,sub_height-sub_spacer-but_bar);
  //     { 
  //       Fl_Group *g=new Fl_Group(spacer, spacer+tab_height, sub_width-sub_spacer, 
  // 			       sub_height-sub_spacer-but_bar, "Colors");
  //       line_cnt=(3*spacer)+tab_height;
  //       Fl_Choice *b1=new Fl_Choice(sub_tab+2*spacer,line_cnt,
  // 				  sub_label_width, sub_label_height,"Background: ");
  //       b1->menu(back_pull);
  //       menus[1]= b1;
  //       line_cnt+=sub_item_spacing;
  //       Fl_Box *l=new Fl_Box(FL_NO_BOX,2*spacer,line_cnt,
  // 			   sub_label_width, sub_label_height,"Plot:");
  //       l->align(label_align);
  //       l->labelcolor(FL_BLUE);
  //       line_cnt+=(2*spacer);
  //       Fl_Choice *b2=new Fl_Choice(sub_tab+2*spacer,line_cnt,
  // 				  sub_label_width, sub_label_height,"Magnitude: ");
  //       b2->menu(norm_pull);
  //       menus[2]= b2;
  //       line_cnt+=(3*spacer);
  //       Fl_Choice *b3=new Fl_Choice(sub_tab+2*spacer,line_cnt,
  // 				  sub_label_width, sub_label_height,"Real part: ");
  //       b3->menu(real_pull);
  //       menus[3]= b3;
  //       line_cnt+=(3*spacer);
  //       Fl_Choice *b4=new Fl_Choice(sub_tab+2*spacer,line_cnt,
  // 				  sub_label_width, sub_label_height,"Imag part: ");
  //       b4->menu(imag_pull);
  //       menus[4]= b4;
  //       line_cnt+=(3*spacer);
  //       Fl_Choice *b5=new Fl_Choice(sub_tab+2*spacer,line_cnt,
  // 				  sub_label_width, sub_label_height,"Integral: ");
  //       b5->menu(real_pull);
  //       menus[5]= b5;
  //       g->end();
  //     }
  //     { 
  //       Fl_Group *g=new Fl_Group(spacer, spacer+tab_height, sub_width-sub_spacer, 
  // 			       sub_height-sub_spacer-but_bar, "Paths");
  //       g->end();
  //     }
  //     { 
  //       Fl_Group *g=new Fl_Group(spacer, spacer+tab_height, sub_width-sub_spacer, 
  // 			       sub_height-sub_spacer-but_bar, "Math");
  //       g->end();
  //     }
  //     tabs->end();
  //     Fl_Button *sb=new Fl_Button(2*spacer,sub_height-but_bar+spacer,100,30,"Save");
  //     Fl_Button *cb=new Fl_Button(sub_width-2*spacer-100,sub_height-but_bar+spacer,100,30,"Cancel");
  //   }
  //   prefs_window->hotspot(prefs_window);
  //   prefs_window->set_modal();
  // END prefs_window
  // BEGIN load_window
  load_window=new Fl_Window(300,230,"Load File ...");
  {
    line_cnt=10;
    {
      data_len=new Fl_Int_Input(63,line_cnt,100,20,"Length:");
    }
    line_cnt+=35;
    {
      Fl_Group *b=new Fl_Group(10,line_cnt,280,55,"File type");
      b->box(FL_ENGRAVED_BOX);
      b->labelfont(1);
      b->align(label_align);
    }
    line_cnt+=25;
    {
      Fl_Check_Button *b=new Fl_Check_Button(20,line_cnt,100,20,"Bruker DMX");
      b->type(102);
      b->down_box(FL_DIAMOND_DOWN_BOX);
    }
    {
      Fl_Check_Button *b=new Fl_Check_Button(150,line_cnt,100,20,"Bruker MSL");
      b->type(102);
      b->down_box(FL_DIAMOND_DOWN_BOX);
    }
    line_cnt+=40;
    {
      Fl_Group *b=new Fl_Group(10,line_cnt,280,55,"Dimensionality");
      b->box(FL_ENGRAVED_BOX);
      b->labelfont(1);
      b->align(label_align);
    }
    line_cnt+=25;
    {
      Fl_Check_Button *b=new Fl_Check_Button(20,line_cnt,100,20,"1D");
      b->type(102);
      b->down_box(FL_DIAMOND_DOWN_BOX);
    }
    {
      Fl_Check_Button *b=new Fl_Check_Button(150,line_cnt,100,20,"2D");
      b->type(102);
      b->down_box(FL_DIAMOND_DOWN_BOX);
    }
    line_cnt+=40;
    Fl_Button *sb=new Fl_Button(20,line_cnt,100,30,"Load");
    sb->callback(load_button_cb,0);
    Fl_Button *cb=new Fl_Button(180,line_cnt,100,30,"Cancel");
    cb->callback(cancel_button_cb,0);
  }
  load_window->hotspot(load_window);
  load_window->set_modal();
  // END load_window
  window.show(argc,argv);
  return Fl::run();
}
