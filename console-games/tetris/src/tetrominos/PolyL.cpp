/////////////////////////////////////////////////////////////
//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++17
// Part of Tetris
//////////////////////////////
#include "PolyL.h"

void PolyL::Create()
{
	Points locations;
	locations.Add(Point(0, 6));
	locations.Add(Point(1, 4));
	locations.Add(Point(1, 5));
	locations.Add(Point(1, 6));
	SetLocations(locations);
	SetOriginIndex(3);
}