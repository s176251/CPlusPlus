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

const int dotCount = 100;
const int dotSize = 5;
const int rocketCount = 60;

fireworks::fireworks(const char *l,int w, int h, int _rocketcount) : animation_canvas(l, w, h), rocketcount(_rocketcount)
{	
	int j = 10;
	int nw = (4.0/5.0)*w;
	int nh = (4.0/5.0)*h;
	int dw = (1.0/10.0)*w;
	int dh = (1.0/10.0)*h;
	
	for(int i = 0; i < _rocketcount; i++)
	{
		rocket* a = new rocket( dotCount, dotSize, j, (rand()%nw)+dw, (rand()%nh)+dh);
		j += (rand()%50)+40;
		add(a);
	}
}

fireworks::~fireworks()
{
	;
}

int main()
{
	int w = Fl::w();
	int h = Fl::h();
	srand(time(NULL));

	Fl_Window *window=new Fl_Window(w, h, "Dots!");
	//window->fullscreen();
	
	animation_canvas* b = new fireworks("hei", w, h, rocketCount);
	
	window->end();
	window->show();
	
	Fl::add_timeout(0.2, animation_canvas::timer, b);
	
	return Fl::run();
}
