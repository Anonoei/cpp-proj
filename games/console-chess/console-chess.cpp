/*
		TO DO
features:
	Pawn Promotion
	Pawn "en passant"

	Add Castling for kingside and queenside
	ensure pawn capruting works properly

	debug levels 0, 1, 2, 3

gameplay:
	Check if king is in check
	Create game win
	Create game draw	(stalemate)
	Create game lose (singleplayer)

	Add single player functionality (chess AI)

	Add Multiplayer functionality (two players)

	Add different gamemodes??
		Chess960
		King Of The Hill
		Bughouse
		Crazyhouse
		3-Check
*/



#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <climits>

#include <cctype>
#include <iomanip>
#include <fstream>


//	DECLARE GLOBAL VARIBALES
const int iBoardWidth = 8;
const int iBoardHeight = 8;
const int iBoardSize = (iBoardWidth * iBoardHeight) - 1;

//	Boards
char iBoard[iBoardWidth * iBoardHeight] = { ' ' };	//	initialize array with BoardHeight rows, BoardWidth columns
std::string sBoard[iBoardWidth * iBoardHeight] = { " " };	//	Holds name value for piece at location on board
char CheckBoard[iBoardWidth * iBoardHeight] = { ' ' };		//	Holds value for where pieces can move (checks for check)

std::vector<std::string> dHistory;	//debugHistory
std::vector<std::string> mHistory;	//moveHistory
std::vector<std::string> sCaptured;	//	holds captured pieces
int wMoves = 0;
int bMoves = 0;
int pieceType = 0;
int iWhiteScore = 39;
int iBlackScore = 39;


int iMoveFrom = 0;
int iMoveTo = 0;

int iDebugLevel = 0;


bool bWhiteKingInCheck = false;
bool bBlackKingInCheck = false;
int iWhiteKingLocation = 60;
int iBlackKingLocation = 4;
bool bGameStatus = true;
bool CurrentColorIsWhite = true;

char boardType = 'f';

bool bSinglePlayer();
bool bMultiPlayer();

bool bIsKingInCheck();

char cInputValidation();
void printBoard();

bool bSearchObj();

void vUsrInput();


