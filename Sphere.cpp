#include "Sphere.h"
#include <iostream>
#include <math.h>

Sphere::Sphere(){
	center = Vect(0,0,0);
	radius =1.0;
	color =Color(0.5,0.5,0.5,0);
}
Sphere::Sphere(Vect o, double r, Color d): center(o),radius(r), color(d){}

Vect Sphere::getNormal(Vect point){
	//normal always points away from the center fo teh sphere
	Vect normal_vect=(point+(center.negative())).normalize();
	return normal_vect;
}
Intersection Sphere::findIntersection(Ray ray, vector<Source*> light_sources){
	double distance;
	vector<double> angle;
	Vect normal;

	Vect ray_origin = ray.getOrigin();
	double ray_origin_x = ray_origin.getX();
	double ray_origin_y = ray_origin.getY();
	double ray_origin_z = ray_origin.getZ();

	Vect ray_direction = ray.getDirection().normalize();
	double ray_direction_x = ray_direction.getX();
	double ray_direction_y = ray_direction.getY();
	double ray_direction_z = ray_direction.getZ();

	/*std::cout<<std::endl;
	ray_origin.print();
	ray_direction.print();*/

	//double check = ray_direction.normalize().magnitude();

	//std::cout<<check<<" "<<ray_direction.magnitude()<<std::endl;

	Vect sphere_center = center;//ray.getDirection();
	//sphere_center.print();
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
			distance = root_1;
			double x,y,z;
			x = ray_origin_x*(1-distance)+(distance*ray_direction_x);
			y = ray_origin_y*(1-distance)+(distance*ray_direction_y);
			z = ray_origin_z*(1-distance)+(distance*ray_direction_z);
			normal = getNormal(Vect(x,y,z));
			int s = light_sources.size();
			for(int i =0; i < s; ++i){
				double a = (normal.dot(light_sources.at(i)->getPos())) / (normal.magnitude()*light_sources.at(i).magnitude());
				a = (acos(a)-90) * 180/PI;
				angle.push_back(a);
			}
			return Intersection(distance,angle,normal);
		}else{//the second root is the smallest positive root
			double root_2 = ((-1*b + sqrt(discriminant))/2) - 0.00001;
			distance = root_2;
		}
		double x,y,z;
			x = ray_origin_x*(1-distance)+(distance*ray_direction_x);
			y = ray_origin_y*(1-distance)+(distance*ray_direction_y);
			z = ray_origin_z*(1-distance)+(distance*ray_direction_z);
			normal = getNormal(Vect(x,y,z));
			int s = light_sources.size();
			for(int i =0; i < s; ++i){
				double a = (normal.dot(light_sources.at(i)->getPos())) / (normal.magnitude()*light_sources.at(i).magnitude());
				a = (acos(a)-90) * 180/PI;
				angle.push_back(a);
			}
			return Intersection(distance,angle,normal);
	}else {
		//ray missed sphere
		return Intersection(-1,vector<double>(),Vect());
	}


	
}