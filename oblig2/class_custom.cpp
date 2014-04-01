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

const int dotCount = 5;
const int dotSize = 1;
const int rocketCount = 200;




class hello_world: public animation_canvas  
{
  int rocketcount;

 public:
  hello_world(const char* title,int w, int h, int _rocketcount);
  ~hello_world() override;
};

hello_world::hello_world(const char *l,int w, int h, int _rocketcount) : animation_canvas(l, w, h), rocketcount(_rocketcount)
{		
	for(int i = 0; i < _rocketcount; i++)
	{
		rocket* a = new rocket( dotCount, dotSize, rand()%100, rand()%w, rand()%h);
		add(a);
	}
}

hello_world::~hello_world()
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
	
	animation_canvas* b = new hello_world("hei", w, h, rocketCount);
	
	window->end();
	window->show();
	
	Fl::add_timeout(0.1, animation_canvas::timer, b);
	
	return Fl::run();
}
