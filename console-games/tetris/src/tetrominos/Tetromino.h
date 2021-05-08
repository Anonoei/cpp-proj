/////////////////////////////////////////////////////////////
//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++17
// Part of Tetris
//////////////////////////////
#pragma once

#include "TetrisBase.h"

#include <map>
#include <vector>
#include <cmath>

/*
	Tetrominos: - These are the default spawning positions
	/=======================================================\
	|-  I  -|-  J  -|-  L  -|-  O  -|-  S  -|-  Z  -|-  T  -|
	|-------|-------|-------|-------|-------|-------|-------|
	|	X	|	X	|	X	|		|		|		|		|
	|	X	|	X	|	X	|	XX	|	XX	|	XX	|	X	|
	|	X	|  XX	|	XX	|	XX	|  XX	|	 XX	|  XXX	|
	|	X	|		|		|		|		|		|		|
	\=======================================================/
*/
class Tetromino
{
public:
	Tetromino()
		: Type(Poly::Null), Orientation(Rotation::Up), Position(Translation::Null), Tetro(nullptr), IsMoving(true), OriginIndex(0)
	{}
	~Tetromino() {}

	Tetromino* Spawn(int SpawnNum);	//	Called to Spawn Tetromino from the SpawnNum returned from Queue()
	bool Rotate(Rotation rotation, Point& value, int index);	//	Changes rotation
	bool Translate(Translation translate, Point& value);	//	Changes translation

	//	Getters
	Tetromino* GetTetro()         { return this->Tetro; }				//	Used in TetrisLogic
	Poly GetType()                { return this->Type; }				//	Shouldn't be used
	Rotation GetRotation()        { return this->Orientation; }			//	Shouldn't be used
	Translation GetTranslation()  { return this->Position; }			//	Shouldn't be used
	Point GetLocation(int index)  { return this->Locations[index]; }	//	Returns location at specified index
	Points GetLocations()         { return this->Locations; };			//	Returns locations
	Points GetPreviousLocations() { return this->OldLocations; };		//	Returns PreviousLocations
	bool IsPieceMoving()          { return this->IsMoving; }			//	Returns whether the piece is moving
	int GetOriginIndex()          { return this->OriginIndex - 1; }			//	Returns the index of the piece's origin
	Point GetOrigin()             { return this->Locations[this->GetOriginIndex()]; }

	//	Setters
	void SetTetro(Tetromino* tetro) { this->Tetro = tetro; }
	void SetType(Poly type) { this->Type = type; }
	void SetRotation(Rotation orientation) { this->Orientation = orientation; }
	void SetTranslation(Translation position) { this->Position = position; }
	void SetLocations(Points locations)
	{
		for (int i = 0; i < locations.Size(); i++)
		{
			if (locations[i].x < 0)
				locations[i].x = 0;
		}

		this->OldLocations = this->Locations;
		this->Locations = locations;
	}
	void SetPieceMoving(bool moving) { this->IsMoving = moving; }
	void SetOriginIndex(int index)     { this->OriginIndex = index; }

	//	This function is overriden inside the specific poly class & initalizes locations
	void Create() {};

protected:
	Poly Type;
	Rotation Orientation;
	Translation Position;
	Tetromino* Tetro;

	Points Locations;
	Points OldLocations;
	int OriginIndex;
	bool IsMoving;

};
