/////////////////////////////////////////////////////////////
//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++17
// Part of Tetris
//////////////////////////////
#include "Tetris.h"

#include "TetrisBase.h"
#include "input/TetrisInput.h"	//	Temporary Input Class (windows only)

#include <regex>
#include <limits>

int main(void)
{
	srand((unsigned int)time(NULL));	//	Seed for random numbers
	bool m_KeepPlaying = true;
	uint32_t m_TotalScore = 0;
	std::string m_PlayerInput;
	while (m_KeepPlaying)
	{
		Tetris* tetris = new Tetris;	//	Create an instance of Tetris
		tPROFILE_START("Startup", "tetris-startup.json");	//	DEBUG only: profile startup functions
		tetris->Startup();
		tPROFILE_END();

		bool running = true;
		tPROFILE_START("Runtime", "tetris-runtime.json");
		while (tetris->IsRunning())
		{
			//	Calculate Timestep to make moving pieces non-frame restricted
			float time = tetris->GetTime();
			daTimestep timestep = time - tetris->GetLastFrameTime();
			tetris->SetLastFrameTime(time);

			running = tetris->Runtime(timestep);
			tetris->SetIsRunning(running);
		}
		tPROFILE_END();

		//	Ask if the player wants to keep playing
		std::cin.clear();
		daPrint(fgRed, "\n\tKeep playing? (y/N) > ");
		while (true)
		{
			std::cin.clear();
			std::cin >> m_PlayerInput;
			if (std::regex_match(m_PlayerInput, std::regex("[nN]")))	//	No
			{
				m_KeepPlaying = false;
				break;
			}
			else if (std::regex_match(m_PlayerInput, std::regex("[yY]")))	//	Yes
				break;
			else
			{
				m_KeepPlaying = false;
			}
		}

		tPROFILE_START("Shutdown", "tetris-shutdown.json");
		tetris->Shutdown();
		delete tetris;
		tPROFILE_END();
	}
	std::cout << "\n";
	daPrintChar(bgRed,   "\n\t=========================================");
	daPrintChar(bgRed,   "\n\t=                                       =");
	daPrintChar(bgRed,   "\n\t=                                       =");
	daPrintChar(bgGreen, "\n\t=                                       =");
	daPrintChar(bgGreen, "\n\t=>          Thanks for playing!        <=");
	daPrintChar(bgGreen, "\n\t=                                       =");
	daPrintChar(bgBlue,  "\n\t=                                       =");
	daPrintChar(bgBlue,  "\n\t=                                       =");
	daPrintChar(bgBlue,  "\n\t=========================================");
	std::cout << "\n\n";
	std::cin.clear();
	std::cin.get();
	return 0;
}

void Tetris::Startup()
{
	tPROFILE_FUNCTION();
	std::string Version = tVERSION;
	std::string VersionStr = "\n\t    Verison: " + Version;
	tLOG(Level::Info, "Initalizing Tetris...");
	daPrint(fgBlue, "\n\t================================================");
	daPrint(fgBlue, "\n\t=                                              =");
	daPrint(fgBlue, "\n\t=     MMMMM  MMM  MMMMM  MMM   MMMMM   MMM     =");
	daPrint(fgBlue, "\n\t=       M    M      M    M  M    M    M        =");
	daPrint(fgBlue, "\n\t=       M    MM     M    MMM     M     MM      =");
	daPrint(fgBlue, "\n\t=       M    M      M    M  M    M       M     =");
	daPrint(fgBlue, "\n\t=       M    MMM    M    M  M  MMMMM  MMM      =");
	daPrint(fgBlue, "\n\t=                                              =");
	daPrint(fgBlue, "\n\t================================================");
	daPrint(fgBlue, VersionStr.c_str());
	std::cout << std::endl;
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(2000ms);
	this->s_Logic.Init();
	this->m_Timer.Reset();
}

bool Tetris::Runtime(daTimestep ts)
{
	tPROFILE_FUNCTION();
	if (!s_Logic.IsMoving())	//	There is no piece on the board
	{
		Points locations = s_Logic.Spawn();
		this->s_Logic.SpawnTetro(locations);
	}
	else	//	The piece is moving
	{
		Translation translate = TetrisInput::CheckTranslationInput();
		Rotation rotate = TetrisInput::CheckRotationInput();
		if (translate == Translation::Null)
			s_Logic.Move(ts, Translation::Down);
		else	//	Player is trying to move the piece
			s_Logic.Move(ts, translate);

		if (rotate != Rotation::Null)	//	Player is trying to rotate the piece
			s_Logic.Rotate(ts, rotate);

		if (GetKeyState('K') & 0x8000)
			return false;
	}
	return this->s_Logic.Update();
}

void Tetris::Shutdown()
{
	tPROFILE_FUNCTION();
}