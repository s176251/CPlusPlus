//Local includes
#include "class_fireworks.h"
#include "class_animation_canvas.h"
#include "class_rocket.h"
#include "class_square.h"

#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include <time.h>
#include <iostream>
#include <algorithm>


void square::draw()
{	
	fl_color(color);
	fl_rectf(x,y,w,h);
}

square::square(int _x, int _y, int _w, int _w_end, int _h, int _h_end, int c) : x(_x), y(_y), w(_w), w_end(_w_end), has_color(), h(_h), h_end(_h_end)
{
	done = false;
	color = c;
}
void square::operator++() 
{
	if(done) return;
	clear();
	draw();		
}
void square::reset() {}
void square::clear() 
{
	fl_color(FL_BLACK);
	fl_rect(x,y,w,h);
}
square::~square() {}
