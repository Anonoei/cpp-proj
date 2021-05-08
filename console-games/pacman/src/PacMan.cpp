#include "PacMan.h"

#include "PacManBase.h"

int main(void)
{
	bool bKeepPlaying = true;
	uint32_t iTotalScore = 0;
	while (bKeepPlaying)
	{
		PacMan* pacman = new PacMan;
		pPROFILE_START("Startup", "PacMan-Startup.json");
		pacman->Startup();
		pPROFILE_END();

		bool running = true;
		pPROFILE_START("Runtime", "PacMan-Runtime.json");
		while (running)
		{
			float time = pacman->GetTime();
			daTimestep timestep = time - pacman->GetLastFrameTime();
			pacman->SetLastFrameTime(time);

			running = pacman->Runtime(timestep);
		}
		pPROFILE_END();

		pPROFILE_START("Shutdown", "PacMan-Shutdown.json");
		pacman->Shutdown();
		pPROFILE_END();
	
	}
}	//	END main



void PacMan::Startup()
{
	pPROFILE_FUNCTION();
	pLOG_INFO("Initalizing PacMan!");
	this->s_Logic.Init();
}
bool PacMan::Runtime(daTimestep ts)
{
	pPROFILE_FUNCTION();
	this->s_Logic.Update();
	return true;
}
void PacMan::Shutdown()
{
	pPROFILE_FUNCTION();
}