/////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++17
// Part of Tetris
//////////////////////////////
#include "PolyI.h"

void PolyI::Create()
{
	Points locations;
	locations.Add(Point(0, 4));
	locations.Add(Point(0, 5));
	locations.Add(Point(0, 6));
	locations.Add(Point(0, 7));
	SetLocations(locations);
	SetOriginIndex(2);
}