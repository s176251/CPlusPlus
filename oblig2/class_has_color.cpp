#include "class_has_color.h"

has_color::has_color()
{
	unsigned char* rgbPtr = (unsigned char*) &color;
	blue = ++rgbPtr;
	green = ++rgbPtr;
	red = ++rgbPtr;
}
