
#ifndef _OBJECT_H
#define _OBJECT_H

#include "Color.h"
#include "Vect.h"
#include "Ray.h"
#include "Intersection.h"
#include <vector>
class Source;

class Object{
	

public:
	Object();

	//methods
	virtual Intersection findIntersection(Ray,std::vector<Source*>);
	virtual Color getColor(){return Color (0.0,0.0,0.0,0);}
	virtual Vect getNormal(){return Vect(0,0,0);}

};


#endif