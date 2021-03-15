#pragma once

#include "Core.h"

#include "Logic/ChessLogic.h"
#include "board/ChessBoard.h"
#include "piece/aPiece.h"

#include <string>
#include <array>
#include <vector>

class Chess
{
public:
	static Chess& Get() { return s_Chess; }

	static void Startup();
	static void Runtime();
	static void Shutdown();

	static void GetCommand();
	static void PreformCommand();
private:
	static Chess s_Chess;
private:
	ChessLogic s_Logic;
	ChessBoard s_Board;
};	//	END class Chess

Chess Chess::s_Chess;