/*					CONSOLE-CHESS v0.55
		TO DO
debug:

	fixed:
		color randomly changing			// due to the below issue - memory overwrite due to improper array index
		random high values being assigned to integers	//	due to not checking if move INT was between 0 and iBoardSize
		Queen recursive path not travelling full distance.		//	due to bad logic
		Fix mcheck command for KING, QUEEN, ROOK, BISHOP, KNIGHT, and PAWN

features:

	Add options for how player wants mcheck to be displayed******************************

	Pawn Promotion
		~use input to initialize new piece, global varialbe starting from how many default pieces there are.
	Pawn "en passant"

	write "checkmate" command

	Add proper piece capturing and create a more dynamic scoring system

	files:
		make GameNumber work properly
		save user settings
		save game moves
		input move files
			resume previous game or
			watch game move by move

			complete:
					debug levels 0, 1, 2, 3 (mostly)
					Added support for text only consoles (no ANSI codes)
					ensure pawn capturing works properly
					change piece color
					castling
					write mcheck command
					Make board colors more dynamic based on what is trying to be told
					Add text only support with mcheck
					Use b**PieceName**Logic() instead of seperate functions for check and move.
					mcheck - Show move is valid when piece is opposite color
					added input sanitization for commands
					added functions for CharToInt and IntToChar

gameplay:
	Check if king is in check
		Add functionality for checking if a piece of the checked color can move to block the check
			IF false, then checkmate

		~add functionality for only spawning certain pieces for debugging

	Add single player functionality (chess AI)

		complete:
				multiplayer (2 player back and forth)
				verify all peices execute properly	(mcheck logic)
				Create game win
				Create game draw	(stalemate)
				Create game lose	(singleplayer)

extras:
	Add different gamemodes??
		~Chess960
		~King Of The Hill
		~Bughouse
		~Crazyhouse
		~3-Check
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
const unsigned int iBoardWidth = 8;
const unsigned int iBoardHeight = 8;
const unsigned int iBoardSize = (iBoardWidth * iBoardHeight) - 1;

//	Boards
char iBoard[iBoardWidth * iBoardHeight] = { ' ' };	//	initialize array with BoardHeight rows, BoardWidth columns
std::string sBoard[iBoardWidth * iBoardHeight] = { " " };	//	Holds name value for piece at location on board
char CheckBoard[iBoardWidth * iBoardHeight] = { ' ' };		//	Holds value for where pieces can move (checks for check)
char CheckmateBoard[iBoardWidth * iBoardHeight] = { ' ' };	//	Holds value for CheckBoard while checking for checkmate
char cMoveBoard[iBoardWidth * iBoardHeight] = { ' ' };	//	For mcheck command

std::vector<std::string> dHistory;	//debugHistory
std::vector<std::string> mHistory;	//moveHistory
std::vector<std::string> sCaptured;	//	holds captured pieces
std::vector<std::string> sChecking;	//	holds which pieces are checking a king

std::vector<std::string> sSidePrint;	//	holds the strings printed to the side of the board
std::string sErrorMsg = "";

// uncode piece codes for the future
//char const* special_character[] = { "\u2654", "\u2655", "\u2656", "\u2657", "\u2658", "\u2659", 
//		"\u265A", "\u265b", "\u265c", "\u265d", "\u265e", "\u265f" };


unsigned int wMoves = 0;
unsigned int bMoves = 0;
unsigned int pieceType = 0;
unsigned int iWhiteScore = 39;
unsigned int iBlackScore = 39;

unsigned int GameNumber = 0;
unsigned int mHistoryNumber = 0;
unsigned int mHistoryReadNumber = 0;
unsigned int dHistoryReadNumber = 0;
unsigned int dHistoryNumber = 0;
unsigned int iMoveFrom = 0;
unsigned int iMoveTo = 0;


unsigned int iDebugLevel = 0;
unsigned int iPieceColor = 94;


bool bWhiteKingInCheck = false;		//	self explanatory
bool bBlackKingInCheck = false;
bool bCheckmate = false;
unsigned int iWhiteKingLocation = 60;
unsigned int iBlackKingLocation = 4;
bool bGameStatus = true;
bool CurrentColorIsWhite = true;
bool bCurrentlyCastling = false;
bool bCastleSideQueen = false;

bool bRematch = false;

bool bKingLogic();
bool bQueenLogic();
bool bRookLogic();
bool bBishopLogic();
bool bKnightLogic();
bool bPawnLogic();
unsigned int iThisPos = 0;
unsigned int iThisMoves = 0;
bool iThisWhite = true;
bool bMoveCheck = false;

bool bMoveToWhite = false;
bool bCapturePiece = false;

char boardType = 'f';
bool bGraphics = false;

bool bSinglePlayer();
bool bMultiPlayer();

void vGameWin();
void vGameLose();

bool bIsKingInCheck();
bool bIsKingInCheckmate();
void vMoveCheck();
void vInputSanitization(std::string*);
int iFromCharToInt(std::string, int*);
char cFromIntToChar(int, int*);

char cInputValidation();
void printBoard();

bool bSearchObj();

void vUsrInput();

void vDebug();
void vPause()
{
	std::cout << "\n\nPress any key to continue..." << std::endl;
	std::cin.get();
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
	return;
}
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
	unsigned int iPosition;
	unsigned int iValue;
	unsigned int iType;
	unsigned int iMoves;
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
	void SetKingInCheck()
	{
		bMoveCheck = true;
		iThisPos = this->iPosition;
		iThisWhite = this->bWhitePiece;
		iThisMoves = this->iMoves;

		bool bMoveValid = false;

		if (this->iType == 0)	//	King move logic
		{
			bKingLogic();
			dHistory.push_back("INFO: KING written to CheckBoard");
		}
		else if (this->iType == 1)	//	Queen move logic
		{
			bQueenLogic();
			dHistory.push_back("INFO: QUEEN written to CheckBoard");
		}	//	END QUEEN logic
		else if (this->iType == 2)	//	Rook move logic
		{
			bRookLogic();
			dHistory.push_back("INFO: ROOK written to CheckBoard");
		}
		else if (this->iType == 3)	//	Bishop move logic
		{
			bBishopLogic();
			dHistory.push_back("INFO: BISHOP written to CheckBoard");
		}	//	END BISHOP logic
		else if (this->iType == 4)	//	Knight move logic
		{
			bKnightLogic();
			dHistory.push_back("INFO: KNIGHT written to CheckBoard");
		}	//	END KNIGHT logic
		else if (this->iType == 5)	//	Pawn move logic
		{
			bPawnLogic();
			dHistory.push_back("INFO: PAWN written to CheckBoard");
		}	//	End pawn move logic

	}	//	End CheckIfCheck



	bool SetPosition()
	{
		bool bMoveValid = false;
		bMoveCheck = false;

		iThisPos = this->iPosition;
		iThisWhite = this->bWhitePiece;
		iThisMoves = this->iMoves;
		dHistory.push_back("INFO: iPos: " + std::to_string(iThisPos) + "\tiMoves: " + std::to_string(iThisMoves) + "\tiType: " + std::to_string(this->iType) + "\tbWhitePiece: " + std::to_string(iThisWhite));

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
				sErrorMsg = "Something went wrong";
				return false;
			}
			dHistory.push_back("INFO: bCapturePiece: TRUE \tbMoveToWhite: " + std::to_string(bMoveToWhite));
		}
		else
		{
			dHistory.push_back("INFO: bCapturePiece: FALSE");
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

		if (this->iType == 0)	//	King move logic
		{
			bMoveValid = bKingLogic();
		}
		else if (this->iType == 1)	//	Queen move logic
		{
			bMoveValid = bQueenLogic();
		}	//	END QUEEN logic
		else if (this->iType == 2)	//	Rook move logic
		{
			bMoveValid = bRookLogic();
		}
		else if (this->iType == 3)	//	Bishop move logic
		{
			bMoveValid = bBishopLogic();
		}	//	END BISHOP logic
		else if (this->iType == 4)	//	Knight move logic
		{
			bMoveValid = bKnightLogic();
		}	//	END KNIGHT logic
		else if (this->iType == 5)	//	Pawn move logic
		{
			bMoveValid = bPawnLogic();
		}

		if (bMoveValid == true)
		{
			bool CheckKingCheck = true;

			if (this->iType != 0)
			{
				if (bCapturePiece == true)
				{
					mHistory.push_back("\t" + sBoard[iMoveFrom] + " from " + std::to_string(iMoveFrom) + " captured " + sBoard[iMoveTo] + " at " + std::to_string(iMoveTo));
					dHistory.push_back("INFO: " + sBoard[iMoveFrom] + " from " + std::to_string(iMoveFrom) + " captured " + sBoard[iMoveTo] + " at " + std::to_string(iMoveTo));
					sCaptured.push_back(sBoard[iMoveTo]);
				}
				else if (bCurrentlyCastling == true)
				{
					mHistory.push_back("\t" + sBoard[iMoveFrom] + " castled from " + std::to_string(iMoveFrom) + " to " + std::to_string(iMoveTo));
					dHistory.push_back("INFO: " + sBoard[iMoveFrom] + " castled from " + std::to_string(iMoveFrom) + " to " + std::to_string(iMoveTo));
					bCurrentlyCastling = false;
				}
				else
				{
					mHistory.push_back("\t" + sBoard[iMoveFrom] + " moved from " + std::to_string(iMoveFrom) + " to " + std::to_string(iMoveTo));
					dHistory.push_back("INFO: "+ sBoard[iMoveFrom] + " moved from " + std::to_string(iMoveFrom) + " to " + std::to_string(iMoveTo));
				}
				this->iMoves++;
				this->iPosition = iMoveTo;

				iBoard[iMoveTo] = this->cVisual;
				iBoard[iMoveFrom] = ' ';

				sBoard[iMoveTo] = sBoard[iMoveFrom];
				sBoard[iMoveFrom] = ' ';

				CheckKingCheck = bIsKingInCheck();
				bool CheckMateCheck = false;

				if (CheckKingCheck == true)
				{
					if (CurrentColorIsWhite == true)
					{
						dHistory.push_back("INFO: bBlackKingInCheck is TRUE");
						bBlackKingInCheck = true;
						bCheckmate = bIsKingInCheckmate();
					}
					else
					{
						dHistory.push_back("INFO: bWhiteKingInCheck is TRUE");
						bWhiteKingInCheck = true;
						bCheckmate = bIsKingInCheckmate();
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
					CurrentColorIsWhite = true;
				}
				else
				{
					CurrentColorIsWhite = true;
					CheckKingCheck = bIsKingInCheck();
					CurrentColorIsWhite = false;
				}
				std::cout << "CheckKingCheck: " << std::to_string(CheckKingCheck) << std::endl;
				dHistory.push_back("King is in check: " + std::to_string(CheckKingCheck));
				if (CheckKingCheck == true)
				{
					if (CurrentColorIsWhite == true)
					{
						if (CheckBoard[iMoveTo] == 'x')
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
						if (CheckBoard[iMoveTo] == 'x')
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

}
void SetPiece(int iType, bool bWhitePiece, int iPieceNum)
{
	if (iType == 0)	//	for KING pieces
	{
			this->iType = 0;
			this->iValue = 0;
			this->bWhitePiece = bWhitePiece;
			this->iMoves = 0;

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
			this->iMoves = 0;

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
			this->iMoves = 0;

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
			this->iMoves = 0;

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
			this->iMoves = 0;

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
			this->iMoves = 0;

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
	char GetCVisual(void)
	{
		return(this->cVisual);
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
	// initalize debug files / necessary files
	std::ofstream checkfiles;
	for (unsigned int i = 0; i < 500; i++)
	{
		checkfiles.open("GN" + std::to_string(i));
		if (!checkfiles.is_open())
		{
			GameNumber = i;
			break;
		}
	}
	dHistory.push_back("Current game number is " + std::to_string(GameNumber) + ".");
	
	for (int i = 0; i < iBoardSize; i++)
	{
		iBoard[i] = ' ';
		CheckBoard[i] = ' ';
		sBoard[i] = " ";

		CheckmateBoard[i] = ' ';
		cMoveBoard[i] = ' ';
	}
	sSidePrint.push_back("\tGame Commands\t\tM O V E  H I S T O R Y");
	sSidePrint.push_back("\thelp\t\t");
	sSidePrint.push_back("\tmove 'from' 'to'");
	sSidePrint.push_back("\tmcheck 'from'\t");

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

	CurrentColorIsWhite = true;	//	reset game variables 
	wMoves = 0;
	bMoves = 0;
	bWhiteKingInCheck = false;
	bBlackKingInCheck = false;
	bCheckmate = false;
	return;
}

int main( void )
{
	bool game = true;
	bool bGameWin = false;

	char cUsrInput = '0';
	char gameMode = '0';


	while (game == true)
	{
		bool InputFalse = true;

		for (int i = 0; i < mHistory.size(); i++)
		{
			mHistory.pop_back();
		}
		for (int i = 0; i < sSidePrint.size(); i++)
		{
			sSidePrint.pop_back();
		}
		if (!bRematch)
		{
			std::cout << "Weclome to DA Console Chess!" << std::endl;
			std::cout << "Is the below text readable? (Yes/No)" << std::endl;
			std::cout << "\t\033[4;31mT\033[32me\033[34ms\033[37mt\033[0m" << std::endl;

			std::cout << "This choice will effect the entire game." << std::endl;
			cUsrInput = cInputValidation();
			if (cUsrInput == 'y' || cUsrInput == 'Y')
			{
				bGraphics = true;
			}
			else
			{
				bGraphics = false;
			}
			dHistory.push_back("INFO: bGrapics is " + std::to_string(bGraphics));


			while (InputFalse == true)
			{
				if (bGraphics == true)
				{
					std::cout << "Would you like a \033[4mS\033[0mmall or \033[4mL\033[0marge game board?" << std::endl;
				}
				else
				{
					std::cout << "Would you like a Small or Large game board?" << std::endl;
				}
				cUsrInput = cInputValidation();
				if (cUsrInput == 'l')
				{
					boardType = 'l';
					dHistory.push_back("INFO: boardType: 'l'");
					InputFalse = false;
				}
				else if (cUsrInput == 's')
				{
					boardType = 's';
					dHistory.push_back("INFO: boardType: 's'");
					InputFalse = false;
				}
				else
				{
					std::cerr << "You need to enter either S or L!" << std::endl;
					dHistory.push_back("ERR: Invalid boardType.");
				}
			}	//	END InputFalse
		}
		vGameInit();
		dHistory.push_back("Game Initalized.");
		if (!bRematch)
		{
			InputFalse = true;
			while (InputFalse == true)
			{
				if (bGraphics == true)
				{
					std::cout << "Would you like \033[4ms\033[0mingle or \033[4mm\033[0multiplayer?" << std::endl;
				}
				else
				{
					std::cout << "Would you like Single or Multiplayer?" << std::endl;
				}
				cUsrInput = cInputValidation();
				if (cUsrInput == 's' || cUsrInput == 'S' || cUsrInput == '1')
				{
					gameMode = 's';
					dHistory.push_back("INFO: gameMode: 's'");
					InputFalse = false;
				}
				else if (cUsrInput == 'm' || cUsrInput == 'M' || cUsrInput == '2')
				{
					gameMode = 'm';
					dHistory.push_back("INFO: gameMode: 'm'");
					InputFalse = false;
				}
				else
				{
					std::cerr << "That gamemode doesn't exist!\n\n" << std::endl;
					dHistory.push_back("ERR: Invalid gameMode.");
				}
			}	//	END InputFalse
		}
		bRematch = false;
		if (gameMode == 's')	//	SINGLE PLAYER
		{
			bGameWin = bSinglePlayer();
		}
		if (gameMode == 'm')	//	MULTI PLAYER
		{
			bGameWin = bMultiPlayer();
		}

		if (!bRematch)
		{
			std::cout << "Would you like to keep playing?" << std::endl;
			cUsrInput = cInputValidation();
			if (cUsrInput == 'y' || cUsrInput == 'Y')
			{
				game = true;
			}
			else
			{
				std::cout << "Thanks for playing!\n\n" << std::endl;
				game = false;
			}
		}

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

void vDebug()
{
	if (iDebugLevel == 1)
	{
		for (unsigned int i = 0; i < dHistory.size(); i++)
		{
			std::cout << "\t" << i << ".\t" << dHistory.at(i) << std::endl;
		}
	}
	else if (iDebugLevel == 2)
	{
		std::ofstream debugmain;
		debugmain.open("GN" + std::to_string(GameNumber) + " DEBUG", std::fstream::app);
		if (debugmain.is_open())
		{
			for (unsigned int i = dHistoryReadNumber; i < dHistory.size(); i++)
			{
				debugmain << "\t" << i << ".\t" << dHistory.at(i) << std::endl;
				dHistoryReadNumber = i;
			}
			debugmain.close();
			dHistoryNumber++;
		}
		else
		{
			dHistory.push_back("ERR: Failed to open debug file");
			std::cerr << "Failed to open debug file!" << std::endl;
		}
	}
	else if (iDebugLevel == 3)
	{
		std::ofstream debugmain;
		debugmain.open("main.dbg");
		if (debugmain.is_open())
		{
			for (unsigned int i = 0; i < dHistory.size(); i++)
			{
				std::cout << "\t" << i << ".\t" << dHistory.at(i) << std::endl;
				debugmain << "\t" << i << ".\t" << dHistory.at(i) << std::endl;
			}
			debugmain.close();
		}
		else
		{
			dHistory.push_back("ERR: Failed to open debug file");
			std::cerr << "Failed to open debug file!" << std::endl;
		}
	}
}

bool bSinglePlayer()		//	--------------------------	SINGLE PLAYER GAME	-------------------------------------------------------
{
	bGameStatus = true;
	int GameStatusLoop = 0;
	while (bGameStatus == true)
	{
		dHistory.push_back("--------------------------------------------------- Loop number: " + std::to_string(GameStatusLoop) + " ----------------------------");
		dHistory.push_back("bGameStatus loop: " + std::to_string(GameStatusLoop));
		printBoard();
		std::cout << "\n\tEnter a command > ";
		vUsrInput();
		GameStatusLoop++;
		vDebug();
		if (bCheckmate == true)
		{
			printBoard();
			if (bWhiteKingInCheck == true)
			{
				vGameLose();
			}
			else if (bBlackKingInCheck == true)
			{
				vGameWin();
			}
			bGameStatus = false;
		}
		
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
		dHistory.push_back("--------------------------------------------------- Loop number: " + std::to_string(GameStatusLoop) + " -----------------------------");
		dHistory.push_back("bGameStatus loop: " + std::to_string(GameStatusLoop));
		printBoard();
		std::cout << "\n\tEnter a command > ";
		vUsrInput();
		GameStatusLoop++;
		vDebug();
		if (bCheckmate == true)
		{
			printBoard();
			vGameWin();
			bGameStatus = false;
		}
	}
	dHistory.push_back("Game Ended on loop " + std::to_string(GameStatusLoop));
	return 0;
}	//	END OF bMultiPlayer

void vGameWin()
{
	std::cout << std::endl;
	if (bWhiteKingInCheck == true)
	{
		std::cout << "Black ";
	}
	else if (bBlackKingInCheck == true)
	{
		std::cout << "White ";
	}
	std::cout << "W O N the game!" << std::endl;
}
void vGameLose()
{
	std::cout << std::endl;

	if (bWhiteKingInCheck == true)
	{
		std::cout << "Black ";
	}
	else if (bBlackKingInCheck == true)
	{
		std::cout << "White ";
	}
	std::cout << "lost the game!" << std::endl;
	std::cout << "My AI is too good for ya!" << std::endl;
}

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
		vInputSanitization(&cThree);
	}
	else
	{
		sErrorMsg = "You didn't type anything!";
		return;
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
		vInputSanitization(&cTwo);
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
		vInputSanitization(&cOne);
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

	if (cOne == "exit")
	{
		std::cout << "Are you sure you want to end this game?" << std::endl;
		char input = cInputValidation();
		if (input == 'n' || input == 'N')
		{
			return;
		}
		else
		{
			bGameStatus = false;
			return;
		}

	}
	else if (cOne == "help")
	{
		if (cTwo == "")
		{
			dHistory.push_back("command HELP issued.");
			std::cout << "\n\n\t\tFull list of commands:" << std::endl;
			std::cout << "\t    the ' character indicates a variable input, like A5 or a command" << std::endl;
			std::cout << "\tcheckmate\t\tChecks for checkmate, and ends the match" << std::endl;
			std::cout << "\tcolor\t\tChanges piece color on board" << std::endl;
			std::cout << "\tdebug\t\tControls debug settings" << std::endl;
			std::cout << "\texit\t\tExit's to the main menu, and loses all game progress" << std::endl;
			std::cout << "\thelp 'command'\tLists all commands, and provides context for commmands" << std::endl;
			std::cout << "\thistory\t\tPrints full game history to screen" << std::endl;
			std::cout << "\tmove 'from' to'\tMoves the 'from' piece to the 'to' location. Example: move A7 A5." << std::endl;
			std::cout << "\tcmove 'from'\tCheck Move - Shows the valid moves of the 'from' piece. Example: cmove A7" << std::endl;
			std::cout << "\trematch\t\tEnds the current match and starts a new one." << std::endl;
			std::cout << "\twhat\t\t(debug) Says name of piece at current location on all boards" << std::endl;
		}
		else if (cTwo == "checkmate")
		{
			dHistory.push_back("command HELP CHECKMATE issued.");
			std::cout << "\n\n\t\t'checkmate' Command help:" << std::endl;
			std::cout << "\tThe 'checkmate' command is used to check for checkmate, and end the current match." << std::endl;
			std::cout << "\tThe syntax for the checkmate command is as follows:" << std::endl;
			std::cout << "\t\tcheckmate" << std::endl;
			std::cout << "\tI believe in you." << std::endl;
		}
		else if (cTwo == "color")
		{
			if (bGraphics == true)
			{
				if (cThree == "options")
				{
					dHistory.push_back("command HELP COLOR OPTIONS issued.");
					std::cout << "\tblack tile:\twhite tile:" << std::endl;
					std::cout << "\t1.\033[1;40;31m red		\033[0m|\t\033[1;47;31mred		\033[0m" << std::endl;
					std::cout << "\t2.\033[1;40;32m green	\033[0m|\t\033[1;47;32mgreen	\033[0m" << std::endl;
					std::cout << "\t3.\033[1;40;33m yellow	\033[0m|\t\033[1;47;33myellow	\033[0m" << std::endl;
					std::cout << "\t4.\033[1;40;34m blue	\033[0m\t|\t\033[1;47;34mblue		\033[0m" << std::endl;
					std::cout << "\t5.\033[1;40;35m magenta	\033[0m|\t\033[1;47;35mmagenta	\033[0m" << std::endl;
					std::cout << "\t6.\033[1;40;36m cyan	\033[0m\t|\t\033[1;47;36mcyan		\033[0m" << std::endl;
					std::cout << "\t7.\033[1;40;91m bRed	\033[0m\t|\t\033[1;47;91mbRed		\033[0m" << std::endl;
					std::cout << "\t8.\033[1;40;92m bGreen	\033[0m|\t\033[1;47;92mbGreen	\033[0m" << std::endl;
					std::cout << "\t9.\033[1;40;93m bYellow	\033[0m|\t\033[1;47;93mbYellow	\033[0m" << std::endl;
					std::cout << "\t10.\033[1;40;94m bBlue	\033[0m|\t\033[1;47;94mbBlue	\033[0m" << std::endl;
					std::cout << "\t11.\033[1;40;95m bMagenta\033[0m\t|\t\033[1;47;95mbMagenta	\033[0m" << std::endl;
					std::cout << "\t12.\033[1;40;96m bCyan	\033[0m|\t\033[1;47;96mbCyan	\033[0m" << std::endl;
				}
				else
				{
					dHistory.push_back("command HELP COLOR issued.");
					std::cout << "\n\n\t\t'color' Command help:" << std::endl;
					std::cout << "\tThe 'color' command is used to change the color of the pieces to your liking." << std::endl;
					std::cout << "\tThe syntax for the color command is as follows:" << std::endl;
					std::cout << "\t\tcolor color to change to" << std::endl;
					std::cout << "\t\tcolor      blue" << std::endl;
					std::cout << "\tType 'help color options' to view all color options!" << std::endl;
				}
			}
			else
			{
				std::cerr << "Your current configuration doesn't support color changing!" << std::endl;
				dHistory.push_back("ERR: Color cannot be changed while bGraphics is false!");
			}
		}
		else if (cTwo == "debug")
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
		else if (cTwo == "exit")
		{
			dHistory.push_back("command HELP EXIT issued.");
			std::cout << "\n\n\t\t'exit' Command help:" << std::endl;
			std::cout << "\tThe 'exit' command is used to return to the main menu, and end the current match." << std::endl;
			std::cout << "\tThe syntax for the exit command is as follows:" << std::endl;
			std::cout << "\t\texit" << std::endl;
			std::cout << "\tI believe in you." << std::endl;
		}
		else if (cTwo == "history")
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
		else if (cTwo == "move")
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
		else if (cTwo == "mcheck" || cTwo == "cmove")
		{
			dHistory.push_back("command HELP CMOVE issued.");
			std::cout << "\n\n\t\t'cmove' Command help:" << std::endl;
			std::cout << "\tThe 'cmove' or 'check move' command is used to check the available moves for the selected piece." << std::endl;
			std::cout << "\tThe syntax for the cmove command is as follows:" << std::endl;
			std::cout << "\t\tcmove 'from'" << std::endl;
			std::cout << "\t\tcmove   A7" << std::endl;
			std::cout << "\tThis will show you all of the available moves for the piece located at A7." << std::endl;
			std::cout << "\t\tSpecial Uses:" << std::endl;
			std::cout << "\tGetting a fresh view of the board" << std::endl;
		}
		else if (cTwo == "rematch")
		{
			dHistory.push_back("command HELP REMATCH issued.");
			std::cout << "\n\n\t\t'rematch' Command help:" << std::endl;
			std::cout << "\tThe 'rematch' command is used to end the current game, and start a new one." << std::endl;
			std::cout << "\tThe syntax for the rematch command is as follows:" << std::endl;
			std::cout << "\t\trematch" << std::endl;
			std::cout << "\tI Believe in you." << std::endl;
		}
		else if (cTwo == "what")
		{
			dHistory.push_back("command HELP WHAT issued.");
			std::cout << "\n\n\t\t'what' Command help:" << std::endl;
			std::cout << "\tThe 'what' command is a debug command to show what values are at specific locations on the board" << std::endl;
			std::cout << "\tThe syntax for the what command is as follows:" << std::endl;
			std::cout << "\t\twhat location" << std::endl;
			std::cout << "\t\twhat    c0" << std::endl;
			std::cout << "\tThat's it." << std::endl;
		}
		else
		{
			dHistory.push_back("command HELP \"" + cTwo + "\" was not found.");
			sErrorMsg = "Your command wasn't found.";
			return;
		}
		dHistory.push_back("command HELP " + cTwo + " issued.");
		vPause();
		return;
	}
	else if (cOne == "color")
	{
		if (bGraphics)
		{
			if (cTwo == "")
			{
				dHistory.push_back("command COLOR issued.");
				std::cout << "Current Color is: \033[" << iPieceColor << "m!\033[0m or " << iPieceColor << "." << std::endl;
				return;
			}
			else if (cTwo == "r" || cTwo == "red" || cTwo == "31" || cTwo == "1")
			{
				iPieceColor = 31;
			}
			else if (cTwo == "g" || cTwo == "green" || cTwo == "32" || cTwo == "2")
			{
				iPieceColor = 32;
			}
			else if (cTwo == "y" || cTwo == "yellow" || cTwo == "33" || cTwo == "3")
			{
				iPieceColor = 33;
			}
			else if (cTwo == "b" || cTwo == "blue" || cTwo == "34" || cTwo == "4")
			{
				iPieceColor = 34;
			}
			else if (cTwo == "m" || cTwo == "magenta" || cTwo == "35" || cTwo == "5")
			{
				iPieceColor = 35;
			}
			else if (cTwo == "c" || cTwo == "cyan" || cTwo == "36" || cTwo == "6")
			{
				iPieceColor = 36;
			}
			else if (cTwo == "br" || cTwo == "bred" || cTwo == "91" || cTwo == "7")
			{
				iPieceColor = 91;
			}
			else if (cTwo == "bg" || cTwo == "bgreen" || cTwo == "92" || cTwo == "8")
			{
				iPieceColor = 92;
			}
			else if (cTwo == "by" || cTwo == "byellow" || cTwo == "93" || cTwo == "9")
			{
				iPieceColor = 93;
			}
			else if (cTwo == "bb" || cTwo == "bblue" || cTwo == "94" || cTwo == "10")
			{
				iPieceColor = 94;
			}
			else if (cTwo == "bm" || cTwo == "bmagenta" || cTwo == "95" || cTwo == "11")
			{
				iPieceColor = 95;
			}
			else if (cTwo == "bc" || cTwo == "bcyan" || cTwo == "96" || cTwo == "12")
			{
				iPieceColor = 96;
			}
			else
			{
				std::cerr << "That color could not be found!" << std::endl;
				std::cout << "Type 'help color options' to see all available colors." << std::endl;
				vPause();
				return;
			}
			std::cout << "Piece color changed to \033[" << iPieceColor << "m!\033[0m" << std::endl;
			dHistory.push_back("command COLOR issued as " + std::to_string(iPieceColor));
			vPause();
			return;
		}
		else
		{
			sErrorMsg = "Your settings don't allow for color";
		}
	}
	else if (cOne == "checkmate")
	{
		dHistory.push_back("command CHECKMATE issued.");
		//	the stuff for checkmate should go here
		sErrorMsg = "That command hasn't been implemented yet.";
		return;
	}
	else if (cOne == "debug")
	{
		dHistory.push_back("command DEBUG issued.");
		if (cTwo == "0" || cTwo == "zero")
		{
			iDebugLevel = 0;
			dHistory.push_back("iDebugLevel set to 0.");
			std::cout << "Debug level set to 0!" << std::endl;
		}
		else if (cTwo == "1" || cTwo == "one")
		{
			iDebugLevel = 1;
			dHistory.push_back("iDebugLevel set to 1.");
			std::cout << "Debug level set to 1" << std::endl;
		}
		else if (cTwo == "2" || cTwo == "two")
		{
			iDebugLevel = 2;
			dHistory.push_back("iDebugLevel set to 2.");
			std::cout << "Debug level set to 2" << std::endl;
		}
		else if (cTwo == "3" || cTwo == "three")
		{
			iDebugLevel = 3;
			dHistory.push_back("iDebugLevel set to 3.");
			std::cout << "Debug level set to 3" << std::endl;
		}
		else if (cTwo == "print")
		{
			if (cThree == "check")
			{
				std::cout << "\t      A  B  C  D  E  F  G  H  "<< std::endl;
				std::cout << "\t    ==========================";
				for (int height = 0; height < iBoardHeight; height++)
				{
					std::cout << std::endl;
					std::cout << "\t " << height + 1 << " | ";
					for (int width = 0; width < iBoardWidth; width++)
					{
						int iBoardPrint = ((width + 1) + (height * iBoardHeight)) - 1;
						std::cout << " " << CheckBoard[iBoardPrint] << " ";
					}
				}
			}

		}
		else
		{
			sErrorMsg = "Improper Debug level";
		}
		vPause();
		return;
	}	//	end DEBUG
	else if (cOne == "history" || cOne == "hist" || cOne == "h")
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
				sErrorMsg = "You have no history to display.";
			}
		}
		else if (cTwo == "save" || cTwo == "s")
		{
			dHistory.push_back("command HISTORY SAVE issued.");

			std::ofstream historymain;
			historymain.open("GN" + std::to_string(GameNumber) + " HN " + std::to_string(mHistoryNumber));

			if (historymain.is_open())
			{
				for (unsigned int i = mHistoryReadNumber; i < mHistory.size(); i++)
				{
					historymain << "\t" << i << ".\t" << mHistory.at(i) << std::endl;
					mHistoryReadNumber = i;
				}
				historymain.close();
				mHistoryNumber++;
			}
			else
			{
				dHistory.push_back("ERR: Failed to open history file. GN" + std::to_string(GameNumber) + " HN " + std::to_string(mHistoryNumber));
				sErrorMsg = "Failed to open file!";
				return;
			}
			return;
		}
		else if (cTwo == "clear" || cTwo == "c")
		{
			if (mHistory.size() != 0)
			{
				dHistory.push_back("command HISTORY CLEAR issued.");
				for (size_t j = (mHistory.size()); j > 0; j--)
				{
					mHistory.pop_back();
				}
				mHistoryReadNumber = 0;
			}
			else
			{
				dHistory.push_back("ERR: No move history to clear!");
				sErrorMsg = "You have no history to clear!";
				vPause();
				return;
			}
		}
		else if (cTwo == "debug")
		{
			if (cThree == "save" || cThree == "s")
			{
				std::cout << "To enable saving debug history to a file, use the command 'debug 2' or 'help debug'" << std::endl;
				return;
			}
			else if (cThree == "clear" || cThree == "c")
			{
				if (dHistory.size() != 0)
				{
					dHistory.push_back("command HISTORY DEBUG CLEAR issued.");
					for (size_t j = (dHistory.size()); j > 0; j--)
					{
						dHistory.pop_back();
					}
					dHistoryReadNumber = 0;
					dHistory.push_back("command HISTORY DEBUG CLEAR issued sucessfully.");
				}
				else
				{
					sErrorMsg = "You have no history to clear!";
					dHistory.push_back("ERR: No debug history to clear!");
					return;
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
		vPause();
		return;
	}
	else if (cOne == "mcheck" || cOne == "cmove" || cOne == "cmoves")
	{
		int iAtIndex = 0;
		if (cTwo.size() == 2)
		{
			int iMovefWidth = 0;
			int iMovefHeight = 0;

			iMovefWidth = iFromCharToInt(cTwo, &iAtIndex);
			if (iAtIndex == 0)
			{
				iMovefHeight = cTwo.at(1) - '0';
			}
			else if (iAtIndex == 1)
			{
				iMovefHeight = cTwo.at(0) - '0';
			}
			iMoveFrom = ((iMovefWidth)+((iMovefHeight - 1) * iBoardHeight)) - 1;
			dHistory.push_back("command CMOVE issued.\tiMoveFrom: " + std::to_string(iMoveFrom) + " from Width: " + std::to_string(iMovefWidth) + " and Height: " + std::to_string(iMovefHeight));

			vMoveCheck();
			return;
		}
		else
		{
			dHistory.push_back("ERR: command CMOVE issued improperly.");
			sErrorMsg = "Improper use of the cmove command.";
			return;
		}
	}
	else if (cOne == "rematch")
	{
		dHistory.push_back("command REMATCH issued.");
		bGameStatus = false;
		bRematch = true;
		return;
	}
	else if (cOne == "move" || cOne == "mov" || cOne == "mv" || cOne == "m")
	{
	dHistory.push_back("command MOVE issued.");
		int iMovefWidth = 0;
		int iMovefHeight = 0;
		int iMovetWidth = 0;
		int iMovetHeight = 0;
		int iAtIndex = 0;

		if (cTwo.size() == 2 && cThree.size() == 2)
		{
			iMovefWidth = iFromCharToInt(cTwo, &iAtIndex);
			if (iAtIndex == 0)
			{
				iMovefHeight = cTwo.at(1) - '0';
			}
			else if (iAtIndex == 1)
			{
				iMovefHeight = cTwo.at(0) - '0';
			}
			iMoveFrom = ((iMovefWidth)+((iMovefHeight - 1) * iBoardHeight)) - 1;

			iMovetWidth = iFromCharToInt(cThree, &iAtIndex);
			if (iAtIndex == 0)
			{
				iMovetHeight = cThree.at(1) - '0';
			}
			else if (iAtIndex == 1)
			{
				iMovetHeight = cThree.at(0) - '0';
			}
			iMoveTo = ((iMovetWidth)+((iMovetHeight - 1) * iBoardHeight)) - 1;

			dHistory.push_back("INFO: iMoveFrom: " + std::to_string(iMoveFrom) + " from Width: " + std::to_string(iMovefWidth) + " and Height: " + std::to_string(iMovefHeight) + "\tiMoveTo: " + std::to_string(iMoveTo) + " from Width: " + std::to_string(iMovetWidth) + " and Height: " + std::to_string(iMovetHeight));

			bSearchObj();	//	call function for moving piece
			return;
		}
		else
		{
			dHistory.push_back("ERR: Invalid move location " + cTwo + " to " + cThree + ".");
			sErrorMsg = "Invalid move location.";
			return;
		}
	}	//	END IF command is "move" 
	else if (cOne == "what")
	{
		dHistory.push_back("command WHAT issued");
		int iCheckLocation = 0;
		int iCheckWidth = 0;
		int iCheckHeight = 0;
		int iAtIndex = 0;

		if (cTwo.size() != 2)
		{
			dHistory.push_back("ERR: Invalid board location");
			sErrorMsg = "Invalid location";
			return;
		}

		iCheckWidth = iFromCharToInt(cTwo, &iAtIndex);
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
		std::cout << "cMoveCheck: \"" << cMoveBoard[iCheckLocation] << "\"" << std::endl;
		vPause();
		return;
	}


	//clear stream
	dHistory.push_back("ERR: Unknown command issued...");
	std::cerr << "\tUnknown command!" << std::endl;
	std::cout << "\tTry typing 'help' for instructions." << std::endl;
	vPause();

	return;


}	//	END UsrInput

void vInputSanitization(std::string *cInput)
{
	std::string cValue = *cInput;
	std::string tmpString = "";
	for (int i = 0; i < cValue.size(); i++)
	{
		if (cValue.at(i) == 'A')
			tmpString = tmpString + 'a';
		else if (cValue.at(i) == 'B')
			tmpString = tmpString + 'b';
		else if (cValue.at(i) == 'C')
			tmpString = tmpString + 'c';
		else if (cValue.at(i) == 'D')
			tmpString = tmpString + 'd';
		else if (cValue.at(i) == 'E')
			tmpString = tmpString + 'e';
		else if (cValue.at(i) == 'F')
			tmpString = tmpString + 'f';
		else if (cValue.at(i) == 'G')
			tmpString = tmpString + 'g';
		else if (cValue.at(i) == 'H')
			tmpString = tmpString + 'h';
		else if (cValue.at(i) == 'I')
			tmpString = tmpString + 'i';
		else if (cValue.at(i) == 'J')
			tmpString = tmpString + 'j';
		else if (cValue.at(i) == 'K')
			tmpString = tmpString + 'k';
		else if (cValue.at(i) == 'L')
			tmpString = tmpString + 'l';
		else if (cValue.at(i) == 'M')
			tmpString = tmpString + 'm';
		else if (cValue.at(i) == 'N')
			tmpString = tmpString + 'n';
		else if (cValue.at(i) == 'O')
			tmpString = tmpString + 'o';
		else if (cValue.at(i) == 'P')
			tmpString = tmpString + 'p';
		else if (cValue.at(i) == 'Q')
			tmpString = tmpString + 'q';
		else if (cValue.at(i) == 'R')
			tmpString = tmpString + 'r';
		else if (cValue.at(i) == 'S')
			tmpString = tmpString + 's';
		else if (cValue.at(i) == 'T')
			tmpString = tmpString + 't';
		else if (cValue.at(i) == 'U')
			tmpString = tmpString + 'u';
		else if (cValue.at(i) == 'V')
			tmpString = tmpString + 'v';
		else if (cValue.at(i) == 'W')
			tmpString = tmpString + 'w';
		else if (cValue.at(i) == 'X')
			tmpString = tmpString + 'x';
		else if (cValue.at(i) == 'Y')
			tmpString = tmpString + 'y';
		else if (cValue.at(i) == 'Z')
			tmpString = tmpString + 'z';
		else
			tmpString = tmpString + cValue.at(i);
	}
	*cInput = tmpString;
}

int iFromCharToInt(std::string cValue, int* iAtIndex)	// convert from char to integer
{
	int iMoveWidth = 0;
	for (int i = 0; i < 2; i++)
	{
		char cCompare = cValue.at(i);
		if (cCompare == 'A' || cCompare == 'a')
		{
			*iAtIndex = i;
			iMoveWidth = 1;
		}
		else if (cCompare == 'B' || cCompare == 'b')
		{
			*iAtIndex = i;
			iMoveWidth = 2;
		}
		else if (cCompare == 'C' || cCompare == 'c')
		{
			*iAtIndex = i;
			iMoveWidth = 3;
		}
		else if (cCompare == 'D' || cCompare == 'd')
		{
			*iAtIndex = i;
			iMoveWidth = 4;
		}
		else if (cCompare == 'E' || cCompare == 'e')
		{
			*iAtIndex = i;
			iMoveWidth = 5;
		}
		else if (cCompare == 'F' || cCompare == 'f')
		{
			*iAtIndex = i;
			iMoveWidth = 6;
		}
		else if (cCompare == 'G' || cCompare == 'g')
		{
			*iAtIndex = i;
			iMoveWidth = 7;
		}
		else if (cCompare == 'H' || cCompare == 'h')
		{
			*iAtIndex = i;
			iMoveWidth = 8;
		}
	}
	return iMoveWidth;
}	//	END iFromCharToInt
char cFromIntToChar(int cValue, int* cHeight)		//	convert from integer to char
{
	char cWidth = '0';

	for (int i = 1; i <= iBoardHeight; i++)
	{
		if (cValue <= (i * iBoardHeight) - 1)
		{
			*cHeight = i;
		}
	}

	if (cValue % iBoardWidth == 0)
	{
		cWidth = 'A';
	}
	else if (cValue % iBoardWidth == 1)
	{
		cWidth = 'B';
	}
	else if (cValue % iBoardWidth == 2)
	{
		cWidth = 'C';
	}
	else if (cValue % iBoardWidth == 3)
	{
		cWidth = 'D';
	}
	else if (cValue % iBoardWidth == 4)
	{
		cWidth = 'E';
	}
	else if (cValue % iBoardWidth == 5)
	{
		cWidth = 'F';
	}
	else if (cValue % iBoardWidth == 6)
	{
		cWidth = 'G';
	}
	else if (cValue % iBoardWidth == 7)
	{
		cWidth = 'H';
	}
	return cWidth;
}

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
}

bool bIsKingInCheck()
{
	for (int i = 0; i < iBoardSize; i++)
	{
		CheckBoard[i] = ' ';
	}
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
		if (CheckBoard[iBlackKingLocation] == 'x')
		{
			dHistory.push_back("INFO: BLACK King is in check!");
			return true;
		}
	}
	else
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
		if (CheckBoard[iWhiteKingLocation] == 'x')
		{
			dHistory.push_back("INFO: WHITE King in in check!");
			return true;
		}
	}
	return false;
}	//	END bIsKingInCheck

bool bIsKingInCheckmate()
{
	bool lCheckmate = false;
	for (unsigned int i = 0; i < iBoardSize; i++)
	{
		CheckmateBoard[i] = CheckBoard[i];
		CheckBoard[i] = ' ';
	}

	if (bWhiteKingInCheck == true)
	{
		wKing.SetKingInCheck();
		for (unsigned int i = 0; i < iBoardSize; i++)
		{
			if (CheckBoard[i] == 'x' && CheckmateBoard[i] == ' ')
			{
				dHistory.push_back("Possible move at " + std::to_string(i));
			}
			else
			{
				lCheckmate = true;
			}
		}
	}
	else if (bBlackKingInCheck == true)
	{
		bKing.SetKingInCheck();
		for (unsigned int i = 0; i < iBoardSize; i++)
		{
			if (CheckBoard[i] == 'x' && CheckmateBoard[i] == ' ')
			{
				dHistory.push_back("Possible move at " + std::to_string(i));
			}
			else
			{
				lCheckmate = true;
			}
		}
	}
	for (unsigned int i = 0; i < iBoardSize; i++)
	{
		CheckBoard[i] = CheckmateBoard[i];
		CheckmateBoard[i] = ' ';
	}

	if (lCheckmate == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void vMoveCheck()
{
	bool lValidMove = false;
	std::string pName = sBoard[iMoveFrom];

	for (unsigned int i = 0; i < iBoardSize; i++)
	{
		CheckBoard[i] = ' ';
	}

	if (pName == "wKing")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		wKing.SetKingInCheck();
	}
	else if (pName == "bKing")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		bKing.SetKingInCheck();
	}
	else if (pName == "wQueen")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		wQueen.SetKingInCheck();
	}
	else if (pName == "bQueen")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		bQueen.SetKingInCheck();
	}
	else if (pName == "wRook1")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		wRook1.SetKingInCheck();
	}
	else if (pName == "wRook2")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		wRook2.SetKingInCheck();
	}
	else if (pName == "bRook1")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		bRook1.SetKingInCheck();
	}
	else if (pName == "bRook2")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		bRook2.SetKingInCheck();
	}
	else if (pName == "wBishop1")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		wBishop1.SetKingInCheck();
	}
	else if (pName == "wBishop2")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		wBishop2.SetKingInCheck();
	}
	else if (pName == "bBishop1")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		bBishop1.SetKingInCheck();
	}
	else if (pName == "bBishop2")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		bBishop2.SetKingInCheck();
	}
	else if (pName == "wKnight1")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		wKnight1.SetKingInCheck();
	}
	else if (pName == "wKnight2")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		wKnight2.SetKingInCheck();
	}
	else if (pName == "bKnight1")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		bKnight1.SetKingInCheck();
	}
	else if (pName == "bKnight2")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		bKnight2.SetKingInCheck();
	}
	else if (pName == "wPawn1")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		wPawn1.SetKingInCheck();
	}
	else if (pName == "wPawn2")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		wPawn2.SetKingInCheck();
	}
	else if (pName == "wPawn3")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		wPawn3.SetKingInCheck();
	}
	else if (pName == "wPawn4")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		wPawn4.SetKingInCheck();
	}
	else if (pName == "wPawn5")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		wPawn5.SetKingInCheck();
	}
	else if (pName == "wPawn6")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		wPawn6.SetKingInCheck();
	}
	else if (pName == "wPawn7")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		wPawn7.SetKingInCheck();
	}
	else if (pName == "wPawn8")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		wPawn8.SetKingInCheck();
	}
	else if (pName == "bPawn1")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		bPawn1.SetKingInCheck();
	}
	else if (pName == "bPawn2")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		bPawn2.SetKingInCheck();
	}
	else if (pName == "bPawn3")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		bPawn3.SetKingInCheck();
	}
	else if (pName == "bPawn4")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		bPawn4.SetKingInCheck();
	}
	else if (pName == "bPawn5")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		bPawn5.SetKingInCheck();
	}
	else if (pName == "bPawn6")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		bPawn6.SetKingInCheck();
	}
	else if (pName == "bPawn7")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		bPawn7.SetKingInCheck();
	}
	else if (pName == "bPawn8")
	{
		dHistory.push_back("INFO: Piece at iMoveFrom is: \"" + pName + "\".");
		bPawn8.SetKingInCheck();
	}
	else
	{
		dHistory.push_back("ERR: No piece at " + std::to_string(iMoveFrom));
		sErrorMsg = "There isn't a piece there!";
	}

	for (unsigned int i = 0; i < iBoardSize; i++)
	{
		cMoveBoard[i] = CheckBoard[i];
		CheckBoard[i] = ' ';
	}
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
	std::string sScore;
	if (bGraphics == true)
	{
		sScore = "\tScore:\t \033[1;107;90mWHITE : " + std::to_string(iWhiteScore) + "\033[0m\t\033[1;100;97mBLACK : " + std::to_string(iBlackScore) + "\033[0m";
	}
	else
	{
		sScore = "\tScore:\t WHITE : " + std::to_string(iWhiteScore) + "\tBLACK : " + std::to_string(iBlackScore);
	}
	if (CurrentColorIsWhite == true)
	{
		if (bGraphics == true)
		{
			sTurn = "\033[1;107;90mWHITE\033[0m (Uppercase)";
		}
		else
		{
			sTurn = "WHITE (Uppercase)";
		}
		dHistory.push_back("INFO: CurrentColorIsWhite is TRUE");
	}
	else
	{
		if (bGraphics == true)
		{
			sTurn = "\033[1;100;97mBLACK\033[0m (lowercase)";
		}
		else
		{
			sTurn = "black (lowercase)";
		}
		dHistory.push_back("INFO: CurrentColorIsWhite is FALSE");
	}



	if (boardType == 'l')
	{
		long unsigned int l = 0;
		bool whiteSpace = false;
		int iSpaceNum = 0;
		if (bGraphics == true) { std::cout << "\t\033[1;31m" << sErrorMsg << "\033[0m" << std::endl; }
		else { std::cout << "\t" << sErrorMsg << std::endl; }
		std::cout << "\tc u r r e n t  t u r n: " << sTurn << std::endl;
		std::cout << "\t       A    B    C    D    E    F    G    H    " << sScore << std::endl;
		std::cout << "\t    ========================================== "<< sSidePrint[0];

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
						if (bGraphics == true)
						{
							if (bWhiteKingInCheck == true && iBoard[iBoardPrint] == 'K')
							{
								std::cout << "\033[1;41m  \033[1;" << iPieceColor << "m" << iBoard[iBoardPrint] << "  \033[0m";
							}
							else if (bBlackKingInCheck == true && iBoard[iBoardPrint] == 'k')
							{
								std::cout << "\033[1;41m  \033[1;" << iPieceColor << "m" << iBoard[iBoardPrint] << "  \033[0m";
							}
							else if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] == 'x') && (iBoard[iBoardPrint] == ' '))
							{
								std::cout << "\033[1;42m  \033[1;" << iPieceColor << "m" << iBoard[iBoardPrint] << "  \033[0m";
							}
							else
							{
								std::cout << "\033[1;47m  \033[1;" << iPieceColor << "m" << iBoard[iBoardPrint] << "  \033[0m";
							}
						}
						else
						{
							if (bWhiteKingInCheck == true && iBoard[iBoardPrint] == 'K')
							{
								std::cout << "##" << iBoard[iBoardPrint] << "##";
							}
							else if (bBlackKingInCheck == true && iBoard[iBoardPrint] == 'k')
							{
								std::cout << "##" << iBoard[iBoardPrint] << "##";
							}
							else if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] == 'x') && (iBoard[iBoardPrint] == ' '))
							{
								std::cout << "  *  ";
							}
							else
							{
								std::cout << "  " << iBoard[iBoardPrint] << "  ";
							}
						}
					}
					else
					{
						if (bGraphics == true)
						{
							if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] == 'x'))
							{
								if (iThisWhite == true && iBoard[iBoardPrint] != ' ')
								{
									if (iBoard[iBoardPrint] == 'k' || iBoard[iBoardPrint] == 'q' || iBoard[iBoardPrint] == 'r' || iBoard[iBoardPrint] == 'b' || iBoard[iBoardPrint] == 'n' || iBoard[iBoardPrint] == 'p')
										std::cout << "\033[1;41m \033[0m   \033[1;41m \033[0m";
									else
										std::cout << "\033[1;47m     \033[0m";
								}
								else if (iThisWhite == false && iBoard[iBoardPrint] != ' ')
								{
									if (iBoard[iBoardPrint] == 'K' || iBoard[iBoardPrint] == 'Q' || iBoard[iBoardPrint] == 'R' || iBoard[iBoardPrint] == 'B' || iBoard[iBoardPrint] == 'N' || iBoard[iBoardPrint] == 'P')
										std::cout << "\033[1;41m \033[0m   \033[1;41m \033[0m";
									else
										std::cout << "\033[1;47m     \033[0m";
								}
								else
								{
									std::cout << "\033[1;47m     \033[0m";
								}
							}
							else
							{
								std::cout << "\033[1;47m     \033[0m";
							}
						}
						else
						{
							if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] == 'x'))
							{
								if (iThisWhite == true && iBoard[iBoardPrint] != ' ')
								{
									if (iBoard[iBoardPrint] == 'k' || iBoard[iBoardPrint] == 'q' || iBoard[iBoardPrint] == 'r' || iBoard[iBoardPrint] == 'b' || iBoard[iBoardPrint] == 'n' || iBoard[iBoardPrint] == 'p')
										std::cout << "*   *";
									else
										std::cout << "     ";
								}
								else if (iThisWhite == false && iBoard[iBoardPrint] != ' ')
								{
									if (iBoard[iBoardPrint] == 'K' || iBoard[iBoardPrint] == 'Q' || iBoard[iBoardPrint] == 'R' || iBoard[iBoardPrint] == 'B' || iBoard[iBoardPrint] == 'N' || iBoard[iBoardPrint] == 'P')
										std::cout << "*   *";
									else
										std::cout << "     ";
								}
								else
								{
									std::cout << "     ";
								}
							}
							else
							{
								std::cout << "     ";
							}
						}
					}

					whiteSpace = true;
				}
				else if (whiteSpace == true)
				{
					if ((height - 1) % 3 == 0)
					{
						if (bGraphics == true)
						{
							if (bWhiteKingInCheck == true && iBoard[iBoardPrint] == 'K')
							{
								std::cout << "\033[1;41m  \033[1;" << iPieceColor << "m" << iBoard[iBoardPrint] << "  \033[0m";
							}
							else if (bBlackKingInCheck == true && iBoard[iBoardPrint] == 'k')
							{
								std::cout << "\033[1;41m  \033[1;" << iPieceColor << "m" << iBoard[iBoardPrint] << "  \033[0m";
							}
							else if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] == 'x') && (iBoard[iBoardPrint] == ' '))
							{
								std::cout << "\033[1;42m  \033[1;" << iPieceColor << "m" << iBoard[iBoardPrint] << "  \033[0m";
							}
							else
							{
								std::cout << "\033[1;40m  \033[1;" << iPieceColor << "m" << iBoard[iBoardPrint] << "  \033[0m";
							}
						}
						else
						{
							if (bWhiteKingInCheck == true && iBoard[iBoardPrint] == 'K')
							{
								std::cout << "##" << iBoard[iBoardPrint] << "##";
							}
							else if (bBlackKingInCheck == true && iBoard[iBoardPrint] == 'k')
							{
								std::cout << "##" << iBoard[iBoardPrint] << "##";
							}
							else if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] == 'x') && (iBoard[iBoardPrint] == ' '))
							{
								std::cout << "- * -";
							}
							else
							{
								std::cout << "- " << iBoard[iBoardPrint] << " -";
							}
						}
					}
					else
					{
						if (bGraphics == true)
						{
							if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] == 'x'))
							{
								if (iThisWhite == true && iBoard[iBoardPrint] != ' ')
								{
									if (iBoard[iBoardPrint] == 'k' || iBoard[iBoardPrint] == 'q' || iBoard[iBoardPrint] == 'r' || iBoard[iBoardPrint] == 'b' || iBoard[iBoardPrint] == 'n' || iBoard[iBoardPrint] == 'p')
										std::cout << "\033[1;41m \033[0m   \033[1;41m \033[0m";
									else
										std::cout << "\033[1;40m     \033[0m";
								}
								else if (iThisWhite == false && iBoard[iBoardPrint] != ' ')
								{
									if (iBoard[iBoardPrint] == 'K' || iBoard[iBoardPrint] == 'Q' || iBoard[iBoardPrint] == 'R' || iBoard[iBoardPrint] == 'B' || iBoard[iBoardPrint] == 'N' || iBoard[iBoardPrint] == 'P')
										std::cout << "\033[1;41m \033[0m   \033[1;41m \033[0m";
									else
										std::cout << "\033[1;40m     \033[0m";
								}
								else
								{
									std::cout << "\033[1;40m     \033[0m";
								}
							}
							else
							{
								std::cout << "\033[1;40m     \033[0m";
							}
						}
						else
						{
							if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] == 'x'))
							{
								if (iThisWhite == true && iBoard[iBoardPrint] != ' ')
								{
									if (iBoard[iBoardPrint] == 'k' || iBoard[iBoardPrint] == 'q' || iBoard[iBoardPrint] == 'r' || iBoard[iBoardPrint] == 'b' || iBoard[iBoardPrint] == 'n' || iBoard[iBoardPrint] == 'p')
										std::cout << "*---*";
									else
										std::cout << "-----";
								}
								else if (iThisWhite == false && iBoard[iBoardPrint] != ' ')
								{
									if (iBoard[iBoardPrint] == 'K' || iBoard[iBoardPrint] == 'Q' || iBoard[iBoardPrint] == 'R' || iBoard[iBoardPrint] == 'B' || iBoard[iBoardPrint] == 'N' || iBoard[iBoardPrint] == 'P')
										std::cout << "*---*";
									else
										std::cout << "-----";
								}
								else
								{
									std::cout << "-----";
								}
							}
							else
							{
								std::cout << "-----";
							}
						}
					}

					whiteSpace = false;
				}
				if (width == iBoardWidth)
				{
					std::cout << " |";
				}
			}
			if (height < iBoardHeight && height + 1 < sSidePrint.size())
				std::cout << sSidePrint[height + 1];
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
		for (unsigned int i = 0; i < iBoardSize; i++) cMoveBoard[i] = ' '; bMoveCheck = false;
		sErrorMsg = "";
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
		std::cout << "\n\n\n\n" << std::endl;
		if (bGraphics == true) {std::cout << "\t\033[1;31m" << sErrorMsg << "\033[0m" << std::endl; }
		else {std::cout << "\t" << sErrorMsg << std::endl; }

		std::cout << "\tcurrent  turn: " << sTurn << std::endl;;
		std::cout << "\t      A  B  C  D  E  F  G  H   " << sScore << std::endl;
		std::cout << "\t    ========================== " << sSidePrint[0];

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
					if (bGraphics == true)
					{
						if (bWhiteKingInCheck == true && iBoard[iBoardPrint] == 'K')
						{
							std::cout << "\033[1;41m\033[1;" << iPieceColor << "m";
						}
						else if (bBlackKingInCheck == true && iBoard[iBoardPrint] == 'k')
						{
							std::cout << "\033[1;41m\033[1;" << iPieceColor << "m";
						}
						else if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] == 'x'))
						{
							if (iThisWhite == true && iBoard[iBoardPrint] != ' ')
							{
								if (iBoard[iBoardPrint] == 'k' || iBoard[iBoardPrint] == 'q' || iBoard[iBoardPrint] == 'r' || iBoard[iBoardPrint] == 'b' || iBoard[iBoardPrint] == 'n' || iBoard[iBoardPrint] == 'p')
									std::cout << "\033[1;42m\033[1;" << iPieceColor << "m";
								else
									std::cout << "\033[1;47m\033[1;" << iPieceColor << "m";
							}
							else if (iThisWhite == false && iBoard[iBoardPrint] != ' ')
							{
								if (iBoard[iBoardPrint] == 'K' || iBoard[iBoardPrint] == 'Q' || iBoard[iBoardPrint] == 'R' || iBoard[iBoardPrint] == 'B' || iBoard[iBoardPrint] == 'N' || iBoard[iBoardPrint] == 'P')
									std::cout << "\033[1;42m\033[1;" << iPieceColor << "m";
								else
									std::cout << "\033[1;47m\033[1;" << iPieceColor << "m";
							}
							else
							{
								std::cout << "\033[1;42m\033[1;" << iPieceColor << "m";
							}
						}
						else
						{
							std::cout << "\033[1;47m\033[1;" << iPieceColor << "m";
						}
						std::cout << " " << iBoard[iBoardPrint] << " ";
						std::cout << "\033[0m";
					}
					else
					{
						if (bWhiteKingInCheck == true && iBoard[iBoardPrint] == 'K')
						{
							std::cout << "#" << iBoard[iBoardPrint] << "#";
						}
						else if (bBlackKingInCheck == true && iBoard[iBoardPrint] == 'k')
						{
							std::cout << "#" << iBoard[iBoardPrint] << "#";
						}
						else if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] == 'x'))
						{
							if (iThisWhite == true && iBoard[iBoardPrint] != ' ')
							{
								if (iBoard[iBoardPrint] == 'k' || iBoard[iBoardPrint] == 'q' || iBoard[iBoardPrint] == 'r' || iBoard[iBoardPrint] == 'b' || iBoard[iBoardPrint] == 'n' || iBoard[iBoardPrint] == 'p')
									std::cout << "*" << iBoard[iBoardPrint] << "*";
								else
									std::cout << " " << iBoard[iBoardPrint] << " ";
							}
							else if (iThisWhite == false && iBoard[iBoardPrint] != ' ')
							{
								if (iBoard[iBoardPrint] == 'K' || iBoard[iBoardPrint] == 'Q' || iBoard[iBoardPrint] == 'R' || iBoard[iBoardPrint] == 'B' || iBoard[iBoardPrint] == 'N' || iBoard[iBoardPrint] == 'P')
									std::cout << "*" << iBoard[iBoardPrint] << "*";
								else
									std::cout << " " << iBoard[iBoardPrint] << " ";
							}
							else
							{
								std::cout << " * ";
							}
						}
						else
						{
							std::cout << " " << iBoard[iBoardPrint] << " ";
						}
					}
					whiteSpace = true;
				}
				else if (whiteSpace == true)
				{
					if (bGraphics == true)
					{
						if (bWhiteKingInCheck == true && iBoard[iBoardPrint] == 'K')
						{
							std::cout << "\033[1;41m\033[1;" << iPieceColor << "m";
						}
						else if (bBlackKingInCheck == true && iBoard[iBoardPrint] == 'k')
						{
							std::cout << "\033[1;41m\033[1;" << iPieceColor << "m";
						}
						else if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] == 'x'))
						{
							if (iThisWhite == true && iBoard[iBoardPrint] != ' ')
							{
								if (iBoard[iBoardPrint] == 'k' || iBoard[iBoardPrint] == 'q' || iBoard[iBoardPrint] == 'r' || iBoard[iBoardPrint] == 'b' || iBoard[iBoardPrint] == 'n' || iBoard[iBoardPrint] == 'p')
									std::cout << "\033[1;42m\033[1;" << iPieceColor << "m";
								else
									std::cout << "\033[1;40m\033[1;" << iPieceColor << "m";
							}
							else if (iThisWhite == false && iBoard[iBoardPrint] != ' ')
							{
								if (iBoard[iBoardPrint] == 'K' || iBoard[iBoardPrint] == 'Q' || iBoard[iBoardPrint] == 'R' || iBoard[iBoardPrint] == 'B' || iBoard[iBoardPrint] == 'N' || iBoard[iBoardPrint] == 'P')
									std::cout << "\033[1;42m\033[1;" << iPieceColor << "m";
								else
									std::cout << "\033[1;40m\033[1;" << iPieceColor << "m";
							}
							else
							{
								std::cout << "\033[1;42m\033[1;" << iPieceColor << "m";
							}
						}
						else
						{
							std::cout << "\033[1;40m\033[1;" << iPieceColor << "m";
						}
						std::cout << " " << iBoard[iBoardPrint] << " ";
						std::cout << "\033[0m";
					}
					else
					{
						if (bWhiteKingInCheck == true && iBoard[iBoardPrint] == 'K')
						{
							std::cout << "#" << iBoard[iBoardPrint] << "#";
						}
						else if (bBlackKingInCheck == true && iBoard[iBoardPrint] == 'k')
						{
							std::cout << "#" << iBoard[iBoardPrint] << "#";
						}
						else if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] == 'x'))
						{
							if (iThisWhite == true && iBoard[iBoardPrint] != ' ')
							{
								if (iBoard[iBoardPrint] == 'k' || iBoard[iBoardPrint] == 'q' || iBoard[iBoardPrint] == 'r' || iBoard[iBoardPrint] == 'b' || iBoard[iBoardPrint] == 'n' || iBoard[iBoardPrint] == 'p')
									std::cout << "*" << iBoard[iBoardPrint] << "*";
								else
									std::cout << "=" << iBoard[iBoardPrint] << "=";
							}
							else if (iThisWhite == false && iBoard[iBoardPrint] != ' ')
							{
								if (iBoard[iBoardPrint] == 'K' || iBoard[iBoardPrint] == 'Q' || iBoard[iBoardPrint] == 'R' || iBoard[iBoardPrint] == 'B' || iBoard[iBoardPrint] == 'N' || iBoard[iBoardPrint] == 'P')
									std::cout << "*" << iBoard[iBoardPrint] << "*";
								else
									std::cout << "=" << iBoard[iBoardPrint] << "=";
							}
							else
								std::cout << " * ";
						}
						else
						{
							std::cout << "=" << iBoard[iBoardPrint] << "=";
						}
						
					}
					whiteSpace = false;
				}

			}
			if (height < iBoardHeight && height + 1 < sSidePrint.size())
				std::cout << sSidePrint[height + 1];
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
						std::cout << "\tMake a move!";
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
		for (unsigned int i = 0; i < iBoardSize; i++) {cMoveBoard[i] = ' '; bMoveCheck = false;}
		sErrorMsg = "";
		return;
	}
}	//	END OF PRINTBOARD



bool bKingLogic()		//---------------------------------------	KING LOGIC	-------------------------------------------	KING LOGIC	----------------------------------	-------------------------------------------	KING LOGIC	----------------------------------
{
	bool bKingInCheck = true;

	unsigned int pEquationDown = iThisPos + 8;
	unsigned int pEquationUp = iThisPos - 8;

	unsigned int pEquationLeft = iThisPos + 1;
	unsigned int pEquationRight = iThisPos - 1;

	unsigned int pEquationUpLeft = iThisPos - 9;
	unsigned int pEquationUpRight = iThisPos - 7;

	unsigned int pEquationDownLeft = iThisPos + 7;
	unsigned int pEquationDownRight = iThisPos + 9;


	if (pEquationDown >= 0 && pEquationDown <= iBoardSize)
	{
		if (bMoveCheck)
		{
			CheckBoard[pEquationDown] = 'x';
		}
		else
		{
			if (iMoveTo == pEquationDown && iThisWhite != bMoveToWhite)	//	move down
			{
				dHistory.push_back("INFO: King moved down");
				return true;
			}
		}
	}
	if (pEquationUp >= 0 && pEquationUp <= iBoardSize)
	{
		if (bMoveCheck)
		{
			CheckBoard[pEquationUp] = 'x';
		}
		else
		{
			if (iMoveTo == pEquationUp && iThisWhite != bMoveToWhite)	//	move up
			{
				dHistory.push_back("INFO: King moved up");
				return true;
			}
		}
	}
	if (pEquationLeft >= 0 && pEquationLeft <= iBoardSize)
	{
		for (unsigned int i = 0; i < iBoardSize; i++)
		{
			if ((iThisPos >= i * iBoardWidth) && (iThisPos <= (i * iBoardWidth) + (iBoardWidth - 1)) &&
				(pEquationLeft >= i * iBoardWidth) && (pEquationLeft <= (i * iBoardWidth) + (iBoardWidth - 1)))
			{
				if (bMoveCheck)
				{
					CheckBoard[pEquationLeft] = 'x';
				}
				else
				{
					if (iMoveTo == pEquationLeft && iThisWhite != bMoveToWhite)	//	move left
					{
						dHistory.push_back("INFO: King moved left");
						return true;
					}
				}
			}
		}
	}
	if (pEquationRight >= 0 && pEquationRight <= iBoardSize)
	{
		for (unsigned int i = 0; i < iBoardSize; i++)
		{
			if ((iThisPos >= i * iBoardWidth) && (iThisPos <= (i * iBoardWidth) + (iBoardWidth - 1)) &&
				(pEquationRight >= i * iBoardWidth) && (pEquationRight <= (i * iBoardWidth) + (iBoardWidth - 1)))
			{
				if (bMoveCheck)
				{
					CheckBoard[pEquationRight] = 'x';
				}
				else
				{
					if (iMoveTo == pEquationRight && iThisWhite != bMoveToWhite)	//	move right
					{
						dHistory.push_back("INFO: King moved right");
						return true;
					}
				}
			}
		}
	}
	if (pEquationDownLeft >= 0 && pEquationDownLeft <= iBoardSize)
	{
		for (unsigned int i = 0; i < iBoardSize; i++)
		{
			if ((iThisPos >= i * iBoardWidth) && (iThisPos <= (i * iBoardWidth) + (iBoardWidth - 1)) &&
				(pEquationDownLeft >= (i + 1) * iBoardWidth) && (pEquationDownLeft <= ((i + 1) * iBoardWidth) + (iBoardWidth - 1)))
			{
				if (bMoveCheck)
				{
					CheckBoard[pEquationDownLeft] = 'x';
				}
				else
				{
					if (iMoveTo == pEquationDownLeft && iThisWhite != bMoveToWhite)	//	move down left
					{
						dHistory.push_back("INFO: King moved down left");
						return true;
					}
				}
			}
		}
	}
	if (pEquationDownRight >= 0 && pEquationDownRight <= iBoardSize)
	{
		for (unsigned int i = 0; i < iBoardSize; i++)
		{
			if ((iThisPos >= i * iBoardWidth) && (iThisPos <= (i * iBoardWidth) + (iBoardWidth - 1)) &&
				(pEquationDownRight >= (i + 1) * iBoardWidth) && (pEquationDownRight <= ((i + 1) * iBoardWidth) + (iBoardWidth - 1)))
			{
				if (bMoveCheck)
				{
					CheckBoard[pEquationDownRight] = 'x';
				}
				else
				{
					if (iMoveTo == pEquationDownRight && iThisWhite != bMoveToWhite)	//	move down right
					{
						dHistory.push_back("INFO: King moved down right");
						return true;
					}
				}
			}
		}
	}
	if (pEquationUpLeft >= 0 && pEquationUpLeft <= iBoardSize)
	{
		for (unsigned int i = 0; i < iBoardSize; i++)
		{
			if ((iThisPos >= i * iBoardWidth) && (iThisPos <= (i * iBoardWidth) + (iBoardWidth - 1)) &&
				(pEquationUpLeft >= (i - 1) * iBoardWidth) && (pEquationUpLeft <= ((i - 1) * iBoardWidth) + (iBoardWidth - 1)))
			{
				if (bMoveCheck)
				{
					CheckBoard[pEquationUpLeft] = 'x';
				}
				else
				{
					if (iMoveTo == pEquationUpLeft && iThisWhite != bMoveToWhite)	//	move up left
					{
						dHistory.push_back("INFO: King moved up left");
						return true;
					}
				}
			}
		}
	}
	if (pEquationUpRight >= 0 && pEquationUpRight <= iBoardSize)
	{
		for (unsigned int i = 0; i < iBoardSize; i++)
		{
			if ((iThisPos >= i * iBoardWidth) && (iThisPos <= (i * iBoardWidth) + (iBoardWidth - 1)) &&
				(pEquationUpRight >= (i - 1) * iBoardWidth) && (pEquationUpRight <= ((i - 1) * iBoardWidth) + (iBoardWidth - 1)))
			{
				if (bMoveCheck)
				{
					CheckBoard[pEquationUpRight] = 'x';
				}
				else
				{
					if (iMoveTo == pEquationUpRight && iThisWhite != bMoveToWhite)	//	move up right
					{
						dHistory.push_back("INFO: King moved up right");
						return true;
					}
				}
			}
		}
	}
	if (iThisMoves == 0)	// Queenside castling
	{
		bool lValidMove = false;
		if (iMoveTo >= (iThisPos - 4) && iMoveTo <= (iThisPos - 2))
		{
			if (sBoard[iThisPos - 3] == " " && sBoard[iThisPos - 2] == " " && sBoard[iThisPos - 1] == " ")
			{
				dHistory.push_back("Attempting queenside castle...");
				bCastleSideQueen = true;
				bCurrentlyCastling = true;
				lValidMove = bRookLogic();
				if (lValidMove)
				{
					iMoveTo = iThisPos - 2;
					return true;
				}
			}
			else
			{
				sErrorMsg = "There can't be any pieces between the King and Rook!";
				return false;
			}
		}
		else if (iMoveTo >= (iThisPos + 2) && iMoveTo <= (iThisPos + 3))	//Kingside	castling
		{
			if (sBoard[iThisPos + 1] == " " && sBoard[iThisPos + 2] == " ")
			{
				dHistory.push_back("Attempting kingside castle...");
				bCastleSideQueen = false;
				bCurrentlyCastling = true;
				lValidMove = bRookLogic();
				if (lValidMove)
				{
					iMoveTo = iThisPos + 1;
					return true;
				}
			}
			else
			{
				sErrorMsg = "There can't be any pieces between the King and Rook!";
				return false;
			}
		}	//	END Kingside White
	}
	if (!bMoveCheck)
	{
		dHistory.push_back("King move was invalid");
		sErrorMsg = "King move was invalid";
	}
	return false;
}	//	END bKingLogic

bool bQueenLogic()		//---------------------------------------	QUEEN LOGIC	-------------------------------------------	QUEEN LOGIC	----------------------------------	-------------------------------------------	QUEEN LOGIC	----------------------------------
{
	unsigned int iThroughPiece = 0;
	unsigned int iLoopNum = 0;
	bool bThroughCalc = false;
	bool bDown = false;
	bool bUp = false;
	bool bLeft = false;
	bool bRight = false;
	bool bUpLeft = false;
	bool bUpRight = false;
	bool bDownLeft = false;
	bool bDownRight = false;

	for (int i = 1; i < iBoardWidth; i++)
	{
		unsigned int pEquationDown = iThisPos + (i * 8);
		unsigned int pEquationUp = iThisPos + -(i * 8);

		unsigned int pEquationLeft = iThisPos + -(i);
		unsigned int pEquationRight = iThisPos + (i);

		unsigned int pEquationUpLeft = iThisPos + -(i * 9);
		unsigned int pEquationUpRight = iThisPos + -(i * 7);

		unsigned int pEquationDownLeft = iThisPos + (i * 7);
		unsigned int pEquationDownRight = iThisPos + (i * 9);


		if (bDown == false)
		{
			iLoopNum = i;
			for (int i = 1; i < iBoardWidth; i++)
			{
				if (bDown == true) { break; }
				int pEquationDown = iThisPos + (i * 8);
				if (pEquationDown >= 0 && pEquationDown <= iBoardSize)
				{
					if (sBoard[pEquationDown] == " ")
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationDown] = 'x';
						}
					}
					else
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationDown] = 'x';
						}
						else
						{
							if (bCapturePiece == true)
							{
								if (iMoveTo == pEquationDown)
								{
									dHistory.push_back("Queen moved down");
									return true;
								}
							}
							else
							{
								int pEquationDown = iThisPos + ((i - 1) * 8);
								if (iMoveTo == pEquationDown)
								{
									dHistory.push_back("Queen moved down");
									return true;
								}
							}
						}
						bDown = true;
					}
				}
				else { bDown = true; }
			}
		}
		if (bUp == false)
		{
			iLoopNum = i;
			for (int i = 1; i < iBoardWidth; i++)
			{
				if (bUp == true) { break; }
				int pEquationUp = iThisPos + -(i * 8);
				if (pEquationUp >= 0 && pEquationUp <= iBoardSize)
				{
					if (sBoard[pEquationUp] == " ")
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationUp] = 'x';
						}
					}
					else
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationUp] = 'x';
						}
						else
						{
							if (bCapturePiece == true)
							{
								if (iMoveTo == pEquationUp)
								{
									dHistory.push_back("Queen moved up");
									return true;
								}
							}
							else
							{
								int pEquationUp = iThisPos + -((i - 1) * 8);
								if (iMoveTo == pEquationUp)
								{
									dHistory.push_back("Queen moved up");
									return true;
								}
							}
						}
						bUp = true;
					}
				}
				else { bUp = true; }
			}
		}
		if (bLeft == false)
		{
			iLoopNum = i;
			for (int i = 1; i < iBoardWidth; i++)
			{
				if (bLeft == true) { break; }
				int pEquationLeft = iThisPos + -(i);
				if (pEquationLeft >= 0 && pEquationLeft <= iBoardSize)
				{
					for (unsigned int j = 0; j < iBoardWidth; j++)
					{
						if (pEquationLeft == (j * iBoardWidth))
						{
							bLeft = true;
						}
					}
					if (sBoard[pEquationLeft] == " ")
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationLeft] = 'x';
						}
					}
					else
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationLeft] = 'x';
						}
						else
						{
							if (bCapturePiece == true)
							{
								if (iMoveTo == pEquationLeft)
								{
									dHistory.push_back("Queen moved left");
									return true;
								}
							}
							else
							{
								int pEquationLeft = iThisPos + -(i - 1);
								if (iMoveTo == pEquationLeft)
								{
									dHistory.push_back("Queen moved left");
									return true;
								}
							}
						}
						bLeft = true;
					}
				}
				else { bLeft = true; }
			}
		}
		if (bRight == false)
		{
			iLoopNum = i;
			for (int i = 1; i < iBoardWidth; i++)
			{
				if (bRight == true) { break; }
				int pEquationRight = iThisPos + (i);
				if (pEquationRight >= 0 && pEquationRight <= iBoardSize)
				{
					for (unsigned int j = 0; j < iBoardWidth; j++)
					{
						if (pEquationRight == (j * iBoardWidth) - 1)
						{
							bRight = true;
						}
					}
					if (sBoard[pEquationRight] == " ")
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationRight] = 'x';
						}
					}
					else
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationRight] = 'x';
						}
						else
						{
							if (bCapturePiece == true)
							{
								if (iMoveTo == pEquationRight)
								{
									dHistory.push_back("Queen moved right");
									return true;
								}
							}
							else
							{
								int pEquationRight = iThisPos + (i - 1);
								if (iMoveTo == pEquationRight)
								{
									dHistory.push_back("Queen moved right");
									return true;
								}
							}
						}
						bRight = true;
					}
				}
				else { bRight = true; }
			}
		}
		if (bUpLeft == false)
		{
			iLoopNum = i;
			for (int i = 1; i < iBoardWidth; i++)
			{
				if (bUpLeft == true) { break; }
				int pEquationUpLeft = iThisPos + -(i * 9);
				if (pEquationUpLeft >= 0 && pEquationUpLeft <= iBoardSize)
				{
					for (unsigned int j = 0; j < iBoardWidth; j++)
					{
						if (pEquationUpLeft == (j * iBoardWidth))
						{
							bUpLeft = true;
						}
					}
					if (sBoard[pEquationUpLeft] == " ")
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationUpLeft] = 'x';
						}
					}
					else
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationUpLeft] = 'x';
						}
						else
						{
							if (bCapturePiece == true)
							{
								if (iMoveTo == pEquationUpLeft)
								{
									dHistory.push_back("Queen moved up left");
									return true;
								}
							}
							else
							{
								int pEquationUpLeft = iThisPos + -((i - 1) * 9);
								if (iMoveTo == pEquationUpLeft)
								{
									dHistory.push_back("Queen moved up left");
									return true;
								}
							}
						}
						bUpLeft = true;
					}
				}
				else { bUpLeft = true; }
			}
		}
		if (bUpRight == false)
		{
			iLoopNum = i;
			for (int i = 1; i < iBoardWidth; i++)
			{
				if (bUpRight == true) { break; }
				int pEquationUpRight = iThisPos + -(i * 7);
				if (pEquationUpRight >= 0 && pEquationUpRight <= iBoardSize)
				{
					for (unsigned int j = 0; j < iBoardWidth; j++)
					{
						if (pEquationUpRight == (j * iBoardWidth) - 1)
						{
							bUpRight = true;
						}
					}
					if (sBoard[pEquationUpRight] == " ")
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationUpRight] = 'x';
						}
					}
					else
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationUpRight] = 'x';
						}
						else
						{
							if (bCapturePiece == true)
							{
								if (iMoveTo == pEquationUpRight)
								{
									dHistory.push_back("Queen moved up right");
									return true;
								}
							}
							else
							{
								int pEquationUpRight = iThisPos + -((i - 1) * 7);
								if (iMoveTo == pEquationUpRight)
								{
									dHistory.push_back("Queen moved up right");
									return true;
								}
							}
						}
						bUpRight = true;
					}
				}
				else { bUpRight = true; }
			}
		}
		if (bDownLeft == false)
		{
			iLoopNum = i;
			for (int i = 1; i < iBoardWidth; i++)
			{
				if (bDownLeft == true) { break; }
				int pEquationDownLeft = iThisPos + (i * 7);
				if (pEquationDownLeft >= 0 && pEquationDownLeft <= iBoardSize)
				{
					for (unsigned int j = 0; j < iBoardWidth; j++)
					{
						if (pEquationDownLeft == (j * iBoardWidth))
						{
							bDownLeft = true;
						}
					}
					if (sBoard[pEquationDownLeft] == " ")
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationDownLeft] = 'x';
						}
					}
					else
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationDownLeft] = 'x';
						}
						else
						{
							if (bCapturePiece == true)
							{
								if (iMoveTo == pEquationDownLeft)
								{
									dHistory.push_back("Queen moved down left");
									return true;
								}
							}
							else
							{
								int pEquationDownLeft = iThisPos + ((i - 1) * 7);
								if (iMoveTo == pEquationDownLeft)
								{
									dHistory.push_back("Queen moved down left");
									return true;
								}
							}
						}
						bDownLeft = true;
					}
				}
				else { bDownLeft = true; }
			}
		}
		if (bDownRight == false)
		{
			iLoopNum = i;
			bThroughCalc = false;
			for (int i = 1; i < iBoardWidth; i++)
			{
				if (bDownRight == true) { break; }
				int pEquationDownRight = iThisPos + (i * 9);
				if (pEquationDownRight >= 0 && pEquationDownRight <= iBoardSize)
				{
					for (unsigned int j = 0; j < iBoardWidth; j++)
					{
						if (pEquationDownRight == (j * iBoardWidth) - 1)
						{
							bDownRight = true;
						}
					}
					if (sBoard[pEquationDownRight] == " ")
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationDownRight] = 'x';
						}
					}
					else
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationDownRight] = 'x';
						}
						else
						{
							if (bCapturePiece == true)
							{
								if (iMoveTo == pEquationDownRight)
								{
									dHistory.push_back("Queen moved down left");
									return true;
								}
							}
							else
							{
								int pEquationDownRight = iThisPos + ((i - 1) * 9);
								if (iMoveTo == pEquationDownRight)
								{
									dHistory.push_back("Queen moved down left");
									return true;
								}
							}
						}
						bDownRight = true;
					}
				}
				else { bDownRight = true; }
			}
		}
	}
	if (!bMoveCheck)
	{
		dHistory.push_back("Queen move was invalid");
		sErrorMsg = "Queen move was invalid";
	}
	return false;
}	//	END bQueenLogic

bool bRookLogic()		//---------------------------------------	ROOK LOGIC	-------------------------------------------	ROOK LOGIC	----------------------------------	-------------------------------------------	ROOK LOGIC	----------------------------------
{
	unsigned int iThroughPiece = 0;
	unsigned int iLoopNum = 0;
	bool bThroughCalc = false;

	if (bCurrentlyCastling == true)
	{
		if (iThisMoves == 0)
		{
			if (CurrentColorIsWhite == true)
			{
				if (bCastleSideQueen == true)
				{
					iThisMoves++;
					iThisPos = 59;
					sBoard[59] = sBoard[56];
					iBoard[59] = iBoard[56];
					sBoard[56] = " ";
					iBoard[56] = ' ';
					dHistory.push_back("INFO: Queenside WHITE Rook castled sucessfully!");
					return true;
				}
				else    // Castle side is king
				{
					iThisMoves++;
					iThisPos = 61;
					sBoard[61] = sBoard[63];
					iBoard[61] = iBoard[63];
					sBoard[63] = " ";
					iBoard[63] = ' ';
					dHistory.push_back("INFO: Kingside WHITE Rook castled sucessfully!");
					return true;
				}
			}
			else    //CurrentColor is black
			{
				if (bCastleSideQueen == true)
				{
					iThisMoves++;
					iThisPos = 3;
					sBoard[3] = sBoard[0];
					iBoard[3] = iBoard[0];
					sBoard[0] = " ";
					iBoard[0] = ' ';
					dHistory.push_back("INFO: Queenside BLACK Rook castled sucessfully!");
					return true;
				}
				else    // Castle side is king
				{
					iThisMoves++;
					iThisPos = 5;
					sBoard[5] = sBoard[7];
					iBoard[5] = iBoard[7];
					sBoard[7] = " ";
					iBoard[7] = ' ';
					dHistory.push_back("INFO: Kingside BLACK Rook castled sucessfully!");
					return true;
				}
			}
		}
		else
		{
			dHistory.push_back("ERR: Rook must have 0 moves to castle!");
			sErrorMsg = "Rook must have 0 moves to castle";
			return false;
		}
	}	//	End bCurrentlyCastling

	bool bDown = false;
	bool bUp = false;
	bool bLeft = false;
	bool bRight = false;

	for (int i = 1; i < iBoardWidth; i++)
	{
		unsigned int pEquationDown = iThisPos + (i * 8);
		unsigned int pEquationUp = iThisPos + -(i * 8);

		unsigned int pEquationLeft = iThisPos + -(i);
		unsigned int pEquationRight = iThisPos + (i);

		if (bDown == false)
		{
			iLoopNum = i;
			for (int i = 1; i < iBoardWidth; i++)
			{
				if (bDown == true) { break; }
				int pEquationDown = iThisPos + (i * 8);
				if (pEquationDown >= 0 && pEquationDown <= iBoardSize)
				{
					if (sBoard[pEquationDown] == " ")
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationDown] = 'x';
						}
					}
					else
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationDown] = 'x';
						}
						else
						{
							if (bCapturePiece == true)
							{
								if (iMoveTo == pEquationDown)
								{
									dHistory.push_back("Rook moved down");
									return true;
								}
							}
							else
							{
								int pEquationDown = iThisPos + ((i - 1) * 8);
								if (iMoveTo == pEquationDown)
								{
									dHistory.push_back("Rook moved down");
									return true;
								}
							}
						}
						bDown = true;
					}
				}
				else { bDown = true; }
			}
		}
		if (bUp == false)
		{
			iLoopNum = i;
			for (int i = 1; i < iBoardWidth; i++)
			{
				if (bUp == true) { break; }
				int pEquationUp = iThisPos + -(i * 8);
				if (pEquationUp >= 0 && pEquationUp <= iBoardSize)
				{
					if (sBoard[pEquationUp] == " ")
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationUp] = 'x';
						}
					}
					else
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationUp] = 'x';
						}
						else
						{
							if (bCapturePiece == true)
							{
								if (iMoveTo == pEquationUp)
								{
									dHistory.push_back("Rook moved up");
									return true;
								}
							}
							else
							{
								int pEquationUp = iThisPos + -((i - 1) * 8);
								if (iMoveTo == pEquationUp)
								{
									dHistory.push_back("Rook moved up");
									return true;
								}
							}
						}
						bUp = true;
					}
				}
				else { bUp = true; }
			}
		}
		if (bLeft == false)
		{
			iLoopNum = i;
			for (int i = 1; i < iBoardWidth; i++)
			{
				if (bLeft == true) { break; }
				int pEquationLeft = iThisPos + -(i);
				if (pEquationLeft >= 0 && pEquationLeft <= iBoardSize)
				{
					for (unsigned int j = 0; j < iBoardWidth; j++)
					{
						if (pEquationLeft == (j * iBoardWidth))
						{
							bLeft = true;
						}
					}
					if (sBoard[pEquationLeft] == " ")
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationLeft] = 'x';
						}
					}
					else
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationLeft] = 'x';
						}
						else
						{
							if (bCapturePiece == true)
							{
								if (iMoveTo == pEquationLeft)
								{
									dHistory.push_back("Rook moved left");
									return true;
								}
							}
							else
							{
								int pEquationLeft = iThisPos + -(i - 1);
								if (iMoveTo == pEquationLeft)
								{
									dHistory.push_back("Rook moved left");
									return true;
								}
							}
						}
						bLeft = true;
					}
				}
				else { bLeft = true; }
			}
		}
		if (bRight == false)
		{
			iLoopNum = i;
			for (int i = 1; i < iBoardWidth; i++)
			{
				if (bRight == true) { break; }
				int pEquationRight = iThisPos + (i);
				if (pEquationRight >= 0 && pEquationRight <= iBoardSize)
				{
					for (unsigned int j = 0; j < iBoardWidth; j++)
					{
						if (pEquationRight == (j * iBoardWidth) - 1)
						{
							bRight = true;
						}
					}
					if (sBoard[pEquationRight] == " ")
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationRight] = 'x';
						}
					}
					else
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationRight] = 'x';
						}
						else
						{
							if (bCapturePiece == true)
							{
								if (iMoveTo == pEquationRight)
								{
									dHistory.push_back("Rook moved right");
									return true;
								}
							}
							else
							{
								int pEquationRight = iThisPos + (i - 1);
								if (iMoveTo == pEquationRight)
								{
									dHistory.push_back("Rook moved right");
									return true;
								}
							}
						}
						bRight = true;
					}
				}
				else { bRight = true; }
			}
		}
	}
	if (!bMoveCheck)
	{
		dHistory.push_back("Rook move was invalid");
		sErrorMsg = "Rook move was invalid";
	}
	return false;
}	//	END bRookLogic

bool bBishopLogic()		//---------------------------------------	BISHOP LOGIC	---------------------------------------	BISHOP LOGIC	----------------------------------	---------------------------------------	BISHOP LOGIC	----------------------------------
{
	unsigned int iThroughPiece = 0;
	unsigned int iLoopNum = 0;
	bool bThroughCalc = false;
	bool bUpLeft = false;
	bool bUpRight = false;
	bool bDownLeft = false;
	bool bDownRight = false;

	for (int i = 1; i < iBoardWidth; i++)
	{

		unsigned int pEquationUpLeft = iThisPos + -(i * 9);
		unsigned int pEquationUpRight = iThisPos + -(i * 7);

		unsigned int pEquationDownLeft = iThisPos + (i * 7);
		unsigned int pEquationDownRight = iThisPos + (i * 9);

		if (bUpLeft == false)
		{
			iLoopNum = i;
			for (int i = 1; i < iBoardWidth; i++)
			{
				if (bUpLeft == true) { break; }
				int pEquationUpLeft = iThisPos + -(i * 9);
				if (pEquationUpLeft >= 0 && pEquationUpLeft <= iBoardSize)
				{
					for (unsigned int j = 0; j < iBoardWidth; j++)
					{
						if (pEquationUpLeft == (j * iBoardWidth))
						{
							bUpLeft = true;
						}
					}
					if (sBoard[pEquationUpLeft] == " ")
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationUpLeft] = 'x';
						}
					}
					else
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationUpLeft] = 'x';
						}
						else
						{
							if (bCapturePiece == true)
							{
								if (iMoveTo == pEquationUpLeft)
								{
									dHistory.push_back("Bishop moved up left");
									return true;
								}
							}
							else
							{
								int pEquationUpLeft = iThisPos + -((i - 1) * 9);
								if (iMoveTo == pEquationUpLeft)
								{
									dHistory.push_back("Rook moved up left");
									return true;
								}
							}
						}
						bUpLeft = true;
					}
				}
				else { bUpLeft = true; }
			}
		}
		if (bUpRight == false)
		{
			iLoopNum = i;
			for (int i = 1; i < iBoardWidth; i++)
			{
				if (bUpRight == true) { break; }
				int pEquationUpRight = iThisPos + -(i * 7);
				if (pEquationUpRight >= 0 && pEquationUpRight <= iBoardSize)
				{
					for (unsigned int j = 0; j < iBoardWidth; j++)
					{
						if (pEquationUpRight == (j * iBoardWidth) - 1)
						{
							bUpRight = true;
						}
					}
					if (sBoard[pEquationUpRight] == " ")
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationUpRight] = 'x';
						}
					}
					else
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationUpRight] = 'x';
						}
						else
						{
							if (bCapturePiece == true)
							{
								if (iMoveTo == pEquationUpRight)
								{
									dHistory.push_back("Bishop moved up right");
									return true;
								}
							}
							else
							{
								int pEquationUpRight = iThisPos + -((i - 1) * 7);
								if (iMoveTo == pEquationUpRight)
								{
									dHistory.push_back("Rook moved up right");
									return true;
								}
							}
						}
						bUpRight = true;
					}
				}
				else { bUpRight = true; }
			}
		}
		if (bDownLeft == false)
		{
			iLoopNum = i;
			for (int i = 1; i < iBoardWidth; i++)
			{
				if (bDownLeft == true) { break; }
				int pEquationDownLeft = iThisPos + (i * 7);
				if (pEquationDownLeft >= 0 && pEquationDownLeft <= iBoardSize)
				{
					for (unsigned int j = 0; j < iBoardWidth; j++)
					{
						if (pEquationDownLeft == (j * iBoardWidth))
						{
							bDownLeft = true;
						}
					}
					if (sBoard[pEquationDownLeft] == " ")
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationDownLeft] = 'x';
						}
					}
					else
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationDownLeft] = 'x';
						}
						else
						{
							if (bCapturePiece == true)
							{
								if (iMoveTo == pEquationDownLeft)
								{
									dHistory.push_back("Bishop moved down left");
									return true;
								}
							}
							else
							{
								int pEquationDownLeft = iThisPos + ((i - 1) * 7);
								if (iMoveTo == pEquationDownLeft)
								{
									dHistory.push_back("Rook moved down left");
									return true;
								}
							}
						}
						bDownLeft = true;
					}
				}
				else { bDownLeft = true; }
			}
		}
		if (bDownRight == false)
		{
			iLoopNum = i;
			bThroughCalc = false;
			for (int i = 1; i < iBoardWidth; i++)
			{
				if (bDownRight == true) { break; }
				int pEquationDownRight = iThisPos + (i * 9);
				if (pEquationDownRight >= 0 && pEquationDownRight <= iBoardSize)
				{
					for (unsigned int j = 0; j < iBoardWidth; j++)
					{
						if (pEquationDownRight == (j * iBoardWidth) - 1)
						{
							bDownRight = true;
						}
					}
					if (sBoard[pEquationDownRight] == " ")
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationDownRight] = 'x';
						}
					}
					else
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationDownRight] = 'x';
						}
						else
						{
							if (bCapturePiece == true)
							{
								if (iMoveTo == pEquationDownRight)
								{
									dHistory.push_back("Bishop moved down right");
									return true;
								}
							}
							else
							{
								int pEquationDownRight = iThisPos + ((i - 1) * 9);
								if (iMoveTo == pEquationDownRight)
								{
									dHistory.push_back("Rook moved down right");
									return true;
								}
							}
						}
						bDownRight = true;
					}
				}
				else { bDownRight = true; }
			}
		}
	}
	if (!bMoveCheck)
	{
		dHistory.push_back("Bishop move was invalid");
		sErrorMsg = "Bishop move was invalid";
	}
	return false;
}	//	END bBishopLogic

bool bKnightLogic()		//---------------------------------------	KNIGHT LOGIC	---------------------------------------	KNIGHT LOGIC	----------------------------------	---------------------------------------	KNIGHT LOGIC	----------------------------------
{
	unsigned int pEquationDownLeft = iThisPos + 15;	//	Down
	unsigned int pEquationDownRight = iThisPos + 17;

	unsigned int pEquationUpLeft = iThisPos - 17;		// Up
	unsigned int pEquationUpRight = iThisPos - 15;

	unsigned int pEquationLeftDown = iThisPos + 10;	//	left / right down
	unsigned int pEquationRightDown = iThisPos + 6;

	unsigned int pEquationLeftUp = iThisPos - 10;		// left / right up
	unsigned int pEquationRightUp = iThisPos - 6;

	if (pEquationDownLeft >= 0 && pEquationDownLeft <= iBoardSize)
	{
		for (unsigned int i = 0; i < iBoardWidth; i++)
		{
			if (iThisPos >= (i * iBoardWidth) && (iThisPos <= ((i * iBoardWidth) + (iBoardWidth - 1))) &&
				(pEquationDownLeft >= ((i + 2) * iBoardWidth) - 1) && pEquationDownLeft <= (((i + 2) * iBoardWidth) + (iBoardWidth - 1)))
			{
				if (bMoveCheck)
				{
					CheckBoard[pEquationDownLeft] = 'x';
				}
				else
				{
					if (iMoveTo == pEquationDownLeft)
					{
						dHistory.push_back("Knight moved down left");
						return true;
					}
				}
			}
		}
	}
	if (pEquationDownRight >= 0 && pEquationDownRight <= iBoardSize)
	{
		for (unsigned int i = 0; i < iBoardWidth; i++)
		{
			if (iThisPos >= (i * iBoardWidth) && (iThisPos <= ((i * iBoardWidth) + (iBoardWidth - 1))) &&
				(pEquationDownRight >= ((i + 2) * iBoardWidth)) && pEquationDownRight <= (((i + 2) * iBoardWidth) + (iBoardWidth - 1)))
			{
				if (bMoveCheck)
				{
					CheckBoard[pEquationDownRight] = 'x';
				}
				else
				{
					if (iMoveTo == pEquationDownRight)
					{
						dHistory.push_back("Knight moved down right");
						return true;
					}
				}
			}
		}
	}
	if (pEquationUpLeft >= 0 && pEquationUpLeft <= iBoardSize)
	{
		for (unsigned int i = 0; i < iBoardWidth; i++)
		{
			if (iThisPos >= (i * iBoardWidth) && (iThisPos <= ((i * iBoardWidth) + (iBoardWidth - 1))) &&
				(pEquationUpLeft >= ((i - 2) * iBoardWidth)) && pEquationUpLeft <= (((i - 2) * iBoardWidth) + (iBoardWidth - 1)))
			{
				if (bMoveCheck)
				{
					CheckBoard[pEquationUpLeft] = 'x';
				}
				else
				{
					if (iMoveTo == pEquationUpLeft)
					{
						dHistory.push_back("Knight moved up left");
						return true;
					}
				}
			}
		}
	}
	if (pEquationUpRight >= 0 && pEquationUpRight <= iBoardSize)
	{
		for (unsigned int i = 0; i < iBoardWidth; i++)
		{
			if (iThisPos >= (i * iBoardWidth) && (iThisPos <= ((i * iBoardWidth) + (iBoardWidth - 1))) &&
				(pEquationUpRight >= ((i - 2) * iBoardWidth)) && pEquationUpRight <= (((i - 2) * iBoardWidth) + (iBoardWidth - 1)))
			{
				if (bMoveCheck)
				{
					CheckBoard[pEquationUpRight] = 'x';
				}
				else
				{
					if (iMoveTo == pEquationUpRight)
					{
						dHistory.push_back("Knight moved up right");
						return true;
					}
				}
			}
		}
	}
	if (pEquationLeftDown >= 0 && pEquationLeftDown <= iBoardSize)
	{
		for (unsigned int i = 0; i < iBoardWidth; i++)
		{
			if (iThisPos >= (i * iBoardWidth) && (iThisPos <= ((i * iBoardWidth) + (iBoardWidth - 1))) &&
				(pEquationLeftDown >= ((i + 1) * iBoardWidth)) && pEquationLeftDown <= (((i + 1) * iBoardWidth) + (iBoardWidth - 1)))
			{
				if (bMoveCheck)
				{
					CheckBoard[pEquationLeftDown] = 'x';
				}
				else
				{
					if (iMoveTo == pEquationLeftDown)
					{
						dHistory.push_back("Knight moved left down");
						return true;
					}
				}
			}
		}
	}
	if (pEquationRightDown >= 0 && pEquationRightDown <= iBoardSize)
	{
		for (unsigned int i = 0; i < iBoardWidth; i++)
		{
			if (iThisPos >= (i * iBoardWidth) && (iThisPos <= ((i * iBoardWidth) + (iBoardWidth - 1))) &&
				(pEquationRightDown >= ((i + 1) * iBoardWidth)) && pEquationRightDown <= (((i + 1) * iBoardWidth) + (iBoardWidth - 1)))
			{
				if (bMoveCheck)
				{
					CheckBoard[pEquationRightDown] = 'x';
				}
				else
				{
					if (iMoveTo == pEquationRightDown)
					{
						dHistory.push_back("Knight moved right down");
						return true;
					}
				}
			}
		}
	}
	if (pEquationLeftUp >= 0 && pEquationLeftUp <= iBoardSize)
	{
		for (unsigned int i = 0; i < iBoardWidth; i++)
		{
			if (iThisPos >= (i * iBoardWidth) && (iThisPos <= ((i * iBoardWidth) + (iBoardWidth - 1))) &&
				(pEquationLeftUp >= ((i - 1) * iBoardWidth)) && pEquationLeftUp <= (((i - 1) * iBoardWidth) + (iBoardWidth - 1)))
			{
				if (bMoveCheck)
				{
					CheckBoard[pEquationLeftUp] = 'x';
				}
				else
				{
					if (iMoveTo == pEquationLeftUp)
					{
						dHistory.push_back("Knight moved left up");
						return true;
					}
				}
			}
		}
	}
	if (pEquationRightUp >= 0 && pEquationRightUp <= iBoardSize)
	{
		for (unsigned int i = 0; i < iBoardWidth; i++)
		{
			if (iThisPos >= (i * iBoardWidth) && (iThisPos <= ((i * iBoardWidth) + (iBoardWidth - 1))) &&
				(pEquationRightUp >= ((i - 1) * iBoardWidth)) && pEquationRightUp <= (((i - 1) * iBoardWidth) + (iBoardWidth - 1)))
			{
				if (bMoveCheck)
				{
					CheckBoard[pEquationRightUp] = 'x';
				}
				else
				{
					if (iMoveTo == pEquationRightUp)
					{
						dHistory.push_back("Knight moved right up");
						return true;
					}
				}
			}
		}
	}
	if (!bMoveCheck)
	{
		dHistory.push_back("Knight move was invalid");
		sErrorMsg = "Knight move was invalid";
	}
	return false;
}	//	END bKnightLogic

bool bPawnLogic()		//---------------------------------------	PAWN LOGIC	-------------------------------------------	PAWN LOGIC	----------------------------------	-------------------------------------------	PAWN LOGIC	----------------------------------
{
	unsigned int pEquationUp = 0;
	unsigned int pEquationDouble = 0;
	unsigned int pEquationRightCapture = 0;
	unsigned int pEquationLeftCapture = 0;
	if (iThisWhite == true)
	{
		pEquationUp = iThisPos - 8;
		pEquationDouble = iThisPos - 16;
		pEquationRightCapture = iThisPos - 7;
		pEquationLeftCapture = iThisPos - 9;

	}
	else // color is black
	{
		pEquationUp = iThisPos + 8;
		pEquationDouble = iThisPos + 16;
		pEquationRightCapture = iThisPos + 7;
		pEquationLeftCapture = iThisPos + 9;
	}
	for (unsigned int i = 0; i < iBoardWidth; i++)
	{
		if (iThisWhite == true)
		{
			if (	((iThisPos >= i * iBoardWidth) && (iThisPos <= (i * iBoardWidth) + (iBoardWidth - 1)))	)
			{
				if (((pEquationLeftCapture >= 0) && (pEquationLeftCapture <= iBoardSize)) &&
					((pEquationLeftCapture >= ((i - 1) * iBoardWidth)) && (pEquationLeftCapture <= (((i - 1) * iBoardWidth) + (iBoardWidth - 1)))))
				{
					if (bMoveCheck)
					{
						CheckBoard[pEquationLeftCapture] = 'x';
					}
					else
					{
						if (iMoveTo == pEquationLeftCapture)
						{
							dHistory.push_back("Pawn captured left");
							return true;
						}
					}
				}
				if (((pEquationRightCapture >= 0) && (pEquationRightCapture <= iBoardSize)) &&
					((pEquationRightCapture >= ((i - 1) * iBoardWidth)) && (pEquationRightCapture <= (((i - 1) * iBoardWidth) + (iBoardWidth - 1)))))
				{
					if (bMoveCheck)
					{
						CheckBoard[pEquationRightCapture] = 'x';
					}
					else
					{
						if (iMoveTo == pEquationRightCapture)
						{
							dHistory.push_back("Pawn captured right");
							return true;
						}
					}
				}
				if (((pEquationUp >= 0) && (pEquationUp <= iBoardSize)) &&
					((pEquationUp >= ((i - 1) * iBoardWidth)) && (pEquationUp <= (((i - 1) * iBoardWidth) + (iBoardWidth - 1)))))
				{
					if (bMoveCheck)
					{
						CheckBoard[pEquationUp] = 'x';
					}
					else
					{
						if (iMoveTo == pEquationUp)
						{
							dHistory.push_back("Pawn moved up");
							return true;
						}
					}
					if (iThisMoves == 0)
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationDouble] = 'x';
						}
						else
						{
							if (iMoveTo == pEquationDouble)
							{
								dHistory.push_back("Pawn moved up double");
								return true;
							}
						}
					}
				}
			}
		}
		else    // piece is  black
		{
			if (((iThisPos >= i * iBoardWidth) && (iThisPos <= (i * iBoardWidth) + (iBoardWidth - 1))))
			{
				if (((pEquationLeftCapture >= 0) && (pEquationLeftCapture <= iBoardSize)) &&
					((pEquationLeftCapture >= ((i + 1) * iBoardWidth)) && (pEquationLeftCapture <= (((i + 1) * iBoardWidth) + (iBoardWidth - 1)))))
				{
					if (bMoveCheck)
					{
						CheckBoard[pEquationLeftCapture] = 'x';
					}
					else
					{
						if (iMoveTo == pEquationLeftCapture)
						{
							dHistory.push_back("Pawn captured left");
							return true;
						}
					}
				}
				if (((pEquationRightCapture >= 0) && (pEquationRightCapture <= iBoardSize)) &&
					((pEquationRightCapture >= ((i + 1) * iBoardWidth)) && (pEquationRightCapture <= (((i + 1) * iBoardWidth) + (iBoardWidth - 1)))))
				{
					if (bMoveCheck)
					{
						CheckBoard[pEquationRightCapture] = 'x';
					}
					else
					{
						if (iMoveTo == pEquationRightCapture)
						{
							dHistory.push_back("Pawn captured right");
							return true;
						}
					}
				}
				if (((pEquationUp >= 0) && (pEquationUp <= iBoardSize)) &&
					((pEquationUp >= ((i + 1) * iBoardWidth)) && (pEquationUp <= (((i + 1) * iBoardWidth) + (iBoardWidth - 1)))))
				{
					if (bMoveCheck)
					{
						CheckBoard[pEquationUp] = 'x';
					}
					else
					{
						if (iMoveTo == pEquationUp)
						{
							dHistory.push_back("Pawn moved down");
							return true;
						}
					}
					if (iThisMoves == 0)
					{
						if (bMoveCheck)
						{
							CheckBoard[pEquationDouble] = 'x';
						}
						else
						{
							if (iMoveTo == pEquationDouble)
							{
								dHistory.push_back("Pawn moved down double");
								return true;
							}
						}
					}
				}
			}
		}
	}
	if (!bMoveCheck)
	{
		dHistory.push_back("Pawn move was invalid");
		sErrorMsg = "Pawn move was invalid";
	}
	return false;
}	//	END bPawnLogic