#include "PolyT.h"

void PolyT::Create()
{
	Points locations;
	locations.Add(Point(0, 6));
	locations.Add(Point(1, 6));
	locations.Add(Point(1, 5));
	locations.Add(Point(1, 7));
	SetLocations(locations);
}