#pragma once

#include "TetrisBase.h"

#include <iostream>
#include <array>
#include <vector>

class TetrisBoard
{
public:
	TetrisBoard() { Init(); };
	~TetrisBoard() {}

	void Init();

	void Clear(int rows);
	void Print(char nextPiece);

	void SpawnPoly(Points locations);

	void Draw(Points NewLocatation);
	void Erase(Points OldLocations);

	void SetMaxHeight(Point point);

	//	Getters
	int GetWidth()     const { return this->Width;     }
	int GetHeight()    const { return this->Height;    }
	int GetBoardSize() const { return this->BoardSize; }

	int GetMaxHeight(int PosX);

private:
	static const int Width = 12;
	static const int Height = 20;
	static const int BoardSize = Width * Height;
	//		   Row # | Column #
	char Board[Height][Width] = { ' ' };

	Points Heights;	//	This contains the (lowest) height for each X value on the board;
};

