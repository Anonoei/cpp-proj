#pragma once

#include "Core.h"
#include "aPiece.h"

class RookPiece : public Piece
{
public:
	RookPiece(int startLocation, bool IsWhite);
	~RookPiece() {}

	bool CanMove(int location);
	std::vector<int> CheckMoves();
};