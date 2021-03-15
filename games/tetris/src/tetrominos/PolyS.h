#pragma once

#include "Tetromino.h"

#include <vector>

class PolyS : public Tetromino
{
public:
	PolyS() { this->Create(); }
	~PolyS() {}

	void Create();

};	//	END class PolyS

