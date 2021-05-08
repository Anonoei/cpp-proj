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
	static void Startup();
	static void Runtime();
	static void Shutdown();

	static void GetCommand();
	static void PreformCommand();
private:
	ChessLogic s_Logic;
	ChessBoard s_Board;
};	//	END class Chess