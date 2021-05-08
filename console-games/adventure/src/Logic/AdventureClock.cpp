#include "AdventureClock.h"

void AdventureClock::Init()
{
	aPROFILE_FUNCTION();

	this->m_Time.Reset();
}


void AdventureClock::Runtime()
{
	aPROFILE_FUNCTION();

	uint32_t time = (uint32_t)GetTime();
	if (time == m_PreviousTime)
		return;

	if (time != 0 && time % 15 == 0)
		this->m_Minute += 1;

	if (this->m_Minute == 60)
	{
		this->m_Hour += 1;
		this->m_Minute = 0;
		this->m_Time.Reset();
	}

	if (this->m_Hour == 24)
	{
		this->m_Day += 1;
		this->m_Hour = 1;
	}

	this->m_PreviousTime = time;
}

void AdventureClock::End()
{
	aPROFILE_FUNCTION();
}

std::string AdventureClock::CheckTime()
{
	aPROFILE_FUNCTION();

	std::string Day = "Day: " + std::to_string(GetDay());
	std::string Hour = std::to_string(GetHour());
	if (Hour.size() == 1)
		Hour = "0" + Hour;
	std::string Minute = std::to_string(GetMinute());
	if (Minute.size() == 1)
		Minute = "0" + Minute;
	std::string Second = std::to_string(GetSecond());
	if (Second.size() == 1)
		Second = "0" + Second;
	return (Day + " " + Hour + ":" + Minute + "." + Second);
}

std::string AdventureClock::CheckClock()
{
	aPROFILE_FUNCTION();

	std::string Hour = std::to_string(GetHour());
	if (Hour.size() == 1)
		Hour = "0" + Hour;
	std::string Minute = std::to_string(GetMinute());
	if (Minute.size() == 1)
		Minute = "0" + Minute;
	return (Hour + ":" + Minute);
}
std::string AdventureClock::CheckSeconds()
{
	aPROFILE_FUNCTION();

	std::string Hour;
	std::string Minute;
	std::string Second;
	return (Hour + ":" + Minute + "." + Second);
}