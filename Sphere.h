
#ifndef _SPHERE_H
#define _SPHERE_H

#include "Color.h"
#include "Object.h"
#include "Vect.h"
#include "math.h"

class Sphere : public Object {
	Vect center;
	double radius;
	Color color;

public:
	Sphere();
	Sphere (Vect,double, Color);

	//methods
	virtual Vect getCenter(){return center;}
	virtual double getRadius(){return radius;}
	virtual Color getColor(){return color;}

	virtual Vect getNormalAt(Vect point);
	virtual double findIntersection(Ray ray);

};


#endif