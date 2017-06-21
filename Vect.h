
#ifndef _VECT_H
#define _VECT_H
#include "math.h"
#include <iostream>
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

	Vect operator*(const double&)const;
	void print(){ std::cout<<"X: "<<x<<" Y: "<<y<< " Z: "<<z<<std::endl;}

};


#endif