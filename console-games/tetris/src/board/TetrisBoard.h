/////////////////////////////////////////////////////////////
//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++17
// Part of Tetris
//////////////////////////////
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

	void Print(char nextPiece);

	void SpawnPoly(Points locations, Poly type);

	void Draw(Points NewLocatation, Poly type);
	void Erase(Points OldLocations);
	void EraseRow(int PosY);


	//	Getters
	int GetWidth()     const { return this->Width;     }
	int GetHeight()    const { return this->Height;    }
	int GetBoardSize() const { return this->BoardSize; }
	bool IsLocationClear(Points previousLocations, int y, int x)
	{ 
		Point value;
		for (int i = 0; i < previousLocations.Size(); i++)
		{
			value = previousLocations.Get(i);
			if (value.x == x && value.y == y)
				return true;
		}
		return this->Board[y][x] == ' '  ? true : false;
	}

	int GetMaxHeight(int PosX);
	bool GetFullRow(int PosY);
	void SetMaxHeight(Point point);
private:
	void UpdateNextPiece(char nextPiece);
private:
	static const int Width = 12;
	static const int Height = 20;
	static const int BoardSize = Width * Height;
	//		   Row # | Column #
	char Board[Height][Width] = { ' ' };
	char DrawNextPiece[4][4] = { ' ' };
	char NextPiece = ' ';

	int Heights[Width];	//	This contains the (lowest) height for each X value on the board;
};

