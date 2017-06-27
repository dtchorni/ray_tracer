#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_
#include "Vect.h"
#include <vector>
#include <iostream>

struct Intersection{
	double distance;
	std::vector<double> angle;
	Vect normal, poi;
	Intersection();
	Intersection(double,std::vector<double>,Vect, Vect);
	void print(){
		std::cout<<"Distance: "<<distance<<" Angles: "; 
		for(int i=0; i < angle.size(); ++i){std::cout<<angle.at(i)<<" ";}
		std::cout<<"\nNormal-> ";
		normal.print();
	}
};

#endif