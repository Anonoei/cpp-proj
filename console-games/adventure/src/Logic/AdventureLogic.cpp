#include "AdventureLogic.h"

void AdventureLogic::Init()
{
	aPROFILE_FUNCTION();
	this->m_Clock.Init();
	std::thread clock(this->m_Clock.Runtime());

}

void AdventureLogic::Shutdown()
{
	aPROFILE_FUNCTION();
}

void AdventureLogic::Runtime(dahlTimestep ts)
{
	aPROFILE_FUNCTION();

	this->m_Clock.Runtime();
	if (this->m_Clock.GetSecond() == this->m_PreviousSecond)
		return;
	this->m_PreviousSecond = this->m_Clock.GetSecond();
	Update(ts);
}

void AdventureLogic::Update(dahlTimestep ts)
{
	aPROFILE_FUNCTION();
	std::cout << this->m_Clock.CheckTime() << std::endl;
}