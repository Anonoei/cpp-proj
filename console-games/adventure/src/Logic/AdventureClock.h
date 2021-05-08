#pragma once

#include "Core/Base.h"
#include <thread>

class AdventureClock
{
public:
	AdventureClock() {}
	~AdventureClock() {}

	void Init();
	void Runtime();
	void End();

	std::string CheckTime();
	std::string CheckClock();
	std::string CheckSeconds();

	//	Getters
	inline float GetMillis() { return this->m_Time.ElapsedMillis(); }
	inline float GetTime()   { return this->m_Time.Elapsed(); }
	inline uint64_t GetDay()    { return this->m_Day; }
	inline uint16_t GetHour()   { return this->m_Hour; }
	inline uint16_t GetMinute() { return this->m_Minute; }
	inline uint16_t GetSecond() { return ((uint32_t)GetMillis() - (GetMinute() * 15000)) * 0.004; }
private:
	dahlTimer m_Time;
	uint64_t m_Day = 0;
	uint16_t m_Hour = 6;
	uint16_t m_Minute = 0;

	uint16_t m_PreviousTime = 0;
};

