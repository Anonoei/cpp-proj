#pragma once
#define ChessLogic_H

// Version 0.5.0

#include <iostream>
#include <array>
#include <string>


// Initalize GLOBAL VARIBALES
	//	Initalize Board Dimentions
extern const unsigned int iBoardWidth;
extern const unsigned int iBoardHeight;
extern const unsigned int iBoardSize;

	//	Initalize ARRAYS
extern char iBoard			[8 * 8];	//	Holds values the player sees
extern std::string sBoard	[8 * 8];	//	Holds class name of piece and serves as a search function for objects within the class
extern char CheckBoard		[8 * 8];	//	Holds value for where pieces can move -- Used for checking for check / Checking valid moves
extern char CheckmateBoard	[8 * 8];	//	Holds value for checkmate (Can the king move?)
extern char cMoveBoard		[8 * 8];	//	When cmove issued, CheckBoard is copied to this

	//	Initalize VECTORS
extern std::vector<std::string> dHistory;		//	Stores Debug History	--	written to when something happens inside ChessLogic
extern std::vector<std::string> mHistory;		//	Stores Move History		--	written to when piece moves sucessfully
extern std::vector<std::string> sCaptured;		//	Stores Captured Pieces
std::vector<std::string> sbChecking;			//	Stores which pieces are checking the king
std::vector<std::string> swChecking;			//	Stores which pieces are checking the king
extern std::string sErrorMsg;				//	Stores Error Message when something is invalid



extern unsigned int wMoves;					//	Stores total WHITE moves			--	UN-NEEDED unless purpose is found	(due to this->iMoves)
extern unsigned int bMoves;					//	Stores total BLACK moves			--	UN-NEEDED unless purpose is found	(due to this->iMoves)
extern unsigned int iWhiteScore;			//	Stores WHITE score based on number of pieces	--	For ChessAI
extern unsigned int iBlackScore;			//	Stores BLACK score based on number of pieces	--	For ChessAI


	//	Check Logic
extern bool bWhiteKingInCheck;			//	Is the WHITE king in check?
extern bool bBlackKingInCheck;			//	Is the BLACK king in check?
extern bool bCheckmate;					//	Is the game a checkmate?
extern unsigned int iWhiteKingLocation;	//	Stores WHITE king location for Check if Check validation		---		UN-NEEDED if using wKing GetPostion
extern unsigned int iBlackKingLocation;	//	Stores BLACK king location for Check if Check validation		---		UN-NEEDED if using bKing GetPostion
char KingCheckBoard		[8 * 8] = { ' ' };
char lKingCheckBoard	[8 * 8] = { ' ' };
char QueenCheckBoard	[8 * 8] = { ' ' };		//	POSSIBLY UN-NEEDED
char RookCheckBoard		[8 * 8] = { ' ' };		//	POSSIBLY UN-NEEDED
char BishopCheckBoard	[8 * 8] = { ' ' };		//	POSSIBLY UN-NEEDED
char KnightCheckBoard	[8 * 8] = { ' ' };		//	POSSIBLY UN-NEEDED
char PawnCheckBoard		[8 * 8] = { ' ' };		//	POSSIBLY UN-NEEDED
bool bCheckingForCheckmate = false;
bool bCheckingbChecking = false;

	//	Move Logic
bool bMoveToWhite;						//	Find color of Piece the player is attempting to move to
bool bCapturePiece = false;				//	Determine if move to capture a Piece is attempted
extern bool CurrentColorIsWhite;		//	Current move is WHITE		-- Global extern for printBoard
bool bCurrentlyCastling = false;		//	CASTLE move was attempted	--	Set in King logic, used in Rook Logic
bool bCastleSideQueen = false;			//	CASTLE move was QUEENSIDE	--	Set in King logic, used in Rook Logic
extern unsigned int iMoveFrom;			//	Player selected Piece is Moving From
extern unsigned int iMoveTo;			//	Player selected Piece is attempting to Move To

	//	Save this-> values to variable for use inside printBoard function
extern bool iThisWhite;					//	Used in printBoard to verify the piece at a move location is not the same color as the selected piece
extern bool bMoveCheck;					//	Used in printBoard if the player chose to check if a move was valid and shows avialable moves

/*
	//				                W I D T H
	//			       A    B    C    D    E    F    G    H   
	//			    ==========================================
	//			   | #####-----#####-----#####-----#####----- |
	//			 8 | # 0 #- 1 -# 2 #- 3 -# 4 #- 5 -# 6 #- 7 - | 8
	//			   | #####-----#####-----#####-----#####----- |
	//		H	   | -----#####-----#####-----#####-----##### |		//		      A  B  C  D  E  F  G  H   
	//			 7 | - 8 -# 9 #- 10-# 11#- 12-# 13#- 14-# 15# |	7	//		    _________________________
	//		E	   | -----#####-----#####-----#####-----##### |		//		 8 |  0  1  2  3  4  5  6  7	8
	//			   | #####-----#####-----#####-----#####----- |		//		 7 |  8  9 10 11 12 13 14 15	7
	//		I	 6 | # 16#- 17-# 18#- 19-# 20#- 21-# 22#- 23- |	6	//		 6 | 16 17 18 19 20 21 22 23	6
	//			   | #####-----#####-----#####-----#####----- |		//		 5 | 24 25 26 27 28 29 30 31	5
	//		G	   | -----#####-----#####-----#####-----##### |		//		 4 | 32 33 34 35 36 37 38 39	4
	//			 5 | - 24-# 25#- 26-# 27#- 28-# 29#- 30-# 31# |	5	//		 3 | 40 41 42 43 44 45 46 47	3
	//		H	   | -----#####-----#####-----#####-----##### | 	//		 2 | 48 49 50 51 52 53 54 55	2
	//			   | #####-----#####-----#####-----#####----- |		//		 1 | 56 57 58 59 60 61 62 63	1
	//		T	 4 | # 32#- 33-# 34#- 35-# 36#- 37-# 38#- 39- |	4	//
	//			   | #####-----#####-----#####-----#####----- |		//			  A  B  C  D  E  F  G  H
	//			   | -----#####-----#####-----#####-----##### |
	//			 3 | - 40-# 41#- 42-# 43#- 44-# 45#- 46-# 47# |	3	
	//			   | -----#####-----#####-----#####-----##### |
	//			   | #####-----#####-----#####-----#####----- |
	//			 2 | # 48#- 49-# 50#- 51-# 52#- 53-# 54#- 55- |	2	
	//			   | #####-----#####-----#####-----#####----- |
	//			   | -----#####-----#####-----#####-----##### |
	//			 1 | - 56-# 57#- 58-# 59#- 60-# 61#- 62-# 63# |	1	
	//			   | -----#####-----#####-----#####-----##### |
	//			    ==========================================	
	//			       A    B    C    D    E    F    G    H

	Type 0: King	Value: infinite
	Type 1: Queen	Value: 9

	Type 2: Rook	Value: 5

	Type 3: Bishop	Value: 3
	Type 4: Knight	Value: 3

	Type 5: Pawn	Value: 1

*/
namespace ChessLogic_H
{
	void vPieceInit();
	bool bSearchObj(std::string);				//	Finds the Piece object at iMoveFrom and calls logic for that Piece
	void vMoveCheck();				//	Called when player uses 'cmove' to call only the specific piece requested
	bool bIsKingInCheck();			//	Writes all pieces of current color to CheckBoard and tests if opposite king location is on a valid move
	bool bIsKingInCheckmate();		//	Logic for determining if king is in CHECK or CHECKMATE
	bool bRookCastle();				//	Calls Rook piece for castling

	int iFromCharToInt1(std::string, int*);		//	Called to convert player inputted STRING [A7] to the board width
	int iFromCharToInt2(std::string, int*);		//	Called to convert player inputted STRING [A7] to the board height
	char cFromIntToChar1(unsigned int);			//	Called to convert background Integer to player-readable board width
	char cFromIntToChar2(unsigned int);			//	Called to convert background Integer to player-readable board height
	void vLoadHistory(std::string, std::string, std::string, std::string, std::string, std::string, std::string, std::string);

	struct Piece {
	public:
		unsigned int iPosition;
		unsigned int iValue;
		unsigned int iType;
		unsigned int iMoves;
		bool bWhitePiece;
		bool bInGame;
		char cVisual;
		std::string sName;
		unsigned int iPieceNumber;
		//	Construtors
		Piece()
		{
			this->iPosition = 0;
			this->iValue = 0;
			this->iType = 0;
			this->bWhitePiece = true;
			this->iMoves = 0;
			this->bInGame = true;
			this->cVisual = ' ';
			this->sName = "";
			this->iPieceNumber = 0;
		}


		//	Destructors
		~Piece(void) {}

