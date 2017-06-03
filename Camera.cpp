#include "Camera.h"

Camera::Camera(){
	campos =Vect(0,0,0);
	camdir=Vect(0,0,1);
	camright=Vect(0,0,0);
	camdown=Vect(0,0,0);
}

Camera::Camera(Vect a, Vect b, Vect c, Vect d):campos(a),camdir(b),camright(c),camdown(d){}
