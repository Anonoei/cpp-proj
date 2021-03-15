#include "PolyS.h"

void PolyS::Create()
{
	Points locations;
	locations.Add(Point(0, 6));
	locations.Add(Point(0, 5));
	locations.Add(Point(1, 5));
	locations.Add(Point(1, 4));
	SetLocations(locations);
}