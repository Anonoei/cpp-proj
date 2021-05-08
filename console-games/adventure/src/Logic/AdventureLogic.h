#pragma once

#include "AdventureClock.h"
#include "Entities/Entity.h"

#include <atomic>
#include <thread>
#include <chrono>
//#include <mutex>

class AdventureLogic
{
public:
	AdventureLogic() {}
	~AdventureLogic() {}

	void Init();
	void Shutdown();

	void Runtime(dahlTimestep ts);
	void Update(dahlTimestep ts);

	inline bool GameOver() { return this->m_GameOver; }
private:
	void ThreadUpdate(std::atomic<bool>* program_is_running, unsigned int update_interval_millisecs)
	{
		const auto wait_duration = std::chrono::milliseconds(update_interval_millisecs);
		while (program_is_running)
		{
			std::this_thread::sleep_for(wait_duration)
		}
	}
private:
	AdventureClock m_Clock;
	std::vector<std::thread> m_Threads;

	bool m_GameOver = false;
	uint16_t m_PreviousSecond = 0;
};

