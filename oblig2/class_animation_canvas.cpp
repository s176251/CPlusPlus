// 2014-03-28 - Martin W. Løkkeberg (s176251) - C++11.
#include "class_animation_canvas.h"

#include <FL/fl_draw.H>

int animation_canvas::fps = 48;
int timesRun = 0;

animation_canvas::animation_canvas(const char *l,int w, int h) : Fl_Box(0,0, w, h, l)
{	

}

void animation_canvas::add(animated* part)
{
	parts.push_back(part);
}

void animation_canvas::draw()
{
	if( timesRun++ == 0)
	{
		fl_color(FL_BLACK);
		fl_rectf(0,0, Fl::w(), Fl::h());
	}
	for (int i = 0; i < parts.size(); i++)
	{
		++(*parts[i]);
	}	
}

void animation_canvas::timer(void* canvas)
{	
	((animation_canvas*) canvas)->redraw();
	Fl::repeat_timeout((1.0/animation_canvas::fps), animation_canvas::timer, canvas);
}

animation_canvas::~animation_canvas()
{
	for (int i = 0; i < parts.size(); i++)
	{
		delete parts[i];
	}
}