/*
	Type 0: King	Value: infinite
	Type 1: Queen	Value: 9

	Type 2: Rook	Value: 5

	Type 3: Bishop	Value: 3
	Type 4: Knight	Value: 3

	Type 5: Pawn	Value:1


*/
class Piece {
private:
	int iPosition;
	int iValue;
	int iType;
	int iMoves;
	bool bWhitePiece;
	bool bInGame;
	char cVisual;

public:
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
	}


	//	Destructors
	~Piece(void) {}

	//	Setters
	bool SetKingInCheck()
	{
		bool bMoveValid = false;


		//	King Logic
			int pEquationDown = this->iPosition + 8;
			int pEquationUp = this->iPosition - 8;

			int pEquationLeft = this->iPosition + 1;
			int pEquationRight = this->iPosition - 1;

			int pEquationUpLeft = this->iPosition - 9;
			int pEquationUpRight = this->iPosition - 7;

			int pEquationDownLeft = iMoveTo == this->iPosition + 7;
			int pEquationDownRight = iMoveTo == this->iPosition + 9;

			if (iMoveTo == pEquationDown)	//	move down
			{
				CheckBoard[pEquationDown] = 'x';
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationUp)	//	move up
			{
				CheckBoard[pEquationUp] = 'x';
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationLeft)
			{
				CheckBoard[pEquationLeft] = 'x';
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationRight)
			{
				CheckBoard[pEquationRight] = 'x';
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationUpLeft)
			{
				CheckBoard[pEquationUpLeft] = 'x';
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationUpRight)
			{
				CheckBoard[pEquationUpRight] = 'x';
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationDownLeft)
			{
				CheckBoard[pEquationDownLeft] = 'x';
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationDownRight)
			{
				CheckBoard[pEquationDownRight] = 'x';
				bMoveValid = true;
			}
			else
			{
				bMoveValid = false;
			}

		//	Queen Logic

			int iThroughPiece = 0;
			int iLoopNum = 0;
			bool bThroughCalc = false;

			for (int i = 1; i < iBoardWidth; i++)
			{
				int pEquationDown = this->iPosition + (i * 8);
				int pEquationUp = this->iPosition + -(i * 8);

				int pEquationLeft = this->iPosition + -(i);
				int pEquationRight = this->iPosition + (i);

				int pEquationUpLeft = this->iPosition + -(i * 9);
				int pEquationUpRight = this->iPosition + -(i * 7);

				int pEquationDownLeft = this->iPosition + (i * 7);
				int pEquationDownRight = this->iPosition + (i * 9);

				if (iMoveTo == pEquationDown)		//	move down
				{
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						if (sBoard[pEquationDown] == "")
						{
							iThroughPiece++;
							CheckBoard[pEquationDown] = 'x';
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationUp)	//	move up
				{
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						if (sBoard[pEquationUp] == "")
						{
							iThroughPiece++;
							CheckBoard[pEquationUp] = 'x';
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationLeft)	//	move left
				{
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						if (sBoard[pEquationLeft] == "")
						{
							iThroughPiece++;
							CheckBoard[pEquationLeft] = 'x';
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationRight)	//	move right
				{
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						if (sBoard[pEquationRight] == "")
						{
							iThroughPiece++;
							CheckBoard[pEquationRight] = 'x';
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationUpLeft)	//	move up left
				{
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						if (sBoard[pEquationUpLeft] == "")
						{
							iThroughPiece++;
							CheckBoard[pEquationUpLeft] = 'x';
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationUpRight)	//	move up right
				{
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						if (sBoard[pEquationUpRight] == "")
						{
							iThroughPiece++;
							CheckBoard[pEquationUpRight] = 'x';
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationDownLeft)	//	move down left
				{
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						if (sBoard[pEquationDownLeft] == "")
						{
							iThroughPiece++;
							CheckBoard[pEquationDownLeft] = 'x';
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationDownRight)	//	move down right
				{
					iLoopNum = i;
					bThroughCalc = false;
					for (int i = 1; i < iLoopNum; i++)
					{
						if (sBoard[pEquationDownRight] == "")
						{
							iThroughPiece++;
							CheckBoard[pEquationDownRight] = 'x';
						}
					}
					bThroughCalc = true;
				}
				else
				{
					bMoveValid = false;
				}
			}

			if (bThroughCalc == true)
			{
				if (iThroughPiece == iLoopNum)
				{
					bMoveValid = true;
				}
				else
				{
					bMoveValid = false;
				}
			}

			//	Rook 

			iThroughPiece = 0;
			iLoopNum = 0;
			bThroughCalc = false;

			for (int i = 1; i < iBoardWidth; i++)
			{
				int pEquationDown = this->iPosition + (i * 8);
				int pEquationUp = this->iPosition + -(i * 8);

				int pEquationLeft = this->iPosition + -(i);
				int pEquationRight = this->iPosition + (i);

				if (iMoveTo == pEquationDown)		//	move down
				{
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						if (sBoard[pEquationDown] == "")
						{
							iThroughPiece++;
							CheckBoard[pEquationDown] = 'x';
						}
					}

				}
				else if (iMoveTo == pEquationUp)	//	move up
				{
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						if (sBoard[pEquationUp] == "")
						{
							iThroughPiece++;
							CheckBoard[pEquationUp] = 'x';
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationLeft)	//	move left
				{
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						if (sBoard[pEquationLeft] == "")
						{
							iThroughPiece++;
							CheckBoard[pEquationLeft] = 'x';
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationRight)	//	move right
				{
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						if (sBoard[pEquationRight] == "")
						{
							iThroughPiece++;
							CheckBoard[pEquationRight] = 'x';
						}
					}
					bThroughCalc = true;
				}

			}

			if (bThroughCalc == true)
			{
				if (iThroughPiece == iLoopNum)
				{
					bMoveValid = true;
				}
				else
				{
					bMoveValid = false;
				}
			}

				// Bishop

			iThroughPiece = 0;
			iLoopNum = 0;
			bThroughCalc = false;

			for (int i = 1; i < iBoardWidth; i++)
			{

				int pEquationUpLeft = this->iPosition + -(i * 9);
				int pEquationUpRight = this->iPosition + -(i * 7);

				int pEquationDownLeft = iMoveTo == this->iPosition + (i * 7);
				int pEquationDownRight = iMoveTo == this->iPosition + (i * 9);

				if (iMoveTo == pEquationUpLeft)	//	move up left
				{
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						if (sBoard[pEquationUpLeft] == "")
						{
							iThroughPiece++;
							CheckBoard[pEquationUpLeft] = 'x';
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationUpRight)	//	move up right
				{
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						if (sBoard[pEquationUpRight] == "")
						{
							iThroughPiece++;
							CheckBoard[pEquationUpRight] = 'x';
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationDownLeft)	//	move down left
				{
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						if (sBoard[pEquationDownLeft] == "")
						{
							iThroughPiece++;
							CheckBoard[pEquationDownLeft] = 'x';
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationDownRight)	//	move down right
				{
					iLoopNum = i;
					bThroughCalc = false;
					for (int i = 1; i < iLoopNum; i++)
					{
						if (sBoard[pEquationDownRight] == "")
						{
							iThroughPiece++;
							CheckBoard[pEquationDownRight] = 'x';
						}
					}
					bThroughCalc = true;
				}
				else
				{
					bMoveValid = false;
				}
			}

			if (bThroughCalc == true)
			{
				if (iThroughPiece == iLoopNum)
				{
					bMoveValid = true;
				}
				else
				{
					bMoveValid = false;
				}
			}

				//	Knight

			pEquationDownLeft = this->iPosition + 15;	//	Down
			pEquationDownRight = this->iPosition + 17;

			pEquationUpLeft = this->iPosition - 17;		// Up
			pEquationUpRight = this->iPosition - 15;

			int pEquationLeftDown = this->iPosition + 10;	//	left / right down
			int pEquationRightDown = this->iPosition + 6;

			int pEquationLeftUp = this->iPosition - 10;		// left / right up
			int pEquationRightUp = this->iPosition - 6;

			if (iMoveTo == pEquationDownLeft)
			{
				CheckBoard[pEquationDownLeft] = 'x';
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationDownRight)
			{
				CheckBoard[pEquationDownRight] = 'x';
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationUpLeft)
			{
				CheckBoard[pEquationUpLeft] = 'x';
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationUpRight)
			{
				CheckBoard[pEquationUpRight] = 'x';
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationLeftDown)
			{
				CheckBoard[pEquationLeftDown] = 'x';
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationRightDown)
			{
				CheckBoard[pEquationRightDown] = 'x';
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationLeftUp)
			{
				CheckBoard[pEquationLeftUp] = 'x';
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationRightUp)
			{
				CheckBoard[pEquationRightUp] = 'x';
				bMoveValid = true;
			}
			else
			{
				bMoveValid = false;
			}

			//	Pawn

			if (this->bWhitePiece == true)
			{
				int pEquationUp = this->iPosition - 8;
				int pEquationDouble = this->iPosition - 16;
				int pEquationRightCapture = this->iPosition - 7;
				int pEquationLeftCapture = this->iPosition - 9;


				if (iMoveTo == pEquationUp)
				{
					CheckBoard[pEquationUp] = 'x';
					bMoveValid = true;
				}
				else if (iMoveTo == pEquationDouble && this->iMoves == 0)
				{
					CheckBoard[pEquationDouble] = 'x';
					bMoveValid = true;
				}
				else if (iMoveTo == pEquationRightCapture)
				{
					CheckBoard[pEquationRightCapture] = 'x';
					bMoveValid = true;
				}
				else if (iMoveTo == pEquationLeftCapture)
				{
					CheckBoard[pEquationLeftCapture] = 'x';
					bMoveValid = true;
				}
				else
				{
					bMoveValid = false;
				}
			}
			else
			{
				int pEquationUp = this->iPosition + 8;
				int pEquationDouble = this->iPosition + 16;
				int pEquationRightCapture = this->iPosition + 7;
				int pEquationLeftCapture = this->iPosition + 9;


				if (iMoveTo == pEquationUp)
				{
					CheckBoard[pEquationUp] = 'x';
					bMoveValid = true;
				}
				else if (iMoveTo == pEquationDouble && this->iMoves == 0)
				{
					CheckBoard[pEquationDouble] = 'x';
					bMoveValid = true;
				}
				else if (iMoveTo == pEquationRightCapture)
				{
					CheckBoard[pEquationRightCapture] = 'x';
					bMoveValid = true;
				}
				else if (iMoveTo == pEquationLeftCapture)
				{
					CheckBoard[pEquationLeftCapture] = 'x';
					bMoveValid = true;
				}
				else
				{
					bMoveValid = false;
				}
			}
			return false;
}	//	End CheckIfCheck




bool SetPosition()
	{
		bool bMoveValid = false;
		bool bMoveToWhite = false;
		bool bCapturePiece = false;

		std::string sMoveToPiece = sBoard[iMoveTo];
		std::cerr << "sMoveToPiece: \"" << sMoveToPiece << "\"" << std::endl;

		if (sMoveToPiece != " ")
		{
			dHistory.push_back("INFO: bCapturePiece: TRUE");
			bCapturePiece = true;

			if (sMoveToPiece.at(0) == 'w')
			{
				dHistory.push_back("INFO: bMoveToWhite: TRUE");
				std::cout << "bMoveToWhite is true" << std::endl;
				bMoveToWhite = true;
			}
			else if (sMoveToPiece.at(0) == 'b')
			{
				dHistory.push_back("INFO: bCapturePiece: FALSE");
				std::cout << "bMoveToWhite is false" << std::endl;
				bMoveToWhite = false;
			}
			else
			{
				dHistory.push_back("CRITICAL: sMoveToPiece function failed due to input \"" + sMoveToPiece + "\".");
				std::cerr << "Something went wrong" << std::endl;
				return false;
			}
		}
		else
		{
			dHistory.push_back("INFO: bCapturePiece: FALSE");
			std::cout << "bCapturePiece is false" << std::endl;
			bCapturePiece = false;
		}

		if (iMoveTo > iBoardSize)
		{
			dHistory.push_back("ERR: Move was outside of board boundaries");
			bMoveValid = false;
		}
		else if (this->bWhitePiece != CurrentColorIsWhite)
		{
			dHistory.push_back("ERR: It's not that color's turn!");
			std::cerr << "It's not that color's turn!" << std::endl;
			return false;
		}
		else if (bCapturePiece == true)
		{
			if (this->bWhitePiece == bMoveToWhite)
			{
				dHistory.push_back("ERR: You can't capture your own piece!");
				std::cerr << "You can't capture your own piece!" << std::endl;
				return false;
			}
		}

		//		      A  B  C  D  E  F  G  H   
		//		    _________________________
		//		 1 |  0  1  2  3  4  5  6  7
		//		 2 |  8  9 10 11 12 13 14 15
		//		 3 | 16 17 18 19 20 21 22 23
		//		 4 | 24 25 26 27 28 29 30 31
		//		 5 | 32 33 34 35 36 37 38 39
		//		 6 | 40 41 42 43 44 45 46 47
		//		 7 | 48 49 50 51 52 53 54 55
		//		 8 | 56 57 58 59 60 61 62 63

		if (this->iType == 0)	//	King move logic
		{
			bool bKingInCheck = true;

			int pEquationDown = this->iPosition + 8;
			int pEquationUp = this->iPosition - 8;

			int pEquationLeft = this->iPosition + 1;
			int pEquationRight = this->iPosition - 1;

			int pEquationUpLeft = this->iPosition - 9;
			int pEquationUpRight = this->iPosition - 7;

			int pEquationDownLeft = iMoveTo == this->iPosition + 7;
			int pEquationDownRight = iMoveTo == this->iPosition + 9;

			if (iMoveTo == pEquationDown)	//	move down
			{
				dHistory.push_back("INFO: King moved down");
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationUp)	//	move up
			{
				dHistory.push_back("INFO: KING moved UP");
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationLeft)
			{
				dHistory.push_back("INFO: KING moved LEFT");
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationRight)
			{
				dHistory.push_back("INFO: KING moved RIGHT");
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationUpLeft)
			{
				dHistory.push_back("INFO: KING moved UP LEFT");
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationUpRight)
			{
				dHistory.push_back("INFO: KING moved UP RIGHT");
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationDownLeft)
			{
				dHistory.push_back("INFO: KING moved DOWN LEFT");
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationDownRight)
			{
				dHistory.push_back("INFO: KING moved DOWN RIGHT");
				bMoveValid = true;
			}
			else
			{
				dHistory.push_back("INFO: KING move didn't match the equations.");
				bMoveValid = false;
			}
		}
		else if (this->iType == 1)	//	Queen move logic
		{
			int iThroughPiece = 0;
			int iLoopNum = 0;
			bool bThroughCalc = false;

			for (int i = 1; i < iBoardWidth; i++)
			{
				int pEquationDown = this->iPosition + (i * 8);
				int pEquationUp = this->iPosition + -(i * 8);

				int pEquationLeft = this->iPosition + -(i);
				int pEquationRight = this->iPosition + (i);

				int pEquationUpLeft = this->iPosition + -(i * 9);
				int pEquationUpRight = this->iPosition + -(i * 7);

				int pEquationDownLeft = this->iPosition + (i * 7);
				int pEquationDownRight = this->iPosition + (i * 9);

				if (iMoveTo == pEquationDown)		//	move down
				{
					dHistory.push_back("INFO: QUEEN moved DOWN");
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						int pEquationDown = this->iPosition + (i * 8);
						if (sBoard[pEquationDown] == " ")
						{
							iThroughPiece++;
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationUp)	//	move up
				{
					dHistory.push_back("INFO: QUEEN moved UP");
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						int pEquationUp = this->iPosition + -(i * 8);
						if (sBoard[pEquationUp] == " ")
						{
							iThroughPiece++;
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationLeft)	//	move left
				{
					dHistory.push_back("INFO: QUEEN moved LEFT");
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						int pEquationLeft = this->iPosition + -(i);
						if (sBoard[pEquationLeft] == " ")
						{
							iThroughPiece++;
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationRight)	//	move right
				{
					dHistory.push_back("INFO: QUEEN moved RIGHT");
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						int pEquationRight = this->iPosition + (i);
						if (sBoard[pEquationRight] == " ")
						{
							iThroughPiece++;
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationUpLeft)	//	move up left
				{
					dHistory.push_back("INFO: QUEEN moved UP LEFT");
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						int pEquationUpLeft = this->iPosition + -(i * 9);
						if (sBoard[pEquationUpLeft] == " ")
						{
							iThroughPiece++;
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationUpRight)	//	move up right
				{
					dHistory.push_back("INFO: QUEEN moved UP RIGHT");
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						int pEquationUpRight = this->iPosition + -(i * 7);
						if (sBoard[pEquationUpRight] == " ")
						{
							iThroughPiece++;
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationDownLeft)	//	move down left
				{
					dHistory.push_back("INFO: QUEEN moved DOWN LEFT");
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						int pEquationDownLeft = this->iPosition + (i * 7);
						if (sBoard[pEquationDownLeft] == " ")
						{
							iThroughPiece++;
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationDownRight)	//	move down right
				{
					dHistory.push_back("INFO: QUEEN moved DOWN RIGHT");
					iLoopNum = i;
					bThroughCalc = false;
					for (int i = 1; i < iLoopNum; i++)
					{
						int pEquationDownRight = this->iPosition + (i * 9);
						if (sBoard[pEquationDownRight] == " ")
						{
							iThroughPiece++;
						}
					}
					bThroughCalc = true;
				}
				else
				{
					dHistory.push_back("ERR: QUEEN move attempt failed x " + std::to_string(i));
					bMoveValid = false;
				}

				if (bThroughCalc == true)
				{
					break;
				}
			}

			if (bThroughCalc == true)
			{
				if (iThroughPiece == iLoopNum - 1)
				{
					bMoveValid = true;
				}
				else
				{
					std::cerr << "The Queen cannot travel through pieces! iThroughPiece: " << iThroughPiece << "\tiLoopNum: " << iLoopNum - 1 << std::endl;
					dHistory.push_back("ERR: QUEEN cannot move through pieces! Attempted: " + std::to_string(iLoopNum) + " out of: " + std::to_string(iThroughPiece) + " tiles.");
					bMoveValid = false;
				}
			}
			else
			{
				dHistory.push_back("INFO: QUEEN move didn't match the equations.");
				bMoveValid = false;
			}

		}	//	END QUEEN logic
		else if (this->iType == 2)	//	Rook move logic
		{
			int iThroughPiece = 0;
			int iLoopNum = 0;
			bool bThroughCalc = false;

			for (int i = 1; i < iBoardWidth; i++)
			{
				int pEquationDown = this->iPosition + (i * 8);
				int pEquationUp = this->iPosition + -(i * 8);

				int pEquationLeft = this->iPosition + -(i);
				int pEquationRight = this->iPosition + (i);

				if (iMoveTo == pEquationDown)		//	move down
				{
					dHistory.push_back("INFO: ROOK moved DOWN");
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						int pEquationDown = this->iPosition + (i * 8);
						if (sBoard[pEquationDown] == " ")
						{
							iThroughPiece++;
						}
					}

				}
				else if (iMoveTo == pEquationUp)	//	move up
				{
					dHistory.push_back("INFO: ROOK moved UP");
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						int pEquationUp = this->iPosition + -(i * 8);
						if (sBoard[pEquationUp] == " ")
						{
							iThroughPiece++;
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationLeft)	//	move left
				{
					dHistory.push_back("INFO: ROOK moved LEFT");
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						int pEquationLeft = this->iPosition + -(i);
						if (sBoard[pEquationLeft] == " ")
						{
							iThroughPiece++;
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationRight)	//	move right
				{
					dHistory.push_back("INFO: ROOK moved RIGHT");
					iLoopNum = i;
					int pEquationRight = this->iPosition + (i);
					for (int i = 1; i < iLoopNum; i++)
					{
						if (sBoard[pEquationRight] == " ")
						{
							iThroughPiece++;
						}
					}
					bThroughCalc = true;
				}
				else
				{
					dHistory.push_back("INFO: ROOK move didn't match the equations");
					std::cerr << "Invalid Rook Move!" << i << std::endl;
					bMoveValid = false;
				}

			}

			if (bThroughCalc == true)
			{
				if (iThroughPiece == iLoopNum - 1)
				{
					bMoveValid = true;
				}
				else
				{
					dHistory.push_back("ERR: ROOK cannot move through pieces! Attempted: " + std::to_string(iLoopNum) + " out of: " + std::to_string(iThroughPiece) + " tiles.");
					std::cerr << "The Rook cannot travel through pieces! iThroughPiece: " << iThroughPiece << "\tiLoopNum: " << iLoopNum - 1 << std::endl;
					bMoveValid = false;
				}
			}
			else
			{
				bMoveValid = false;
			}
		}
		else if (this->iType == 3)	//	Bishop move logic
		{

			int iThroughPiece = 0;
			int iLoopNum = 0;
			bool bThroughCalc = false;

			for (int i = 1; i < iBoardWidth; i++)
			{

				int pEquationUpLeft = this->iPosition + -(i * 9);
				int pEquationUpRight = this->iPosition + -(i * 7);

				int pEquationDownLeft = iMoveTo == this->iPosition + (i * 7);
				int pEquationDownRight = iMoveTo == this->iPosition + (i * 9);

				if (iMoveTo == pEquationUpLeft)	//	move up left
				{
					dHistory.push_back("INFO: BISHOP moved UP LEFT");
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						int pEquationUpLeft = this->iPosition + -(i * 9);
						if (sBoard[pEquationUpLeft] == "")
						{
							iThroughPiece++;
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationUpRight)	//	move up right
				{
					dHistory.push_back("INFO: BISHOP moved UP RIGHT");
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						int pEquationUpRight = this->iPosition + -(i * 7);
						if (sBoard[pEquationUpRight] == "")
						{
							iThroughPiece++;
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationDownLeft)	//	move down left
				{
					dHistory.push_back("INFO: BISHOP moved DOWN LEFT");
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						int pEquationDownLeft = iMoveTo == this->iPosition + (i * 7);
						if (sBoard[pEquationDownLeft] == "")
						{
							iThroughPiece++;
						}
					}
					bThroughCalc = true;
				}
				else if (iMoveTo == pEquationDownRight)	//	move down right
				{
					dHistory.push_back("INFO: BISHOP moved DOWN RIGHT");
					iLoopNum = i;
					bThroughCalc = false;
					for (int i = 1; i < iLoopNum; i++)
					{
						int pEquationDownRight = iMoveTo == this->iPosition + (i * 9);
						if (sBoard[pEquationDownRight] == "")
						{
							iThroughPiece++;
						}
					}
					bThroughCalc = true;
				}
				else
				{
					std::cerr << "Invalid Bishop move!" << std::endl;
					bMoveValid = false;
				}
			}

			if (bThroughCalc == true)
			{
				if (iThroughPiece == iLoopNum - 1)
				{
					bMoveValid = true;
				}
				else
				{
					dHistory.push_back("ERR: BISHOP cannot move through pieces! Attempted: " + std::to_string(iLoopNum) + " out of: " + std::to_string(iThroughPiece) + " tiles.");
					std::cerr << "The Bishop cannot travel through pieces! iThroughPiece: " << iThroughPiece << "\tiLoopNum: " << iLoopNum - 1 << std::endl;
					bMoveValid = false;
				}
			}
			else
			{
				bMoveValid = false;
			}

		}	//	END BISHOP logic
		else if (this->iType == 4)	//	Knight move logic
		{
			int pEquationDownLeft = this->iPosition + 15;	//	Down
			int pEquationDownRight = this->iPosition + 17;

			int pEquationUpLeft = this->iPosition - 17;		// Up
			int pEquationUpRight = this->iPosition - 15;

			int pEquationLeftDown = this->iPosition + 10;	//	left / right down
			int pEquationRightDown = this->iPosition + 6;

			int pEquationLeftUp = this->iPosition - 10;		// left / right up
			int pEquationRightUp = this->iPosition - 6;

			if (iMoveTo == pEquationDownLeft)
			{
				dHistory.push_back("INFO: KNIGHT moved DOWN LEFT");
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationDownRight)
			{
				dHistory.push_back("INFO: KNIGHT moved DOWN RIGHT");
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationUpLeft)
			{
				dHistory.push_back("INFO: KNIGHT moved UP LEFT");
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationUpRight)
			{
				dHistory.push_back("INFO: KNIGHT moved UP RIGHT");
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationLeftDown)
			{
				dHistory.push_back("INFO: KNIGHT moved LEFT DOWN");
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationRightDown)
			{
				dHistory.push_back("INFO: KNIGHT moved RIGHT DOWN");
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationLeftUp)
			{
				dHistory.push_back("INFO: KNIGHT moved LEFT UP");
				bMoveValid = true;
			}
			else if (iMoveTo == pEquationRightUp)
			{
				dHistory.push_back("INFO: KNIGHT moved RIGHT UP");
				bMoveValid = true;
			}
			else
			{
				dHistory.push_back("INFO: Invalid KNIGHT move.");
				std::cerr << "Invalid Knight move!" << std::endl;
				bMoveValid = false;
			}

		}	//	END KNIGHT logic
		else if (this->iType == 5)	//	Pawn move logic
		{
			if (this->bWhitePiece == true)
			{
				int pEquationUp = this->iPosition - 8;
				int pEquationDouble = this->iPosition - 16;
				int pEquationRightCapture = this->iPosition - 7;
				int pEquationLeftCapture = this->iPosition - 9;


				if (iMoveTo == pEquationUp)
				{
					dHistory.push_back("INFO: PAWN moved UP");
					bMoveValid = true;
				}
				else if (iMoveTo == pEquationDouble && this->iMoves == 0)
				{
					dHistory.push_back("INFO: PAWN moved UP DOUBLE");
					bMoveValid = true;
				}
				else if (iMoveTo == pEquationRightCapture)
				{
					dHistory.push_back("INFO: PAWN captured RIGHT");
					bMoveValid = true;
				}
				else if (iMoveTo == pEquationLeftCapture)
				{
					dHistory.push_back("INFO: PAWN captured LEFT");
					bMoveValid = true;
				}
				else
				{
					dHistory.push_back("INFO: PAWN move didn't match the equations.");
					bMoveValid = false;
				}
			}
			else
			{
				int pEquationUp = this->iPosition + 8;
				int pEquationDouble = this->iPosition + 16;
				int pEquationRightCapture = this->iPosition + 7;
				int pEquationLeftCapture = this->iPosition + 9;

				if (iMoveTo == pEquationUp)
				{
					dHistory.push_back("INFO: PAWN moved DOWN");
					bMoveValid = true;
				}
				else if (iMoveTo == pEquationDouble && this->iMoves == 0)
				{
					dHistory.push_back("INFO: PAWN moved DOWN DOUBLE");
					bMoveValid = true;
				}
				else if (iMoveTo == pEquationRightCapture)
				{
					dHistory.push_back("INFO: PAWN captured RIGHT");
					bMoveValid = true;
				}
				else if (iMoveTo == pEquationLeftCapture)
				{
					dHistory.push_back("INFO: PAWN captured LEFT");
					bMoveValid = true;
				}
				else
				{
					dHistory.push_back("INFO: PAWN move didn't match the equations.");
					bMoveValid = false;
				}
			}
		}

		if (bMoveValid == true)
		{
			
			bool CheckKingCheck = true;
			
			std::cout << "Checking if king is in check..." << std::endl;
			CheckKingCheck = bIsKingInCheck();
			dHistory.push_back("King is in check: " + std::to_string(CheckKingCheck));
			std::cout << CheckKingCheck << std::endl;

			if (this->iType != 0 || ( this->iType == 0 && CheckKingCheck == false ) )
			{
				if (bCapturePiece == true)
				{
					mHistory.push_back(sBoard[iMoveFrom] + " from " + std::to_string(iMoveFrom) + " captured " + sBoard[iMoveTo] + " at " + std::to_string(iMoveTo));
					dHistory.push_back("INFO: " + sBoard[iMoveFrom] + " from " + std::to_string(iMoveFrom) + " captured " + sBoard[iMoveTo] + " at " + std::to_string(iMoveTo));
					//std::cout << sBoard[iMoveTo] + " from " + std::to_string(iMoveFrom) + " captured " + sBoard[iMoveTo] + " at " + std::to_string(iMoveTo) << std::endl;

				}
				else
				{
					mHistory.push_back(sBoard[iMoveFrom] + " moved from " + std::to_string(iMoveFrom) + " to " + std::to_string(iMoveTo));
					dHistory.push_back("INFO: "+ sBoard[iMoveFrom] + " moved from " + std::to_string(iMoveFrom) + " to " + std::to_string(iMoveTo));
					//std::cout << sBoard[iMoveTo] + " moved from " + std::to_string(iMoveFrom) + " to " + std::to_string(iMoveTo) << std::endl;
					sCaptured.push_back(sBoard[iMoveTo]);
				}

				if (sBoard[iMoveFrom] == "wKing")
				{
					iWhiteKingLocation = iMoveTo;
					dHistory.push_back("White King Location: " + std::to_string(iWhiteKingLocation));
				}
				else if (sBoard[iMoveFrom] == "bKing")
				{
					iBlackKingLocation = iMoveTo;
					dHistory.push_back("Black King Location: " + std::to_string(iBlackKingLocation));
				}

				this->iMoves++;
				this->iPosition = iMoveTo;

				iBoard[this->iPosition] = this->cVisual;
				iBoard[iMoveFrom] = ' ';

				sBoard[iMoveTo] = sBoard[iMoveFrom];
				sBoard[iMoveFrom] = ' ';
				return true;
			}
			else
			{
				dHistory.push_back("ERR: You can't move your king into check!");
				std::cerr << "You can't move your king into check!" << std::endl;
				return false;
			}
		}
		else
		{
			return false;
		}

	}
	void SetPiece(int iType, bool bWhitePiece, int iPieceNum)
	{
		if (iType == 0)	//	for KING pieces
		{
			this->iType = 0;
			this->iValue = 0;
			this->bWhitePiece = bWhitePiece;


			if (bWhitePiece == true)
			{
				this->iPosition = 60;
				iBoard[this->iPosition] = 'K';
				this->cVisual = 'K';
				sBoard[this->iPosition] = "wKing";
			}
			else if (bWhitePiece == false)
			{
				this->iPosition = 4;
				iBoard[this->iPosition] = 'k';
				this->cVisual = 'k';
				sBoard[this->iPosition] = "bKing";
			}

		}
		else if (iType == 1)	//	for QUEEN pieces
		{
			this->iType = 1;
			this->iValue = 9;
			this->bWhitePiece = bWhitePiece;

			if (bWhitePiece == true)
			{
				this->iPosition = 59;
				iBoard[this->iPosition] = 'Q';
				this->cVisual = 'Q';
				sBoard[this->iPosition] = "wQueen";
			}
			else if (bWhitePiece == false)
			{
				this->iPosition = 3;
				iBoard[this->iPosition] = 'q';
				this->cVisual = 'q';
				sBoard[this->iPosition] = "bQueen";
			}
		}
		else if (iType == 2)	//	for ROOK pieces
		{
			this->iType = 2;
			this->iValue = 5;
			this->bWhitePiece = bWhitePiece;

			if (bWhitePiece == true)
			{
				this->iPosition = 56;
				if (iPieceNum == 2)
				{
					this->iPosition += 7;
				}
				iBoard[this->iPosition] = 'R';
				this->cVisual = 'R';
				sBoard[this->iPosition] = "wRook" + std::to_string(iPieceNum);
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
				sBoard[this->iPosition] = "bRook" + std::to_string(iPieceNum);
			}
		}
		else if (iType == 3)	//	for BISHOP pieces
		{
			this->iType = 3;
			this->iValue = 3;
			this->bWhitePiece = bWhitePiece;

			if (bWhitePiece == true)
			{
				this->iPosition = 58;
				if (iPieceNum == 2)
				{
					this->iPosition += 3;
				}
				iBoard[this->iPosition] = 'B';
				this->cVisual = 'B';
				sBoard[this->iPosition] = "wBishop" + std::to_string(iPieceNum);
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
				sBoard[this->iPosition] = "bBishop" + std::to_string(iPieceNum);
			}

		}
		else if (iType == 4)	//	for KNIGHT pieces
		{
			this->iType = 4;
			this->iValue = 3;
			this->bWhitePiece = bWhitePiece;

			if (bWhitePiece == true)
			{
				this->iPosition = 57;
				if (iPieceNum == 2)
				{
					this->iPosition += 5;
				}
				iBoard[this->iPosition] = 'N';
				this->cVisual = 'N';
				sBoard[this->iPosition] = "wKnight" + std::to_string(iPieceNum);
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
				sBoard[this->iPosition] = "bKnight" + std::to_string(iPieceNum);
			}
		}
		else if (iType == 5)	//	for PAWN pieces
		{
			this->iType = 5;
			this->iValue = 1;
			this->bWhitePiece = bWhitePiece;

			if (bWhitePiece == true)
			{
				this->iPosition = 48;
				if (iPieceNum > 1)
				{
					this->iPosition += iPieceNum - 1;
				}
				iBoard[this->iPosition] = 'P';
				this->cVisual = 'P';
				sBoard[this->iPosition] = "wPawn" + std::to_string(iPieceNum);
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
				sBoard[this->iPosition] = "bPawn" + std::to_string(iPieceNum);
			}
		}
		else
		{
			std::cerr << "This piece could not be initalized. Please try again." << std::endl;
		}

	}

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

	//	Other Functions

};

Piece wKing;
Piece wQueen;

Piece wRook1;
Piece wRook2;

Piece wBishop1;
Piece wBishop2;

Piece wKnight1;
Piece wKnight2;

Piece wPawn1;
Piece wPawn2;
Piece wPawn3;
Piece wPawn4;
Piece wPawn5;
Piece wPawn6;
Piece wPawn7;
Piece wPawn8;

// Initalize Black Pieces
Piece bKing;
Piece bQueen;

Piece bRook1;
Piece bRook2;

Piece bBishop1;
Piece bBishop2;

Piece bKnight1;
Piece bKnight2;

Piece bPawn1;
Piece bPawn2;
Piece bPawn3;
Piece bPawn4;
Piece bPawn5;
Piece bPawn6;
Piece bPawn7;
Piece bPawn8;

void vGameInit()	//	INITALIZE Board and pieces
{
	for (int i = 0; i < iBoardSize; i++)
	{
		iBoard[i] = ' ';
	}
	for (int i = 0; i < iBoardSize; i++)
	{
		CheckBoard[i] = ' ';
	}
	for (int i = 0; i < iBoardSize; i++)
	{
		sBoard[i] = " ";
	}
	// Initalize White Pieces
	wKing.SetPiece(0, true, 0);
	wQueen.SetPiece(1, true, 0);

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

	return;
}

int main()
{
	bool game = true;
	bool bGameWin = false;

	char cUsrInput = '0';
	char gameMode = '0';


	while (game == true)
	{
		std::cout << "Weclome to DA Console Chess!" << std::endl;
		std::cout << "Would you like a \033[4mS\033[0mmall or \033[4mL\033[0marge game board?" << std::endl;
		cUsrInput = cInputValidation();
		if (cUsrInput == 'l')
		{
			boardType = 'l';
			dHistory.push_back("INFO: boardType: 'l'");
		}
		else if (cUsrInput == 's')
		{
			boardType = 's';
			dHistory.push_back("INFO: boardType: 's'");
		}

		vGameInit();
		dHistory.push_back("Game Initalized");

		std::cout << "Would you like \033[4ms\033[0mingle or \033[4mm\033[0multiplayer?" << std::endl;
		cUsrInput = cInputValidation();
		if (cUsrInput == 's' || cUsrInput == 'S' || cUsrInput == '1')
		{
			gameMode = 's';
			dHistory.push_back("INFO: gameMode: 's'");
		}
		else if (cUsrInput == 'm' || cUsrInput == 'M' || cUsrInput == '2')
		{
			gameMode = 'm';
			dHistory.push_back("INFO: gameMode: 'm'");
		}
		//	input for single/multiplayer

		if (gameMode == 's')	//	SINGLE PLAYER
		{
			bGameWin = bSinglePlayer();
		}
		if (gameMode == 'm')	//	MULTI PLAYER
		{
			bGameWin = bMultiPlayer();
		}
		else
		{
			dHistory.push_back("ERR: That gamemode doesn't exist");
			return 1;
		}
		system("pause");

	}	//	END of GAME LOOP

	return 0;

}	//	END OF MAIN



char cInputValidation()
{
	char choice = '0';
	std::cin >> std::setw(1) >> choice;


	while (!std::cin.good())	// error check
	{
		std::cout << "Invalid Input! Try again." << std::endl;

		//	clear stream
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');

		std::cout << "Enter your choice again." << std::endl;
		std::cin >> std::setw(1) >> choice;

	}
	//clear stream
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');

	return choice;
}

bool bSinglePlayer()		//	--------------------------	SINGLE PLAYER GAME	-------------------------------------------------------
{
	bGameStatus = true;
	int GameStatusLoop = 0;
	while (bGameStatus == true)
	{
		dHistory.push_back("-------------------------------------------------------------");
		dHistory.push_back("bGameStatus loop: " + std::to_string(GameStatusLoop));
		printBoard();
		std::cout << "\n\tWhat is your move?\n\t\t";
		vUsrInput();
		GameStatusLoop++;
	}
	dHistory.push_back("Game Ended on loop " + std::to_string(GameStatusLoop));
	return 0;
}	//	END OF bSinglePlayer

bool bMultiPlayer()			//	--------------------------	MULTI PLAYER GAME	-------------------------------------------------------
{
	bGameStatus = true;
	int GameStatusLoop = 0;
	while (bGameStatus == true)
	{
		dHistory.push_back("-------------------------------------------------------------");
		dHistory.push_back("bGameStatus loop: " + std::to_string(GameStatusLoop));
		printBoard();
		std::cout << "\n\tWhat is your move?\n\t\t";
		vUsrInput();
		GameStatusLoop++;
	}
	dHistory.push_back("Game Ended on loop " + std::to_string(GameStatusLoop));
	return 0;
}	//	END OF bMultiPlayer




void vUsrInput()
{

	std::string cOne;
	std::string cTwo;
	std::string cThree;
	std::string input;
	int iEndInput = 0;

	std::getline(std::cin, input);
	dHistory.push_back("User input is: \"" + input + "\"");
	size_t lastPhrase = (input.find_last_of(' '));
	size_t nLastPhrase = (input.find_last_of(' '));

	if (!input.empty())
	{
		if (lastPhrase > input.size())
		{
			cThree = input;
			iEndInput = 1;
			input.erase();
		}
		else
		{
			cThree = input.substr(lastPhrase + 1, input.size());

			while (nLastPhrase == lastPhrase)
			{
				input.pop_back();
				nLastPhrase = (input.find_last_of(' '));
			}
		}
	}
	else
	{
		std::cerr << "You didn't type anything..." << std::endl;
	}

	if (!input.empty())
	{
		lastPhrase = (input.find_last_of(' '));


		if (lastPhrase > input.size())
		{
			cTwo = input;
			iEndInput = 2;
			input.erase();
		}
		else
		{
			cTwo = input.substr(lastPhrase + 1, input.size());

			while (nLastPhrase == lastPhrase)
			{
				input.pop_back();
				nLastPhrase = (input.find_last_of(' '));
			}
		}
	}
	else
	{

		cOne = cThree;
		cTwo = "";
		cThree = "";

	}

	if (!input.empty())
	{
		lastPhrase = (input.find_last_of(' '));


		if (lastPhrase > input.size())
		{
			cOne = input;
			input.erase();
		}
		else
		{
			cOne = input;

			while (nLastPhrase == lastPhrase)
			{
				input.pop_back();
				nLastPhrase = (input.find_last_of(' '));
			}

		}
	}
	else
	{
		if (iEndInput != 1)
		{
			cOne = cTwo;
			cTwo = cThree;
			cThree = "";
		}
	}

	dHistory.push_back("INFO: cOne: \"" + cOne + "\"\tcTwo: \"" + cTwo + "\"\tcThree: \"" + cThree + "\".");

	if (cOne == "exit" || cOne == "Exit" || cOne == "EXIT")
	{
		std::cout << "Are you sure you want to quit?" << std::endl;
		char input = cInputValidation();
		if (input == 'n' || input == 'N')
		{
			return;
		}
		else
		{
			std::cout << "Thanks for playing!" << std::endl;
			bGameStatus = false;
			return;
		}

	}
	else if (cOne == "help" || cOne == "Help" || cOne == "HELP")
	{
		if (cTwo == "")
		{
			dHistory.push_back("command HELP issued.");
			std::cout << "\n\n\t\tFull list of commands:" << std::endl;
			std::cout << "\t    the ' character indicates a variable input, like A5 or a command" << std::endl;
			std::cout << "\tcheckmate\t\tChecks for checkmate, and ends the match" << std::endl;
			std::cout << "\tdebug\t\tControls the debug output levels" << std::endl;
			std::cout << "\texit\t\tExit's to the main menu, and loses all game progress" << std::endl;
			std::cout << "\thelp 'command'\tLists all commands, and provides context for commmands" << std::endl;
			std::cout << "\thistory\t\tPrints full game history to screen" << std::endl;
			std::cout << "\tmove 'from' to'\tMoves the 'from' piece to the 'to' location. Example: move A7 A5." << std::endl;
			std::cout << "\tmcheck 'from'\tMove Check - Shows the valid moves of the 'from' piece" << std::endl;
			std::cout << "\trematch\t\tEnds the current match and starts a new one." << std::endl;
			std::cout << "\what\t\t(debug) Says name of piece at current location on all boards" << std::endl;
		}
		else if (cTwo == "checkmate" || cTwo == "Checkmate" || cTwo == "CheckMate" || cTwo == "CHECKMATE")
		{
			dHistory.push_back("command HELP CHECKMATE issued.");
			std::cout << "\n\n\t\t'checkmate' Command help:" << std::endl;
			std::cout << "\tThe 'checkmate' command is used to check for checkmate, and end the current match." << std::endl;
			std::cout << "\tThe syntax for the checkmate command is as follows:" << std::endl;
			std::cout << "\t\tcheckmate" << std::endl;
			std::cout << "\tI believe in you." << std::endl;
		}
		else if (cTwo == "debug" || cTwo == "Debug" || cTwo == "DEBUG")
		{
			dHistory.push_back("command HELP DEBUG issued.");
			std::cout << "\n\n\t\t'debug' Command help:" << std::endl;
			std::cout << "\tThe 'debug' command is used to change the debug output levels" << std::endl;
			std::cout << "\tThe syntax for the checkmate command is as follows:" << std::endl;
			std::cout << "\t\tdebug level (default is 0)" << std::endl;
			std::cout << "\t\tdebug  0" << std::endl;
			std::cout << "\tDebug level 0 will output nothing." << std::endl;
			std::cout << "\tDebug level 1 will output to the command line." << std::endl;
			std::cout << "\tDebug level 2 will output to a file." << std::endl;
			std::cout << "\tDebug level 3 will output to both" << std::endl;

			std::cout << "\tTHIS HASN'T BEEN IMPLEMENTED YET" << std::endl;

		}
		else if (cTwo == "exit" || cTwo == "Exit" || cTwo == "EXIT")
		{
			dHistory.push_back("command HELP EXIT issued.");
			std::cout << "\n\n\t\t'exit' Command help:" << std::endl;
			std::cout << "\tThe 'exit' command is used to return to the main menu, and end the current match." << std::endl;
			std::cout << "\tThe syntax for the exit command is as follows:" << std::endl;
			std::cout << "\t\texit" << std::endl;
			std::cout << "\tI believe in you." << std::endl;
		}
		else if (cTwo == "history" || cTwo == "History" || cTwo == "HISTORY")
		{
			dHistory.push_back("command HELP HISTORY issued.");
			std::cout << "\n\n\t\t'history' Command help:" << std::endl;
			std::cout << "\tThe 'history' command is used to display all events of the current match" << std::endl;
			std::cout << "\tThe syntax for the move command is as follows:" << std::endl;
			std::cout << "\t\thistory option" << std::endl;
			std::cout << "\t\thistory debug" << std::endl;
			std::cout << "\t\thistory save" << std::endl;
			std::cout << "\t\tSpecial Uses:" << std::endl;
			std::cout << "\t'Save to Files'" << std::endl;
			std::cout << "\t in the future I'll write what is supposed to be here." << std::endl;
		}
		else if (cTwo == "move" || cTwo == "Move" || cTwo == "MOVE")
		{
			dHistory.push_back("command HELP MOVE issued.");
			std::cout << "\n\n\t\t'move' Command help:" << std::endl;
			std::cout << "\tThe 'move' command is used to move any piece from one location to another" << std::endl;
			std::cout << "\tThe syntax for the move command is as follows:" << std::endl;
			std::cout << "\t\tmove 'from'\t'to'" << std::endl;
			std::cout << "\t\tmove   A7 \tA5" << std::endl;
			std::cout << "\tThis moves the piece at location 'A7' to the 'A5'" << std::endl;
			std::cout << "\tThis command has input validation, and will ensure your move is legal." << std::endl;
			std::cout << "\t\tSpecial Uses:" << std::endl;
			std::cout << "\t'castling'" << std::endl;
			std::cout << "\t\tAliases: mov, mv" << std::endl;
			std::cout << "\t in the future I'll write what is supposed to be here." << std::endl;
		}
		else if (cTwo == "mcheck" || cTwo == "Mcheck" || cTwo == "mCheck" || cTwo == "MCHECK")
		{
			dHistory.push_back("command HELP MCHECK issued.");
			std::cout << "\n\n\t\t'mcheck' Command help:" << std::endl;
			std::cout << "\tThe 'mcheck' or 'Move Check' command is used to check the available moves for the selected piece." << std::endl;
			std::cout << "\tThe syntax for the mcheck command is as follows:" << std::endl;
			std::cout << "\t\tmcheck 'from'" << std::endl;
			std::cout << "\t\tmcheck   A7" << std::endl;
			std::cout << "\tThis will show you all of the available moves for the piece located at A7." << std::endl;
			std::cout << "\t\tSpecial Uses:" << std::endl;
			std::cout << "\tGetting a fresh view of the board" << std::endl;
		}
		else if (cTwo == "rematch" || cTwo == "Rematch" || cTwo == "reMatch" || cTwo == "REMATCH")
		{
			dHistory.push_back("command HELP REMATCH issued.");
			std::cout << "\n\n\t\t'rematch' Command help:" << std::endl;
			std::cout << "\tThe 'rematch' command is used to end the current game, and start a new one." << std::endl;
			std::cout << "\tThe syntax for the rematch command is as follows:" << std::endl;
			std::cout << "\t\trematch" << std::endl;
			std::cout << "\tI Believe in you." << std::endl;
		}
		else if (cTwo == "what" || cTwo == "What" || cTwo == "WHAT")
		{
			dHistory.push_back("command HELP WHAT issued.");
			std::cout << "\n\n\t\t'what' Command help:" << std::endl;
			std::cout << "\tThe 'what' command is a debug command to show what values are at specific locations on the board" << std::endl;
			std::cout << "\tThe syntax for the what command is as follows:" << std::endl;
			std::cout << "\t\what location" << std::endl;
			std::cout << "\t\what    c0" << std::endl;
			std::cout << "\tThat's it." << std::endl;
		}
		else
		{
		dHistory.push_back("command HELP cTwo was not found.");
			std::cout << "\n\t\tYour command wasn't found..." << std::endl;
			std::cout << "\t\tTry running just 'help' if you keep having issues" << std::endl;
		}



		std::cout << "\nPress any key to continue..." << std::endl;
		std::cin.get();
		std::cin.clear();
		return;
	}
	else if (cOne == "debug" || cOne == "Debug" || cOne == "DEBUG")
	{
		dHistory.push_back("command DEBUG issued.");
		std::cout << "This command hasn't been implemented yet" << std::endl;
	}
	else if (cOne == "checkmate")
	{
	dHistory.push_back("command CHECKMATE issued.");
		//	the stuff for checkmate should go here
		std::cout << "This command hasn't been implemented yet" << std::endl;
		return;
	}
	else if (cOne == "history" || cOne == "History" || cOne == "HISTORY" || cOne == "hist" || cOne == "h")
	{
		if (cTwo == "")
		{
			
			if (mHistory.size() != 0)
			{
				for (long unsigned int i = 0; i < mHistory.size(); i++)
				{
					std::cout << "\t" << i + 1 << ".\t" << mHistory.at(i) << std::endl;
				}
				dHistory.push_back("command HISTORY issued successfully.");
			}
			else
			{
				dHistory.push_back("ERR: No move history to display!");
				std::cout << "There's no move history to display!" << std::endl;
			}
		}
		else if (cTwo == "save" || cTwo == "Save" || cTwo == "SAVE" || cTwo == "s" || cTwo == "S")
		{
			dHistory.push_back("command HISTORY SAVE issued.");
			std::cout << "This hasn't been implemented yet but will soon!" << std::endl;
			//	-	-	-	-	-	-	-	-	-	location for saving move histroy to file.
		}
		else if (cTwo == "clear" || cTwo == "Clear" || cTwo == "CLEAR" || cTwo == "c" || cTwo == "C")
		{
			if (mHistory.size() != 0)
			{
				dHistory.push_back("command HISTORY CLEAR issued.");
				for (long unsigned int j = (mHistory.size()); j > 0; j--)
				{
					mHistory.pop_back();
				}
			}
			else
			{
				std::cout << "You can't clear zero history!" << std::endl;
				dHistory.push_back("ERR: No move history to clear!");
			}
		}
		else if (cTwo == "debug" || cTwo == "Debug" || cTwo == "DEBUG")
		{
			if (cThree == "save" || cThree == "Save" || cThree == "SAVE" || cThree == "s" || cThree == "S")
			{
				std::cout << "To enable saving debug history to a file, use the command 'debug 2' or 'help debug'" << std::endl;
			}
			else if (cThree == "clear" || cThree == "Clear" || cThree == "CLEAR" || cThree == "c" || cThree == "C")
			{
				if (dHistory.size() != 0)
				{
					dHistory.push_back("command HISTORY DEBUG CLEAR issued.");
					for (long unsigned int j = (dHistory.size()); j > 0; j--)
					{
						dHistory.pop_back();
					}
					dHistory.push_back("command HISTORY DEBUG CLEAR issued sucessfully.");
				}
				else
				{
					std::cout << "You can't clear zero history!" << std::endl;
					dHistory.push_back("ERR: No debug history to clear!");
				}
			}
			else
			{
				dHistory.push_back("command HISTORY DEBUG issued.");
				for (long unsigned int i = 0; i < dHistory.size(); i++)
				{
					std::cout << "\t" << i + 1 << ".\t" << dHistory.at(i) << std::endl;
				}
			}
		}
		std::cout << "\nPress any key to continue..." << std::endl;
		std::cin.get();
		std::cin.clear();
		return;
	}
	else if (cOne == "mcheck")
	{
		//	the stuff for mcheck should go here
		dHistory.push_back("command MCHECK issued.");
		std::cout << "This command hasn't been implemented yet" << std::endl;
		return;
	}
	else if (cOne == "rematch")
	{
		dHistory.push_back("command REMATCH issued.");
		bGameStatus = false;
		return;
	}
	else if (cOne == "move" || cOne == "Move" || cOne == "MOVE" || cOne == "mov" || cOne == "mv")
	{
	dHistory.push_back("command MOVE issued.");
		int iMovefWidth = 0;
		int iMovefHeight = 0;
		int iMovetWidth = 0;
		int iMovetHeight = 0;
		int iAtIndex = 0;

		if (cTwo.size() != 2 || cThree.size() != 2)
		{
			dHistory.push_back("ERR: Invalid move location " + cTwo + " to " + cThree + ".");
			std::cerr << "Please enter a valid location" << std::endl;
			return;
		}

		for (int i = 0; i < 2; i++)
		{
			char cCompare = cTwo.at(i);
			if (cCompare == 'A' || cCompare == 'a')			//	convert FROM to integer
			{
				iAtIndex = i;
				iMovefWidth = 1;
			}
			else if (cCompare == 'B' || cCompare == 'b')
			{
				iAtIndex = i;
				iMovefWidth = 2;
			}
			else if (cCompare == 'C' || cCompare == 'c')
			{
				iAtIndex = i;
				iMovefWidth = 3;
			}
			else if (cCompare == 'D' || cCompare == 'd')
			{
				iAtIndex = i;
				iMovefWidth = 4;
			}
			else if (cCompare == 'E' || cCompare == 'e')
			{
				iAtIndex = i;
				iMovefWidth = 5;
			}
			else if (cCompare == 'F' || cCompare == 'f')
			{
				iAtIndex = i;
				iMovefWidth = 6;
			}
			else if (cCompare == 'G' || cCompare == 'g')
			{
				iAtIndex = i;
				iMovefWidth = 7;
			}
			else if (cCompare == 'H' || cCompare == 'h')
			{
				iAtIndex = i;
				iMovefWidth = 8;
			}
		}	//	end for loop

			//std::cerr << "Unknown Move location: " << cTwo << std::endl;
			//std::cout << iMovefWidth << std::endl;
			//std::cout << "Press any key to continue..." << std::endl;
			//std::cin.get();
			//std::cin.clear();
			//return;


		if (iAtIndex == 0)
		{
			iMovefHeight = cTwo.at(1) - '0';
		}
		else if (iAtIndex == 1)
		{
			iMovefHeight = cTwo.at(0) - '0';
		}

		iMoveFrom = ((iMovefWidth)+((iMovefHeight - 1) * iBoardHeight)) - 1;
		dHistory.push_back("INFO: iMoveFrom: " + std::to_string(iMoveFrom) + "from Width: " + std::to_string(iMovefWidth) + " and Height: " + std::to_string(iMovefHeight));

		for (int i = 0; i < 2; i++)		//	cThree
		{
			char cCompare = cThree.at(i);
			if (cCompare == 'A' || cCompare == 'a')		// Convert cThree location to Integer
			{
				iAtIndex = i;
				iMovetWidth = 1;
			}
			else if (cCompare == 'B' || cCompare == 'b')
			{
				iAtIndex = i;
				iMovetWidth = 2;
			}
			else if (cCompare == 'C' || cCompare == 'c')
			{
				iAtIndex = i;
				iMovetWidth = 3;
			}
			else if (cCompare == 'D' || cCompare == 'd')
			{
				iAtIndex = i;
				iMovetWidth = 4;
			}
			else if (cCompare == 'E' || cCompare == 'e')
			{
				iAtIndex = i;
				iMovetWidth = 5;
			}
			else if (cCompare == 'F' || cCompare == 'f')
			{
				iAtIndex = i;
				iMovetWidth = 6;
			}
			else if (cCompare == 'G' || cCompare == 'g')
			{
				iAtIndex = i;
				iMovetWidth = 7;
			}
			else if (cCompare == 'H' || cCompare == 'h')
			{
				iAtIndex = i;
				iMovetWidth = 8;
			}
		}	//	end for loop

		if (iAtIndex == 0)
		{

			iMovetHeight = cThree.at(1) - '0';

		}
		else if (iAtIndex == 1)
		{
			iMovetHeight = cThree.at(0) - '0';
		}

		iMoveTo = ((iMovetWidth)+((iMovetHeight - 1) * iBoardHeight)) - 1;

		dHistory.push_back("INFO: iMoveTo: " + std::to_string(iMoveTo) + "from Width: " + std::to_string(iMovetWidth) + " and Height: " + std::to_string(iMovetHeight));

		bool lValidMove = bSearchObj();

		if (lValidMove == true)
		{
			return;
		}
		else
		{
			return;
		}

	}	//	END IF command is "move" 
	else if (cOne == "what" || cOne == "What" || cOne == "WHAT")
	{
		dHistory.push_back("command WHAT issued");
		int iCheckLocation = 0;
		int iCheckWidth = 0;
		int iCheckHeight = 0;
		int iAtIndex = 0;

		if (cTwo.size() != 2)
		{
			dHistory.push_back("ERR: Invalid board location");
			std::cerr << "Please enter a valid location" << std::endl;
			return;
		}

		for (int i = 0; i < 2; i++)
		{
			char cCompare = cTwo.at(i);
			if (cCompare == 'A' || cCompare == 'a')			//	convert FROM to integer
			{
				iAtIndex = i;
				iCheckWidth = 1;
			}
			else if (cCompare == 'B' || cCompare == 'b')
			{
				iAtIndex = i;
				iCheckWidth = 2;
			}
			else if (cCompare == 'C' || cCompare == 'c')
			{
				iAtIndex = i;
				iCheckWidth = 3;
			}
			else if (cCompare == 'D' || cCompare == 'd')
			{
				iAtIndex = i;
				iCheckWidth = 4;
			}
			else if (cCompare == 'E' || cCompare == 'e')
			{
				iAtIndex = i;
				iCheckWidth = 5;
			}
			else if (cCompare == 'F' || cCompare == 'f')
			{
				iAtIndex = i;
				iCheckWidth = 6;
			}
			else if (cCompare == 'G' || cCompare == 'g')
			{
				iAtIndex = i;
				iCheckWidth = 7;
			}
			else if (cCompare == 'H' || cCompare == 'h')
			{
				iAtIndex = i;
				iCheckWidth = 8;
			}

		}	//	end for loop

		if (iAtIndex == 0)
		{
			iCheckHeight = cTwo.at(1) - '0';
		}
		else if (iAtIndex == 1)
		{
			iCheckHeight = cTwo.at(0) - '0';
		}

		iCheckLocation = ((iCheckWidth)+((iCheckHeight - 1) * iBoardHeight)) - 1;
		std::cout << "Location: " << iCheckLocation << " on board:" << std::endl;
		std::cout << "iBoard: \"" << iBoard[iCheckLocation] << "\"" << std::endl;
		std::cout << "sBoard: \"" << sBoard[iCheckLocation] << "\"" << std::endl;
		std::cout << "CheckBoard: \"" << CheckBoard[iCheckLocation] << "\"" << std::endl;
	}


	//clear stream
	dHistory.push_back("ERR: Unknown command issued...");
	std::cerr << "\tThat command isn't on my list..." << std::endl;
	std::cerr << "\tTry typing 'help' for instructions." << std::endl;
	std::cout << "Press any key to continue..." << std::endl;
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');

	return;


}	//	END UsrInput


bool bSearchObj()
{
	bool lValidMove = false;
	std::string pName = sBoard[iMoveFrom];

	if (pName == "wKing")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = wKing.SetPosition();
	}
	else if (pName == "bKing")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = bKing.SetPosition();
	}
	else if (pName == "wQueen")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = wQueen.SetPosition();
	}
	else if (pName == "bQueen")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = bQueen.SetPosition();
	}
	else if (pName == "wRook1")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = wRook1.SetPosition();
	}
	else if (pName == "wRook2")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = wRook2.SetPosition();
	}
	else if (pName == "bRook1")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = bRook1.SetPosition();
	}
	else if (pName == "bRook2")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = bRook2.SetPosition();
	}
	else if (pName == "wBishop1")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = wBishop1.SetPosition();
	}
	else if (pName == "wBishop2")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = wBishop2.SetPosition();
	}
	else if (pName == "bBishop1")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = bBishop1.SetPosition();
	}
	else if (pName == "bBishop2")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = bBishop2.SetPosition();
	}
	else if (pName == "wKnight1")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = wKnight1.SetPosition();
	}
	else if (pName == "wKnight2")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = wKnight2.SetPosition();
	}
	else if (pName == "bKnight1")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = bKnight1.SetPosition();
	}
	else if (pName == "bKnight2")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = bKnight2.SetPosition();
	}
	else if (pName == "wPawn1")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = wPawn1.SetPosition();
	}
	else if (pName == "wPawn2")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = wPawn2.SetPosition();
	}
	else if (pName == "wPawn3")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = wPawn3.SetPosition();
	}
	else if (pName == "wPawn4")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = wPawn4.SetPosition();
	}
	else if (pName == "wPawn5")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = wPawn5.SetPosition();
	}
	else if (pName == "wPawn6")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = wPawn6.SetPosition();
	}
	else if (pName == "wPawn7")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = wPawn7.SetPosition();
	}
	else if (pName == "wPawn8")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = wPawn8.SetPosition();
	}
	else if (pName == "bPawn1")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = bPawn1.SetPosition();
	}
	else if (pName == "bPawn2")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = bPawn2.SetPosition();
	}
	else if (pName == "bPawn3")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = bPawn3.SetPosition();
	}
	else if (pName == "bPawn4")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = bPawn4.SetPosition();
	}
	else if (pName == "bPawn5")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = bPawn5.SetPosition();
	}
	else if (pName == "bPawn6")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = bPawn6.SetPosition();
	}
	else if (pName == "bPawn7")
	{
	dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = bPawn7.SetPosition();
	}
	else if (pName == "bPawn8")
	{
	dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		lValidMove = bPawn8.SetPosition();
	}
	else
	{
		dHistory.push_back("ERR: \"" + pName + "\" cannot be moved.");
		std::cerr << "You can't move that piece!";
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
}

