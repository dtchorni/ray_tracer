#include "Plane.h"

#include <iostream>
Plane::Plane(){
	normal = Vect(1,0,0);
	distance = 0;
	color =Color(0.5,0.5,0.5,0);
}
Plane::Plane(Vect n, double d, Color c): normal(n),distance(d), color(c){}

Vect Plane::getNormalAt(Vect point){return normal;}

Intersection Plane::findIntersection(Ray ray, std::vector<Source*> lights){
	Vect ray_direction = ray.getDirection().normalize();
	Vect ray_origin = ray.getOrigin();
	double a = ray_direction.dot(normal);
	double dist, x, y ,z;
	Vect poi;
	std::vector<double> angles;

	if (a == 0) return Intersection(0,angles,Vect(),Vect()); // parallel to plane
	else{
		double b = -1*((normal.dot(ray.getOrigin())) + distance);
		dist  = b/a;
		poi = ray.point(dist);
		//std::cout<<dist<<std::endl;

		//calculate angles...
		return Intersection(dist,angles, normal, poi);


		
	}
}

Vect Plane::getPosition(){
	return Vect();
}