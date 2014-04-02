//Local includes
#include "class_circle.h"
#include "class_animation_canvas.h"
#include "class_square.h"
#include "class_cloud.h"
#include "class_sun.h"

#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include <time.h>
#include <iostream>
#include <algorithm>

const int cloudcount = 10;


//*********************************************************************************************************************************************
//*********************************************************************************************************************************************

// Class that creates a scenery with blue sky, a green hill, floating clouds and a moving sun.
class hello_world: public animation_canvas  
{
	public:
		hello_world(const char* title,int w, int h, int _cloudcount);
		~hello_world() override;
};

hello_world::hello_world(const char *l,int w, int h, int _cloudcount) : animation_canvas(l, w, h)
{	
	square* bg = new square(0, 0, w, w, h, h, FL_BLUE);
	add(bg);
	
	sun* s = new sun(h/10, -100, w/10, w);
	add(s);	
	
	circle* hill = new circle(-(w/4), h-(h/3), w*1.5, 0, 180, FL_GREEN, FL_BLACK, true);
	add(hill);
	
	for(int i = 0; i < _cloudcount; i++)
	{
		cloud* c = new cloud(h/2, w, 70);
		add(c);
	}
}

hello_world::~hello_world(){}

//*********************************************************************************************************************************************
//*********************************************************************************************************************************************

int main()
{
	int w = Fl::w();
	int h = Fl::h();
	srand(time(NULL));

	Fl_Window *window = new Fl_Window(w, h, "Stuff!");
	window->fullscreen();
	window->color(FL_BLACK);
	
	animation_canvas* b = new hello_world("stf", w, h, cloudcount);
		
	window->end();
	window->show();
		
	Fl::add_timeout(0.2, animation_canvas::timer, b);
	
	int r = Fl::run();
	
	delete b;
	delete window;
	
	return r;
}
