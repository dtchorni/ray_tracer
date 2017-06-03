#include "Vect.h"

Vect::Vect(){
	x=0;
	y=0;
	z=0;
}
Vect::Vect(double x,double y, double z): x(x), y(y), z(z){}


double Vect::magnitude() const{ return sqrt((x*x)+(y*y)+(z*z));}

Vect Vect::normalize() const{
	double mag = magnitude();
	return Vect(x/mag,y/mag, z/mag);
}

Vect Vect::negative() const{ return Vect(-x,-y,-z);}

double Vect::dot(const Vect v) const{ return x*(v.getX()) + y*v.getY() + z*v.getZ();}

Vect Vect::cross(const Vect v) const{ return Vect(y*v.getZ() - z*v.getY(), z*v.getX() - x*v.getZ(), x*v.getY()-y*v.getX()); }

Vect Vect::operator+(const Vect &v) const{ return Vect(x+v.getX(),y+v.getY(),z+v.getZ());}

Vect Vect::operator*(const double& num) const{ return Vect(x*num,y*num,z*num);}
