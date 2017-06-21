#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_
#include "Vect.h"
#include <vector>

struct Intersection{
	double distance, angle;
	Vect normal;
	Intersection();
	Intersection(double,vector<double>,Vect);

};

#endif