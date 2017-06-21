#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_
#include "Vect.h"

struct Intersection{
	double distance, angle;
	Vect normal;
	Intersection();
	Intersection(double,double,Vect);

};

#endif