//Local includes
#include "class_fireworks.h"
#include "class_dot.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include <time.h>
#include <iostream>

int duration = 200;
int elapsed = 0;

void callback(void* b)
{

}

int main()
{
	int w = Fl::w();
	int h = Fl::h();
	int dotSize = 7;
	srand(time(NULL));
	
	Fl_Window *window=new Fl_Window(w, h, "Dots!");
	
	animation_canvas* b = new animation_canvas("hei", w, h);
	
	for(int i = 0; i < 100; i++)
	{	
		dot* a = new dot( rand()%w, rand()%h , dotSize);
		b->add(a);
	}
	
	window->end();
	window->show();
	
	Fl::add_timeout(0.2, animation_canvas::timer, b);
	
	return Fl::run();
}