
#ifndef _CAMERA_H
#define _CAMERA_H

#include "Vect.h"

class Camera{
	Vect campos, camdir, camright, camdown;

public:
	Camera();
	Camera (Vect,Vect,Vect,Vect);

	//methods
	Vect getCampos(){return campos;}
	Vect getCamdir(){return camdir;}
	Vect getCamright(){return camright;}
	Vect getCamdown(){return camdown;}

};


#endif