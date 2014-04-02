//Local includes
#include "class_fireworks.h"
#include "class_animation_canvas.h"
#include "class_rocket.h"
#include "class_cloud.h"


#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include <time.h>
#include <iostream>
#include <algorithm>


double rngDouble(double dMin, double dMax)
{
    double d = (double)rand() / RAND_MAX;
    return dMin + d * (dMax - dMin);
}

void cloud::draw()
{	
	for(int i = 0; i < clouds.size(); i++)
	{
		clouds[i]->move( speed, 0, 0);
	}
	if(itr%itr_before_turn == 0)
	{
		speed = speed*-1;
	}
	itr++;
}
cloud::cloud(int _x_max, int _y_max, int r) : has_color(), x_max(_x_max), y_max(_y_max)
{
	done = false;
	color = FL_WHITE;
	itr_before_turn = (rand()%800)+100;
	itr = 1;
	direction = (rand()%2);
	
	if(direction == 0.0)
	{
		speed = rngDouble(0.1, 0.6);
	}
	else
		speed = rngDouble(0.1, 0.6) * -1;
	
	int startX = rand()%_x_max;
	int startY = rand()%_y_max;
	
	for(int i = 0; i < 10; i++)
	{
		clouds.push_back(new circle(startY+((rand()%70)-35), startX+((rand()%20)-10), r, 0, 360, color, FL_BLUE, false));
	}
}
void cloud::operator++() 
{
	if(done) return;
	draw();		
}
void cloud::reset() {}
void cloud::clear() {}
cloud::~cloud() 
{
	for(int i = 0; i < clouds.size(); i++)
	{
		delete clouds[i];
	}
}
