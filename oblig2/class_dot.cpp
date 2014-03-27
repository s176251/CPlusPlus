//Local includes
#include "class_dot.h"
#include <FL/fl_draw.H>

#include <iostream>

void dot::draw()
{
	fl_color( fl_rgb_color((unsigned char)rand()%256, (unsigned char)rand()%256, (unsigned char)rand()%256) );
	fl_pie(x,y,r,r,0,360);
}

dot::dot(float _x,float _y,float _r) : x(_x), y(_y), r(_r), x_orig(_x), y_orig(_y)
{

}

void dot::clear()
{
	fl_color(FL_BLACK);
	fl_pie(x,y,r,r,0,360);
}

void dot::operator++() 
{ 
	clear();
	x = x + ((rand()%20)-10);
	y = y + ((rand()%20)-10);
	draw();		
	//std::cout << "x:" << x  << " x_org:" << x_orig << " y:" << y << " y_org:" << y_orig << std::endl;
}

void dot::reset() {}

dot::~dot(){}


