#include "Intersection.h"

Intersection::Intersection():angle(0), distance(0), normal(Vect()), poi(Vect()){}
Intersection::Intersection(double distance, std::vector<double> angle, Vect norm, Vect poi):angle(angle),distance(distance),normal(norm), poi(poi){}
