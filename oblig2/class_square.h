#ifndef CLASS_SQUARE_H
#define CLASS_SQUARE_H

//Local includes
#include "class_fireworks.h"
#include "class_animation_canvas.h"
#include "class_rocket.h"

#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include <time.h>
#include <iostream>
#include <algorithm>

class square : public animated, has_color
{
	double w;
	double w_end;	
	double h;
	double h_end;
	double x;
	double y;
	bool done;
	void draw() override;
  
	public:
		square(int _x, int _y, int _w, int _w_end, int _h, int _h_end, int color);
		void clear() override;
		void operator++() override;
		void reset() override;
		~square() override;
};


#endif