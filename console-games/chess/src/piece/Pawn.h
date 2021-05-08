#pragma once

#include "Core.h"
#include "aPiece.h"

class PawnPiece : public Piece
{
public:
	PawnPiece(int startLocation, bool IsWhite);
	~PawnPiece() {}

	bool CanMove(int location);
	std::vector<int> CheckMoves();
};