bool bIsKingInCheck()
{
	dHistory.push_back("Is King in Check?");
	if (CurrentColorIsWhite == true)
	{
		for (int i = 0; i < iBoardSize; i++)
		{
			std::string pName = sBoard[i];
			if (pName == "wKing")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				wKing.SetKingInCheck();
			}
			else if (pName == "wQueen")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				wQueen.SetKingInCheck();
			}
			else if (pName == "wRook1")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				wRook1.SetKingInCheck();
			}
			else if (pName == "wRook2")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				wRook2.SetKingInCheck();
			}
			else if (pName == "wBishop1")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				wBishop1.SetKingInCheck();
			}
			else if (pName == "wBishop2")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				wBishop2.SetKingInCheck();
			}
			else if (pName == "wKnight1")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				wKnight1.SetKingInCheck();
			}
			else if (pName == "wKnight2")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				wKnight2.SetKingInCheck();
			}
			else if (pName == "wPawn1")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				wPawn1.SetKingInCheck();
			}
			else if (pName == "wPawn2")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				wPawn2.SetKingInCheck();
			}
			else if (pName == "wPawn3")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				wPawn3.SetKingInCheck();
			}
			else if (pName == "wPawn4")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				wPawn4.SetKingInCheck();
			}
			else if (pName == "wPawn5")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				wPawn5.SetKingInCheck();
			}
			else if (pName == "wPawn6")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				wPawn6.SetKingInCheck();
			}
			else if (pName == "wPawn7")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				wPawn7.SetKingInCheck();
			}
			else if (pName == "wPawn8")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				wPawn8.SetKingInCheck();
			}
		}

		if (CheckBoard[iWhiteKingLocation] == 'x')
		{
			for (int i = 0; i < iBoardSize; i++)
			{
				CheckBoard[i] = ' ';
			}
			dHistory.push_back("INFO: White King is in check!");
			return true;
		}
	}
	else if (CurrentColorIsWhite == false)
	{
		for (int i = 0; i < iBoardSize; i++)
		{
			std::string pName = sBoard[i];

			if (pName == "bKing")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				bKing.SetKingInCheck();
			}
			else if (pName == "bQueen")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				bQueen.SetKingInCheck();
			}
			else if (pName == "bRook1")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				bRook1.SetKingInCheck();
			}
			else if (pName == "bRook2")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				bRook2.SetKingInCheck();
			}
			else if (pName == "bBishop1")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				bBishop1.SetKingInCheck();
			}
			else if (pName == "bBishop2")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				bBishop2.SetKingInCheck();
			}
			else if (pName == "bKnight1")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				bKnight1.SetKingInCheck();
			}
			else if (pName == "bKnight2")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				bKnight2.SetKingInCheck();
			}
			else if (pName == "bPawn1")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				bPawn1.SetKingInCheck();
			}
			else if (pName == "bPawn2")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				bPawn2.SetKingInCheck();
			}
			else if (pName == "bPawn3")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				bPawn3.SetKingInCheck();
			}
			else if (pName == "bPawn4")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				bPawn4.SetKingInCheck();
			}
			else if (pName == "bPawn5")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				bPawn5.SetKingInCheck();
			}
			else if (pName == "bPawn6")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				bPawn6.SetKingInCheck();
			}
			else if (pName == "bPawn7")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				bPawn7.SetKingInCheck();
			}
			else if (pName == "bPawn8")
			{
				dHistory.push_back("INFO: Piece at " + std::to_string(i) + " is: \"" + pName + "\".");
				bPawn8.SetKingInCheck();
			}
		}
		if (CheckBoard[iBlackKingLocation] == 'x')
		{
			for (int i = 0; i < iBoardSize; i++)
			{
				CheckBoard[i] = ' ';
			}
			dHistory.push_back("Black King in in check!");
			return true;
		}
	}
	for (int i = 0; i < iBoardSize; i++)
	{
		CheckBoard[i] = ' ';
	}
	return false;
}	//	END bIsKingInCheck


