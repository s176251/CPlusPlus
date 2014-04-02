//Local includes
#include "class_sun.h"

void sun::draw()
{	
	if(count <= (iterations/2))
	{
		s->move( 1, 0, -0.6);
	}
	else
	{
		s->move( 1, 0, 0.6);
	}
	count--;
}
sun::sun(int _x, int _y, int _r,  int itr) : has_color(), x(_x), y(_y), r(_r), iterations(itr)
{
	count = itr;
	done = false;
	color = FL_YELLOW;
	s = new circle(y, x, r, 0, 360, color, FL_BLUE, true);
}
void sun::operator++() 
{
	if(done) return;
	draw();		
}
void sun::reset() {}
void sun::clear() {}
sun::~sun()
{
	delete s;
}