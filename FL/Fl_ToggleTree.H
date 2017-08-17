#ifndef Fl_ToggleTree_H
#define Fl_ToggleTree_H

#include <FL/Fl_ToggleNode.H>
#include <FL/Fl_Tree.H>
#include <FL/Fl_Pixmap.H>

enum Fl_ToggleState{
  FL_TOGGLE_NONE,	
  FL_TOGGLE_OPENED,
  FL_TOGGLE_CLOSED,
  FL_TOGGLE_SELECT,
  FL_TOGGLE_HIT
};

class Fl_ToggleTree:public Fl_Tree {
public:
  void open(Fl_ToggleNode* node);
  void close(Fl_ToggleNode* node);

  Fl_ToggleNode* current(void){
  	return current_;
  }
  Fl_ToggleState state(void){
  	return state_;
  }
protected:
  virtual void draw_node(int depth,int cy,Fl_Node* node);
  int label_offset_;
  int pixmap_offset_;

  Fl_ToggleNode* current_;
  Fl_ToggleState state_;
public:
  static Fl_Pixmap* sOpenIcon;
  static Fl_Pixmap* sClosedIcon;

      
  virtual int handle(int event);
  Fl_ToggleTree(int x,int y,int w,int h);
  void label_offset(int l){
  	label_offset_=l;
  }
  void pixmap_offset(int l){
  	pixmap_offset_=l;
  }
  void selectrange(Fl_ToggleNode* start,Fl_ToggleNode* end,bool add=false);
  void unselect(void){
    selectrange(0,0,0);
  }


  Fl_ToggleNode* selection(void);
};

#endif
