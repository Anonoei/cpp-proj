//---===============================================================================================---
//---=     ___     ____      _     _    _____    __    _    _______   _     _    ____     _____    =---
//---=    / _ \   |  _ \    | |   | |  |  ___|  |  \  | |  |__   __| | |   | |  |  _ \   |  ___|   =---
//---=   / /_\ \  | | \ \   | |   | |  | |__    | | \ | |     | |    | |   | |  | |_\ |  | |__     =---
//---=   |  _  |  | |  | |  | |   | |  |  __|   | |\ \| |     | |    | |   | |  |  _  /  |  __|    =---
//---=   | | | |  | |_/ /    \ \_/ /   | |___   | | \ | |     | |     \ \_/  |  | | | |  | |___    =---
//---=   |_| |_|  |____/      \___/    |_____|  |_|  \__|     |_|      \___/\|  |_| \_\  |_____|   =---
//---=                                                                                             =---
//---===============================================================================================---
//---=---------------------------------------  Version 0.0.2a  ------------------------------------=---
//---===============================================================================================---
//
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++17
//////////////////////////////////////////
//
//  This is a text based adventure game.
//    Each in-game day takes 6 hours
//    
//
//
#pragma once

#include "Core/Base.h"
#include "Logic/AdventureLogic.h"
#include "Commands/AdventureCommands.h"

#include <future>
#include <thread>
#include <chrono>

class Adventure
{
public:
	Adventure() {}
	~Adventure() {}

	void Startup();
	bool Runtime(dahlTimestep ts);
	void Shutdown();

	float GetTime() { return this->m_Timer.ElapsedMillis(); }

	bool IsRunning() { return this->m_Running; }
	void SetIsRunning(bool enable) { this->m_Running = enable; }

	float GetLastFrameTime() { return this->m_LastFrameTime; }
	void SetLastFrameTime(float time) { this->m_LastFrameTime = time; }

private:
	dahlTimer m_Timer;
	AdventureLogic m_Logic;
	AdventureCommands m_Commands;
	bool m_Running = true;
	float m_LastFrameTime = 0.0f;
};

