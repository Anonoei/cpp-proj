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

