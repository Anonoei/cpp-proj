#include "PolyO.h"

void PolyO::Create()
{
	Points locations;
	locations.Add(Point(0, 5));
	locations.Add(Point(0, 6));
	locations.Add(Point(1, 5));
	locations.Add(Point(1, 6));
	SetLocations(locations);
}