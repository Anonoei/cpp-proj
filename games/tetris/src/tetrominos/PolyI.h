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
