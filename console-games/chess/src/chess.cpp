#include "chess.h"

int main()
{
	cLOG(Level::Info, "Console-Chess Initalizing...");

	Chess* chess;
	chess->Startup();

	chess->Runtime();

	chess->Shutdown();
	
}	//	END main()

void Chess::Startup()
{
	cLOG(Level::Info, "Begining startup...");
	this->s_Logic.InitPieces(gChess.s_Logic);
	this->s_Logic.InitBoard(gChess.s_Board);

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