#include "Ray.h"

Ray::Ray(){
	origin = Vect(0,0,0);
	direction =Vect(1,0,0);
}
Ray::Ray(Vect o, Vect d): origin(o), direction(d){}

Vect Ray::point(double t){
	double x,y,z;
	x = t*direction.getX() + origin.getX();
	y = t*direction.getY() + origin.getY();
	z = t*direction.getZ() + origin.getZ();
	return Vect(x,y,z);
}