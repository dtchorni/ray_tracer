
#ifndef _LIGHT_H
#define _LIGHT_H

#include "Color.h"
#include "Vect.h"
#include "Source.h"

class Light : public Source{
	Vect position;
	Color color;

public:
	Light();
	Light (Vect,Color);

	//methods
	virtual Vect getPosition(){return position;}
	virtual Color getColor(){return color;}

};


#endif