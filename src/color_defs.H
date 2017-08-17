// Color definitions

// How many predefined colors do we have?
#define max_colors 7

char  pref_xcolors[max_colors][30]={"wheat","lightsteelblue","plum","thistle","snow2","gray90","black"};

float pref_fcolors[max_colors][3]= {{0.96,0.87,0.70},    // wheat
				    {0.69,0.77,0.87},    // lightsteelblue
				    {0.87,0.63,0.87},    // plum
				    {0.85,0.75,0.85},    // thistle
				    {0.93,0.91,0.91},    // snow2
				    {0.90,0.90,0.90},    // gray90
				    {0.00,0.00,0.00}};   // black

float plot_colors[4][3]=  {{0.0,0.0,0.0},       // black --> norm
			   {1.0,0.0,0.0},       // red   --> real
			   {0.0,1.0,0.0},       // green --> imag
			   {0.0,0.0,1.0}};      // blue  --> integ
