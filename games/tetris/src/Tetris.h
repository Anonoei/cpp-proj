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

	void Startup(Tetris tetris);
	void Runtime(Tetris tetris);
	void Shutdown(Tetris tetris);
private:
	TetrisLogic s_Logic;
};