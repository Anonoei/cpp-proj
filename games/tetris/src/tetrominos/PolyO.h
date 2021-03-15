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

