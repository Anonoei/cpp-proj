#include "ChessLogic.h"

//////////////////////////////////////////////////////////////
//  ---------------------  Startup  ----------------------  //
//////////////////////////////////////////////////////////////
void ChessLogic::InitPieces(ChessLogic logic)
{
		//	White pieces
	//	Initalize objects
	KingPiece wKing(60, true);
	QueenPiece wQueen(59, true);

	KnightPiece wKnight1(57, true);
	KnightPiece wKnight2(62, true);

	RookPiece wRook1(56, true);
	RookPiece wRook2(63, true);

	BishopPiece wBishop1(58, true);
	BishopPiece wBishop2(61, true);

	PawnPiece wPawn1(48, true);
	PawnPiece wPawn2(49, true);
	PawnPiece wPawn3(50, true);
	PawnPiece wPawn4(51, true);
	PawnPiece wPawn5(52, true);
	PawnPiece wPawn6(53, true);
	PawnPiece wPawn7(54, true);
	PawnPiece wPawn8(55, true);

	//	Assign objects to map
	logic.AddPiece(wKing.GetLocation(), wKing);
	logic.AddPiece(wQueen.GetLocation(), wQueen);

	logic.AddPiece(wKnight1.GetLocation(), wKnight1);
	logic.AddPiece(wKnight2.GetLocation(), wKnight2);

	logic.AddPiece(wRook1.GetLocation(), wRook1);
	logic.AddPiece(wRook2.GetLocation(), wRook2);

	logic.AddPiece(wBishop1.GetLocation(), wBishop1);
	logic.AddPiece(wBishop2.GetLocation(), wBishop2);

	logic.AddPiece(wPawn1.GetLocation(), wPawn1);
	logic.AddPiece(wPawn2.GetLocation(), wPawn2);
	logic.AddPiece(wPawn3.GetLocation(), wPawn3);
	logic.AddPiece(wPawn4.GetLocation(), wPawn4);
	logic.AddPiece(wPawn5.GetLocation(), wPawn5);
	logic.AddPiece(wPawn6.GetLocation(), wPawn6);
	logic.AddPiece(wPawn7.GetLocation(), wPawn7);
	logic.AddPiece(wPawn8.GetLocation(), wPawn8);

		//	Black pieces
	//	Initalize Objects
	KingPiece bKing(4, false);
	QueenPiece bQueen(3, false);

	KnightPiece bKnight1(1, false);
	KnightPiece bKnight2(6, false);

	RookPiece bRook1(0, false);
	RookPiece bRook2(7, false);

	BishopPiece bBishop1(2, false);
	BishopPiece bBishop2(5, false);

	PawnPiece bPawn1(8,  false);
	PawnPiece bPawn2(9,  false);
	PawnPiece bPawn3(10, false);
	PawnPiece bPawn4(11, false);
	PawnPiece bPawn5(12, false);
	PawnPiece bPawn6(13, false);
	PawnPiece bPawn7(14, false);
	PawnPiece bPawn8(15, false);

	//	Assign objects to map
	logic.AddPiece(bKing.GetLocation(), bKing);
	logic.AddPiece(bQueen.GetLocation(), bQueen);

	logic.AddPiece(bKnight1.GetLocation(), bKnight1);
	logic.AddPiece(bKnight2.GetLocation(), bKnight2);

	logic.AddPiece(bRook1.GetLocation(), bRook1);
	logic.AddPiece(bRook2.GetLocation(), bRook2);

	logic.AddPiece(bBishop1.GetLocation(), bBishop1);
	logic.AddPiece(bBishop2.GetLocation(), bBishop2);

	logic.AddPiece(bPawn1.GetLocation(), bPawn1);
	logic.AddPiece(bPawn2.GetLocation(), bPawn2);
	logic.AddPiece(bPawn3.GetLocation(), bPawn3);
	logic.AddPiece(bPawn4.GetLocation(), bPawn4);
	logic.AddPiece(bPawn5.GetLocation(), bPawn5);
	logic.AddPiece(bPawn6.GetLocation(), bPawn6);
	logic.AddPiece(bPawn7.GetLocation(), bPawn7);
	logic.AddPiece(bPawn8.GetLocation(), bPawn8);

	cLOG(Level::Info, "Initalized Pieces!");
}

void ChessLogic::InitBoard(ChessBoard board)
{
	board.Init();
	cLOG(Level::Info, "Initalized Board!");
}
//////////////////////////////////////////////////////////////
//  --------------------  Commands  ----------------------  //
//////////////////////////////////////////////////////////////
bool ChessLogic::Move(Piece, int MoveLocation)
{
	return false;
}

std::vector<int> ChessLogic::ShowMoves(Piece)
{
	std::vector<int> ValidMoves;
	ValidMoves.push_back(0);
	return ValidMoves;
}

//////////////////////////////////////////////////////////////
//  ---------------------  Getters  ----------------------  //
//////////////////////////////////////////////////////////////
//	Get piece from location
Piece ChessLogic::GetPiece(int location)
{
	std::map<int, Piece>::iterator it;
	for (it = PieceMap.find(location); it != PieceMap.end(); it++)
	{
		std::string message = "Found object: " + std::to_string(it->first);
		cLOG(Level::Trace, message.c_str());
		return it->second;	//	return the piece
	}
}

int ChessLogic::GetLocation(Piece piece)
{
	std::map<int, Piece>::iterator it;
	//for (it = PieceMap.find(piece); it != PieceMap.end(); it++)
	//{
	//	std::string message = "Found object: " + std::to_string(it->first);
	//	cLOG(Level::Trace, message.c_str());
	//	return it->first;	//	return the piece
	//}
	return 0;
}





//////////////////////////////////////////////////////////////
//  ---------------------  Private  ----------------------  //
//////////////////////////////////////////////////////////////
void ChessLogic::CapturePiece(int MoveLocation)
{

}

bool ChessLogic::CheckIfChecked()
{
	return false;
}