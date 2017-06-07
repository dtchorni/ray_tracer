#include "Sphere.h"
#include <iostream>

Sphere::Sphere(){
	center = Vect(0,0,0);
	radius =1.0;
	color =Color(0.5,0.5,0.5,0);
}
Sphere::Sphere(Vect o, double r, Color d): center(o),radius(r), color(d){}

Vect Sphere::getNormalAt(Vect point){
	//normal always points away from the center fo teh sphere
	Vect normal_vect=point+(center.negative()).normalize();
	return normal_vect;
}
double Sphere::findIntersection(Ray ray){
	Vect ray_origin = ray.getOrigin();
	double ray_origin_x = ray_origin.getX();
	double ray_origin_y = ray_origin.getY();
	double ray_origin_z = ray_origin.getZ();

	Vect ray_direction = ray.getDirection().normalize();
	double ray_direction_x = ray_direction.getX();
	double ray_direction_y = ray_direction.getY();
	double ray_direction_z = ray_direction.getZ();

	//double check = ray_direction.normalize().magnitude();

	//std::cout<<check<<" "<<ray_direction.magnitude()<<std::endl;

	Vect sphere_center = ray.getDirection();
	double sphere_center_x = sphere_center.getX();
	double sphere_center_y = sphere_center.getY();
	double sphere_center_z = sphere_center.getZ();

	double a =1;//normalized
	double b = 2*(((ray_origin_x - sphere_center_x)*ray_direction_x) + ((ray_origin_y - sphere_center_y)*ray_direction_y) + ((ray_origin_z - sphere_center_z)*ray_direction_z));
	double c = pow(ray_origin_x - sphere_center_x,2) + pow(ray_origin_y - sphere_center_y,2) + pow(ray_origin_z - sphere_center_z,2) - (radius*radius);

	double discriminant = b*b - 4*c;

	if(discriminant>0){//ray intersects
		//first root
		double root_1 = ((-1*b - sqrt(discriminant))/2) - 0.00001;
		if(root_1>0){//first rot is the smallest positive root
			return root_1;
		}else{//the second root is the smallest positive root
			double root_2 = ((-1*b + sqrt(discriminant))/2) - 0.00001;
			return root_2;
		}
	}else {
		//ray missed sphere
		return -1;
	}


	
}