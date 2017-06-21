
#ifndef _OBJECT_H
#define _OBJECT_H

#include "Color.h"
#include "Vect.h"
#include "Ray.h"

class Object{
	

public:
	Object();

	//methods
	virtual double findIntersection(Ray);
	virtual Color getColor(){return Color (0.0,0.0,0.0,0);}
	virtual Vect getNormal(){return Vect(0,0,0);}

};


#endif