/////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++17
// Part of Tetris
//////////////////////////////
#include "PolyJ.h"

void PolyJ::Create()
{
	Points locations;
	locations.Add(Point(0, 4));
	locations.Add(Point(1, 4));
	locations.Add(Point(1, 5));
	locations.Add(Point(1, 6));
	SetLocations(locations);
	SetOriginIndex(3);
}