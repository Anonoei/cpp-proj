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

