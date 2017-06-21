#include "Intersection.h"

Intersection::Intersection():angle(0), distance(0), normal(Vect()){}
Intersection::Intersection(double distance, std::vector<double> angle, Vect norm):angle(angle),distance(distance),normal(norm){}
