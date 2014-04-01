// 2014-03-28 - Martin W. Løkkeberg (s176251) - C++11.
#include "class_rocket.h"

rocket::rocket(int _dotcount,int dotsize, int _fuse, int x, int y) : dotcount(_dotcount), fuse(_fuse)
{
	done = false;
	t = 157;
	
	for(int i = 0; i < _dotcount; i++)
	{
		dot* a = new dot( x, y, dotsize);
		dots.push_back(*a);
		delete a;
	}	
}

void rocket::clear()
{
	for (int i = 0; i < dots.size(); i++)
	{
		dots[i].clear();
	}
}

void rocket::draw()
{	
	if(done) return;
	if(fuse == 0)
	{
		for (int i = 0; i < dots.size(); i++)
		{
			++(dots[i]);
		}		
		if(--t == 0) done = true;
	}
	else fuse--;
}

void rocket::operator++() 
{ 
	draw();	
}

void rocket::reset()
{
	for (int i = 0; i < dots.size(); i++)
	{
		dots[i].reset();
	}
	t = 157;
	done = false;
}

rocket::~rocket()
{
	dots.clear(); //Calls the destructor of all its elements (as long as they're not ptrs)
}