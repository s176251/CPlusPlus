// 2014-03-28 - Martin W. Løkkeberg (s176251) - C++11.
#include "class_dot.h"

#include <FL/fl_draw.H>

// Generates a random double value between dMin and dMax.
double dRand(double dMin, double dMax)
{
    double d = (double)rand() / RAND_MAX;
    return dMin + d * (dMax - dMin);
}

// Draws dot on screen.
void dot::draw()
{	
	unsigned char* rgbPtr = (unsigned char*) &color;
	blue = ++rgbPtr;
	green = ++rgbPtr;
	red = ++rgbPtr;
	
	// Decrement all parts of the color til it's black.
	if(*blue > 1) --(*blue);
	if(*green > 1) --(*green);
	if(*red > 1) --(*red);

	// Set current color
	fl_color(color);
	
	// Draw dot
	fl_pie(x,y,r,r,0,360);
}

// Initialize values and rng color.
dot::dot(float _x,float _y,float _r) : x(_x), y(_y), r(_r), x_orig(_x), y_orig(_y), has_color()
{
	done = false;

	//Pseudorandomly choose overweight of red, green or blue,
	//based on x so that all colors that start in the same spot has the same overweight of a color.
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
	
	//rng a direction between -pi and pi.
	direction = (float)dRand(M_PI*-1, M_PI);
	
	//rng a staring speed.
	speed = dRand(1.0, 3.0);
}

// Draw black over the last dot draw spot.
void dot::clear()
{
	fl_color(FL_BLACK);
	fl_pie(x,y,r,r,0,360);
}

// Clear previous dot location.
// Calculate new coordinates.
// Increase dot size.
// Decrease speed.
// Draw dot anew.
void dot::operator++() 
{
	if(done) return;
	clear();
	x += speed * cos(direction);
	y += speed * sin(direction);
	r += 0.1;
	
	if(speed > 0.5)	speed -= 0.02; 
	draw();		
}

void dot::reset() 
{
	x = x_orig;
	y = y_orig;
}

dot::~dot(){}