void printBoard()
{
	//			                W I D T H " << std::endl;
	//			       A    B    C    D    E    F    G    H   " << std::endl;				white space	   black space
	//			    ==========================================" << std::endl;				#####			-----
	//			   | #####-----#####-----#####-----#####----- |
	//			 1 | # 0 #- 1 -# 2 #- 3 -# 4 #- 5 -# 6 #- 7 - |" << std::endl;				# 0 #			- 0 -
	//			   | #####-----#####-----#####-----#####----- |
	//		H	   | -----#####-----#####-----#####-----##### |
	//			 2 | - 8 -# 9 #- 10-# 11#- 12-# 13#- 14-# 15# |" << std::endl;				#####	
	//		E	   | -----#####-----#####-----#####-----##### |
	//			   | #####-----#####-----#####-----#####----- |
	//		I	 3 | # 16#- 17-# 18#- 19-# 20#- 21-# 22#- 23- |" << std::endl;		
	//			   | #####-----#####-----#####-----#####----- |
	//		G	   | -----#####-----#####-----#####-----##### |
	//			 4 | - 24-# 25#- 26-# 27#- 28-# 29#- 30-# 31# |" << std::endl;		
	//		H	   | -----#####-----#####-----#####-----##### | 
	//			   | #####-----#####-----#####-----#####----- |
	//		T	 5 | # 32#- 33-# 34#- 35-# 36#- 37-# 38#- 39- |" << std::endl;	
	//			   | #####-----#####-----#####-----#####----- |
	//			   | -----#####-----#####-----#####-----##### |
	//			 6 | - 40-# 41#- 42-# 43#- 44-# 45#- 46-# 47# |" << std::endl;		
	//			   | -----#####-----#####-----#####-----##### |
	//			   | #####-----#####-----#####-----#####----- |
	//			 7 | # 48#- 49-# 50#- 51-# 52#- 53-# 54#- 55- |" << std::endl;		
	//			   | #####-----#####-----#####-----#####----- |
	//			   | -----#####-----#####-----#####-----##### |
	//			 8 | - 56-# 57#- 58-# 59#- 60-# 61#- 62-# 63# |" << std::endl;		
	//			   | -----#####-----#####-----#####-----##### |
	//			    ==========================================" << std::endl;		
	//			      A  B  C  D  E  F  G  H " << std::endl;		
	std::string sTurn;
	if (CurrentColorIsWhite == true)
	{
		sTurn = "\033[1;107;90mWHITE\033[0m (Uppercase)";
		dHistory.push_back("INFO: CurrentColorIsWhite is TRUE");
	}
	else
	{
		sTurn = "\033[1;100;97mBLACK\033[0m (lowercase)";
		dHistory.push_back("INFO: CurrentColorIsWhite is FALSE");
	}



	if (boardType == 'l')
	{
		long unsigned int l = 0;
		bool whiteSpace = false;
		int iSpaceNum = 0;
		std::cout << "\tc u r r e n t  t u r n: " << sTurn << std::endl;
		std::cout << "\t       A    B    C    D    E    F    G    H" << std::endl;
		std::cout << "\t    ==========================================";

		for (int height = 0; height < iBoardHeight * 3; height++)
		{
			std::cout << std::endl;
			if (((height) / 3) % 2 == 0)
			{
				whiteSpace = true;
			}
			else
			{
				whiteSpace = false;
			}

			if ((height - 1) % 3 == 0)
			{
				std::cout << "\t " << (height / 3) + 1 << " | ";
			}
			else
			{
				std::cout << "\t   | ";
				iSpaceNum++;
			}

			for (int width = 0; width < iBoardWidth; width++)
			{
				int iBoardPrint = ((width + 1) + ((height / 3) * iBoardHeight)) - 1;

				if (whiteSpace == false)
				{

					if ((height - 1) % 3 == 0)
					{
						std::cout << "\033[1;47m  \033[1;94m" << iBoard[iBoardPrint] << "  \033[0m";
					}
					else
					{
						std::cout << "\033[1;47m     \033[0m";
					}

					whiteSpace = true;
				}
				else if (whiteSpace == true)
				{
					if ((height - 1) % 3 == 0)
					{
						std::cout << "\033[1;40m  \033[1;94m" << iBoard[iBoardPrint] << "  \033[0m";
					}
					else
					{
						std::cout << "\033[1;40m     \033[0m";
					}

					whiteSpace = false;
				}
				if (width == iBoardWidth)
				{
					std::cout << " |";
				}
			}
			if (height == 0)
			{
				std::cout << "\tGame Commands\t     M O V E  H I S T O R Y";
			}
			else if (height == 1)
			{
				std::cout << "\thelp 'command'\t";
			}
			else if (height == 2)
			{
				std::cout << "\texit\t\t";
			}
			else if (height == 3)
			{
				std::cout << "\tmove from to\t";
			}
			else if (height == 4)
			{
				std::cout << "\tmcheck from\t";
			}
			else if (height == 5)
			{
				std::cout << "\tcheckmate\t";
			}
			else if (height == 6)
			{
				std::cout << "\trematch\t\t";
			}
			else if (height == 7)
			{
				std::cout << "\tline 1071\t";
			}
			else
			{
				std::cout << "\t\t\t";
			}

			if (height > 0)
			{
				if (mHistory.size() == 0)
				{
					std::cout << "\tMake a move!";
				}
				else if (mHistory.size() < iBoardHeight * 3)
				{
					if (l < mHistory.size())
					{
						std::cout << l + 1 << ". " << mHistory.at(l);
						l++;
					}
					else
					{
						std::cout << "\tMake a move!";
					}
				}
				else
				{
					int l = (mHistory.size() - iBoardHeight) + height;
					std::cout << "\t " << l + 1 << ". " << mHistory.at(l);
				}
			}

		}

		std::cout << std::endl;
		dHistory.push_back("Board printed sucessfully");
		return;
	}


	//		      A  B  C  D  E  F  G  H   
	//		    _________________________
	//		 1 |  0  1  2  3  4  5  6  7
	//		 2 |  8  9 10 11 12 13 14 15
	//		 3 | 16 17 18 19 20 21 22 23
	//		 4 | 24 25 26 27 28 29 30 31
	//		 5 | 32 33 34 35 36 37 38 39
	//		 6 | 40 41 42 43 44 45 46 47
	//		 7 | 48 49 50 51 52 53 54 55
	//		 8 | 56 57 58 59 60 61 62 63

	if (boardType == 's')
	{
		long unsigned int l = 0;
		bool whiteSpace = false;
		std::cout << "\n\n\n\n\n" << std::endl;
		std::cout << "\tcurrent  turn: " << sTurn << std::endl;;
		std::cout << "\t      A  B  C  D  E  F  G  H   \t\tScore:\t White: " << iWhiteScore << "\tBlack: " << iBlackScore << std::endl;
		std::cout << "\t    ========================== \tGame Commands\tM o v e  H i s t o r y ";

		for (int height = 0; height < iBoardHeight; height++)
		{
			if (height % 2 == 0)
			{
				whiteSpace = true;
			}
			else
			{
				whiteSpace = false;
			}

			std::cout << std::endl;
			std::cout << "\t " << height + 1 << " | ";
			for (int width = 0; width < iBoardWidth; width++)
			{
				int iBoardPrint = ((width + 1) + (height * iBoardHeight)) - 1;
				if (whiteSpace == false)
				{
					std::cout << "\033[1;47m\033[1;94m";
					std::cout << " " << iBoard[iBoardPrint] << " ";
					std::cout << "\033[0m";
					whiteSpace = true;
				}
				else if (whiteSpace == true)
				{
					std::cout << "\033[1;40m\033[1;94m";
					std::cout << " " << iBoard[iBoardPrint] << " ";
					std::cout << "\033[0m";
					whiteSpace = false;
				}

			}
			if (height == 0)
			{
				std::cout << "\thelp 'command'\t";
			}
			else if (height == 1)
			{
				std::cout << "\texit\t\t";
			}
			else if (height == 2)
			{
				std::cout << "\tmove from to\t";
			}
			else if (height == 3)
			{
				std::cout << "\tmcheck from\t";
			}
			else if (height == 4)
			{
				std::cout << "\tcheckmate\t";
			}
			else if (height == 5)
			{
				std::cout << "\t\t\t";
			}
			else if (height == 6)
			{
				std::cout << "\tline 1071\t";
			}
			else
			{
				std::cout << "\t\t\t";
			}

			if (height > 0)
			{
				if (mHistory.size() == 0)
				{
					std::cout << "\tMake a move!";
				}
				else if (mHistory.size() < iBoardHeight)
				{
					if (l < mHistory.size())
					{
						std::cout << l + 1 << ". " << mHistory.at(l);
						l++;
					}
					else
					{
						std::cout << "\tMake a move!";
					}
				}
				else
				{
					int l = (mHistory.size() - iBoardHeight) + height;
					std::cout << "\t " << l + 1 << ". " << mHistory.at(l);
				}
			}
		}
		std::cout << "\n\n\n\n\n\n\n\n\n\n" << std::endl;
		dHistory.push_back("Board printed sucessfully");
		return;
	}
}	//	END OF PRINTBOARD
