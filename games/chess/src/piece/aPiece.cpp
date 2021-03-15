#include "aPiece.h"

Piece::Piece(Type Piecetype, int startLocation, bool IsWhite)
	: type(Piecetype), Location(startLocation), IsPieceWhite(IsWhite), Design('X')
	{
		if (Piecetype == Type::King)
		{
			if (IsPieceWhite)
				this->Design = 'K';
			else
				this->Design = 'k';
		}
		else if (Piecetype == Type::Queen)
		{
			if (IsPieceWhite)
				this->Design = 'Q';
			else
				this->Design = 'q';
		}
		else if (Piecetype == Type::Knight)
		{
			if (IsPieceWhite)
				this->Design = 'N';
			else
				this->Design = 'n';
		}
		else if (Piecetype == Type::Rook)
		{
			if (IsPieceWhite)
				this->Design = 'R';
			else
				this->Design = 'r';
		}
		else if (Piecetype == Type::Bishop)
		{
			if (IsPieceWhite)
				this->Design = 'B';
			else
				this->Design = 'b';
		}
		else if (Piecetype == Type::Pawn)
		{
			if (IsPieceWhite)
				this->Design = 'P';
			else
				this->Design = 'p';
		}
		else
		{
			cLOG(Level::Error, "Unknown Piece type!");
		}
	}