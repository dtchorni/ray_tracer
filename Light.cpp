#include "Light.h"

Light::Light(){
	position = Vect(0,0,0);
	color =Color(1,1,1,0);
}
Light::Light(Vect o, Color d): position(o), color(d){}
