//--------------------------------------------------------------------------------------
//----==============================================================================~~~~
//----=                                                                            =----
//----=         MMMM   M   M   MMMM    MMM    MMM      MMM    MMMMM                =----
//----=        M       M   M   M      M      M        M   M     M         M        =----
//----=        M       MMMMM   MMM     MM     MM      MMMMM     M         M        =----
//----=        M       M   M   M         M      M     M   M     M         MMM      =----
//----=         MMMM   M   M   MMMM   MMM    MMM      M   M   MMMMM   X   M  M     =----
//----=                                                                            =----
//----==============================================================================~~~~
//------------------------------    version 0.0.1    -----------------------------------
// Author: Anonoei (https ://github.com/anonoei)
// License : GPLv3
// This file is a part of console-chess.cpp 
// This file contains the AI logic for my game console-chess

#pragma once
#define ChessAI_H

#include "ChessLogic.h"
#include <string>
#include <array>
#include <vector>

extern const unsigned int iBoardSize;

extern unsigned int iWhiteScore;			//	Stores WHITE score based on number of pieces	--	For ChessAI
extern unsigned int iBlackScore;			//	Stores BLACK score based on number of pieces	--	For ChessAI
extern std::vector<std::string> dHistory;	//	Stores Debug History	--	written to when something happens inside ChessLogic
extern char CheckBoard[8 * 8];				//	Holds value for where pieces can move -- Used for checking for check / Checking valid moves
extern std::string sBoard[8 * 8];			//	Holds class name of piece and serves as a search function for objects within the class

extern bool CurrentColorIsWhite;		//	Current move is WHITE

extern bool bMoveCheck;					//	Used in printBoard if the player chose to check if a move was valid and shows avialable moves

extern unsigned int iMoveFrom;			//	Player selected Piece is Moving From
extern unsigned int iMoveTo;			//	Player selected Piece is attempting to Move To

extern unsigned int iDepthAI;

std::vector<int> iValidMoves;
int iMaximumEval = 555;
int iMinimumEval = 555;
unsigned int iMostValueMoveFrom = 0;
unsigned int iMostValueMoveTo = 0;

namespace ChessAI_H
{
	bool bFindPiece(std::string, int, bool);

	void vCallAI()
	{
		int lDepthAI = iDepthAI;
		int iCurrentPosValue = 555;

		int iMoveFromLocal = 0;
		int iMoveToLocal = 0;
		std::string pName;
		bool bPieceFound = false;
		bool bLocalColorIsWhite = CurrentColorIsWhite;
		for (unsigned int i = 0; i <= iBoardSize; i++)
		{
			bLocalColorIsWhite = !bLocalColorIsWhite;	//	First, the possible player moves are checked
			pName = sBoard[i];
			bPieceFound = bFindPiece(pName, i, bLocalColorIsWhite);
			if (bPieceFound)
			{
				//	Now a valid piece has been found, and it's possible moves are written to CheckBoard.
				for (int j = 0; i <= iBoardSize; j++)
				{
					if (CheckBoard[i] != ' ')
						iValidMoves.push_back(j);
				}
				//for (int j = iValidMoves.size(); j > 0 ; j--)
				//{
				//	iMoveToLocal = iValidMoves.at(j);
				//	iMoveFromLocal = i;
				//	iValidMoves.pop_back();
				//}
				iMoveFromLocal = i;	//	set iMoveFromLocal to the value where a valid piece was found
				iCurrentPosValue = iMiniMax(iMoveFromLocal, lDepthAI, bLocalColorIsWhite, false);	//	send the (current piece iMoveFrom , Local Depth AI , and b LocalColorIsWhite);
				if (CurrentColorIsWhite)	//	This means the AI's color is WHITE
				{
					//if (iCurrentPosValue > iLastPosValue)
					//{
					//	iMostValueMoveFrom = i;
					//	iMostValueMoveTo = y;
					//}
				}

			}	//	End if bPieceFound
		}	//	End FOR i <= iBoardSize
	}	//	END vCallAI();




	//	Inital call
	//	iMiniMax(currentPosition, 3, true)
	//	One way to return a value is to 

	//	Add the value of the white pieces, 
	//	and subtract the value of the black pieces

	int iMiniMax(int cPosition, int depth, bool bMaximizePlayer, bool bChildEval)
	{
		if (depth == 0)	//	Or Gameover in position
		{
			return cPosition;	//	Static evauluation of position
		}

		if (bMaximizePlayer)
		{
			int iMaxEval = -INT_MAX;
			for (int Children = iValidMoves.size(); Children > 0; Children--)	//	For each child of cPosition
			{
				int child = iValidMoves.at(Children);
				int iEval = iMiniMax(child, depth - 1, false, true);	//	iEval = iMiniMax(child, depth -1, false)
				if (iMaxEval < iEval)	//	if iMaxEval is less than the child eval, set iMaxEval to iEval
					iMaxEval = iEval;	//	iMaxEval = max(iMaxEval, eval)
			}
			iMaximumEval = iMaxEval;	//	return iMaxEval;
		}
		else
		{
			int iMinEval = INT_MAX;
			for (int Children = iValidMoves.size(); Children > 0; Children--)	//	For each child of cPosition
			{
				int child = iValidMoves.at(Children);
				int iEval = iMiniMax(child, depth - 1, false, true);	//	iEval = iMiniMax(child, depth -1, true)
				if (iMinEval > iEval)	//	If iMinEval is greater than the child eval, set iMinEval to iEval
					iMinEval = iEval;	//	iMinEval = min(iMinEval, eval)
			}
			iMinimumEval = iMinEval;	//	return iMinEval;
		}
		depth--;

	}

