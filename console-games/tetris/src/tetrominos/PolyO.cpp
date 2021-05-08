/////////////////////////////////////////////////////////////
//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++17
// Part of Tetris
//////////////////////////////
#include "PolyO.h"

void PolyO::Create()
{
	Points locations;
	locations.Add(Point(0, 5));
	locations.Add(Point(0, 6));
	locations.Add(Point(1, 5));
	locations.Add(Point(1, 6));
	SetLocations(locations);
	SetOriginIndex(2);	//	This piece shouldn't be able to rotate
}