
#ifndef _RAY_H
#define _RAY_H

#include "math.h"
#include "Vect.h"

class Ray{
	Vect origin, direction;

public:
	Ray();
	Ray (Vect,Vect);

	//methods
	Vect getOrigin(){return origin;}
	Vect getDirection(){return direction;}
	Vect point(double);

};


#endif