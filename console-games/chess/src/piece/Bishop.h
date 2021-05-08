#pragma once

#include "Core.h"
#include "aPiece.h"

class BishopPiece : public Piece
{
public:
	BishopPiece(int startLocation, bool IsWhite);
	~BishopPiece() {}

	bool CanMove(int location);
	std::vector<int> CheckMoves();
};