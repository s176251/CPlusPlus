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

const int dotCount = 20;
const int dotSize = 7;
const int rocketCount = 20;

fireworks::fireworks(const char *l,int w, int h, int _rocketcount) : animation_canvas(l, w, h), rocketcount(_rocketcount)
{	
	for(int i = 0; i < _rocketcount; i++)
	{
		rocket* a = new rocket( dotCount, dotSize, (rand()%200)*i, rand()%w, rand()%h);
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
	
	//std::cout << "main(),1" << std::endl;
	Fl_Window *window=new Fl_Window(w, h, "Dots!");
	//window->fullscreen();
	
	//std::cout << "main(),2" << std::endl;
	animation_canvas* b = new fireworks("hei", w, h, rocketCount);
	
	//std::cout << "main(),3" << std::endl;
	window->end();
	window->show();
	
	//std::cout << "main(),4" << std::endl;
	Fl::add_timeout(0.2, animation_canvas::timer, b);
	
	return Fl::run();
}
