#ifndef CLASS_SUN_H
#define CLASS_SUN_H

//Local includes
#include "class_animation_canvas.h"
#include "class_circle.h"

#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include <time.h>
#include <iostream>
#include <algorithm>

class sun : public animated, has_color, is_vector
{
	bool done;
	int x;
	int y;
	int r;
	int count;
	int iterations;
	circle* s;
	void draw() override;
  
	public:
		sun(int _x, int _y, int r, int iterations);
		void clear() override;
		void operator++() override;
		void reset() override;
		~sun() override;
};

#endif