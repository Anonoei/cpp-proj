/////////////////////////////////////////////////////////////
//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++17
// Part of Tetris
//////////////////////////////
#pragma once

#include "Tetromino.h"

#include <vector>

class PolyL : public Tetromino
{
public:
	PolyL() { this->Create(); }
	~PolyL() {}

	void Create();

};	//	END class PolyL

