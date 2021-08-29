//-----------------------------------------------------------------------------------------------------
//----=============================================================================================~~~~
//----=                                                                                           =----
//----=                    MMMMM   MMMM   MMMMM   MMM    MMMMM    MMM                             =----
//----=                      M     M        M     M  M     M     M                                =----
//----=                      M     MMM      M     MMM      M      MM                              =----
//----=                      M     M        M     M  M     M        M                             =----
//----=                      M     MMMM     M     M  M   MMMMM   MMM                              =----
//----=                                                                                           =----
//----=============================================================================================~~~~
//----=----------------------------------  version 0.2.1a  ---------------------------------------=----
//----=============================================================================================----
//	Author: Anonoei (https://github.com/anonoei)
//	License : GPLv3
//	Language: C++17
//	Dependencies: A Sandbox Application
//	This is my ASCII version of the game, Tetris. The names for things are fairly explanatory
//	  Tetris.cpp serves as the game run time, and only controlls what part your in (Startup, Runtime, Shutdown)
//	  TetrisLogic controlls most aspects of the game, and uses TetrisBoard to draw the board, and Tetrominos to create pieces
///////////////////////////////////////////////////
#pragma once

#include <time.h>
#include <chrono>
#include <thread>
#include <cstdlib>

#include "logic/TetrisLogic.h"	//	Class for Tetris Logic

class Tetris
{
public:
	Tetris() {}
	~Tetris() {}

	void Startup();
	bool Runtime(daTimestep ts);
	void Shutdown();

	float GetTime() { return this->m_Timer.ElapsedMillis(); }

	bool IsRunning() { return this->m_Running; }
	void SetIsRunning(bool enable) { this->m_Running = enable; }

	float GetLastFrameTime() { return this->m_LastFrameTime; }
	void SetLastFrameTime(float time) { this->m_LastFrameTime = time; }

	void OnEvent(daEvent& e)
	{
		daEventDispatcher dispatcher(e);
		dispatcher.Dispatch<daKeyPressedEvent>(DA_BIND_EVENT_FN(Tetris::OnKeyPressed));
		dispatcher.Dispatch<daMouseButtonPressedEvent>(DA_BIND_EVENT_FN(Tetris::OnMouseButtonPressed));
	}

	bool OnMouseButtonPressed(daMouseButtonPressedEvent& e)
	{
		
	}

	bool OnKeyPressed(daKeyPressedEvent& e)
	{
		if (e.GetRepeatCount() > 0)
			return false;

		switch (e.GetKeyCode())
		{
			//	Translation
			case daKey::W:
			{
				break;
			}
			case daKey::A:
			{
				break;
			}
			case daKey::S:
			{
				break;
			}
			case daKey::D:
			{
				break;
			}
			//	Rotation
			case daKey::Q:
			{
				break;
			}
			case daKey::E:
			{
				break;
			}
		}
		return false;
	}
private:
	TetrisLogic s_Logic;
	daTimer m_Timer;
	bool m_Running = true;
	float m_LastFrameTime = 0.0f;
};