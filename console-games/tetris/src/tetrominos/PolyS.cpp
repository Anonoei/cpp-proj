/////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++17
// Part of Tetris
//////////////////////////////
#include "PolyS.h"

void PolyS::Create()
{
	Points locations;
	locations.Add(Point(0, 6));
	locations.Add(Point(0, 5));
	locations.Add(Point(1, 5));
	locations.Add(Point(1, 4));
	SetLocations(locations);
	SetOriginIndex(3);
}