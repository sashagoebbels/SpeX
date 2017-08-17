#include <stdlib.h>
#include <math.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>

#define v3f(x) glVertex3fv(x)

class spec_box : public Fl_Gl_Window {
  void draw();
public:
  double lasttime;
  int mode;             // mode=2: 2D, mode=3: 3D
  double size;
  double speed;
  spec_box(int x,int y,int w,int h,const char *l=0) : Fl_Gl_Window(x,y,w,h,l) 
    {
      lasttime = 0.0;
    }
};

