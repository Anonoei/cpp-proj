/////////////////////////////////////////////////////////////
//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++17
// Part of Tetris
//////////////////////////////
#pragma once

#include "Tetromino.h"

#include <vector>

class PolyJ : public Tetromino
{
public:
	PolyJ() { this->Create(); }
	~PolyJ() {}

	void Create();

};	//	END class PolyJ

