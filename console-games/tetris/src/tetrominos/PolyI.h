/////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++17
// Part of Tetris
//////////////////////////////
#pragma once

#include "Tetromino.h"

#include <vector>

class PolyI : public Tetromino
{
public:
	PolyI() { this->Create(); }
	~PolyI() {}

	void Create();

};	//	END class PolyI
