
#ifndef _VECT_H
#define _VECT_H
#include "math.h"

class Vect{
	double x,y,z;

public:
	Vect();
	Vect (double,double,double);

	//methods
	double getX() const {return x;}
	const double getY() const {return y;}
	const double getZ() const{return z;}

	double magnitude() const;

	Vect normalize() const;

	Vect negative() const;
	
	double dot(const Vect v) const;
	
	Vect cross(const Vect h) const;

	Vect operator+(const Vect&) const;

};


#endif