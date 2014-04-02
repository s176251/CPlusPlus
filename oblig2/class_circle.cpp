//Local includes
#include "class_fireworks.h"
#include "class_animation_canvas.h"
#include "class_rocket.h"
#include "class_circle.h"

#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include <time.h>
#include <iostream>
#include <algorithm>


void circle::draw()
{	
	fl_color(color);
	fl_pie(x,y,r,r,start_angle,end_angle);
}

circle::circle(int _x, int _y, int _r_start, int s_angle, int e_angle, int c, int cc, bool _clr) : x(_x), y(_y), r(_r_start), has_color(), start_angle(s_angle), end_angle(e_angle), clr(_clr)
{
	clearColor = cc;
	done = false;
	color = c;
}
void circle::operator++() 
{
	if(done) return;
	move(0, 0, 0);	
}
void circle::finish() 
{
	done = true;
}
bool circle::isDone() 
{
	return done;
}
void circle::move(double dx, double dy, double dr) 
{
	if(clr) clear();
	x += dx;
	y += dy;
	r += dr;	
	draw();	
}

void circle::reset() {}
void circle::clear() 
{
	fl_color(clearColor);
	fl_pie(x,y,r,r,start_angle,end_angle);
}
circle::~circle() {}