	// With Alpha-Beta pruning
	int iMiniMaxPruning(int cPosition, int depth, int alpha, int beta, bool bMaximizingPlayer)
	{
		if (depth == 0)	//	Or game over in position
			return cPosition;	//	Static evauluation of position

		if (bMaximizingPlayer)
		{
			int iMaxEval = -INT_MAX;
			//	For each child of position
				//	eval = iMiniMaxPruning(child, depth -1, alpha, beta, false)
			//	iMaxEval = max(iMaxEval, eval)
			//	alpha = max(alpha, eval)
			if (beta <= alpha)
				return;	//	break
			return  iMaxEval;
		}
		else
		{
			int iMinEval = INT_MAX;
			//	For each child of position
				//	eval = iMiniMaxPruning(child, depth -1, alpha, beta, true)
			//	iMinEval = min(iMinEval, eval)
			//	beta = min(beta, eval)
			if (beta <= alpha)
				return;	//	break
			return  iMinEval;
		}
	}

	bool bFindPiece(std::string pName, int i, bool bLocalColorIsWhite)
	{
		bool bPieceFound = false;
		if (CurrentColorIsWhite)
		{
			if (pName.at(0) == 'w')
				bPieceFound = true;
		}
		else
		{
			if (pName.at(0) == 'b')
				bPieceFound = true;
		}
		if (bPieceFound)
		{
			bMoveCheck = true;
			if (CurrentColorIsWhite)
			{
				if (pName == "wKing" || pName == "wking")
					wKing.SetPosition();
				else if (pName == "wQueen" || pName == "wqueen")
					wQueen.SetPosition();
				else if (pName == "wRook1" || pName == "wrook1")
					wRook1.SetPosition();
				else if (pName == "wRook2" || pName == "wrook2")
					wRook2.SetPosition();
				else if (pName == "wBishop1" || pName == "wbishop1")
					wBishop1.SetPosition();
				else if (pName == "wBishop2" || pName == "wbishop2")
					wBishop2.SetPosition();
				else if (pName == "wKnight1" || pName == "wknight1")
					wKnight1.SetPosition();
				else if (pName == "wKnight2" || pName == "wknight2")
					wKnight2.SetPosition();
				else if (pName == "wPawn1" || pName == "wpawn1")
					wPawn1.SetPosition();
				else if (pName == "wPawn2" || pName == "wpawn2")
					wPawn2.SetPosition();
				else if (pName == "wPawn3" || pName == "wpawn3")
					wPawn3.SetPosition();
				else if (pName == "wPawn4" || pName == "wpawn4")
					wPawn4.SetPosition();
				else if (pName == "wPawn5" || pName == "wpawn5")
					wPawn5.SetPosition();
				else if (pName == "wPawn6" || pName == "wpawn6")
					wPawn6.SetPosition();
				else if (pName == "wPawn7" || pName == "wpawn7")
					wPawn7.SetPosition();
				else if (pName == "wPawn8" || pName == "wpawn8")
					wPawn8.SetPosition();
				else
				{
					dHistory.push_back("No valid WHITE piece was found at " + std::to_string(i) + "!");
					return false;
				}
			}
			else
			{
				if (pName == "bKing" || pName == "bking")
					bKing.SetPosition();
				else if (pName == "bQueen" || pName == "bqueen")
					bQueen.SetPosition();
				else if (pName == "bRook1" || pName == "brook1")
					bRook1.SetPosition();
				else if (pName == "bRook2" || pName == "brook2")
					bRook2.SetPosition();
				else if (pName == "bBishop1" || pName == "bbishop1")
					bBishop1.SetPosition();
				else if (pName == "bBishop2" || pName == "bbishop2")
					bBishop2.SetPosition();
				else if (pName == "bKnight1" || pName == "bknight1")
					bKnight1.SetPosition();
				else if (pName == "bKnight2" || pName == "bknight2")
					bKnight2.SetPosition();
				else if (pName == "bPawn1" || pName == "bpawn1")
					bPawn1.SetPosition();
				else if (pName == "bPawn2" || pName == "bpawn2")
					bPawn2.SetPosition();
				else if (pName == "bPawn3" || pName == "bpawn3")
					bPawn3.SetPosition();
				else if (pName == "bPawn4" || pName == "bpawn4")
					bPawn4.SetPosition();
				else if (pName == "bPawn5" || pName == "bpawn5")
					bPawn5.SetPosition();
				else if (pName == "bPawn6" || pName == "bpawn6")
					bPawn6.SetPosition();
				else if (pName == "bPawn7" || pName == "bpawn7")
					bPawn7.SetPosition();
				else if (pName == "bPawn8" || pName == "bpawn8")
					bPawn8.SetPosition();
				else
				{
					dHistory.push_back("No valid BLACK piece was found at " + std::to_string(i) + "!");
					return false;
				}
			}
			bPieceFound = true;
			return bPieceFound;
		}
		return false;
	}



}	//	END namespace ChessAI_H