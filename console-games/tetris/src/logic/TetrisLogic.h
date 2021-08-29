/////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++17
// Part of Tetris
//////////////////////////////
#pragma once

#include "TetrisBase.h"
#include "board/TetrisBoard.h"
#include "tetrominos/Tetromino.h"

class TetrisLogic
{
public:
	TetrisLogic() { Init(); }
	~TetrisLogic() {}

	void Init();

	int Queue();

	Points Spawn();

	bool Update();
	 
	//	Getters
	int GetNextSpawn() { return SpawnIndex == 7 ? this->SpawnNum[0] : this->SpawnNum[this->SpawnIndex]; }
	char GetNextChar()
	{
		int NextPiece = GetNextSpawn();
		if (NextPiece == 0)
			return 'L';
		else if (NextPiece == 1)
			return 'J';
		else if (NextPiece == 2)
			return 'L';
		else if (NextPiece == 3)
			return 'O';
		else if (NextPiece == 4)
			return 'S';
		else if (NextPiece == 5)
			return 'Z';
		else
			return 'T';
	}
	bool IsMoving()
	{ 
		if (this->Tetro == nullptr)	//	The tetro ins't created yet
			return this->IsPolyMoving;
		if (this->IsPolyMoving != this->Tetro->IsPieceMoving())
			SetIsMoving(this->Tetro->IsPieceMoving());
		return this->IsPolyMoving;
	}
	//	This stores the float values for movement, and calls MoveTetro to move the piece when valid
	void Move(daTimestep ts, Translation direction);
	//	This moves the current tetromino on the screen
	void MoveTetro(Translation direction);
	//	This stores the float values for rotation, then calls RotateTetro to rotate it
	void Rotate(daTimestep ts, Rotation direction);

	void RotateTetro(Rotation direction);

	//	Helper functions
	void     SpawnTetro(Points locations) { this->s_Board.SpawnPoly(locations, this->Tetro->GetType()); }	//	Spawn a Tetromino on the board
	Points   GetLocations()               { return this->Tetro->GetLocations();         }	//	Get the locations of the Tetromino
	Points   GetOldPositions()            { return this->Tetro->GetPreviousLocations(); }	//	Get the old locations of the Tetromino
	Rotation GetOrientation()             { return this->Tetro->GetRotation();          }	//	Get the rotation of the Tetromino
	int      GetMaxHeight(int PosX)       { return this->s_Board.GetMaxHeight(PosX);    }	//	Get the Max Height at a specific column
	bool     GetUpdateBoard()             { return this->UpdateBoard; }
	void     SetUpdateBoard(bool update)  { this->UpdateBoard = update; }
	Point    GetOrigin()                  { return this->Tetro->GetOrigin(); }


	//	Setters
	void SetIsMoving(bool moving) { this->IsPolyMoving = moving; }
private:
	void QueueNextArray();
	bool CheckHeight();
	void CheckWidth();
	void EraseRows();
private:
	int SpawnNum[7] = { 0 };
	int SpawnIndex = 0;
	bool IsPolyMoving;		//	If poly is moving on the screen
	Tetromino* Tetro;
	TetrisBoard s_Board;	//	Instance of the TetrisBoard

	int HighestLocation;	//	This holds the (lowest) y on the board
	float m_LastFrameTime = 0.0f;
	std::vector<fPoint> floatPoints;
	float RotateTimer = 0.0f;
	bool UpdateBoard = false;
	bool ActiveGame = true;

	std::vector<int> RemoveRows;	//	Holds the rows to erase
};

