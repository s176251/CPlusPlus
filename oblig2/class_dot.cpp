//Local includes
#include "class_dot.h"
#include <FL/fl_draw.H>

#include <iostream>

double dRand(double dMin, double dMax)
{
    double d = (double)rand() / RAND_MAX;
    return dMin + d * (dMax - dMin);
}

void dot::draw()
{
	//fl_color( fl_rgb_color((unsigned char)rand()%256, (unsigned char)rand()%256, (unsigned char)rand()%256) );
	if(*blue > 1) --(*blue);
	if(*green > 1) --(*green);
	if(*red > 1) --(*red);

	fl_color(color);
	fl_pie(x,y,r,r,0,360);
}

dot::dot(float _x,float _y,float _r) : x(_x), y(_y), r(_r), x_orig(_x), y_orig(_y), has_color()
{
	done = false;

	int weight = ((int)x)%3;
	if(weight == 0)
	{
		*blue = (unsigned char)(rand()%56)+100;
		*green =(unsigned char)(rand()%56)+50;
		*red = (unsigned char)(rand()%56)+50;	
	}
	else if(weight == 1)
	{
		*blue = (unsigned char)(rand()%56)+50;
		*green =(unsigned char)(rand()%56)+100;
		*red = (unsigned char)(rand()%56)+50;		
	}
	else
	{
		*blue = (unsigned char)(rand()%56)+50;
		*green =(unsigned char)(rand()%56)+50;
		*red = (unsigned char)(rand()%56)+100;		
	}
	
	direction = (float)dRand(M_PI*-1, M_PI);
	speed = dRand(1.0, 3.0);
}

void dot::clear()
{
	fl_color(FL_BLACK);
	fl_pie(x,y,r,r,0,360);
}

void dot::operator++() 
{
	if(done) return;
	clear();
	//x = x + ((rand()%20)-10);
	//y = y + ((rand()%20)-10);
	x += speed * cos(direction);
	y += speed * sin(direction);
	r += 0.1;
	
	if(speed > 0.5)	speed -= 0.02; //dRand(0.005, 0.02);
	draw();		
}

void dot::reset() 
{
	x = x_orig;
	y = y_orig;
}

dot::~dot(){}


