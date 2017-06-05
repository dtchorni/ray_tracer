
#ifndef _PLANE_H
#define _PLANE_H

#include "Color.h"
#include "Object.h"
#include "Vect.h"
#include "math.h"

class Plane : public Object {
	Vect normal;
	double distance;
	Color color;

public:
	Plane();
	Plane (Vect,double, Color);

	//methods
	virtual Vect getNormal(){return normal;}
	virtual double getDistance(){return distance;}
	virtual Color getColor(){return color;}

	Vect getNormalAt(Vect point);

	virtual double findIntersection(Ray);

};


#endif