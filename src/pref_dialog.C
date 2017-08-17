Fl_Window *pref_win;

int pref_win_open;

Fl_Window* create_preferences()
{
  Fl_Window *w;
  {
    Fl_Window *o=pref_win=w=new Fl_Window(sub_width,sub_height,"Preferences");
    {
      Fl_Tabs *tabs=new Fl_Tabs(spacer,spacer,sub_width-sub_spacer,sub_height-sub_spacer-but_bar);
      { 
	Fl_Group *g=new Fl_Group(spacer, spacer+tab_height, sub_width-sub_spacer, 
				 sub_height-sub_spacer-but_bar, "Colors");
	line_cnt=(3*spacer)+tab_height;
	Fl_Choice *b1=new Fl_Choice(sub_tab+2*spacer,line_cnt,
				    sub_label_width, sub_label_height,"Background: ");
	b1->menu(back_pull);
	menus[1]= b1;
	line_cnt+=sub_item_spacing;
	Fl_Box *l=new Fl_Box(FL_NO_BOX,2*spacer,line_cnt,
			     sub_label_width, sub_label_height,"Plot:");
	l->align(label_align);
	l->labelcolor(FL_BLUE);
	line_cnt+=(2*spacer);
	Fl_Choice *b2=new Fl_Choice(sub_tab+2*spacer,line_cnt,
				    sub_label_width, sub_label_height,"Magnitude: ");
	b2->menu(norm_pull);
	menus[2]= b2;
	line_cnt+=(3*spacer);
	Fl_Choice *b3=new Fl_Choice(sub_tab+2*spacer,line_cnt,
				    sub_label_width, sub_label_height,"Real part: ");
	b3->menu(real_pull);
	menus[3]= b3;
	line_cnt+=(3*spacer);
	Fl_Choice *b4=new Fl_Choice(sub_tab+2*spacer,line_cnt,
				    sub_label_width, sub_label_height,"Imag part: ");
	b4->menu(imag_pull);
	menus[4]= b4;
	line_cnt+=(3*spacer);
	Fl_Choice *b5=new Fl_Choice(sub_tab+2*spacer,line_cnt,
				    sub_label_width, sub_label_height,"Integral: ");
	b5->menu(real_pull);
	menus[5]= b5;
	g->end();
      }
      { 
	Fl_Group *g=new Fl_Group(spacer, spacer+tab_height, sub_width-sub_spacer, 
				 sub_height-sub_spacer-but_bar, "Paths");
	g->end();
      }
      { 
	Fl_Group *g=new Fl_Group(spacer, spacer+tab_height, sub_width-sub_spacer, 
				 sub_height-sub_spacer-but_bar, "Math");
	g->end();
      }
      tabs->end();
      {
	Fl_Button *o=new Fl_Button(2*spacer,sub_height-but_bar+spacer,100,30,"Save");
	o->callback(pref_save_cb);
      }
      {
	Fl_Button *o=new Fl_Button(sub_width-2*spacer-100,sub_height-but_bar+spacer,100,30,"Cancel");
	o->callback(pref_cancel_cb);
      }
    }
    prefs_window->hotspot(prefs_window);
    prefs_window->set_modal();
  }
  return w;
}

void pref_save_cb(Fl_Button *b, void *ptr)
{
  pref_win->hide();
  delete pref_win;
  pref_win_open=0;
}

void pref_cancel_cb(Fl_Button *b, void *ptr)
{
  pref_win->hide();
  delete pref_win;
  pref_win_open=0;
}

int preferences_window()
{
  Fl_Window *w;
  w=create_preferences();
  w->show();
  pref_win_open=1;
  while(pref_win_open)
    {
      (void)Fl::readqueue();
      Fl::wait(1.0);
    }
  return 0;
}
