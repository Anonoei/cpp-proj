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

	void Update();
	 
	//	Getters
	int GetNextSpawn() { return this->NextSpawnNum; }
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

	//	Helper functions
	void     SpawnTetro(Points locations) { this->s_Board.SpawnPoly(locations); }	//	Spawn a Tetromino on the board
	Points   GetLocations()               { return this->Tetro->GetLocations();         }	//	Get the locations of the Tetromino
	Points   GetOldPositions()            { return this->Tetro->GetPreviousLocations(); }	//	Get the old locations of the Tetromino
	Rotation GetOrientation()             { return this->Tetro->GetRotation();          }	//	Get the rotation of the Tetromino
	int      GetMaxHeight(int PosX)       { return this->s_Board.GetMaxHeight(PosX);    }	//	Get the Max Height at a specific column
	void Move(Translation direction);
	void Rotate(Rotation direction);

	//	Setters
	void SetIsMoving(bool moving) { this->IsPolyMoving = moving; }
private:
	void CheckHeight();
	void GameOver();
private:
	int SpawnNum, NextSpawnNum;
	bool IsPolyMoving;	//	If poly is moving on the screen
	Tetromino* Tetro;
	TetrisBoard s_Board;	//	Instance of the TetrisBoard

	int HighestLocation;	//	This holds the (lowest) y on the board
};

