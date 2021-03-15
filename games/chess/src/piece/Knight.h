#pragma once

#include "Core.h"
#include "aPiece.h"

class KnightPiece : public Piece
{
public:
	KnightPiece(int startLocation, bool IsWhite);
	~KnightPiece() {}

	bool CanMove(int location);
	std::vector<int> CheckMoves();
};