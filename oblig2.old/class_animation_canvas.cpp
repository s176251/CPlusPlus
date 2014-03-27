#include "class_animation_canvas.h"

#include <FL/fl_draw.H>
#include <algorithm>


animation_canvas::animation_canvas(const char *l,int w, int h) : Fl_Box(0,0, w, h, l)
{	
	parts = *(new std::vector<animated*>);
}

void animation_canvas::add(animated* part)
{
	parts.push_back(part);
}

void increment(animated* a)
{
	++(*a);
}

void animation_canvas::draw()
{
	fl_color(FL_BLACK);
    fl_rectf(0,0,Fl::w(),Fl::h());
	
	std::for_each(parts.begin(), parts.end(), &increment);
}

void animation_canvas::timer(void* canvas)
{	
	((animation_canvas*) canvas)->redraw();
	Fl::repeat_timeout(0.1, animation_canvas::timer, canvas);
}

animation_canvas::~animation_canvas()
{
	delete &parts;
}