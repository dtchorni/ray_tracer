
#ifndef _COLOR_H
#define _COLOR_H
#include "math.h"

class Color{
	double red,green,blue,special;

public:
	Color();
	Color (double,double,double,double );

	//methods
	const double getRed() const {return red;}
	const double getBlue() const {return blue;}
	const double getGreen() const{return green;}
	const double getSpecial() const{return special;}

	void setRed(double n)  {red=n;}
	void setBlue(double n)  {blue=n;}
	void setGreen(double n) { green=n;}
	void setSpecial(double n) { special=n;}




};


#endif