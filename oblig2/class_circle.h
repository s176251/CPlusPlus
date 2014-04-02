#ifndef CLASS_CIRCLE_H
#define CLASS_CIRCLE_H

//Local includes
#include "class_fireworks.h"
#include "class_animation_canvas.h"
#include "class_rocket.h"

#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include <time.h>
#include <iostream>
#include <algorithm>

class circle : public animated, has_color
{
	double r;
	double r_end;
	double x;
	double y;
	double x_orig;
	double y_orig;
	int start_angle;
	int end_angle;
	int clearColor;
	bool done;
	bool clr;
	void draw() override;
  
	public:
		circle(int _x, int _y, int _r_start, int start_angle, int end_angle, int color, int clearColor, bool clr);
		void clear() override;
		void finish();
		bool isDone();
		void move(double dx, double dy, double dr);
		void operator++() override;
		void reset() override;
		~circle() override;
};

#endif