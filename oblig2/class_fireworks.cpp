// 2014-03-28 - Martin W. Løkkeberg (s176251) - C++11.
/*
 * Har gjort programmet så lekkasjefritt som mulig,
 * men noen av funksjonene til fltk har lekkasjer jeg ikke får gjort noe med.
 * Testet ved å kommentere ut all kode jeg har skrevet, og bare et kall til
 * f.eks Fl::w() forårsaker 81 minnelekkasjer, uten ett eneste new kall av meg.
 *
 */
#include "class_fireworks.h"
#include "class_rocket.h"

#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include <time.h>

const int dotCount = 100;
const int dotSize = 5;
const int rocketCount = 60;

fireworks::fireworks(const char *l,int w, int h, int _rocketcount) : animation_canvas(l, w, h), rocketcount(_rocketcount)
{	
	int j = 10; // Fuse length.
	
	// Calculate coordinates so rockets don't start too close to screen edge.
	int nw = (4.0/5.0)*w; 
	int nh = (4.0/5.0)*h;
	int dw = (1.0/10.0)*w;
	int dh = (1.0/10.0)*h;
	
	//Create rockets and add them to canvas.
	for(int i = 0; i < _rocketcount; i++)
	{
		rocket* a = new rocket( dotCount, dotSize, j, (rand()%nw)+dw, (rand()%nh)+dh);
		j += (rand()%50)+40;
		add(a);
	}
}

fireworks::~fireworks()
{
	//Nothing to do here
	//Animation_canvas clears any element added with 'add(x)'.
}

// Entry point
int main()
{
	// Get screen width and height.
	int w = Fl::w();
	int h = Fl::h();
	
	srand(time(NULL));

	Fl_Window *window = new Fl_Window(w, h, "Fireworks!");
	
	animation_canvas* b = new fireworks("fws", w, h, rocketCount);
		
	window->end();
	window->show();
	
	Fl::add_timeout(0.2, animation_canvas::timer, b);
	
	int r = Fl::run();
	
	delete b;
	delete window;
	
	return r;
}
