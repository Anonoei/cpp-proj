#include "PacManLogic.h"

void PacManLogic::Init()
{
	this->s_Board.Init();
}

void PacManLogic::Update()
{
	if (this->DrawBoard)
	{
		this->s_Board.Draw(PacDirection::Left);
	}
}