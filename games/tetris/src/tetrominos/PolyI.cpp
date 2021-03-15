#include "PolyI.h"

void PolyI::Create()
{
	Points locations;
	locations.Add(Point(0, 6));
	locations.Add(Point(1, 6));
	locations.Add(Point(2, 6));
	locations.Add(Point(3, 6));
	SetLocations(locations);
}