#pragma once

#include "Core.h"
#include "aPiece.h"

class KingPiece : public Piece
{
public:
	KingPiece(int startLocation, bool IsWhite);
	~KingPiece() {}

	bool CanMove(int location);
	std::vector<int> CheckMoves();
};