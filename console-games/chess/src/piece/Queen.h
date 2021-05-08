#pragma once

#include "Core.h"
#include "aPiece.h"

class QueenPiece : public Piece
{
public:
	QueenPiece(int startLocation, bool IsWhite);
	~QueenPiece() {}

	bool CanMove(int location);
	std::vector<int> CheckMoves();
};