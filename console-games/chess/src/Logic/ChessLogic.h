#pragma once

#include "Core.h"
#include "piece/aPiece.h"
#include "piece/King.h"
#include "piece/Queen.h"
#include "piece/Knight.h"
#include "piece/Bishop.h"
#include "piece/Rook.h"
#include "piece/Pawn.h"

#include "board/ChessBoard.h"

#include <map>
#include <vector>
#include <string>

enum class Turn
{
	White = 0, Black = 1
};

class ChessLogic
{
public:
	//	Startup
	static void InitPieces(ChessLogic logic);
	static void InitBoard(ChessBoard board);

	//	Commands
	bool Move(Piece, int MoveLocation);
	std::vector<int> ShowMoves(Piece);

	//	Getters
	Piece GetPiece(int location);
	int GetLocation(Piece piece);

private:
	//	Private functions
	void CapturePiece(int MoveLocation);
	bool CheckIfChecked();

	void AddPiece(int location, Piece piece) { PieceMap.emplace(location, piece); }

private:
	std::map<int, Piece> PieceMap;

};	//	END class ChessLogic