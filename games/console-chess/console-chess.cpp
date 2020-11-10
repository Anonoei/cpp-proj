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
char iBoard[iBoardWidth * iBoardHeight] = {' '};	//	initialize array with BoardHeight rows, BoardWidth columns
std::vector<std::string> mHistory;	//moveHistory
std::string sBoard[iBoardWidth * iBoardHeight] = {""};	//stringBoard
int wMoves = 0;
int bMoves = 0;
int pieceType = 0;
int iWhiteScore = 39;
int iBlackScore = 39;

long unsigned int iOldHistorySize = 0;


int iMoveFrom = 0;
int iMoveTo = 0;

bool bGameStatus = true;
bool CurrentColorIsWhite = true;

char boardType = 'f';

bool bSinglePlayer();
bool bMultiPlayer();
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
	bool SetPosition()
	{
		bool bMoveValid = false;
		bool bMoveToWhite = false;
		bool bCapturePiece = false;

		if (sBoard[iMoveTo] == "")
		{
			bCapturePiece = false;
		}
		else
		{
			bCapturePiece = true;
			std::string sMoveToPiece = sBoard[iMoveTo];

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
				std::cerr << "Something went wrong" << std::endl;
				return false;
			}

		}

		if (iMoveTo > iBoardSize)
		{
			bMoveValid = false;
		}
		else if (this->bWhitePiece != CurrentColorIsWhite)
		{
			std::cerr << "It's not that color's turn!" << std::endl;
			return false;
		}
		else if (bCapturePiece == true)
		{
			if (this->bWhitePiece == bMoveToWhite)
			{
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
			if (iMoveTo == this->iPosition + 1 ||	//	move right	
				iMoveTo == this->iPosition - 1 ||	//	move left
				iMoveTo == this->iPosition - 8 ||	//	move up
				iMoveTo == this->iPosition - 7 ||	//	move diagonal up right
				iMoveTo == this->iPosition - 9 ||	//	move diagonal up left
				iMoveTo == this->iPosition + 8 ||	//	move down
				iMoveTo == this->iPosition + 7 ||	//	move diagonal down left
				iMoveTo == this->iPosition + 9)		//	move diagonal down right
			{
				//	need to check for check
				bMoveValid = true;
			}
			else
			{
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

				int pEquationDownLeft = iMoveTo == this->iPosition + (i * 7);
				int pEquationDownRight = iMoveTo == this->iPosition + (i * 9);

				if (iMoveTo == pEquationDown)		//	move down
				{
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						if (sBoard[pEquationDown] == "")
						{												
							iThroughPiece++;
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
				if (bCapturePiece == true)
				{
					if (iThroughPiece == iLoopNum - 1)
					{
						bMoveValid = true;
					}
					else
					{
						bMoveValid = false;
					}
				}
				else if (bCapturePiece == false)
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
			}
			else
			{
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
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						if (sBoard[pEquationDown] == "")
						{
							iThroughPiece++;
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
						}
					}
					bThroughCalc = true;
				}

			}

			if (bThroughCalc == true)
			{
				if (bCapturePiece == true)
				{
					if (iThroughPiece == iLoopNum - 1)
					{
						bMoveValid = true;
					}
					else
					{
						bMoveValid = false;
					}
				}
				else if (bCapturePiece == false)
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
					iLoopNum = i;
					for (int i = 1; i < iLoopNum; i++)
					{
						if (sBoard[pEquationUpLeft] == "")
						{
							iThroughPiece++;
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
				if (bCapturePiece == true)
				{
					if (iThroughPiece == iLoopNum - 1)
					{
						bMoveValid = true;
					}
					else
					{
						bMoveValid = false;
					}
				}
				else if (bCapturePiece == false)
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
			}
			else
			{
				bMoveValid = false;
			}

		}	//	END BISHOP logic
		else if (this->iType == 4)	//	Knight move logic
		{
			if (iMoveTo == this->iPosition - 15 ||	//	move up up right	
				iMoveTo == this->iPosition - 17 ||	//	move up up left
				iMoveTo == this->iPosition - 6 ||	//	move up right right
				iMoveTo == this->iPosition - 10 ||	//	move up left left
				iMoveTo == this->iPosition + 10 ||	//	move left left down
				iMoveTo == this->iPosition - 10 ||	//	move left left up
				iMoveTo == this->iPosition + 15 ||	//	move down down left
				iMoveTo == this->iPosition + 17)	//	move down down right
			{
				bMoveValid = true;
			}
			else
			{
				bMoveValid = false;
			}
			
		}	//	END KNIGHT logic
		else if (this->iType == 5)	//	Pawn move logic
		{
			if (this->bWhitePiece == true)
			{

				if ((iMoveTo == this->iPosition - 8 || 
					iMoveTo == this->iPosition -7) && (bCapturePiece == true || 
					iMoveTo == this->iPosition - 9) && bCapturePiece == true)
				{
					bMoveValid = true;
				}
				else if (iMoves == 0 && iMoveTo == this->iPosition - 16)
				{
					bMoveValid = true;
				}
				else
				{
					bMoveValid = false;
				}
			}
			else
			{
				if (iMoveTo == this->iPosition + 8)
				{
					bMoveValid = true;
				}
				else if (iMoves == 0 && iMoveTo == this->iPosition + 16)
				{
					bMoveValid = true;
				}
				else
				{
					bMoveValid = false;
				}
			}
			
		}

		
		if (bMoveValid == true)
		{
			this->iMoves++;
			this->iPosition = iMoveTo;
			iBoard[this->iPosition] = this->cVisual;
			iBoard[iMoveFrom] = ' ';
			sBoard[iMoveTo] = sBoard[iMoveFrom];
			sBoard[iMoveFrom] = ' ';
			iOldHistorySize = mHistory.size();

			if (bCapturePiece == true)
			{
				mHistory.push_back(sBoard[iMoveTo] + " from " + std::to_string(iMoveFrom) + " captured " + sBoard[iMoveTo] + " at " + std::to_string(iMoveTo));
				//std::cout << sBoard[iMoveTo] + " from " + std::to_string(iMoveFrom) + " captured " + sBoard[iMoveTo] + " at " + std::to_string(iMoveTo) << std::endl;

				return true;
			}
			else
			{
				mHistory.push_back(sBoard[iMoveTo] + " moved from " + std::to_string(iMoveFrom) + " to " + std::to_string(iMoveTo));
				//std::cout << sBoard[iMoveTo] + " moved from " + std::to_string(iMoveFrom) + " to " + std::to_string(iMoveTo) << std::endl;
				return true;
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
	memset(iBoard, ' ', iBoardSize);	//	initalize board with all ' '
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
		}
		else if (cUsrInput == 's')
		{
			boardType = 's';
		}

		vGameInit();

		std::cout << "Would you like \033[4ms\033[0mingle or \033[4mm\033[0multiplayer?" << std::endl;
		cUsrInput = cInputValidation();
		if (cUsrInput == 's' || cUsrInput == 'S' || cUsrInput == '1')
		{
			gameMode = 's';
		}
		else if (cUsrInput == 'm' || cUsrInput == 'M' || cUsrInput == '2')
		{
			gameMode = 'm';
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
			std::cout << "That gamemode doesn\'t exist" << std::endl;
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

	while (bGameStatus == true)
	{
		printBoard();
		std::cout << "\n\tWhat is your move?\n\t\t";
		vUsrInput();
	}

	return 0;
}	//	END OF bSinglePlayer

bool bMultiPlayer()			//	--------------------------	MULTI PLAYER GAME	-------------------------------------------------------
{
	bGameStatus = true;

	while (bGameStatus == true)
	{
		printBoard();
		

	}
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

	//std::cout << "\"" << cOne << "\"\t \"" << cTwo << "\"\t \"" << cThree << std::endl;

	if (cThree == "exit")
	{ 
		std::cout << "Are you sure you want to quit?" << std::endl;
		char input = cInputValidation();
		if (input == 'n' || input == 'N')
		{
			
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
		std::cout << "\tHelp is on the way!" << std::endl;
		if (cTwo == "")
		{
			std::cout << "\n\n\t\tFull list of commands:" << std::endl;
			std::cout << "\t    the ' character indicates a variable input, like A5 or a command" << std::endl;
			std::cout << "\tcheckmate\t\tChecks for checkmate, and ends the match" << std::endl;
			std::cout << "\texit\t\tExit's to the main menu, and loses all game progress" << std::endl;
			std::cout << "\thelp 'command'\tLists all commands, and provides context for commmands" << std::endl;
			std::cout << "\thistory\t\tPrints full game history to screen" << std::endl;
			std::cout << "\tmove 'from' to'\tMoves the 'from' piece to the 'to' location. Example: move A7 A5." << std::endl;
			std::cout << "\tmcheck 'from'\tMove Check - Shows the valid moves of the 'from' piece" << std::endl;
			std::cout << "\trematch\t\tEnds the current match and starts a new one." << std::endl;
		}
		else if (cTwo == "checkmate" || cTwo == "Checkmate" || cTwo == "CheckMate" || cTwo == "CHECKMATE")
		{
			std::cout << "\n\n\t\t'checkmate' Command help:" << std::endl;
			std::cout << "\tThe 'checkmate' command is used to check for checkmate, and end the current match." << std::endl;
			std::cout << "\tThe syntax for the checkmate command is as follows:" << std::endl;
			std::cout << "\t\tcheckmate" << std::endl;
			std::cout << "\tI believe in you." << std::endl;
		}
		else if (cTwo == "exit" || cTwo == "Exit" || cTwo == "EXIT")
		{
			std::cout << "\n\n\t\t'exit' Command help:" << std::endl;
			std::cout << "\tThe 'exit' command is used to return to the main menu, and end the current match." << std::endl;
			std::cout << "\tThe syntax for the exit command is as follows:" << std::endl;
			std::cout << "\t\texit" << std::endl;
			std::cout << "\tI believe in you." << std::endl;
		}
		else if (cTwo == "history" || cTwo == "History" || cTwo == "HISTORY")
		{
			std::cout << "\n\n\t\t'history' Command help:" << std::endl;
			std::cout << "\tThe 'history' command is used to display all events of the current match" << std::endl;
			std::cout << "\tThe syntax for the move command is as follows:" << std::endl;
			std::cout << "\t\thistory" << std::endl;
			std::cout << "\t\tSpecial Uses:" << std::endl;
			std::cout << "\t'Save to Files'" << std::endl;
			std::cout << "\t in the future I'll write what is supposed to be here." << std::endl;
		}
		else if (cTwo == "move" || cTwo == "Move" || cTwo == "MOVE")
		{
			std::cout << "\n\n\t\t'move' Command help:" << std::endl;
			std::cout << "\tThe 'move' command is used to move any piece from one location to another" << std::endl;
			std::cout << "\tThe syntax for the move command is as follows:" << std::endl;
			std::cout << "\t\tmove 'from'\t'to'" << std::endl;
			std::cout << "\t\tmove   A7 \tA5" << std::endl;
			std::cout << "\tThis moves the piece at location 'A7' to the 'A5'" << std::endl;
			std::cout << "\tThis command has input validation, and will ensure your move is legal." << std::endl;
			std::cout << "\t\tSpecial Uses:" << std::endl;
			std::cout << "\t'castling'" << std::endl;
			std::cout << "\t in the future I'll write what is supposed to be here." << std::endl;
		}
		else if (cTwo == "mcheck" || cTwo == "Mcheck" || cTwo == "mCheck" || cTwo == "MCHECK")
		{
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
			std::cout << "\n\n\t\t'rematch' Command help:" << std::endl;
			std::cout << "\tThe 'rematch' command is used to end the current game, and start a new one." << std::endl;
			std::cout << "\tThe syntax for the rematch command is as follows:" << std::endl;
			std::cout << "\t\trematch" << std::endl;
			std::cout << "\tI Believe in you." << std::endl;
		}
		else
		{
			std::cout << "\n\t\tYour command wasn't found..." << std::endl;
			std::cout << "\t\ttry running just 'help' if you keep having issues" << std::endl;
		}



		std::cout << "\nPress any key to continue..." << std::endl;
		std::cin.get();
		std::cin.clear();
		return;
	}
	else if (cOne == "checkmate")
	{
		//	the stuff for checkmate should go here
		std::cout << "This command hasn't been implemented yet" << std::endl;
		return;
	}
	else if (cOne == "history" || cOne == "History" || cOne == "HISTORY" || cOne == "hist" || cOne == "h")
	{
		for (long unsigned int i = 0; i < mHistory.size(); i++)
		{
			std::cout << i + 1 << ".\t" << mHistory.at(i) << std::endl;
		}
		std::cout << "\nPress any key to continue..." << std::endl;
		std::cin.get();
		std::cin.clear();
		return;
	}
	else if (cOne == "mcheck")
	{
		//	the stuff for mcheck should go here
		std::cout << "This command hasn't been implemented yet" << std::endl;
		return;
	}
	else if (cOne == "rematch")
	{
		bGameStatus = false;
		return;
	}
	else if (cOne == "move" || cOne == "Move" || cOne == "MOVE" || cOne == "mov" || cOne == "mv")
	{
		int iMovefWidth = 0;
		int iMovefHeight = 0;
		int iMovetWidth = 0;
		int iMovetHeight = 0;
		int iAtIndex = 0;

		if (cTwo.size() > 2 || cThree.size() > 2)
		{
			std::cerr << "That location does not exist!" << std::endl;
			std::cout << "Press any key to continue..." << std::endl;
			std::cin.get();
			std::cin.clear();
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

		iMoveFrom = ((iMovefWidth) + ((iMovefHeight - 1) * iBoardHeight)) - 1;


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

		iMoveTo = ((iMovetWidth) + ((iMovetHeight - 1) * iBoardHeight)) - 1;

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
	

	//clear stream
	std::cerr << "\tThat command doesn't seem to work!" << std::endl;
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
		lValidMove = wKing.SetPosition();
	}
	else if (pName == "bKing")
	{
		lValidMove = bKing.SetPosition();
	}
	else if (pName == "wQueen")
	{
		lValidMove = wQueen.SetPosition();
	}
	else if (pName == "bQueen")
	{
		lValidMove = bQueen.SetPosition();
	}
	else if (pName == "wRook1")
	{
		lValidMove = wRook1.SetPosition();
	}
	else if (pName == "wRook2")
	{
		lValidMove = wRook2.SetPosition();
	}
	else if (pName == "bRook1")
	{
		lValidMove = bRook1.SetPosition();
	}
	else if (pName == "bRook2")
	{
		lValidMove = bRook2.SetPosition();
	}
	else if (pName == "wBishop1")
	{
		lValidMove = wBishop1.SetPosition();
	}
	else if (pName == "wBishop2")
	{
		lValidMove = wBishop2.SetPosition();
	}
	else if (pName == "bBishop1")
	{
		lValidMove = bBishop1.SetPosition();
	}
	else if (pName == "bBishop2")
	{
		lValidMove = bBishop2.SetPosition();
	}
	else if (pName == "wKnight1")
	{
		lValidMove = wKnight1.SetPosition();
	}
	else if (pName == "wKnight2")
	{
		lValidMove = wKnight2.SetPosition();
	}
	else if (pName == "bKnight1")
	{
		lValidMove = bKnight1.SetPosition();
	}
	else if (pName == "bKnight2")
	{
		lValidMove = bKnight2.SetPosition();
	}
	else if (pName == "wPawn1")
	{
		lValidMove = wPawn1.SetPosition();
	}
	else if (pName == "wPawn2")
	{
		lValidMove = wPawn2.SetPosition();
	}
	else if (pName == "wPawn3")
	{
		lValidMove = wPawn3.SetPosition();
	}
	else if (pName == "wPawn4")
	{
		lValidMove = wPawn4.SetPosition();
	}
	else if (pName == "wPawn5")
	{
		lValidMove = wPawn5.SetPosition();
	}
	else if (pName == "wPawn6")
	{
		lValidMove = wPawn6.SetPosition();
	}
	else if (pName == "wPawn7")
	{
		lValidMove = wPawn7.SetPosition();
	}
	else if (pName == "wPawn8")
	{
		lValidMove = wPawn8.SetPosition();
	}
	else if (pName == "bPawn1")
	{
		lValidMove = bPawn1.SetPosition();
	}
	else if (pName == "bPawn2")
	{
		lValidMove = bPawn2.SetPosition();
	}
	else if (pName == "bPawn3")
	{
		lValidMove = bPawn3.SetPosition();
	}
	else if (pName == "bPawn4")
	{
		lValidMove = bPawn4.SetPosition();
	}
	else if (pName == "bPawn5")
	{
		lValidMove = bPawn5.SetPosition();
	}
	else if (pName == "bPawn6")
	{
		lValidMove = bPawn6.SetPosition();
	}
	else if (pName == "bPawn7")
	{
		lValidMove = bPawn7.SetPosition();
	}
	else if (pName == "bPawn8")
	{
		lValidMove = bPawn8.SetPosition();
	}
	else
	{
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
	}
	else
	{
		sTurn = "\033[1;100;97mBLACK\033[0m (lowercase)";
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
		return;
	}


}	//	END OF PRINTBOARD
