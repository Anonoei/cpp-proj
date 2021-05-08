#pragma once

#include "../board/PacManBoard.h"
#include "../PacManBase.h"

class PacManLogic
{
public:
	PacManLogic() {}
	~PacManLogic() {}

	void Init();

	void Update();

private:
	PacManBoard s_Board;
	bool DrawBoard = true;
};
