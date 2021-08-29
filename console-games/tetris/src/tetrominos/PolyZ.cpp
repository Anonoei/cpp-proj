/////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++17
// Part of Tetris
//////////////////////////////
#include "PolyZ.h"

void PolyZ::Create()
{
	Points locations;
	locations.Add(Point(0, 5));
	locations.Add(Point(0, 6));
	locations.Add(Point(1, 6));
	locations.Add(Point(1, 7));
	SetLocations(locations);
	SetOriginIndex(3);
}