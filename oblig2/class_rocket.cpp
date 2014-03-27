#include "class_rocket.h"

#include <algorithm>

rocket::rocket(int _dotcount,int dotsize, int _fuse, int x, int y) : dotcount(_dotcount), fuse(_fuse)
{
	dots = (* new std::vector<dot*>);
	
	for(int i = 0; i < _dotcount; i++)
	{
		dot* a = new dot( x, y, dotsize);
		dots.push_back(a);
	}	
}

void rocket::clear()
{
}

void incrementDots(dot* a)
{
	++(*a);
}

void rocket::draw()
{	
	if(fuse == 0) std::for_each(dots.begin(), dots.end(), &incrementDots);
	else fuse--;
}

void rocket::operator++() 
{ 
	draw();	
}

void rocket::reset() {}


rocket::~rocket(){}