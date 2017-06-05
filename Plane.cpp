#include "Plane.h"

Plane::Plane(){
	normal = Vect(1,0,0);
	distance = 0;
	color =Color(0.5,0.5,0.5,0);
}
Plane::Plane(Vect n, double d, Color c): normal(n),distance(d), color(c){}

Vect Plane::getNormalAt(Vect point){return normal;}

double Plane::findIntersection(Ray ray){
	Vect ray_direction = ray.getDirection();
	double a = ray_direction.dot(normal);

	if (a == 0) return -1; // parallel to plane
	else{
		double b = normal.dot(ray.getOrigin() + (normal*distance).negative());
		return -1*b/a;
	}
}