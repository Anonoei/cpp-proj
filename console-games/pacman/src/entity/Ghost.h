#pragma once

#include "../PacManBase.h"

class Ghost
{
public:
	Ghost();
	~Ghost();
	void Update();	//	This is the move function

	Point GetLocation() { return this->Location; }
	void SetLocation(Point location) { this->Location = location; }	//	Shouldn't be used
private:
	Point Location;
};