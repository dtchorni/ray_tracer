#include "Color.h"

Color::Color():red(0.5),green(0.5),blue(0.5){}

Color::Color(double x,double y, double z,double s): red(x), green(y), blue(z),special(s){}

double Color::brightness(){ return (red +green+blue)/3;}

Color Color::colorScalar(double scalar) const{return Color(red*scalar,green*scalar,blue*scalar,special);}

Color Color::operator+(const Color &c) const{return Color(red+c.getRed(),green+c.getGreen(),blue+c.getBlue(),special);}

Color Color::operator*(const Color &c) const{return Color(red*c.getRed(),green*c.getGreen(),blue*c.getBlue(),special);}

Color Color::colorAverage(Color c){ return Color((red+c.getRed())/2,(green+c.getGreen())/2,(blue+c.getBlue())/2,special);}
