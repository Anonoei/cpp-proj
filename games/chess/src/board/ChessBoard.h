#pragma once

#include "Core.h"
#include <array>
#include "piece/aPiece.h"

class ChessBoard
{
public:
	static void Init();

	static void Draw();

	static void SetLocation(int location);
	static void SetDimentions(int width, int height);

	static int& GetDimentions() {}
private:
	int Width = 8, Height = 8;
	int BoardSize = Width * Height;

	Piece board[64];

};	//	END class Board