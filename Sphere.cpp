#include "Sphere.h"

Sphere::Sphere(){
	center = Vect(0,0,0);
	radius =1.0;
	color =Color(0.5,0.5,0.5,0);
}
Sphere::Sphere(Vect o, double r, Color d): center(o),radius(r), color(d){}
