#include "chess.h"

#define gChess Chess::Get()

int main()
{
	cLOG(Level::Info, "Console-Chess Initalizing...");
	gChess.Startup();
	
}	//	END main()

void Chess::Startup()
{
	cLOG(Level::Info, "Begining startup...");
	gChess.s_Logic.InitPieces(gChess.s_Logic);
	gChess.s_Logic.InitBoard(gChess.s_Board);

}	//	END Chess::Startup()

void Chess::Runtime()
{
	while (true)
	{

	}

}	//	END Chess::Runtime()

void Chess::Shutdown()
{
	cLOG(Level::Info, "Shutting down...");

}	//	END Chess::Shutdown()

void Chess::GetCommand()
{

}	//	END Chess::GetCommand()

void Chess::PreformCommand()
{

}	//	END Chess::PreformCommand()