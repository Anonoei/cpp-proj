#include "Adventure.h"

int main(void)
{
	//srand((unsigned int)time(NULL));
	bool m_KeepPlaying = true;
	while (m_KeepPlaying)
	{
		Adventure* game = new Adventure;
		aPROFILE_START("startup", "adventure-startup.json");
		game->Startup();
		aPROFILE_END();

		bool running = true;
		aPROFILE_START("Runtime", "adventure-runtime.json");
		using namespace std::chrono_literals;
		auto future = std::async(std::launch::async, []
			{
				return 8;
			});
		while (game->IsRunning())
		{
			//	Calculate Timestep
			float time = game->GetTime();
			dahlTimestep timestep = time - game->GetLastFrameTime();
			game->SetLastFrameTime(time);
			auto status = future.wait_for(0ms);
			if (status == std::future_status::ready)
				std::cout << "Thread Finished!" << std::endl;
			else
				std::cout << "Thread still running" << std::endl;

			auto result = future.get();
			running = game->Runtime(timestep);
			game->SetIsRunning(running);
		}
		aPROFILE_END();

		//	If the game ends, we go here
		aPROFILE_START("Shutdown", "adventure-shutdown.json");
		game->Shutdown();
		delete game;
		aPROFILE_END();

		return 0;
	}

}	//	END main()

void Adventure::Startup()
{
	aPROFILE_FUNCTION();
	std::string Version = aVERSION;
	std::string VersionStr = "\n\t===>    Version: " + Version;
	dahlInit();
	aLOG(Level::Info, "Initializing Tetris...");
	dahlPrint(fgBlue, "\n\t==============================================================================================");
	dahlPrint(fgBlue, "\n\t=>    ___     ____      _     _    _____    __    _    _______   _     _    ____     _____   =");
	dahlPrint(fgBlue, "\n\t=>   / _ \\   |  _ \\    | |   | |  |  ___|  |  \\  | |  |__   __| | |   | |  |  _ \\   |  ___|  =");
	dahlPrint(fgBlue, "\n\t=>  / /_\\ \\  | | \\ \\   | |   | |  | |__    | | \\ | |     | |    | |   | |  | |_\\ |  | |__    =");
	dahlPrint(fgBlue, "\n\t=>  |  _  |  | |  | |  | |   | |  |  __|   | |\\ \\| |     | |    | |   | |  |  _  /  |  __|   =");
	dahlPrint(fgBlue, "\n\t=>  | | | |  | |_/ /    \\ \\_/ /   | |___   | | \\ | |     | |     \\ \\_/  |  | | | |  | |___   =");
	dahlPrint(fgBlue, "\n\t=>  |_| |_|  |____/      \\___/    |_____|  |_|  \\__|     |_|      \\___/\\|  |_| \\_\\  |_____|  =");
	dahlPrint(fgBlue, "\n\t=>                                                                                           =");
	dahlPrint(fgBlue, "\n\t==============================================================================================");
	dahlPrint(fgBlue, VersionStr.c_str());
	std::cout << std::endl;
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(2000ms);
	this->m_Logic.Init();
	this->m_Timer.Reset();
	dahlClearScreen();
	dahlResetColors();
}

bool Adventure::Runtime(dahlTimestep ts)
{
	aPROFILE_FUNCTION();
	this->m_Logic.Runtime(ts);
	return !(this->m_Logic.GameOver());
}

void Adventure::Shutdown()
{
	aPROFILE_FUNCTION();
}