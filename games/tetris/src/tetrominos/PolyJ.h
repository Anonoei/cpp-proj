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

