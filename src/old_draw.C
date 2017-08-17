// Main drawing widget c... so called canvas ;)
// class Drawing : public Fl_Widget
// {
//   void draw() 
//     {
//       fl_clip(x(),y(),w(),h());
//       fl_color(FL_DARK3);
//       fl_rectf(x(),y(),w(),h());
//       fl_color(FL_BLACK);
//       fl_begin_line();
//       for (int i=0; i<pts; i++)
// 	{
// 	  fl_vertex(cv_ofx+double(pt_x)*(points[i][0]/double(pts)),
// 		    cv_ofy+double(pt_y)*((points[i][1]+double(ofs_y))/double(max_y)));
// 	}
//       fl_end_line();
//       fl_pop_clip();
//     }
// public:
//   Drawing(int X,int Y,int W,int H) : Fl_Widget(X,Y,W,H) 
//     {
//     }
// };
// Drawing *d;               // main canvas
