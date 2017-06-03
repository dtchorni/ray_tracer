
#ifndef _LIGHT_H
#define _LIGHT_H

#include "Color.h"
#include "Vect.h"

class Light{
	Vect position;
	Color color;

public:
	Light();
	Light (Vect,Color);

	//methods
	virtual Vect getPos(){return position;}
	virtual Color getColor(){return color;}

};


#endif