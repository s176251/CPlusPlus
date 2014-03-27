//Local includes
#include "class_dot.h"
#include <FL/fl_draw.H>

void dot::draw()
{
	fl_color( fl_rgb_color((unsigned char)rand()%256, (unsigned char)rand()%256, (unsigned char)rand()%256) );
	fl_pie(x,y,r,r,0,360);
}

dot::dot(float _x,float _y,float _r) : x(_x), y(_y), r(_r), x_orig(_x), y_orig(_y)
{

}

void dot::clear(){}

void dot::operator++() 
{ 
	draw();	
	x += 10;
	y += 10;
}

void dot::reset() {}

dot::~dot(){}


