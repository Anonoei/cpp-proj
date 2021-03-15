#pragma once

#include "Core.h"
#include <vector>

enum class Type
{
	King = 0,
	Queen = 1,
	Knight = 2,
	Rook = 3,
	Bishop = 4,
	Pawn = 5
};

class Piece
{
public:
	Piece()
		: Location(0), Design('X'), IsPieceWhite(false), type(Type::King)
	{}
	Piece(Type type, int startLocation, bool IsWhite);
	~Piece() {}

	//	Getters
	int GetLocation() { return this->Location;     }
	char GetDesign()  { return this->Design;       }
	bool IsWhite()    { return this->IsPieceWhite; }
	Type GetType()    { return this->type;         }

	//	Setters
	void SetLocation(int location) { this->Location = location; }
	void SetDesign(char design)    { this->Design = design; }
	void SetIsWhite(bool IsWhite)  { this->IsPieceWhite = IsWhite; }
	void SetType(Type type)        { this->type = type; }

private:
	int Location;
	char Design;
	bool IsPieceWhite;
	Type type;

};	//	END class Piece