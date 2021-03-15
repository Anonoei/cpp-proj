#include "Tetris.h"

#include "TetrisBase.h"
#include "input/TetrisInput.h"	//	Temporary Input Class (windows only)

int main(void)
{
	srand((unsigned int)time(NULL));
	Tetris tetris;
	tetris.Startup(tetris);
	return 0;
}

void Tetris::Startup(Tetris tetris)
{
	tLOG(Level::Info, "Initalizing Tetris...");

	this->s_Logic.Init();

	tetris.Runtime(tetris);
}

void Tetris::Runtime(Tetris tetris)
{
	using namespace std::chrono_literals;
	while (true)
	{
		std::this_thread::sleep_for(500ms);
		if (!s_Logic.IsMoving())
		{
			Points locations = s_Logic.Spawn();
			this->s_Logic.SpawnTetro(locations);
		}
		else	//	The piece is moving
		{
			Translation translate = TetrisInput::CheckTranslationInput();
			Rotation rotate = TetrisInput::CheckRotationInput();
			if (translate == Translation::Null)
				s_Logic.Move(Translation::Down);
			else	//	Player is trying to move the piece
				s_Logic.Move(translate);

			if (rotate != Rotation::Null)	//	Player is trying to rotate the piece
				s_Logic.Rotate(rotate);
		}
		this->s_Logic.Update();
	}
}

void Tetris::Shutdown(Tetris tetris)
{

}