/////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++17
// Part of Tetris
//////////////////////////////
#pragma once

#include "Tetromino.h"

#include <vector>

class PolyT : public Tetromino
{
public:
	PolyT() { this->Create(); }
	~PolyT() {}

	void Create();

};	//	END class PolyT

