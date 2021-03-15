#include "PolyZ.h"

void PolyZ::Create()
{
	Points locations;
	locations.Add(Point(0, 6));
	locations.Add(Point(0, 7));
	locations.Add(Point(1, 7));
	locations.Add(Point(1, 8));
	SetLocations(locations);
}