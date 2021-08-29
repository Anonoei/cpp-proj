/////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++17
// Part of Tetris
//////////////////////////////
#pragma once

#include "Tetromino.h"

#include <vector>

class PolyO : public Tetromino
{
public:
	PolyO() { this->Create(); }
	~PolyO() {}

	void Create();

};	//	END class PolyO

