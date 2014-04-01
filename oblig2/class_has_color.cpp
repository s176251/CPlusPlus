// 2014-03-28 - Martin W. Løkkeberg (s176251) - C++11.
#include "class_has_color.h"

has_color::has_color()
{
	unsigned char* rgbPtr = (unsigned char*) &color;
	
	// Set the char* to point to their respective colors.
	blue = ++rgbPtr;
	green = ++rgbPtr;
	red = ++rgbPtr;
}

	// Blue, green og red pekerne kan ikke kun settes i denne konstuktøren,
	// fordi 'dot'-objektet kopieres når man legger det til i vektoren; dots.
	// Følgelig kopieres også 'color' og rgb pekerne peker da feil. 
	// (ga meg en fin liten time med debugging for å finne ut hvorfor dottene ikke "fadet" ut)
	// Da blir jo også denne konstruktøren meningsløs, fordi farge kan ikke settes her
	// fordi alle dot'ene i en rakett skal ha samme "fargetyngde" og må derfor baseres
	// på noe felles (f.eks start-koordinater) som ikke er tilgjengelig her.
	// Skulle gjerne endret .h filene, men akk.