		//	Setters
		bool SetPosition()
		{
			bool bMoveValid = false;
			bCapturePiece = false;
			iThisWhite = this->bWhitePiece;
			if (bMoveCheck && bCheckingForCheckmate)
				bCheckingForCheckmate = false;
			if (!bMoveCheck)
			{
				for (unsigned int i = 0; i < swChecking.size(); i++)
					swChecking.pop_back();
				for (unsigned int i = 0; i < sbChecking.size(); i++)
					sbChecking.pop_back();
				std::string sMoveToPiece = sBoard[iMoveTo];

				if (sMoveToPiece != " ")
				{
					bCapturePiece = true;

					if (sMoveToPiece.at(0) == 'w')
					{
						bMoveToWhite = true;
					}
					else if (sMoveToPiece.at(0) == 'b')
					{
						bMoveToWhite = false;
					}
					else
					{
						dHistory.push_back("CRITICAL: sMoveToPiece function failed due to input \"" + sMoveToPiece + "\".");
						sErrorMsg = "Uh-oh! Something went wrong";
						return false;
					}
				}
				else
				{
					bCapturePiece = false;
				}
				if (iMoveTo > iBoardSize)
				{
					dHistory.push_back("ERR: Move was outside of board boundaries");
					sErrorMsg = "Move was out of board boundaries";
					bMoveValid = false;
				}
				else if (this->bWhitePiece != CurrentColorIsWhite)
				{
					dHistory.push_back("ERR: It's not that color's turn!");
					sErrorMsg = "It's not that color turn!";
					return false;
				}
				else if (bCapturePiece == true)
				{
					if (this->bWhitePiece == bMoveToWhite && this->iType != 0)
					{
						dHistory.push_back("ERR: You can't capture your own piece!");
						sErrorMsg = "You can't capture your own piece!";
						return false;
					}
				}
			}

			dHistory.push_back("INFO: " + this->sName + "\tbMoveCheck: " + std::to_string(bMoveCheck) + "\tiPos: " + std::to_string(this->iPosition) + "\tiMoves: " + std::to_string(this->iMoves) + "\tiType: " + std::to_string(this->iType) + " bWhitePiece: " + std::to_string(this->bWhitePiece) + " bCapture: " + std::to_string(bCapturePiece));
			if (this->iType == 0)	//---------------------------------------	KING LOGIC	-------------------------------------------	KING LOGIC	----------------------------------	-------------------------------------------	KING LOGIC	----------------------------------
			{
				bool bKingInCheck = true;

				unsigned int pEquationDown = this->iPosition + 8;
				unsigned int pEquationUp = this->iPosition - 8;

				unsigned int pEquationLeft = this->iPosition + 1;
				unsigned int pEquationRight = this->iPosition - 1;

				unsigned int pEquationUpLeft = this->iPosition - 9;
				unsigned int pEquationUpRight = this->iPosition - 7;

				unsigned int pEquationDownLeft = this->iPosition + 7;
				unsigned int pEquationDownRight = this->iPosition + 9;

				if (pEquationDown >= 0 && pEquationDown <= iBoardSize && bMoveValid == false)
				{
					if (bMoveCheck)
					{
						std::string lMoveToPiece = sBoard[pEquationDown];
						if (lMoveToPiece.at(0) == ' ')
						{
							CheckBoard[pEquationDown] = 'K';
							KingCheckBoard[pEquationDown] = 'K';
						}
						else if (lMoveToPiece.at(0) == 'w' && this->bWhitePiece == false)
						{
							CheckBoard[pEquationDown] = 'K';
							KingCheckBoard[pEquationDown] = 'K';
						}
						else if (lMoveToPiece.at(0) == 'b' && this->bWhitePiece == true)
						{
							CheckBoard[pEquationDown] = 'K';
							KingCheckBoard[pEquationDown] = 'K';
						}
					}
					else
					{
						if (iMoveTo == pEquationDown && this->bWhitePiece != bMoveToWhite)	//	move down
						{
							dHistory.push_back("INFO: King moved down");
							bMoveValid = true;
						}
					}
				}
				if (pEquationUp >= 0 && pEquationUp <= iBoardSize && bMoveValid == false)
				{
					if (bMoveCheck)
					{
						std::string lMoveToPiece = sBoard[pEquationUp];
						if (lMoveToPiece.at(0) == ' ')
						{
							CheckBoard[pEquationUp] = 'K';
							KingCheckBoard[pEquationUp] = 'K';
						}
						else if (lMoveToPiece.at(0) == 'w' && this->bWhitePiece == false)
						{
							CheckBoard[pEquationUp] = 'K';
							KingCheckBoard[pEquationUp] = 'K';
						}
						else if (lMoveToPiece.at(0) == 'b' && this->bWhitePiece == true)
						{
							CheckBoard[pEquationUp] = 'K';
							KingCheckBoard[pEquationUp] = 'K';
						}
					}
					else
					{
						if (iMoveTo == pEquationUp && this->bWhitePiece != bMoveToWhite)	//	move up
						{
							dHistory.push_back("INFO: King moved up");
							bMoveValid = true;
						}
					}
				}
				if (pEquationLeft >= 0 && pEquationLeft <= iBoardSize && bMoveValid == false)
				{
					for (unsigned int i = 0; i < iBoardSize; i++)
					{
						if ((this->iPosition >= i * iBoardWidth) && (this->iPosition <= (i * iBoardWidth) + (iBoardWidth - 1)) &&
							(pEquationLeft >= i * iBoardWidth) && (pEquationLeft <= (i * iBoardWidth) + (iBoardWidth - 1)))
						{
							if (bMoveCheck)
							{
								std::string lMoveToPiece = sBoard[pEquationLeft];
								if (lMoveToPiece.at(0) == ' ')
								{
									CheckBoard[pEquationLeft] = 'K';
									KingCheckBoard[pEquationLeft] = 'K';
								}
								else if (lMoveToPiece.at(0) == 'w' && this->bWhitePiece == false)
								{
									CheckBoard[pEquationLeft] = 'K';
									KingCheckBoard[pEquationLeft] = 'K';
								}
								else if (lMoveToPiece.at(0) == 'b' && this->bWhitePiece == true)
								{
									CheckBoard[pEquationLeft] = 'K';
									KingCheckBoard[pEquationLeft] = 'K';
								}
							}
							else
							{
								if (iMoveTo == pEquationLeft && this->bWhitePiece != bMoveToWhite)	//	move left
								{
									dHistory.push_back("INFO: King moved left");
									bMoveValid = true;
								}
							}
						}
					}
				}
				if (pEquationRight >= 0 && pEquationRight <= iBoardSize && bMoveValid == false)
				{
					for (unsigned int i = 0; i < iBoardSize; i++)
					{
						if ((this->iPosition >= i * iBoardWidth) && (this->iPosition <= (i * iBoardWidth) + (iBoardWidth - 1)) &&
							(pEquationRight >= i * iBoardWidth) && (pEquationRight <= (i * iBoardWidth) + (iBoardWidth - 1)))
						{
							if (bMoveCheck)
							{
								std::string lMoveToPiece = sBoard[pEquationRight];
								if (lMoveToPiece.at(0) == ' ')
								{
									CheckBoard[pEquationRight] = 'K';
									KingCheckBoard[pEquationRight] = 'K';
								}
								else if (lMoveToPiece.at(0) == 'w' && this->bWhitePiece == false)
								{
									CheckBoard[pEquationRight] = 'K';
									KingCheckBoard[pEquationRight] = 'K';
								}
								else if (lMoveToPiece.at(0) == 'b' && this->bWhitePiece == true)
								{
									CheckBoard[pEquationRight] = 'K';
									KingCheckBoard[pEquationRight] = 'K';
								}
							}
							else
							{
								if (iMoveTo == pEquationRight && this->bWhitePiece != bMoveToWhite)	//	move right
								{
									dHistory.push_back("INFO: King moved right");
									bMoveValid = true;
								}
							}
						}
					}
				}
				if (pEquationDownLeft >= 0 && pEquationDownLeft <= iBoardSize && bMoveValid == false)
				{
					for (unsigned int i = 0; i < iBoardSize; i++)
					{
						if ((this->iPosition >= i * iBoardWidth) && (this->iPosition <= (i * iBoardWidth) + (iBoardWidth - 1)) &&
							(pEquationDownLeft >= (i + 1) * iBoardWidth) && (pEquationDownLeft <= ((i + 1) * iBoardWidth) + (iBoardWidth - 1)))
						{
							if (bMoveCheck)
							{
								std::string lMoveToPiece = sBoard[pEquationDownLeft];
								if (lMoveToPiece.at(0) == ' ')
								{
									CheckBoard[pEquationDownLeft] = 'K';
									KingCheckBoard[pEquationDownLeft] = 'K';
								}
								else if (lMoveToPiece.at(0) == 'w' && this->bWhitePiece == false)
								{
									CheckBoard[pEquationDownLeft] = 'K';
									KingCheckBoard[pEquationDownLeft] = 'K';
								}
								else if (lMoveToPiece.at(0) == 'b' && this->bWhitePiece == true)
								{
									CheckBoard[pEquationDownLeft] = 'K';
									KingCheckBoard[pEquationDownLeft] = 'K';
								}
							}
							else
							{
								if (iMoveTo == pEquationDownLeft && this->bWhitePiece != bMoveToWhite)	//	move down left
								{
									dHistory.push_back("INFO: King moved down left");
									bMoveValid = true;
								}
							}
						}
					}
				}
				if (pEquationDownRight >= 0 && pEquationDownRight <= iBoardSize && bMoveValid == false)
				{
					for (unsigned int i = 0; i < iBoardSize; i++)
					{
						if ((this->iPosition >= i * iBoardWidth) && (this->iPosition <= (i * iBoardWidth) + (iBoardWidth - 1)) &&
							(pEquationDownRight >= (i + 1) * iBoardWidth) && (pEquationDownRight <= ((i + 1) * iBoardWidth) + (iBoardWidth - 1)))
						{
							if (bMoveCheck)
							{
								std::string lMoveToPiece = sBoard[pEquationDownRight];
								if (lMoveToPiece.at(0) == ' ')
								{
									CheckBoard[pEquationDownRight] = 'K';
									KingCheckBoard[pEquationDownRight] = 'K';
								}
								else if (lMoveToPiece.at(0) == 'w' && this->bWhitePiece == false)
								{
									CheckBoard[pEquationDownRight] = 'K';
									KingCheckBoard[pEquationDownRight] = 'K';
								}
								else if (lMoveToPiece.at(0) == 'b' && this->bWhitePiece == true)
								{
									CheckBoard[pEquationDownRight] = 'K';
									KingCheckBoard[pEquationDownRight] = 'K';
								}
							}
							else
							{
								if (iMoveTo == pEquationDownRight && this->bWhitePiece != bMoveToWhite)	//	move down right
								{
									dHistory.push_back("INFO: King moved down right");
									bMoveValid = true;
								}
							}
						}
					}
				}
				if (pEquationUpLeft >= 0 && pEquationUpLeft <= iBoardSize && bMoveValid == false)
				{
					for (unsigned int i = 0; i < iBoardSize; i++)
					{
						if ((this->iPosition >= i * iBoardWidth) && (this->iPosition <= (i * iBoardWidth) + (iBoardWidth - 1)) &&
							(pEquationUpLeft >= (i - 1) * iBoardWidth) && (pEquationUpLeft <= ((i - 1) * iBoardWidth) + (iBoardWidth - 1)))
						{
							if (bMoveCheck)
							{
								std::string lMoveToPiece = sBoard[pEquationUpLeft];
								if (lMoveToPiece.at(0) == ' ')
								{
									CheckBoard[pEquationUpLeft] = 'K';
									KingCheckBoard[pEquationUpLeft] = 'K';
								}
								else if (lMoveToPiece.at(0) == 'w' && this->bWhitePiece == false)
								{
									CheckBoard[pEquationUpLeft] = 'K';
									KingCheckBoard[pEquationUpLeft] = 'K';
								}
								else if (lMoveToPiece.at(0) == 'b' && this->bWhitePiece == true)
								{
									CheckBoard[pEquationUpLeft] = 'K';
									KingCheckBoard[pEquationUpLeft] = 'K';
								}
							}
							else
							{
								if (iMoveTo == pEquationUpLeft && this->bWhitePiece != bMoveToWhite)	//	move up left
								{
									dHistory.push_back("INFO: King moved up left");
									bMoveValid = true;
								}
							}
						}
					}
				}
				if (pEquationUpRight >= 0 && pEquationUpRight <= iBoardSize && bMoveValid == false)
				{
					for (unsigned int i = 0; i < iBoardSize; i++)
					{
						if ((this->iPosition >= i * iBoardWidth) && (this->iPosition <= (i * iBoardWidth) + (iBoardWidth - 1)) &&
							(pEquationUpRight >= (i - 1) * iBoardWidth) && (pEquationUpRight <= ((i - 1) * iBoardWidth) + (iBoardWidth - 1)))
						{
							if (bMoveCheck)
							{
								std::string lMoveToPiece = sBoard[pEquationUpRight];
								if (lMoveToPiece.at(0) == ' ')
								{
									CheckBoard[pEquationUpRight] = 'K';
									KingCheckBoard[pEquationUpRight] = 'K';
								}
								else if (lMoveToPiece.at(0) == 'w' && this->bWhitePiece == false)
								{
									CheckBoard[pEquationUpRight] = 'K';
									KingCheckBoard[pEquationUpRight] = 'K';
								}
								else if (lMoveToPiece.at(0) == 'b' && this->bWhitePiece == true)
								{
									CheckBoard[pEquationUpRight] = 'K';
									KingCheckBoard[pEquationUpRight] = 'K';
								}
							}
							else
							{
								if (iMoveTo == pEquationUpRight && this->bWhitePiece != bMoveToWhite)	//	move up right
								{
									dHistory.push_back("INFO: King moved up right");
									bMoveValid = true;
								}
							}
						}
					}
				}
				if (this->iMoves == 0 && bMoveValid == false && !bMoveCheck)	// Queenside castling
				{
					bool lValidMove = false;
					if (iMoveTo >= (this->iPosition - 4) && iMoveTo <= (this->iPosition - 2))
					{
						if (sBoard[this->iPosition - 3] == " " && sBoard[this->iPosition - 2] == " " && sBoard[this->iPosition - 1] == " ")
						{
							dHistory.push_back("Attempting queenside castle...");
							bCastleSideQueen = true;
							bCurrentlyCastling = true;
							lValidMove = bRookCastle();
							if (lValidMove)
							{
								iMoveTo = this->iPosition - 2;
								bMoveValid = true;
							}
						}
						else
						{
							sErrorMsg = "There can't be any pieces between the King and Rook!";
							bMoveValid = false;
						}
					}
					else if (iMoveTo >= (this->iPosition + 2) && iMoveTo <= (this->iPosition + 3))	//Kingside	castling
					{
						if (sBoard[this->iPosition + 1] == " " && sBoard[this->iPosition + 2] == " ")
						{
							dHistory.push_back("Attempting kingside castle...");
							bCastleSideQueen = false;
							bCurrentlyCastling = true;
							lValidMove = bRookCastle();
							if (lValidMove)
							{
								iMoveTo = this->iPosition + 1;
								bMoveValid = true;
							}
						}
						else
						{
							sErrorMsg = "There can't be any pieces between the King and Rook!";
							bMoveValid = false;
						}
					}	//	END Kingside White
				}
			}	//	END bKingLogic
			else if (this->iType == 1)	//---------------------------------------	QUEEN LOGIC	-------------------------------------------	QUEEN LOGIC	----------------------------------	-------------------------------------------	QUEEN LOGIC	----------------------------------
			{
				bool bThroughCalc = false;
				bool bDown = false;
				bool bUp = false;
				bool bLeft = false;
				bool bRight = false;
				bool bUpLeft = false;
				bool bUpRight = false;
				bool bDownLeft = false;
				bool bDownRight = false;

				if ((this->iPosition == 0) || (this->iPosition == 8) || (this->iPosition == 16) || (this->iPosition == 24) || (this->iPosition == 32) || (this->iPosition == 40) || (this->iPosition == 48) || (this->iPosition == 56))
				{
					bLeft = true;
					bUpLeft = true;
					bDownLeft = true;
				}
				else if ((this->iPosition == 7) || (this->iPosition == 15) || (this->iPosition == 23) || (this->iPosition == 31) || (this->iPosition == 39) || (this->iPosition == 47) || (this->iPosition == 55) || (this->iPosition == 63))
				{
					bRight = true;
					bUpRight = true;
					bDownRight = true;
				}

				for (unsigned int i = 1; i < iBoardWidth; i++)
				{
					unsigned int pEquationDown = this->iPosition + (i * 8);
					unsigned int pEquationUp = this->iPosition - (i * 8);

					unsigned int pEquationLeft = this->iPosition - (i);
					unsigned int pEquationRight = this->iPosition + (i);

					unsigned int pEquationUpLeft = this->iPosition - (i * 9);
					unsigned int pEquationUpRight = this->iPosition - (i * 7);

					unsigned int pEquationDownLeft = this->iPosition + (i * 7);
					unsigned int pEquationDownRight = this->iPosition + (i * 9);


					if (bDown == false && !bMoveValid)		//		Queen DOWN		//		QUEEN DOWN		//		QUEEN DOWN
					{
						
						if (pEquationDown >= 0 && pEquationDown <= iBoardSize)
						{
							if (sBoard[pEquationDown] == " ")
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationDown] = 'Q';
									QueenCheckBoard[pEquationDown] = 'Q';
									if (this->bWhitePiece && pEquationDown == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationDown == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else if (iMoveTo == pEquationDown)
								{
									dHistory.push_back("Queen moved down");
									bMoveValid = true;
									bDown = true;
								}
							}
							else
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationDown] = 'Q';
									QueenCheckBoard[pEquationDown] = 'Q';
									if (this->bWhitePiece && pEquationDown == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationDown == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else
								{
									if (iMoveTo == pEquationDown)
									{
										dHistory.push_back("Queen moved down");
										bMoveValid = true;
									}
								}
								bDown = true;
							}
						}
						else { bDown = true; }
					}
					if (bUp == false && !bMoveValid)		//		Queen UP		//		QUEEN UP		//		QUEEN UP
					{
						if (pEquationUp >= 0 && pEquationUp <= iBoardSize)
						{
							if (sBoard[pEquationUp] == " ")
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationUp] = 'Q';
									QueenCheckBoard[pEquationUp] = 'Q';
									if (this->bWhitePiece && pEquationUp == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationUp == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else if (iMoveTo == pEquationUp)
								{
									dHistory.push_back("Queen moved up");
									bMoveValid = true;
									bUp = true;
								}
							}
							else
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationUp] = 'Q';
									QueenCheckBoard[pEquationUp] = 'Q';
									if (this->bWhitePiece && pEquationUp == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationUp == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else
								{
									if (iMoveTo == pEquationUp)
									{
										dHistory.push_back("Queen moved up");
										bMoveValid = true;
									}
								}
								bUp = true;
							}
						}
						else { bUp = true; }
					}
					if (bLeft == false && !bMoveValid)		//		Queen LEFT		//		QUEEN LEFT		//		QUEEN LEFT
					{
						if (pEquationLeft >= 0 && pEquationLeft <= iBoardSize)
						{
							for (unsigned int j = 0; j < iBoardWidth; j++)
							{
								if (pEquationLeft == (j * iBoardWidth))
								{
									bLeft = true;
								}
							}
							if (sBoard[pEquationLeft] == " " && (bLeft == false))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationLeft] = 'Q';
									QueenCheckBoard[pEquationLeft] = 'Q';
									if (this->bWhitePiece && pEquationLeft == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationLeft == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else if (iMoveTo == pEquationLeft)
								{
									dHistory.push_back("Queen moved left");
									bMoveValid = true;
									bLeft = true;
								}
							}
							else if ((sBoard[pEquationLeft] != " ") || (bLeft == true))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationLeft] = 'Q';
									QueenCheckBoard[pEquationLeft] = 'Q';
									if (this->bWhitePiece && pEquationLeft == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationLeft == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else
								{
									if (iMoveTo == pEquationLeft)
									{
										dHistory.push_back("Queen moved left");
										bMoveValid = true;
									}
								}
								bLeft = true;
							}
						}
						else { bLeft = true; }
					}
					if (bRight == false && !bMoveValid)		//		Queen RIGHT		//		QUEEN RIGHT		//		QUEEN RIGHT
					{
						if (pEquationRight >= 0 && pEquationRight <= iBoardSize)
						{
							for (unsigned int j = 0; j < iBoardWidth; j++)
							{
								if (pEquationRight == (j * iBoardWidth) - 1)
								{
									bRight = true;
								}
							}
							if (sBoard[pEquationRight] == " " && (bRight == false))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationRight] = 'Q';
									QueenCheckBoard[pEquationRight] = 'Q';
									if (this->bWhitePiece && pEquationRight == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationRight == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else if (iMoveTo == pEquationRight)
								{
									dHistory.push_back("Queen moved right");
									bMoveValid = true;
									bRight = true;
								}
							}
							else if ((sBoard[pEquationRight] != " ") || (bRight == true))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationRight] = 'Q';
									QueenCheckBoard[pEquationRight] = 'Q';
									if (this->bWhitePiece && pEquationRight == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationRight == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else
								{
									if (iMoveTo == pEquationRight)
									{
										dHistory.push_back("Queen moved right");
										bMoveValid = true;
									}
								}
								bRight = true;
							}
						}
						else { bRight = true; }
					}
					if (bUpLeft == false && !bMoveValid)		//		Queen UP LEFT		//		QUEEN UP LEFT		//		QUEEN UP LEFT
					{
						if (pEquationUpLeft >= 0 && pEquationUpLeft <= iBoardSize)
						{
							for (unsigned int j = 0; j < iBoardWidth; j++)
							{
								if (pEquationUpLeft == (j * iBoardWidth))
								{
									bUpLeft = true;
								}
							}
							if (sBoard[pEquationUpLeft] == " " && (bUpLeft == false))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationUpLeft] = 'Q';
									QueenCheckBoard[pEquationUpLeft] = 'Q';
									if (this->bWhitePiece && pEquationUpLeft == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationUpLeft == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else if (iMoveTo == pEquationUpLeft)
								{
									dHistory.push_back("Queen moved up left");
									bMoveValid = true;
									bUpLeft = true;
								}
							}
							else if ((sBoard[pEquationUpLeft] != " ") || (bUpLeft == true))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationUpLeft] = 'Q';
									QueenCheckBoard[pEquationUpLeft] = 'Q';
									if (this->bWhitePiece && pEquationUpLeft == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationUpLeft == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else
								{
									if (iMoveTo == pEquationUpLeft)
									{
										dHistory.push_back("Queen moved up left");
										bMoveValid = true;
									}
								}
								bUpLeft = true;
							}
						}
						else { bUpLeft = true; }
					}
					if (bUpRight == false && !bMoveValid)		//		Queen UP RIGHT		//		QUEEN UP RIGHT		//		QUEEN UP RIGHT
					{
						if (pEquationUpRight >= 0 && pEquationUpRight <= iBoardSize)
						{
							for (unsigned int j = 0; j < iBoardWidth; j++)
							{
								if (pEquationUpRight == (j * iBoardWidth) - 1)
								{
									bUpRight = true;
								}
							}
							if (sBoard[pEquationUpRight] == " " && (bUpRight == false))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationUpRight] = 'Q';
									QueenCheckBoard[pEquationUpRight] = 'Q';
									if (this->bWhitePiece && pEquationUpRight == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationUpRight == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else if (iMoveTo == pEquationUpRight)
								{
									dHistory.push_back("Queen moved up right");
									bMoveValid = true;
									bUpRight = true;
								}
							}
							else if ((sBoard[pEquationUpRight] != " ") || (bUpRight == true))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationUpRight] = 'Q';
									QueenCheckBoard[pEquationUpRight] = 'Q';
									if (this->bWhitePiece && pEquationUpRight == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationUpRight == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else
								{
									if (iMoveTo == pEquationUpRight)
									{
										dHistory.push_back("Queen moved up right");
										bMoveValid = true;
									}
								}
								bUpRight = true;
							}
						}
						else { bUpRight = true; }
					}
					if (bDownLeft == false && !bMoveValid)		//		Queen DOWN LEFT		//		QUEEN DOWN LEFT		//		QUEEN DOWN LEFT
					{
						if (pEquationDownLeft >= 0 && pEquationDownLeft <= iBoardSize)
						{
							for (unsigned int j = 0; j < iBoardWidth; j++)
							{
								if (pEquationDownLeft == (j * iBoardWidth))
								{
									bDownLeft = true;
								}
							}
							if (sBoard[pEquationDownLeft] == " " && (bDownLeft == false))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationDownLeft] = 'Q';
									QueenCheckBoard[pEquationDownLeft] = 'Q';
									if (this->bWhitePiece && pEquationDownLeft == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationDownLeft == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else if (iMoveTo == pEquationDownLeft)
								{
									dHistory.push_back("Queen moved down left");
									bMoveValid = true;
									bDownLeft = true;
								}
							}
							else if ((sBoard[pEquationDownLeft] != " ") || (bDownLeft == true))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationDownLeft] = 'Q';
									QueenCheckBoard[pEquationDownLeft] = 'Q';
									if (this->bWhitePiece && pEquationDownLeft == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationDownLeft == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else
								{
									if (iMoveTo == pEquationDownLeft)
									{
										dHistory.push_back("Queen moved down left");
										bMoveValid = true;
									}
								}
								bDownLeft = true;
							}
						}
						else { bDownLeft = true; }
					}
					if (bDownRight == false && !bMoveValid)		//		Queen DOWN RIGHT		//		QUEEN DOWN RIGHT		//		QUEEN DOWN RIGHT
					{
						if (pEquationDownRight >= 0 && pEquationDownRight <= iBoardSize)
						{
							for (unsigned int j = 0; j < iBoardWidth; j++)
							{
								if (pEquationDownRight == (j * iBoardWidth) - 1)
								{
									bDownRight = true;
								}
							}
							if (sBoard[pEquationDownRight] == " " && (bDownRight == false))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationDownRight] = 'Q';
									QueenCheckBoard[pEquationDownRight] = 'Q';
									if (this->bWhitePiece && pEquationDownRight == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationDownRight == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else if (iMoveTo == pEquationDownRight)
								{
									dHistory.push_back("Queen moved down right");
									bMoveValid = true;
									bDownRight = true;
								}
							}
							else if ((sBoard[pEquationDownRight] != " ") || (bDownRight == true))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationDownRight] = 'Q';
									QueenCheckBoard[pEquationDownRight] = 'Q';
									if (this->bWhitePiece && pEquationDownRight == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationDownRight == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else
								{
									if (iMoveTo == pEquationDownRight)
									{
										dHistory.push_back("Queen moved down right");
										bMoveValid = true;
									}
								}
								bDownRight = true;
							}
						}
						else { bDownRight = true; }
					}
				}
			}	//	END QUEEN logic
			else if (this->iType == 2)	//---------------------------------------	ROOK LOGIC	-------------------------------------------	ROOK LOGIC	----------------------------------	-------------------------------------------	ROOK LOGIC	----------------------------------
			{
				if (bCurrentlyCastling == true)
				{
					if (this->iMoves == 0 && !bMoveValid)
					{
						if (CurrentColorIsWhite == true)
						{
							if (bCastleSideQueen == true)
							{
								this->iMoves++;
								this->iPosition = 59;
								sBoard[59] = sBoard[56];
								iBoard[59] = iBoard[56];
								sBoard[56] = " ";
								iBoard[56] = ' ';
								dHistory.push_back("INFO: Queenside WHITE Rook castled sucessfully!");
								bMoveValid = true;
							}
							else    // Castle side is king
							{
								this->iMoves++;
								this->iPosition = 61;
								sBoard[61] = sBoard[63];
								iBoard[61] = iBoard[63];
								sBoard[63] = " ";
								iBoard[63] = ' ';
								dHistory.push_back("INFO: Kingside WHITE Rook castled sucessfully!");
								bMoveValid = true;
							}
						}
						else    //CurrentColor is black
						{
							if (bCastleSideQueen == true)
							{
								this->iMoves++;
								this->iPosition = 3;
								sBoard[3] = sBoard[0];
								iBoard[3] = iBoard[0];
								sBoard[0] = " ";
								iBoard[0] = ' ';
								dHistory.push_back("INFO: Queenside BLACK Rook castled sucessfully!");
								bMoveValid = true;
							}
							else    // Castle side is king
							{
								this->iMoves++;
								this->iPosition = 5;
								sBoard[5] = sBoard[7];
								iBoard[5] = iBoard[7];
								sBoard[7] = " ";
								iBoard[7] = ' ';
								dHistory.push_back("INFO: Kingside BLACK Rook castled sucessfully!");
								bMoveValid = true;
							}
						}
					}
					else
					{
						dHistory.push_back("ERR: Rook must have 0 moves to castle!");
						sErrorMsg = "Rook must have 0 moves to castle";
						bMoveValid = false;
					}
				}	//	End bCurrentlyCastling
				
				bool bDown = false;
				bool bUp = false;
				bool bLeft = false;
				bool bRight = false;

				if ((this->iPosition == 0) || (this->iPosition == 8) || (this->iPosition == 16) || (this->iPosition == 24) || (this->iPosition == 32) || (this->iPosition == 40) || (this->iPosition == 48) || (this->iPosition == 56))
				{
					bLeft = true;
				}
				else if ((this->iPosition == 7) || (this->iPosition == 15) || (this->iPosition == 23) || (this->iPosition == 31) || (this->iPosition == 39) || (this->iPosition == 47) || (this->iPosition == 55) || (this->iPosition == 63))
				{
					bRight = true;
				}

				for (unsigned int i = 1; i < iBoardWidth; i++)
				{
					unsigned int pEquationDown = this->iPosition + (i * 8);
					unsigned int pEquationUp = this->iPosition - (i * 8);

					unsigned int pEquationLeft = this->iPosition - (i);
					unsigned int pEquationRight = this->iPosition + (i);

					if (bDown == false && !bMoveValid)		//		ROOK DOWN		//		ROOK DOWN		//		ROOK DOWN
					{
						if (pEquationDown >= 0 && pEquationDown <= iBoardSize)
						{
							if (sBoard[pEquationDown] == " ")
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationDown] = 'R';
									RookCheckBoard[pEquationDown] = 'R';
									if (this->bWhitePiece && pEquationDown == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationDown == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else if (iMoveTo == pEquationDown)
								{
									dHistory.push_back("Rook moved down");
									bMoveValid = true;
									bDown = true;
								}
							}
							else
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationDown] = 'R';
									RookCheckBoard[pEquationDown] = 'R';
									if (this->bWhitePiece && pEquationDown == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationDown == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else
								{
									if (iMoveTo == pEquationDown)
									{
										dHistory.push_back("Rook moved down");
										bMoveValid = true;
									}
								}
								bDown = true;
							}
						}
						else { bDown = true; }
					}
					if (bUp == false && !bMoveValid)		//		ROOK UP		//		ROOK UP		//		ROOK UP
					{
						if (pEquationUp >= 0 && pEquationUp <= iBoardSize)
						{
							if (sBoard[pEquationUp] == " ")
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationUp] = 'R';
									RookCheckBoard[pEquationUp] = 'R';
									if (this->bWhitePiece && pEquationUp == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationUp == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else if (iMoveTo == pEquationUp)
								{
									dHistory.push_back("Rook moved up");
									bMoveValid = true;
									bUp = true;
								}
							}
							else
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationUp] = 'R';
									RookCheckBoard[pEquationUp] = 'R';
									if (this->bWhitePiece && pEquationUp == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationUp == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else
								{
									if (iMoveTo == pEquationUp)
									{
										dHistory.push_back("Rook moved up");
										bMoveValid = true;
									}
								}
								bUp = true;
							}
						}
						else { bUp = true; }
					}
					if (bLeft == false && !bMoveValid)		//		ROOK LEFT		//		ROOK LEFT		//		ROOK LEFT
					{
						if (pEquationLeft >= 0 && pEquationLeft <= iBoardSize)
						{
							for (unsigned int j = 0; j < iBoardWidth; j++)
							{
								if (pEquationLeft == (j * iBoardWidth) || this->iPosition == (j * iBoardWidth))
								{
									bLeft = true;
								}
							}
							if (sBoard[pEquationLeft] == " " && (bLeft == false))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationLeft] = 'R';
									RookCheckBoard[pEquationLeft] = 'R';
									if (this->bWhitePiece && pEquationLeft == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationLeft == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else if (iMoveTo == pEquationLeft)
								{
									dHistory.push_back("Rook moved left");
									bMoveValid = true;
									bLeft = true;
								}
							}
							else if ((sBoard[pEquationLeft] != " ") || (bLeft == true))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationLeft] = 'R';
									RookCheckBoard[pEquationLeft] = 'R';
									if (this->bWhitePiece && pEquationLeft == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationLeft == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else
								{
									if (iMoveTo == pEquationLeft)
									{
										dHistory.push_back("Rook moved left");
										bMoveValid = true;
									}
								}
								bLeft = true;
							}
						}
						else { bLeft = true; }
					}
					if (bRight == false && !bMoveValid)		//		ROOK RIGHT		//		ROOK RIGHT		//		ROOK RIGHT
					{
						if (pEquationRight >= 0 && pEquationRight <= iBoardSize)
						{
							for (unsigned int j = 0; j < iBoardWidth; j++)
							{
								if (pEquationRight == (j * iBoardWidth) - 1 || this->iPosition == (j * iBoardWidth) - 1)
								{
									bRight = true;
								}
							}
							if (sBoard[pEquationRight] == " " && (bRight == false))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationRight] = 'R';
									RookCheckBoard[pEquationRight] = 'R';
									if (this->bWhitePiece && pEquationRight == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationRight == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else if (iMoveTo == pEquationRight)
								{
									dHistory.push_back("Rook moved right");
									bMoveValid = true;
									bRight = true;
								}
							}
							else if ((sBoard[pEquationRight] != " ") || (bRight == true))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationRight] = 'R';
									RookCheckBoard[pEquationRight] = 'R';
									if (this->bWhitePiece && pEquationRight == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationRight == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else
								{
									if (iMoveTo == pEquationRight)
									{
										dHistory.push_back("Rook moved right");
										bMoveValid = true;
									}
								}
								bRight = true;
							}
						}
						else { bRight = true; }
					}
				}
			}	//	END ROOK LOGIC
			else if (this->iType == 3)	//---------------------------------------	BISHOP LOGIC	-------------------------------------------	BISHOP LOGIC	----------------------------------	-------------------------------------------	BISHOP LOGIC	----------------------------------
			{
				bool bUpLeft = false;
				bool bUpRight = false;
				bool bDownLeft = false;
				bool bDownRight = false;

				if ((this->iPosition == 0) || (this->iPosition == 8) || (this->iPosition == 16) || (this->iPosition == 24) || (this->iPosition == 32) || (this->iPosition == 40) || (this->iPosition == 48) || (this->iPosition == 56))
				{
					bUpLeft = true;
					bDownLeft = true;
				}
				else if ((this->iPosition == 7) || (this->iPosition == 15) || (this->iPosition == 23) || (this->iPosition == 31) || (this->iPosition == 39) || (this->iPosition == 47) || (this->iPosition == 55) || (this->iPosition == 63))
				{
					bUpRight = true;
					bDownRight = true;
				}
				for (unsigned int i = 1; i < iBoardWidth; i++)
				{

					unsigned int pEquationUpLeft = this->iPosition - (i * 9);
					unsigned int pEquationUpRight = this->iPosition - (i * 7);

					unsigned int pEquationDownLeft = this->iPosition + (i * 7);
					unsigned int pEquationDownRight = this->iPosition + (i * 9);

					if (bUpLeft == false && !bMoveValid)		//		BISHOP UP LEFT		//		BISHOP UP LEFT		//		BISHOP UP LEFT
					{
						if (pEquationUpLeft >= 0 && pEquationUpLeft <= iBoardSize)
						{
							for (unsigned int j = 0; j < iBoardWidth; j++)
							{
								if (pEquationUpLeft == (j * iBoardWidth) || this->iPosition == (j * iBoardWidth))
								{
									bUpLeft = true;
								}
							}
							if (sBoard[pEquationUpLeft] == " " && (bUpLeft == false))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationUpLeft] = 'B';
									BishopCheckBoard[pEquationUpLeft] = 'B';
									if (this->bWhitePiece && pEquationUpLeft == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationUpLeft == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else if (iMoveTo == pEquationUpLeft)
								{
									dHistory.push_back("Bishop moved up left");
									bMoveValid = true;
									bUpLeft = true;
								}
							}
							else if ((sBoard[pEquationUpLeft] != " ") || (bUpLeft == true))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationUpLeft] = 'B';
									BishopCheckBoard[pEquationUpLeft] = 'B';
									if (this->bWhitePiece && pEquationUpLeft == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationUpLeft == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else
								{
									if (iMoveTo == pEquationUpLeft)
									{
										dHistory.push_back("Bishop moved up left");
										bMoveValid = true;
									}
								}
								bUpLeft = true;
							}
						}
						else { bUpLeft = true; }
					}
					if (bUpRight == false && !bMoveValid)		//		BISHOP UP RIGHT		//		BISHOP UP RIGHT		//		BISHOP UP RIGHT
					{
						if (pEquationUpRight >= 0 && pEquationUpRight <= iBoardSize)
						{
							for (unsigned int j = 0; j < iBoardWidth; j++)
							{
								if (pEquationUpRight == (j * iBoardWidth) - 1 || this->iPosition == (j * iBoardWidth) - 1)
								{
									bUpRight = true;
								}
							}
							if (sBoard[pEquationUpRight] == " " && (bUpRight == false))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationUpRight] = 'B';
									BishopCheckBoard[pEquationUpRight] = 'B';
									if (this->bWhitePiece && pEquationUpRight == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationUpRight == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else if (iMoveTo == pEquationUpRight)
								{
									dHistory.push_back("Bishop moved up right");
									bMoveValid = true;
									bUpRight = true;
								}
							}
							else if ((sBoard[pEquationUpRight] != " ") || (bUpRight == true))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationUpRight] = 'B';
									BishopCheckBoard[pEquationUpRight] = 'B';
									if (this->bWhitePiece && pEquationUpRight == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationUpRight == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else
								{
									if (iMoveTo == pEquationUpRight)
									{
										dHistory.push_back("Bishop moved up right");
										bMoveValid = true;
									}
								}
								bUpRight = true;
							}
						}
						else { bUpRight = true; }
					}
					if (bDownLeft == false && !bMoveValid)		//		BISHOP DOWN LEFT		//		BISHOP DOWN LEFT		//		BISHOP DOWN LEFT
					{
						if (pEquationDownLeft >= 0 && pEquationDownLeft <= iBoardSize)
						{
							for (unsigned int j = 0; j < iBoardWidth; j++)
							{
								if (pEquationDownLeft == (j * iBoardWidth) || this->iPosition == (j * iBoardWidth))
								{
									bDownLeft = true;
								}
							}
							if (sBoard[pEquationDownLeft] == " " && (bDownLeft == false))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationDownLeft] = 'B';
									BishopCheckBoard[pEquationDownLeft] = 'B';
									if (this->bWhitePiece && pEquationDownLeft == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationDownLeft == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else if (iMoveTo == pEquationDownLeft)
								{
									dHistory.push_back("Bishop moved down left");
									bMoveValid = true;
									bDownLeft = true;
								}
							}
							else if ((sBoard[pEquationDownLeft] != " ") || (bDownLeft == true))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationDownLeft] = 'B';
									BishopCheckBoard[pEquationDownLeft] = 'B';
									if (this->bWhitePiece && pEquationDownLeft == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationDownLeft == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else
								{
									if (iMoveTo == pEquationDownLeft)
									{
										dHistory.push_back("Bishop moved down left");
										bMoveValid = true;
									}
								}
								bDownLeft = true;
							}
						}
						else { bDownLeft = true; }
					}
					if (bDownRight == false && !bMoveValid)		//		BISHOP DOWN RIGHT		//		BISHOP DOWN RIGHT		//		BISHOP DOWN RIGHT
					{
						if (pEquationDownRight >= 0 && pEquationDownRight <= iBoardSize)
						{
							for (unsigned int j = 0; j < iBoardWidth; j++)
							{
								if (pEquationDownRight == (j * iBoardWidth) - 1 || this->iPosition == (j * iBoardWidth) - 1)
								{
									bDownRight = true;
								}
							}
							if (sBoard[pEquationDownRight] == " " && (bDownRight == false))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationDownRight] = 'B';
									BishopCheckBoard[pEquationDownRight] = 'B';
									if (this->bWhitePiece && pEquationDownRight == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationDownRight == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else if (iMoveTo == pEquationDownRight)
								{
									dHistory.push_back("Bishop moved down right");
									bMoveValid = true;
									bDownRight = true;
								}
							}
							else if ((sBoard[pEquationDownRight] != " ") || (bDownRight == true))
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationDownRight] = 'B';
									BishopCheckBoard[pEquationDownRight] = 'B';
									if (this->bWhitePiece && pEquationDownRight == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationDownRight == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else
								{
									if (iMoveTo == pEquationDownRight)
									{
										dHistory.push_back("Bishop moved down right");
										bMoveValid = true;
									}
								}
								bDownRight = true;
							}
						}
						else { bDownRight = true; }
					}
				}
			}	//	END BISHOP logic
			else if (this->iType == 4)	//---------------------------------------	KNIGHT LOGIC	-------------------------------------------	KNIGHT LOGIC	----------------------------------	-------------------------------------------	KNIGHT LOGIC	----------------------------------
			{
				unsigned int pEquationDownLeft = this->iPosition + 15;	//	Down
				unsigned int pEquationDownRight = this->iPosition + 17;

				unsigned int pEquationUpLeft = this->iPosition - 17;		// Up
				unsigned int pEquationUpRight = this->iPosition - 15;

				unsigned int pEquationLeftDown = this->iPosition + 10;	//	left / right down
				unsigned int pEquationRightDown = this->iPosition + 6;

				unsigned int pEquationLeftUp = this->iPosition - 10;		// left / right up
				unsigned int pEquationRightUp = this->iPosition - 6;

				if (pEquationDownLeft >= 0 && pEquationDownLeft <= iBoardSize && !bMoveValid)
				{
					for (unsigned int i = 0; i < iBoardWidth; i++)
					{
						if (this->iPosition >= (i * iBoardWidth) && (this->iPosition <= ((i * iBoardWidth) + (iBoardWidth - 1))) &&
							(pEquationDownLeft >= ((i + 2) * iBoardWidth) - 1) && pEquationDownLeft <= (((i + 2) * iBoardWidth) + (iBoardWidth - 1)))
						{
							if (bMoveCheck)
							{
								CheckBoard[pEquationDownLeft] = 'N';
								KnightCheckBoard[pEquationDownLeft] = 'N';
								if (this->bWhitePiece && pEquationDownLeft == iBlackKingLocation)
									swChecking.push_back(this->sName);
								else if (!this->bWhitePiece && pEquationDownLeft == iWhiteKingLocation)
									sbChecking.push_back(this->sName);
							}
							else
							{
								if (iMoveTo == pEquationDownLeft)
								{
									dHistory.push_back("Knight moved down left");
									bMoveValid = true;
								}
							}
						}
					}
				}
				if (pEquationDownRight >= 0 && pEquationDownRight <= iBoardSize && !bMoveValid)
				{
					for (unsigned int i = 0; i < iBoardWidth; i++)
					{
						if (this->iPosition >= (i * iBoardWidth) && (this->iPosition <= ((i * iBoardWidth) + (iBoardWidth - 1))) &&
							(pEquationDownRight >= ((i + 2) * iBoardWidth)) && pEquationDownRight <= (((i + 2) * iBoardWidth) + (iBoardWidth - 1)))
						{
							if (bMoveCheck)
							{
								CheckBoard[pEquationDownRight] = 'N';
								KnightCheckBoard[pEquationDownRight] = 'N';
								if (this->bWhitePiece && pEquationDownRight == iBlackKingLocation)
									swChecking.push_back(this->sName);
								else if (!this->bWhitePiece && pEquationDownRight == iWhiteKingLocation)
									sbChecking.push_back(this->sName);
							}
							else
							{
								if (iMoveTo == pEquationDownRight)
								{
									dHistory.push_back("Knight moved down right");
									bMoveValid = true;
								}
							}
						}
					}
				}
				if (pEquationUpLeft >= 0 && pEquationUpLeft <= iBoardSize && !bMoveValid)
				{
					for (unsigned int i = 0; i < iBoardWidth; i++)
					{
						if (this->iPosition >= (i * iBoardWidth) && (this->iPosition <= ((i * iBoardWidth) + (iBoardWidth - 1))) &&
							(pEquationUpLeft >= ((i - 2) * iBoardWidth)) && pEquationUpLeft <= (((i - 2) * iBoardWidth) + (iBoardWidth - 1)))
						{
							if (bMoveCheck)
							{
								CheckBoard[pEquationUpLeft] = 'N';
								KnightCheckBoard[pEquationUpLeft] = 'N';
								if (this->bWhitePiece && pEquationUpLeft == iBlackKingLocation)
									swChecking.push_back(this->sName);
								else if (!this->bWhitePiece && pEquationUpLeft == iWhiteKingLocation)
									sbChecking.push_back(this->sName);
							}
							else
							{
								if (iMoveTo == pEquationUpLeft)
								{
									dHistory.push_back("Knight moved up left");
									bMoveValid = true;
								}
							}
						}
					}
				}
				if (pEquationUpRight >= 0 && pEquationUpRight <= iBoardSize && !bMoveValid)
				{
					for (unsigned int i = 0; i < iBoardWidth; i++)
					{
						if (this->iPosition >= (i * iBoardWidth) && (this->iPosition <= ((i * iBoardWidth) + (iBoardWidth - 1))) &&
							(pEquationUpRight >= ((i - 2) * iBoardWidth)) && pEquationUpRight <= (((i - 2) * iBoardWidth) + (iBoardWidth - 1)))
						{
							if (bMoveCheck)
							{
								CheckBoard[pEquationUpRight] = 'N';
								KnightCheckBoard[pEquationUpRight] = 'N';
								if (this->bWhitePiece && pEquationUpRight == iBlackKingLocation)
									swChecking.push_back(this->sName);
								else if (!this->bWhitePiece && pEquationUpRight == iWhiteKingLocation)
									sbChecking.push_back(this->sName);
							}
							else
							{
								if (iMoveTo == pEquationUpRight)
								{
									dHistory.push_back("Knight moved up right");
									bMoveValid = true;
								}
							}
						}
					}
				}
				if (pEquationLeftDown >= 0 && pEquationLeftDown <= iBoardSize && !bMoveValid)
				{
					for (unsigned int i = 0; i < iBoardWidth; i++)
					{
						if (this->iPosition >= (i * iBoardWidth) && (this->iPosition <= ((i * iBoardWidth) + (iBoardWidth - 1))) &&
							(pEquationLeftDown >= ((i + 1) * iBoardWidth)) && pEquationLeftDown <= (((i + 1) * iBoardWidth) + (iBoardWidth - 1)))
						{
							if (bMoveCheck)
							{
								CheckBoard[pEquationLeftDown] = 'N';
								KnightCheckBoard[pEquationLeftDown] = 'N';
								if (this->bWhitePiece && pEquationLeftDown == iBlackKingLocation)
									swChecking.push_back(this->sName);
								else if (!this->bWhitePiece && pEquationLeftDown == iWhiteKingLocation)
									sbChecking.push_back(this->sName);
							}
							else
							{
								if (iMoveTo == pEquationLeftDown)
								{
									dHistory.push_back("Knight moved left down");
									bMoveValid = true;
								}
							}
						}
					}
				}
				if (pEquationRightDown >= 0 && pEquationRightDown <= iBoardSize && !bMoveValid)
				{
					for (unsigned int i = 0; i < iBoardWidth; i++)
					{
						if (this->iPosition >= (i * iBoardWidth) && (this->iPosition <= ((i * iBoardWidth) + (iBoardWidth - 1))) &&
							(pEquationRightDown >= ((i + 1) * iBoardWidth)) && pEquationRightDown <= (((i + 1) * iBoardWidth) + (iBoardWidth - 1)))
						{
							if (bMoveCheck)
							{
								CheckBoard[pEquationRightDown] = 'N';
								KnightCheckBoard[pEquationRightDown] = 'N';
								if (this->bWhitePiece && pEquationRightDown == iBlackKingLocation)
									swChecking.push_back(this->sName);
								else if (!this->bWhitePiece && pEquationRightDown == iWhiteKingLocation)
									sbChecking.push_back(this->sName);
							}
							else
							{
								if (iMoveTo == pEquationRightDown)
								{
									dHistory.push_back("Knight moved right down");
									bMoveValid = true;
								}
							}
						}
					}
				}
				if (pEquationLeftUp >= 0 && pEquationLeftUp <= iBoardSize && !bMoveValid)
				{
					for (unsigned int i = 0; i < iBoardWidth; i++)
					{
						if (this->iPosition >= (i * iBoardWidth) && (this->iPosition <= ((i * iBoardWidth) + (iBoardWidth - 1))) &&
							(pEquationLeftUp >= ((i - 1) * iBoardWidth)) && pEquationLeftUp <= (((i - 1) * iBoardWidth) + (iBoardWidth - 1)))
						{
							if (bMoveCheck)
							{
								CheckBoard[pEquationLeftUp] = 'N';
								KnightCheckBoard[pEquationLeftUp] = 'N';
								if (this->bWhitePiece && pEquationLeftUp == iBlackKingLocation)
									swChecking.push_back(this->sName);
								else if (!this->bWhitePiece && pEquationLeftUp == iWhiteKingLocation)
									sbChecking.push_back(this->sName);
							}
							else
							{
								if (iMoveTo == pEquationLeftUp)
								{
									dHistory.push_back("Knight moved left up");
									bMoveValid = true;
								}
							}
						}
					}
				}
				if (pEquationRightUp >= 0 && pEquationRightUp <= iBoardSize && !bMoveValid)
				{
					for (unsigned int i = 0; i < iBoardWidth; i++)
					{
						if (this->iPosition >= (i * iBoardWidth) && (this->iPosition <= ((i * iBoardWidth) + (iBoardWidth - 1))) &&
							(pEquationRightUp >= ((i - 1) * iBoardWidth)) && pEquationRightUp <= (((i - 1) * iBoardWidth) + (iBoardWidth - 1)))
						{
							if (bMoveCheck)
							{
								CheckBoard[pEquationRightUp] = 'N';
								KnightCheckBoard[pEquationRightUp] = 'N';
								if (this->bWhitePiece && pEquationRightUp == iBlackKingLocation)
									swChecking.push_back(this->sName);
								else if (!this->bWhitePiece && pEquationRightUp == iWhiteKingLocation)
									sbChecking.push_back(this->sName);
							}
							else
							{
								if (iMoveTo == pEquationRightUp)
								{
									dHistory.push_back("Knight moved right up");
									bMoveValid = true;
								}
							}
						}
					}
				}
			}	//	END KNIGHT logic
			else if (this->iType == 5)	//---------------------------------------	PAWN LOGIC	-------------------------------------------	PAWN LOGIC	----------------------------------	-------------------------------------------	PAWN LOGIC	----------------------------------
			{
				unsigned int pEquationUp = 0;
				unsigned int pEquationDouble = 0;
				unsigned int pEquationRightCapture = 0;
				unsigned int pEquationLeftCapture = 0;
				if (this->bWhitePiece == true)
				{
					pEquationUp = this->iPosition - 8;
					pEquationDouble = this->iPosition - 16;
					pEquationRightCapture = this->iPosition - 7;
					pEquationLeftCapture = this->iPosition - 9;

				}
				else // color is black
				{
					pEquationUp = this->iPosition + 8;
					pEquationDouble = this->iPosition + 16;
					pEquationRightCapture = this->iPosition + 7;
					pEquationLeftCapture = this->iPosition + 9;
				}
				for (unsigned int i = 0; i < iBoardWidth; i++)
				{
					if (this->bWhitePiece == true)
					{
						if (((this->iPosition >= i * iBoardWidth) && (this->iPosition <= (i * iBoardWidth) + (iBoardWidth - 1))))
						{
							if (((pEquationLeftCapture >= 0) && (pEquationLeftCapture <= iBoardSize)) &&
								((pEquationLeftCapture >= ((i - 1) * iBoardWidth)) && (pEquationLeftCapture <= (((i - 1) * iBoardWidth) + (iBoardWidth - 1)))) && !bMoveValid)
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationLeftCapture] = 'P';
									PawnCheckBoard[pEquationLeftCapture] = 'P';
									if (this->bWhitePiece && pEquationLeftCapture == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationLeftCapture == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else
								{
									if (iMoveTo == pEquationLeftCapture)
									{
										dHistory.push_back("Pawn captured left");
										bMoveValid = true;
									}
								}
							}
							if (((pEquationRightCapture >= 0) && (pEquationRightCapture <= iBoardSize)) &&
								((pEquationRightCapture >= ((i - 1) * iBoardWidth)) && (pEquationRightCapture <= (((i - 1) * iBoardWidth) + (iBoardWidth - 1)))) && !bMoveValid)
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationRightCapture] = 'P';
									PawnCheckBoard[pEquationRightCapture] = 'P';
									if (this->bWhitePiece && pEquationRightCapture == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationRightCapture == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else
								{
									if (iMoveTo == pEquationRightCapture)
									{
										dHistory.push_back("Pawn captured right");
										bMoveValid = true;
									}
								}
							}
							if (((pEquationUp >= 0) && (pEquationUp <= iBoardSize)) &&
								((pEquationUp >= ((i - 1) * iBoardWidth)) && (pEquationUp <= (((i - 1) * iBoardWidth) + (iBoardWidth - 1)))) && !bMoveValid && !bCapturePiece)
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationUp] = 'P';
									PawnCheckBoard[pEquationUp] = 'P';
									if (this->bWhitePiece && pEquationUp == iBlackKingLocation)
										swChecking.push_back(this->sName);
									else if (!this->bWhitePiece && pEquationUp == iWhiteKingLocation)
										sbChecking.push_back(this->sName);
								}
								else
								{
									if (iMoveTo == pEquationUp)
									{
										dHistory.push_back("Pawn moved up");
										bMoveValid = true;
									}
								}
								if (this->iMoves == 0 && !bMoveValid && !bCapturePiece)
								{
									if (bMoveCheck)
									{
										CheckBoard[pEquationDouble] = 'P';
										PawnCheckBoard[pEquationDouble] = 'P';
										if (this->bWhitePiece && pEquationDouble == iBlackKingLocation)
											swChecking.push_back(this->sName);
										else if (!this->bWhitePiece && pEquationDouble == iWhiteKingLocation)
											sbChecking.push_back(this->sName);
									}
									else
									{
										if (iMoveTo == pEquationDouble)
										{
											dHistory.push_back("Pawn moved up double");
											bMoveValid = true;
										}
									}
								}
							}
						}
					}
					else    // piece is  black
					{
						if (((this->iPosition >= i * iBoardWidth) && (this->iPosition <= (i * iBoardWidth) + (iBoardWidth - 1))))
						{
							if (((pEquationLeftCapture >= 0) && (pEquationLeftCapture <= iBoardSize)) &&
								((pEquationLeftCapture >= ((i + 1) * iBoardWidth)) && (pEquationLeftCapture <= (((i + 1) * iBoardWidth) + (iBoardWidth - 1)))) && !bMoveValid)
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationLeftCapture] = 'P';
									PawnCheckBoard[pEquationLeftCapture] = 'P';
								}
								else
								{
									if (iMoveTo == pEquationLeftCapture)
									{
										dHistory.push_back("Pawn captured left");
										bMoveValid = true;
									}
								}
							}
							if (((pEquationRightCapture >= 0) && (pEquationRightCapture <= iBoardSize)) &&
								((pEquationRightCapture >= ((i + 1) * iBoardWidth)) && (pEquationRightCapture <= (((i + 1) * iBoardWidth) + (iBoardWidth - 1)))) && !bMoveValid)
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationRightCapture] = 'P';
									PawnCheckBoard[pEquationRightCapture] = 'P';
								}
								else
								{
									if (iMoveTo == pEquationRightCapture)
									{
										dHistory.push_back("Pawn captured right");
										bMoveValid = true;
									}
								}
							}
							if (((pEquationUp >= 0) && (pEquationUp <= iBoardSize)) &&
								((pEquationUp >= ((i + 1) * iBoardWidth)) && (pEquationUp <= (((i + 1) * iBoardWidth) + (iBoardWidth - 1)))) && !bMoveValid && !bCapturePiece)
							{
								if (bMoveCheck)
								{
									CheckBoard[pEquationUp] = 'P';
									PawnCheckBoard[pEquationUp] = 'P';
								}
								else
								{
									if (iMoveTo == pEquationUp)
									{
										dHistory.push_back("Pawn moved down");
										bMoveValid = true;
									}
								}
								if (this->iMoves == 0 && !bMoveValid && !bCapturePiece)
								{
									if (bMoveCheck)
									{
										CheckBoard[pEquationDouble] = 'P';
										PawnCheckBoard[pEquationDouble] = 'P';
									}
									else
									{
										if (iMoveTo == pEquationDouble)
										{
											dHistory.push_back("Pawn moved down double");
											bMoveValid = true;
										}
									}
								}
							}
						}
					}
				}
			}	//---------------------------------------	PAWN LOGIC END	-------------------------------------------	PAWN LOGIC END	----------------------------------	-------------------------------------------	PAWN LOGIC END	----------------------------------

			if (bMoveCheck) { return false; }
			if (bMoveValid == true)
			{
				bool CheckKingCheck = true;

				std::string sMoveFrom = "";
				std::string sMoveTo = "";
				char cMovefWidth = cFromIntToChar1(iMoveFrom);
				char cMovefHeight = cFromIntToChar2(iMoveFrom);
				sMoveFrom.push_back(cMovefWidth);
				sMoveFrom.push_back(cMovefHeight);
				char cMovetWidth = cFromIntToChar1(iMoveTo);
				char cMovetHeight = cFromIntToChar2(iMoveTo);
				sMoveTo.push_back(cMovetWidth);
				sMoveTo.push_back(cMovetHeight);

				if (this->iType != 0)
				{
					if (bCapturePiece == true)
					{
						mHistory.push_back(sBoard[iMoveFrom] + " from " + sMoveFrom + " captured " + sBoard[iMoveTo] + " at " + sMoveTo);
						dHistory.push_back("INFO: " + sBoard[iMoveFrom] + " from " + sMoveFrom + " captured " + sBoard[iMoveTo] + " at " + sMoveTo);
						sCaptured.push_back(sBoard[iMoveTo]);
					}
					else if (bCurrentlyCastling == true)
					{
						mHistory.push_back(sBoard[iMoveFrom] + " castled from " + sMoveFrom + " to " + sMoveTo);
						dHistory.push_back("INFO: " + sBoard[iMoveFrom] + " castled from " + sMoveFrom + " to " + sMoveTo);
						bCurrentlyCastling = false;
					}
					else
					{
						mHistory.push_back(sBoard[iMoveFrom] + " moved from " + sMoveFrom + " to " + sMoveTo);
						dHistory.push_back("INFO: " + sBoard[iMoveFrom] + " moved from " + sMoveFrom + " to " + sMoveTo);
					}
					this->iMoves++;
					this->iPosition = iMoveTo;

					iBoard[iMoveTo] = this->cVisual;
					iBoard[iMoveFrom] = ' ';

					sBoard[iMoveTo] = sBoard[iMoveFrom];
					sBoard[iMoveFrom] = ' ';
					if (bCheckingForCheckmate == false)
						CheckKingCheck = bIsKingInCheck();
					bMoveCheck = false;
					bool CheckMateCheck = false;

					if (CheckKingCheck == true)
					{
						if (CurrentColorIsWhite == true)
						{
							dHistory.push_back("INFO: bBlackKingInCheck is TRUE");
							bBlackKingInCheck = true;
							bMoveCheck = false;
							if (bCheckingForCheckmate == false)
								bCheckmate = bIsKingInCheckmate();
							else
								return false;
						}
						else
						{
							dHistory.push_back("INFO: bWhiteKingInCheck is TRUE");
							bWhiteKingInCheck = true;
							
							bMoveCheck = false;
							if (bCheckingForCheckmate == false)
								bCheckmate = bIsKingInCheckmate();
							else
								return false;
						}
					}
					else
					{
						if (CurrentColorIsWhite == true)
						{
							dHistory.push_back("INFO: bBlackKingInCheck is FALSE");
							bWhiteKingInCheck = false;
						}
						else
						{
							dHistory.push_back("INFO: bWhiteKingInCheck is FALSE");
							bBlackKingInCheck = false;
						}
					}

					return true;
				}
				else
				{
					iBoard[this->iPosition] = this->cVisual;
					iBoard[iMoveFrom] = ' ';

					sBoard[iMoveTo] = sBoard[iMoveFrom];
					sBoard[iMoveFrom] = ' ';

					this->iMoves++;
					this->iPosition = iMoveTo;

					if (CurrentColorIsWhite == true)
					{
						CurrentColorIsWhite = false;
						CheckKingCheck = bIsKingInCheck();
						bMoveCheck = false;
						CurrentColorIsWhite = true;
					}
					else
					{
						CurrentColorIsWhite = true;
						CheckKingCheck = bIsKingInCheck();
						bMoveCheck = false;
						CurrentColorIsWhite = false;
					}
					std::cout << "CheckKingCheck: " << std::to_string(CheckKingCheck) << std::endl;
					dHistory.push_back("King is in check: " + std::to_string(CheckKingCheck));
					if (CheckKingCheck == true)
					{
						if (CurrentColorIsWhite == true)
						{
							if (CheckBoard[iMoveTo] != ' ')
							{
								dHistory.push_back("ERR: You can't move your king into check!");
								sErrorMsg = "You can't move your king into check!";

								this->iMoves--;
								this->iPosition = iMoveFrom;

								iBoard[this->iPosition] = this->cVisual;
								iBoard[iMoveTo] = ' ';

								sBoard[iMoveFrom] = sBoard[iMoveTo];
								sBoard[iMoveTo] = ' ';
								return false;
							}
							else
							{
								iWhiteKingLocation = iMoveTo;
								dHistory.push_back("White King Location: " + std::to_string(iWhiteKingLocation));
								return true;
							}
						}
						else
						{
							if (CheckBoard[iMoveTo] != ' ')
							{
								dHistory.push_back("ERR: You can't move your king into check!");
								sErrorMsg = "You can't move your king into check!";
								this->iMoves--;
								this->iPosition = iMoveFrom;

								iBoard[this->iPosition] = this->cVisual;
								iBoard[iMoveTo] = ' ';

								sBoard[iMoveFrom] = sBoard[iMoveTo];
								sBoard[iMoveTo] = ' ';
								return false;
							}
							else
							{
								iBlackKingLocation = iMoveTo;
								dHistory.push_back("Black King Location: " + std::to_string(iBlackKingLocation));
								return true;
							}
						}
					}
					else
					{
						return false;
					}
				}
			}
			else
			{
				return false;
			}
		}	//	END SetPosition
		void SetPiece(int iType, bool bWhitePiece, int iPieceNum)			//				SetPiece
		{
			this->bWhitePiece = bWhitePiece;
			this->iMoves = 0;
			this->iPieceNumber = iPieceNum;

			if (iType == 0)	//	for KING pieces
			{
				this->iType = 0;
				this->iValue = 0;

				if (bWhitePiece == true)
				{
					this->iPosition = 60;
					iBoard[this->iPosition] = 'K';
					this->cVisual = 'K';
					this->sName = "wKing";
					sBoard[this->iPosition] = this->sName;
				}
				else if (bWhitePiece == false)
				{
					this->iPosition = 4;
					iBoard[this->iPosition] = 'k';
					this->cVisual = 'k';
					this->sName = "bKing";
					sBoard[this->iPosition] = this->sName;
				}

			}
			else if (iType == 1)	//	for QUEEN pieces
			{
				this->iType = 1;
				this->iValue = 9;

				if (bWhitePiece == true)
				{
					this->iPosition = 59;
					iBoard[this->iPosition] = 'Q';
					this->cVisual = 'Q';
					this->sName = "wQueen";
					sBoard[this->iPosition] = this->sName;
				}
				else if (bWhitePiece == false)
				{
					this->iPosition = 3;
					iBoard[this->iPosition] = 'q';
					this->cVisual = 'q';
					this->sName = "bQueen";
					sBoard[this->iPosition] = this->sName;
				}
			}
			else if (iType == 2)	//	for ROOK pieces
			{
				this->iType = 2;
				this->iValue = 5;

				if (bWhitePiece == true)
				{
					this->iPosition = 56;
					if (iPieceNum == 2)
					{
						this->iPosition += 7;
					}
					iBoard[this->iPosition] = 'R';
					this->cVisual = 'R';
					this->sName = "wRook" + std::to_string(iPieceNum);
					sBoard[this->iPosition] = this->sName;
				}
				else if (bWhitePiece == false)
				{
					this->iPosition = 0;
					if (iPieceNum == 2)
					{
						this->iPosition += 7;
					}
					iBoard[this->iPosition] = 'r';
					this->cVisual = 'r';
					this->sName = "bRook" + std::to_string(iPieceNum);
					sBoard[this->iPosition] = this->sName;
				}
			}
			else if (iType == 3)	//	for BISHOP pieces
			{
				this->iType = 3;
				this->iValue = 3;

				if (bWhitePiece == true)
				{
					this->iPosition = 58;
					if (iPieceNum == 2)
					{
						this->iPosition += 3;
					}
					iBoard[this->iPosition] = 'B';
					this->cVisual = 'B';
					this->sName = "wBishop" + std::to_string(iPieceNum);
					sBoard[this->iPosition] = this->sName;
				}
				else if (bWhitePiece == false)
				{
					this->iPosition = 2;
					if (iPieceNum == 2)
					{
						this->iPosition += 3;
					}
					iBoard[this->iPosition] = 'b';
					this->cVisual = 'b';
					this->sName = "bBishop" + std::to_string(iPieceNum);
					sBoard[this->iPosition] = this->sName;
				}

			}
			else if (iType == 4)	//	for KNIGHT pieces
			{
				this->iType = 4;
				this->iValue = 3;

				if (bWhitePiece == true)
				{
					this->iPosition = 57;
					if (iPieceNum == 2)
					{
						this->iPosition += 5;
					}
					iBoard[this->iPosition] = 'N';
					this->cVisual = 'N';
					this->sName = "wKnight" + std::to_string(iPieceNum);
					sBoard[this->iPosition] = this->sName;
				}
				else if (bWhitePiece == false)
				{
					this->iPosition = 1;
					if (iPieceNum == 2)
					{
						this->iPosition += 5;
					}
					iBoard[this->iPosition] = 'n';
					this->cVisual = 'n';
					this->sName = "bKnight" + std::to_string(iPieceNum);
					sBoard[this->iPosition] = this->sName;
				}
			}
			else if (iType == 5)	//	for PAWN pieces
			{
				this->iType = 5;
				this->iValue = 1;

				if (bWhitePiece == true)
				{
					this->iPosition = 48;
					if (iPieceNum > 1)
					{
						this->iPosition += iPieceNum - 1;
					}
					iBoard[this->iPosition] = 'P';
					this->cVisual = 'P';
					this->sName = "wPawn" + std::to_string(iPieceNum);
					sBoard[this->iPosition] = this->sName;
				}
				else if (bWhitePiece == false)
				{
					this->iPosition = 8;
					if (iPieceNum > 1)
					{
						this->iPosition += iPieceNum - 1;
					}
					iBoard[this->iPosition] = 'p';
					this->cVisual = 'p';
					this->sName = "bPawn" + std::to_string(iPieceNum);
					sBoard[this->iPosition] = this->sName;
				}
			}
			else
			{
				std::cerr << "This piece could not be initalized. Please try again." << std::endl;
			}

		}	//	END SetPiece

		//	Getters
		int GetPosition(void)
		{
			return(this->iPosition);
		}
		int GetValue(void)
		{
			return(this->iValue);
		}
		int GetType(void)
		{
			return(this->iType);
		}
		char GetCVisual(void)
		{
			return(this->cVisual);
		}

		//	Other Functions

	} // Declare WHITE Piece Objects
		wKing,
		wQueen,

		wRook1,
		wRook2,

		wBishop1,
		wBishop2,

		wKnight1,
		wKnight2,

		wPawn1,
		wPawn2,
		wPawn3,
		wPawn4,
		wPawn5,
		wPawn6,
		wPawn7,
		wPawn8,

		// Declare BLACK Objects			------- ADD extras for PAWN PROMOTION
		bKing,
		bQueen,

		bRook1,
		bRook2,

		bBishop1,
		bBishop2,

		bKnight1,
		bKnight2,

		bPawn1,
		bPawn2,
		bPawn3,
		bPawn4,
		bPawn5,
		bPawn6,
		bPawn7,
		bPawn8;	//	END Class Piece

	void vPieceInit()
	{
		// Initalize White Pieces
		wKing.SetPiece(0, true, 0);
		wQueen.SetPiece(1, true, 0);
		iWhiteKingLocation = 60;

		wRook1.SetPiece(2, true, 1);
		wRook2.SetPiece(2, true, 2);

		wBishop1.SetPiece(3, true, 1);
		wBishop2.SetPiece(3, true, 2);

		wKnight1.SetPiece(4, true, 1);
		wKnight2.SetPiece(4, true, 2);

		wPawn1.SetPiece(5, true, 1);
		wPawn2.SetPiece(5, true, 2);
		wPawn3.SetPiece(5, true, 3);
		wPawn4.SetPiece(5, true, 4);
		wPawn5.SetPiece(5, true, 5);
		wPawn6.SetPiece(5, true, 6);
		wPawn7.SetPiece(5, true, 7);
		wPawn8.SetPiece(5, true, 8);

		// Initalize Black Pieces
		bKing.SetPiece(0, false, 0);
		bQueen.SetPiece(1, false, 0);
		iBlackKingLocation = 4;

		bRook1.SetPiece(2, false, 1);
		bRook2.SetPiece(2, false, 2);

		bBishop1.SetPiece(3, false, 1);
		bBishop2.SetPiece(3, false, 2);

		bKnight1.SetPiece(4, false, 1);
		bKnight2.SetPiece(4, false, 2);

		bPawn1.SetPiece(5, false, 1);
		bPawn2.SetPiece(5, false, 2);
		bPawn3.SetPiece(5, false, 3);
		bPawn4.SetPiece(5, false, 4);
		bPawn5.SetPiece(5, false, 5);
		bPawn6.SetPiece(5, false, 6);
		bPawn7.SetPiece(5, false, 7);
		bPawn8.SetPiece(5, false, 8);

		for (unsigned int i = 0; i < iBoardSize; i++)
		{
			KingCheckBoard[i] = ' ';
			QueenCheckBoard[i] = ' ';
			RookCheckBoard[i] = ' ';
			BishopCheckBoard[i] = ' ';
			KnightCheckBoard[i] = ' ';
			PawnCheckBoard[i] = ' ';
		}
	}
	bool bSearchObj(std::string pName)	//----------bSearchObj()----------//----------bSearchObj()----------//----------bSearchObj()----------
	{
		bool lValidMove = false;
		bMoveCheck = false;

		if (pName == "wKing")
			lValidMove = wKing.SetPosition();
		else if (pName == "bKing")
			lValidMove = bKing.SetPosition();
		else if (pName == "wQueen")
			lValidMove = wQueen.SetPosition();
		else if (pName == "bQueen")
			lValidMove = bQueen.SetPosition();
		else if (pName == "wRook1")
			lValidMove = wRook1.SetPosition();
		else if (pName == "wRook2")
			lValidMove = wRook2.SetPosition();
		else if (pName == "bRook1")
			lValidMove = bRook1.SetPosition();
		else if (pName == "bRook2")
			lValidMove = bRook2.SetPosition();
		else if (pName == "wBishop1")
			lValidMove = wBishop1.SetPosition();
		else if (pName == "wBishop2")
			lValidMove = wBishop2.SetPosition();
		else if (pName == "bBishop1")
			lValidMove = bBishop1.SetPosition();
		else if (pName == "bBishop2")
			lValidMove = bBishop2.SetPosition();
		else if (pName == "wKnight1")
			lValidMove = wKnight1.SetPosition();
		else if (pName == "wKnight2")
			lValidMove = wKnight2.SetPosition();
		else if (pName == "bKnight1")
			lValidMove = bKnight1.SetPosition();
		else if (pName == "bKnight2")
			lValidMove = bKnight2.SetPosition();
		else if (pName == "wPawn1")
			lValidMove = wPawn1.SetPosition();
		else if (pName == "wPawn2")
			lValidMove = wPawn2.SetPosition();
		else if (pName == "wPawn3")
			lValidMove = wPawn3.SetPosition();
		else if (pName == "wPawn4")
			lValidMove = wPawn4.SetPosition();
		else if (pName == "wPawn5")
			lValidMove = wPawn5.SetPosition();
		else if (pName == "wPawn6")
			lValidMove = wPawn6.SetPosition();
		else if (pName == "wPawn7")
			lValidMove = wPawn7.SetPosition();
		else if (pName == "wPawn8")
			lValidMove = wPawn8.SetPosition();
		else if (pName == "bPawn1")
			lValidMove = bPawn1.SetPosition();
		else if (pName == "bPawn2")
			lValidMove = bPawn2.SetPosition();
		else if (pName == "bPawn3")
			lValidMove = bPawn3.SetPosition();
		else if (pName == "bPawn4")
			lValidMove = bPawn4.SetPosition();
		else if (pName == "bPawn5")
			lValidMove = bPawn5.SetPosition();
		else if (pName == "bPawn6")
			lValidMove = bPawn6.SetPosition();
		else if (pName == "bPawn7")
			lValidMove = bPawn7.SetPosition();
		else if (pName == "bPawn8")
			lValidMove = bPawn8.SetPosition();
		else
		{
			dHistory.push_back("ERR: \"" + pName + "\" could not be moved.");
			sErrorMsg = "There isn't a piece there!";
			return false;
		}

		if (lValidMove == true)
		{
			if (CurrentColorIsWhite == true)
			{
				CurrentColorIsWhite = false;
				wMoves++;
			}
			else if (CurrentColorIsWhite == false)
			{
				CurrentColorIsWhite = true;
				bMoves++;
			}

			return true;
		}
		return false;
	}//		END bSearchObj()			//			END bSearchObj()			//		END bSearchObj()

	void vMoveCheck()	//----------vMoveCheck()----------//-----------vMoveCheck()----------//----------vMoveCheck()-----------//----------vMoveCheck()---------
	{
		bool lValidMove = false;
		bMoveCheck = true;
		std::string pName = sBoard[iMoveFrom];

		for (unsigned int i = 0; i <= iBoardSize; i++)
		{
			CheckBoard[i] = ' ';
			cMoveBoard[i] = ' ';
		}

		if (pName == "wKing" || pName == "wking")
			wKing.SetPosition();
		else if (pName == "bKing" || pName == "bking")
			bKing.SetPosition();
		else if (pName == "wQueen" || pName == "wqueen")
			wQueen.SetPosition();
		else if (pName == "bQueen" || pName == "bqueen")
			bQueen.SetPosition();
		else if (pName == "wRook1" || pName == "wrook1")
			wRook1.SetPosition();
		else if (pName == "wRook2" || pName == "wrook2")
			wRook2.SetPosition();
		else if (pName == "bRook1" || pName == "brook1")
			bRook1.SetPosition();
		else if (pName == "bRook2" || pName == "brook2")
			bRook2.SetPosition();
		else if (pName == "wBishop1" || pName == "wbishop1")
			wBishop1.SetPosition();
		else if (pName == "wBishop2" || pName == "wbishop2")
			wBishop2.SetPosition();
		else if (pName == "bBishop1" || pName == "bbishop1")
			bBishop1.SetPosition();
		else if (pName == "bBishop2" || pName == "bbishop2")
			bBishop2.SetPosition();
		else if (pName == "wKnight1" || pName == "wknight1")
			wKnight1.SetPosition();
		else if (pName == "wKnight2" || pName == "wknight2")
			wKnight2.SetPosition();
		else if (pName == "bKnight1" || pName == "bknight1")
			bKnight1.SetPosition();
		else if (pName == "bKnight2" || pName == "bknight2")
			bKnight2.SetPosition();
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
			dHistory.push_back("ERR: No piece at " + std::to_string(iMoveFrom));
			sErrorMsg = "There isn't a piece there!";
		}

		for (unsigned int i = 0; i < iBoardSize; i++)
		{
			cMoveBoard[i] = CheckBoard[i];
		}
		return;
	}	//		END vMoveCheck()			//			END vMoveCheck()			//		END vMoveCheck()

	bool bIsKingInCheck()	//----------bIsKingInCheck()----------//---------bIsKingInCheck()------------//----------bIsKingInCheck()----------
	{
		for (unsigned int i = 0; i <= iBoardSize; i++)
		{
			CheckBoard[i] = ' ';
			KingCheckBoard[i] = ' ';
			QueenCheckBoard[i] = ' ';
			RookCheckBoard[i] = ' ';
			BishopCheckBoard[i] = ' ';
			KnightCheckBoard[i] = ' ';
			PawnCheckBoard[i] = ' ';
		}
		bMoveCheck = true;
		std::string pName;
		if (CurrentColorIsWhite)
		{
			dHistory.push_back("Is BLACK King in Check?");
			for (unsigned int i = 0; i < iBoardSize; i++)
			{
				if (bCheckingbChecking)
				{
					if (i < swChecking.size())
						std::string pName = swChecking.at(i);
					else
						return true;
				}
				else
					std::string pName = sBoard[i];
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
			}
			if (CheckBoard[iBlackKingLocation] != ' ' || bCheckingForCheckmate)
			{
				dHistory.push_back("INFO: BLACK King is in check!");
				return true;
			}
		}
		else
		{
			dHistory.push_back("Is WHITE King in Check?");
			for (unsigned int i = 0; i < iBoardSize; i++)
			{
				if (bCheckingbChecking)
				{
					if (i < swChecking.size())
						std::string pName = swChecking.at(i);
					else
						return true;
				}
				else
					std::string pName = sBoard[i];

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
			}
			if (CheckBoard[iWhiteKingLocation] != ' ' || bCheckingForCheckmate)
			{
				dHistory.push_back("INFO: WHITE King in in check!");
				return true;
			}
		}
		return false;
	}	//		END bIsKingInCheck()			//			END bIsKingInCheck()			//		END bIsKingInCheck()

	bool bIsKingInCheckmate()	//----------bIsKingInCheckmate()-------//----------bIsKingInCheckmate()----------//----------bIsKingInCheckmate()----------
	{
		bool lCheckmate = false;
		bool lCurrentColorIsWhite = CurrentColorIsWhite;
		bMoveCheck = true;
		for (unsigned int i = 0; i <= iBoardSize; i++)
		{
			CheckmateBoard[i] = CheckBoard[i];
			CheckBoard[i] = ' ';
		}

		if (bWhiteKingInCheck == true)
		{
			bCheckingForCheckmate = true;
			wKing.SetPosition();
			for (unsigned int i = 0; i <= iBoardSize; i++)
			{
				if (KingCheckBoard[i] != ' ' && CheckmateBoard[i] == ' ')
				{
					dHistory.push_back("Possible move at " + std::to_string(i));
					lCheckmate = false;
					break;
				}
				else
				{
					CurrentColorIsWhite = !CurrentColorIsWhite;
					for (unsigned int j = 0; j < iBoardSize; j++)
					{
						lKingCheckBoard[j] = KingCheckBoard[j];
						CheckBoard[j] = ' ';
					}
					bIsKingInCheck();
					if (lKingCheckBoard[i] != ' ' && CheckBoard[i] != ' ')
					{
						lCheckmate = false;
						break;
					}
					else
					{
						lCheckmate = true;
					}
				}
			}
		}
		else if (bBlackKingInCheck == true)
		{
			bCheckingForCheckmate = true;
			bKing.SetPosition();
			bMoveCheck = true;
			for (unsigned int i = 0; i <= iBoardSize; i++)
			{
				if (KingCheckBoard[i] != ' ' && CheckmateBoard[i] == ' ')
				{
					dHistory.push_back("Possible move at " + std::to_string(i));
					lCheckmate = false;
					int bIndex = iBoardHeight;
					std::cout << "\t            CheckBoard        \t        CheckmateBoard" << std::endl;
					std::cout << "\t      A  B  C  D  E  F  G  H  \t A  B  C  D  E  F  G  H " << std::endl;
					std::cout << "\t    ==========================\t===========================";
					for (unsigned int height = 0; height < iBoardHeight; height++)
					{
						std::cout << std::endl;
						std::cout << "\t " << bIndex << " | ";
						for (unsigned int width = 0; width < iBoardWidth; width++)
						{
							int iBoardPrint = ((width + 1) + (height * iBoardHeight)) - 1;
							std::cout << " " << CheckBoard[iBoardPrint] << " ";
						}
						std::cout << "\t";
						for (unsigned int width = 0; width < iBoardWidth; width++)
						{
							int iBoardPrint = ((width + 1) + (height * iBoardHeight)) - 1;
							std::cout << " " << CheckmateBoard[iBoardPrint] << " ";
						}
						bIndex--;
					}
					for (unsigned int k = 0; k < swChecking.size(); k++)
					{
						std::cout << "\n\t" << k + 1 << ". swChecking: " << swChecking.at(k) << std::endl;
					}
					break;
				}
				else
				{
					CurrentColorIsWhite = !CurrentColorIsWhite;
					for (unsigned int j = 0; j <= iBoardSize; j++)
					{
						lKingCheckBoard[j] = KingCheckBoard[j];
						CheckBoard[j] = ' ';
					}
					bCheckingbChecking = true;
					bIsKingInCheck();
					if (lKingCheckBoard[i] != ' ' && CheckBoard[i] != ' ')
					{
						lCheckmate = false;
						int bIndex = iBoardHeight;
						std::cout << "\t            lKingCheckBoard        \t      CheckBoard" << std::endl;
						std::cout << "\t      A  B  C  D  E  F  G  H  \t A  B  C  D  E  F  G  H " << std::endl;
						std::cout << "\t    ==========================\t===========================";
						for (unsigned int height = 0; height < iBoardHeight; height++)
						{
							std::cout << std::endl;
							std::cout << "\t " << bIndex << " | ";
							for (unsigned int width = 0; width < iBoardWidth; width++)
							{
								int iBoardPrint = ((width + 1) + (height * iBoardHeight)) - 1;
								std::cout << " " << lKingCheckBoard[iBoardPrint] << " ";
							}
							std::cout << "\t";
							for (unsigned int width = 0; width < iBoardWidth; width++)
							{
								int iBoardPrint = ((width + 1) + (height * iBoardHeight)) - 1;
								std::cout << " " << CheckBoard[iBoardPrint] << " ";
							}
							bIndex--;
						}
						for (unsigned int k = 0; k < swChecking.size(); k++)
						{
							std::cout << "\n\t" << k + 1 << ". swChecking: " << swChecking.at(k) << std::endl;
						}
						break;
					}
					else
					{
						lCheckmate = true;
					}
				}
			}
		}
		for (unsigned int i = 0; i <= iBoardSize; i++)
		{
			CheckBoard[i] = CheckmateBoard[i];
			CheckmateBoard[i] = ' ';
		}
		CurrentColorIsWhite = lCurrentColorIsWhite;
		return lCheckmate;
	}	//		END bIsKingInCheckmate()			//			END bIsKingInCheckmate()			//		END bIsKingInCheckmate()

	bool bRookCastle()
	{
		bool lValidMove = false;
		if (bCastleSideQueen)
		{
			if (CurrentColorIsWhite)
				lValidMove = wRook1.SetPosition();
			else
				lValidMove = bRook1.SetPosition();
		}
		else
		{
			if (CurrentColorIsWhite)
				lValidMove = wRook2.SetPosition();
			else
				lValidMove = bRook2.SetPosition();
		}
		return lValidMove;
	}

	int iFromCharToInt1(std::string cValue, int* iAtIndex)	//----------iFromCharToInt1()----------//----------iFromCharToInt1()----------
	{
		int iMoveWidth = 0;
		for (int i = 0; i < 2; i++)
		{
			char cCompare = cValue.at(i);
			if (cCompare == 'a')
				iMoveWidth = 1;
			else if (cCompare == 'b')
				iMoveWidth = 2;
			else if (cCompare == 'c')
				iMoveWidth = 3;
			else if (cCompare == 'd')
				iMoveWidth = 4;
			else if (cCompare == 'e')
				iMoveWidth = 5;
			else if (cCompare == 'f')
				iMoveWidth = 6;
			else if (cCompare == 'g')
				iMoveWidth = 7;
			else if (cCompare == 'h')
				iMoveWidth = 8;

			if (iMoveWidth != 0)
			{
				*iAtIndex = i;
				break;
			}
		}
		return iMoveWidth;
	}	//		END iFromCharToInt1()			//			END iFromCharToInt1()			//		END iFromCharToInt1()
	int iFromCharToInt2(std::string cValue, int* iAtIndex)	//----------iFromCharToInt2()----------//----------iFromCharToInt2()----------
	{
		int iMoveHeight = 0;

		if (*iAtIndex == 0)
		{
			iMoveHeight = cValue.at(1) - '0';
		}
		else if (*iAtIndex == 1)
		{
			iMoveHeight = cValue.at(0) - '0';
		}
		if (iMoveHeight == 1)
			iMoveHeight = 8;
		else if (iMoveHeight == 2)
			iMoveHeight = 7;
		else if (iMoveHeight == 3)
			iMoveHeight = 6;
		else if (iMoveHeight == 4)
			iMoveHeight = 5;
		else if (iMoveHeight == 5)
			iMoveHeight = 4;
		else if (iMoveHeight == 6)
			iMoveHeight = 3;
		else if (iMoveHeight == 7)
			iMoveHeight = 2;
		else if (iMoveHeight == 8)
			iMoveHeight = 1;
		return iMoveHeight;
	}	//		END iFromCharToInt2()			//			END iFromCharToInt2()			//		END iFromCharToInt2()

	char cFromIntToChar1(unsigned int cValue)		//----------cFromIntToChar1()----------//----------cFromIntToChar1()----------
	{
		char cWidth = '0';
		if (cValue % iBoardWidth == 0)
			cWidth = 'A';
		else if (cValue % iBoardWidth == 1)
			cWidth = 'B';
		else if (cValue % iBoardWidth == 2)
			cWidth = 'C';
		else if (cValue % iBoardWidth == 3)
			cWidth = 'D';
		else if (cValue % iBoardWidth == 4)
			cWidth = 'E';
		else if (cValue % iBoardWidth == 5)
			cWidth = 'F';
		else if (cValue % iBoardWidth == 6)
			cWidth = 'G';
		else if (cValue % iBoardWidth == 7)
			cWidth = 'H';

		return cWidth;
	}//		END cFromIntToChar1()			//			END cFromIntToChar1()			//		END cFromIntToChar1()
	char cFromIntToChar2(unsigned int cValue)		//----------cFromIntToChar2()----------//----------cFromIntToChar2()----------
	{
		char cHeight = '0';
		if (cValue >= 0 && cValue <= 7)
			cHeight = '8';
		else if (cValue >= 8 && cValue <= 15)
			cHeight = '7';
		else if (cValue >= 16 && cValue <= 23)
			cHeight = '6';
		else if (cValue >= 24 && cValue <= 31)
			cHeight = '5';
		else if (cValue >= 32 && cValue <= 39)
			cHeight = '4';
		else if (cValue >= 40 && cValue <= 47)
			cHeight = '3';
		else if (cValue >= 48 && cValue <= 55)
			cHeight = '2';
		else if (cValue >= 56 && cValue <= 63)
			cHeight = '1';

		return cHeight;
	}

	void vLoadHistory(std::string sOne, std::string sTwo, std::string sThree, std::string sFour, std::string sFive, std::string sSix, std::string sSeven, std::string sEight)
	{
		//dHistory.push_back(sOne + " " + sTwo + " " + sThree + " " + sFour + " " + sFive + " " + sSix + " " + sSeven + " " + sEight + ".");
		std::string pName = sTwo;
		int iAtIndex = 0;
		int iMovefWidth = 0;
		int iMovefHeight = 0;
		int iMovetWidth = 0;
		int iMovetHeight = 0;

		if (sThree == "from")	//	piece is capturing
		{
			iMovefWidth = iFromCharToInt1(sFour, &iAtIndex);
			iMovefHeight = iFromCharToInt2(sFour, &iAtIndex);
			iMoveFrom = ((iMovefWidth)+((iMovefHeight - 1) * iBoardHeight)) - 1;

			iMovetWidth = iFromCharToInt1(sEight, &iAtIndex);
			iMovetHeight = iFromCharToInt2(sEight, &iAtIndex);
			iMoveTo = ((iMovetWidth)+((iMovetHeight - 1) * iBoardHeight)) - 1;

			bSearchObj(sBoard[iMoveFrom]);
		}
		else if (sThree == "castled")
		{
			iMovefWidth = iFromCharToInt1(sFive, &iAtIndex);
			iMovefHeight = iFromCharToInt2(sFive, &iAtIndex);
			iMoveFrom = ((iMovefWidth)+((iMovefHeight - 1) * iBoardHeight)) - 1;

			iMovetWidth = iFromCharToInt1(sSeven, &iAtIndex);
			iMovetHeight = iFromCharToInt2(sSeven, &iAtIndex);
			iMoveTo = ((iMovetWidth)+((iMovetHeight - 1) * iBoardHeight)) - 1;

			bSearchObj(sBoard[iMoveFrom]);
		}
		else if (sThree == "moved")
		{
			iMovefWidth = iFromCharToInt1(sFive, &iAtIndex);
			iMovefHeight = iFromCharToInt2(sFive, &iAtIndex);
			iMoveFrom = ((iMovefWidth)+((iMovefHeight - 1) * iBoardHeight)) - 1;

			iMovetWidth = iFromCharToInt1(sSeven, &iAtIndex);
			iMovetHeight = iFromCharToInt2(sSeven, &iAtIndex);
			iMoveTo = ((iMovetWidth)+((iMovetHeight - 1) * iBoardHeight)) - 1;

			bSearchObj(sBoard[iMoveFrom]);
		}
		else
		{
			dHistory.push_back("Invalid reading!");
		}
		return;
	}	//	END vLoadHistory()
} // END namspace ChessLogic_H