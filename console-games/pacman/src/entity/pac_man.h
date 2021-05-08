#pragma once

#include "../PacManBase.h"

class pac_man
{
public:
	pac_man();
	~pac_man();

	void Update();

	Point GetLocation() { return this->Location; }
	void SetLocation(Point location) { this->Location = location; }

private:
	Point Location;
};

