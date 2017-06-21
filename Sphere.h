
#ifndef _SPHERE_H
#define _SPHERE_H

#include <vector>
#include "Color.h"
#include "Object.h"
#include "Vect.h"
#include "math.h"
#include "Intersection.h"
#include "Source.h"

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

	virtual Vect getNormal(Vect point);
	virtual Intersection findIntersection(Ray ray,std::vector<Source*> light_sources);

};


#endif