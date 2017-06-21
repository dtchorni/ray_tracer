#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_
#include "Vect.h"
#include <vector>

struct Intersection{
	double distance;
	std::vector<double> angle;
	Vect normal;
	Intersection();
	Intersection(double,std::vector<double>,Vect);

};

#endif