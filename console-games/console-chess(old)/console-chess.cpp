//---------------------------------------------------------------------------------------------------------------------------------------
//----===============================================================================================================================~~~~
//----=                                                                                                                             =----
//----=     MMMM    MMM    MM   M    MMM    MMM    M      MMMM          MMMM   M   M   MMMM    MMM    MMM                           =----
//----=    M       M   M   M M  M   M      M   M   M      M            M       M   M   M      M      M           MM  MMM   MMM      =----
//----=    M       M   M   M  M M    MM    M   M   M      MMM    MMM   M       MMMMM   MMM     MM     MM        M    M  M  M  M     =----
//----=    M       M   M   M   MM      M   M   M   M      M            M       M   M   M         M      M       M    MMM   MMM      =----
//----=     MMMM    MMM    M    M   MMM     MMM    MMMM   MMMM          MMMM   M   M   MMMM   MMM    MMM    X    MM  M     M        =----
//----=                                                                                                                             =----
//----===============================================================================================================================~~~~
//-------------------------------------------------------- version 0.6.1    -------------------------------------------------------------
// Author: Anonoei (https://github.com/anonoei)
// License : GPLv3
// Dependencies: ChessLogic.h and ChessAI.h (for singleplayer)
// This file contains the front-end for my game console-chess

#include <iostream>
#include <vector>
#include <string>

#include <iomanip>		//	For cInputValidation()
#include <fstream>		//	For reading / writing files
#include <filesystem>	//	ONLY AVAILABLE IN C++17 (or by using the boost::filesystem library)
#include <chrono>		//	For vLoadHistory waiting between moves
#include <thread>		//	For vLoadHistory waiting between moves

#include "ChessLogic.h"	//	Header for ALL ChessLogic
//#include "ChessAI.h"	//	Header for ChessAI (Allows singleplayer games)

//	#include <cstdlib>	Possibly needed in non C++17?
//	#include <cstring>	Possibly needed in non C++17?
//	#include <climits>	Possibly needed in non C++17?
//	#include <cctype>	Possibly needed in non C++17?
//	#include <stdio.h>	Possibly needed in non C++17?

//	Initalize GLOBAL VARIBALES	-	-	-	-	-	-	-	-	-	GLOBAL VARIABLES	-	-	-	-	-	-	-	-	-	-	GLOBAL VARIABLES	-	-	-	-	-	-	-	-	-	-	GLOBAL VARIABLES	-	-	-	-	-	-	-	-	-	-
	//	Initalize Board Dimentions
const unsigned int iBoardWidth = 8;		//	BOARD printing is portable and can be modified (ChessLogic isn't portable for boardsize)
const unsigned int iBoardHeight = 8;	//	BOARD printing is portable and can be modified (ChessLogic isn't portable for boardsize)
const unsigned int iBoardSize = (iBoardWidth * iBoardHeight) - 1;

	//	Initalize ARRAYS
char iBoard			[ 8 * 8 ] = { ' ' };	//	Holds values the player sees
std::string sBoard	[ 8 * 8 ] = { " " };	//	Holds class name of piece and serves as a search function for objects within the class
char CheckBoard		[ 8 * 8 ] = { ' ' };	//	Holds value for where pieces can move -- Used for checking for check / Checking valid moves
char CheckmateBoard	[ 8 * 8 ] = { ' ' };	//	Holds value for checkmate (Can the king move?)
char cMoveBoard		[ 8 * 8 ] = { ' ' };	//	When cmove issued, CheckBoard is copied to this

	//	Initalize VECTORS
std::vector<std::string> dHistory;		//	Stores Debug History
std::vector<std::string> mHistory;		//	Stores Move History
std::vector<std::string> sCaptured;		//	Stores Captured Pieces
std::vector<std::string> sSidePrint;	//	Stores strings printed to the side of the board
std::string sErrorMsg = "";				//	Stores Error Message when something is invalid


unsigned int wMoves = 0;				//	Stores total WHITE moves
unsigned int bMoves = 0;				//	Stores total BLACK moves
unsigned int iWhiteScore = 39;			//	Stores WHITE score based on number of pieces	--	For ChessAI && printBoard
unsigned int iBlackScore = 39;			//	Stores BLACK score based on number of pieces	--	For ChessAI && printBoard

	//	Background Game Variables
unsigned long GameNumber = 0;			//	Stores GameNumber for file writing
unsigned long rGameNumber = 0;			//	Stores readGameNumber for history reading
unsigned long mHistoryReadNumber = 0;	//	Stores the Move History Number that was last saved to file
unsigned long dHistoryReadNumber = 0;	//	Stores the Debug History Read Number that was last saved to file
std::vector<int>iValidReadValue;		//	Stores value for valid GN# History files
bool rGameReadValid = false;

	//	Player settings
unsigned int iDebugLevel = 0;			//	Stores the player selected debug level
unsigned int iWhitePieceColor = 94;		//	Stores ASNI color value for white pieces
unsigned int iBlackPieceColor = 91;		//	Stores ANSI color value for black Pieces
bool bStartingColorWhite = true;		//	Stores the player selected starting color
char boardType = 'f';					//	Stores selected Board Type - l for large / s for small
bool bGraphics = false;					//	Stores whether player said ANSI esacpe codes worked, and enables/disables them
bool bLoadHistory = true;				//	Stores whether the player wanted to load previous game history
unsigned int iDepthAI = 4;						//	Stores player specified AI depth value;

	//	Check Logic
bool bWhiteKingInCheck = false;			//	Is the WHITE king in check? For printBoard
bool bBlackKingInCheck = false;			//	Is the BLACK king in check? For printBoard
bool bCheckmate = false;				//	Is the game a checkmate?
unsigned int iWhiteKingLocation = 60;	//	Stores WHITE king location for Check if Check validation
unsigned int iBlackKingLocation = 4;	//	Stores BLACK king location for Check if Check validation

	//	Move Logic
bool CurrentColorIsWhite = true;		//	Current move is WHITE for printBoard
unsigned int iMoveFrom = 0;				//	Player selected Piece is Moving From
unsigned int iMoveTo = 0;				//	Player selected Piece is attempting to Move To

	//	Game Status
bool bGameStatus = true;				//	Stores if a singleplayer / multiplayer match is occuring
bool bRematch = false;					//	Used for 'rematch' command to skip re-inputing game properties

	//	Save this-> values to variable for use inside printBoard function
bool iThisWhite = true;					//	Used in printBoard to verify the piece at a move location is not the same color as the selected piece
bool bMoveCheck = false;				//	Used in printBoard if the player chose to check if a move was valid and shows avialable moves


	//	Functions
bool bSinglePlayer();			//	Player selected Single Player game (vs ChessAI)
bool bMultiPlayer();			//	Player selected Multiplayer game (local 1v1)

void vGameWin();				//	Called when player wins the game
void vGameLose();				//	Called when player loses the game (Only when vs ChessAI)

void vInputSanitization(std::string*);		//	Called inside vUsrInput to convert all UPPERCASE to lowercase, thus sanitizing user input
void vInputInitalization(std::string, std::string*, std::string*, std::string*, std::string*, std::string*, std::string*, std::string*, std::string*);
				//		input string	seperates input string based on spaces and saves the initalized value to the string within the function it was called.

char cInputValidation();		//	Sanitizes and validates user input inside main() for selection Game Options		--	POSSIBLY UN-NEEDED if variable is passed to vUsrInput 
void printBoard();				//	Calls function to print board based off selected Game Options

void vUsrInput();				//	Called to convert input getline to commands

void vSaveHistory();			//	Saves Move history
void vSaveDebug();				//	Saves debug history
void vClearHistory();			//	Clears Move History
void vClearDebug();				//	Clears debug history
bool bReadHistory();			//	Reads move history file and executes

void vDebug();			//	Called in single/multiplayer loop to preform the selected iDebugLevel options
void vPause()			//	Called after a command is issued where the screen needs to pause to show user output and clears buffer
{
	std::cout << "\n\nPress any key to continue..." << std::endl;
	std::cin.get();
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
	return;
}	//	END vPause()
void vGameInit()	//	INITALIZE brand new game
{
	rGameNumber = GameNumber;
	for (int i = 0; i < iBoardSize; i++)
	{
		iBoard[i] = ' ';
		CheckBoard[i] = ' ';
		sBoard[i] = " ";

		CheckmateBoard[i] = ' ';
		cMoveBoard[i] = ' ';
	}
	for (int i = 0; i < sSidePrint.size(); i++)
		sSidePrint.pop_back();
	for (int i = 0; i < mHistory.size(); i++)
		mHistory.pop_back();

	sSidePrint.push_back("\thelp\t\t\t");
	sSidePrint.push_back("\tmove 'from' 'to'\t");
	sSidePrint.push_back("\tmcheck 'from'\t\t");
	//	SetPiece (PieceType , IsWhite , PieceNumber)

	ChessLogic_H::vPieceInit();

	CurrentColorIsWhite = bStartingColorWhite;	//	Reset game variables
	wMoves = 0;									//	UN-NEEDED if GLOBAL wMoves is removed	------------------
	bMoves = 0;									//	UN-NEEDED if GLOBAL bMoves is removed	------------------
	bWhiteKingInCheck = false;
	bBlackKingInCheck = false;
	bCheckmate = false;
	return;
}	//	END vGameInit()


int main( void )
{
	bool bGame = true;
	bool bGameWin = false;

	char cUsrInput = '0';	//	UN-NEEDED if cInputValidation is moved to vUsrInput	--------------
	char gameMode = '0';

	bool InputFalse = true;

	if (!bRematch)
	{
		std::error_code ec;
		bool dirWrite = std::filesystem::create_directories("common/debug");
		if (!dirWrite) { dHistory.push_back("dirWrite: " + ec.message()); }
		unsigned int iReadNumber = 0;
		std::string sCurrentLine = "";
		std::string sGameNumber = "";
		std::string sBoardType = "";
		std::string sGraphics = "";
		std::string sDebugLevel = "";
		std::ifstream checksettings("common/usrSettings.dat", std::ios::in);	//	sets GameNumber based on GN files
		if (checksettings.is_open())
		{
			std::cout << "\n\tWould you like to use the same settings as last time?(Yes/No) > ";
			cUsrInput = cInputValidation();
			if (cUsrInput == 'Y' || cUsrInput == 'y')
			{
				while (getline(checksettings, sCurrentLine))
				{
					if (iReadNumber == 0)
						sGameNumber = sCurrentLine;
					else if (iReadNumber == 1)
						sBoardType = sCurrentLine;
					else if (iReadNumber == 2)
						sGraphics = sCurrentLine;
					else if (iReadNumber == 3)
						sDebugLevel = sCurrentLine;
					iReadNumber++;
				}
				if (sGameNumber != "" && sBoardType != "" && sGraphics != "")
				{
					GameNumber = std::stoi(sGameNumber) + 1;
					iDebugLevel = std::stoi(sDebugLevel);
					if (sBoardType == "large" || sBoardType == "l")
						boardType = 'l';
					else if (sBoardType == "small" || sBoardType == "s")
						boardType = 's';
					if (sGraphics == "true" || sGraphics == "t" || sGraphics == "yes" || sGraphics == "y" || sGraphics == "1")
						bGraphics = true;
					else if (sGraphics == "false" || sGraphics == "f" || sGraphics == "no" || sGraphics == "n" || sGraphics == "0")
						bGraphics = false;
					if (boardType == 'l' || boardType == 's')
						bRematch = true;


					while (InputFalse)
					{
						if (bGraphics)
						{
							std::cout << "\n\tWould you like \033[4ms\033[0mingle or \033[4mm\033[0multiplayer? > ";
						}
						else
						{
							std::cout << "\n\tWould you like Single or Multiplayer? > ";
						}
						cUsrInput = cInputValidation();
						if (cUsrInput == 's' || cUsrInput == 'S' || cUsrInput == '1')
						{
							gameMode = 's';
							InputFalse = false;
						}
						else if (cUsrInput == 'm' || cUsrInput == 'M' || cUsrInput == '2')
						{
							gameMode = 'm';
							InputFalse = false;
						}
						else
						{
							std::cerr << "That gamemode doesn't exist!\n\n" << std::endl;
							dHistory.push_back("ERR: Invalid gameMode.");
						}
					}
				}
			}
			checksettings.close();
		}
		else
		{
			dHistory.push_back("No settings file to open!");
		}
	}

	while (bGame)
	{
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
			InputFalse = true;
			std::cout << "\n\t\tWeclome to DA Console Chess!" << std::endl;
			std::cout << "\tIs the below text readable? (Yes/No)" << std::endl;
			std::cout << "\t\t\033[4;31mT\033[32me\033[34ms\033[37mt\033[0m" << std::endl;

			std::cout << "\tThis choice will effect the entire game. > ";
			cUsrInput = cInputValidation();
			if (cUsrInput == 'y' || cUsrInput == 'Y')
			{
				bGraphics = true;
			}
			else
			{
				bGraphics = false;
			}

			while (InputFalse)
			{
				if (bGraphics)
				{
					std::cout << "\n\tWould you like a \033[4mS\033[0mmall or \033[4mL\033[0marge game board? > ";
				}
				else
				{
					std::cout << "\n\tWould you like a Small or Large game board? > ";
				}
				cUsrInput = cInputValidation();
				if (cUsrInput == 'l')
				{
					boardType = 'l';
					InputFalse = false;
				}
				else if (cUsrInput == 's')
				{
					boardType = 's';
					InputFalse = false;
				}
				else
				{
					std::cerr << "\nYou need to enter either S or L!" << std::endl;
					dHistory.push_back("ERR: Invalid boardType.");
				}
			}	//	END InputFalse
		}
		vGameInit();
		dHistory.push_back("Game Initalized.");
		if (!bRematch)
		{
			InputFalse = true;
			while (InputFalse)
			{
				if (bGraphics)
				{
					std::cout << "\n\tWould you like \033[4ms\033[0mingle or \033[4mm\033[0multiplayer? > ";
				}
				else
				{
					std::cout << "\n\tWould you like Single or Multiplayer? > ";
				}
				cUsrInput = cInputValidation();
				if (cUsrInput == 's' || cUsrInput == 'S' || cUsrInput == '1')
				{
					gameMode = 's';
					InputFalse = false;
				}
				else if (cUsrInput == 'm' || cUsrInput == 'M' || cUsrInput == '2')
				{
					gameMode = 'm';
					InputFalse = false;
				}
				else
				{
					std::cerr << "\nThat gamemode doesn't exist!\n\n" << std::endl;
					dHistory.push_back("ERR: Invalid gameMode.");
				}
			}	//	END InputFalse
		}
		bRematch = false;
		dHistory.push_back("GameNumber: " + std::to_string(GameNumber) + "\tbGraphics: " + std::to_string(bGraphics) +"\tboardType: " + boardType + "\tgameMode: " + gameMode);
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
				vSaveHistory();
				GameNumber++;
				bGame = true;
				bRematch = true;
			}
			else
			{
				std::ofstream SaveGame("common/usrSettings.dat", std::ios::out);
				if (SaveGame.is_open())
				{
					SaveGame << GameNumber << "\n";
					SaveGame << boardType << "\n";
					SaveGame << bGraphics << "\n";
					SaveGame.close();
				}

				std::cout << "Thanks for playing!\n\n" << std::endl;
				bGame = false;
			}
		}
		else
		{
			std::cout << "\n\tWould you like to save this game? > ";
			cUsrInput = cInputValidation();
			if (cUsrInput == 'y' || cUsrInput == 'Y')
			{
				std::ofstream SaveGame("common/usrSettings.dat", std::ios::out);
				if (SaveGame.is_open())
				{
					SaveGame << GameNumber << "\n";
					SaveGame << boardType << "\n";
					SaveGame << bGraphics << "\n";
					SaveGame.close();
				}
			}
			GameNumber++;
		}

	}	//	END of GAME LOOP

	return 0;

}	//	END OF MAIN



char cInputValidation()		//	---------- UN-NEEDED if moved to vUsrInput()
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
}	//	END cInputValidation()		//		END cInputValidation()		//		END cInputValidation()

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
		vSaveDebug();
	}
	else if (iDebugLevel == 3)
	{
		for (unsigned int i = 0; i < dHistory.size(); i++)
		{
			std::cout << "\t" << i << ".\t" << dHistory.at(i) << std::endl;
		}
		vSaveDebug();
	}
	return;
}	//		END vDebug()		//			END vDebug()			//			END vDebug()

bool bSinglePlayer()		//	--------------------------	SINGLE PLAYER GAME	-------------------------------------------------------	SINGLE PLAYER GAME --------------------------
{
	bGameStatus = true;
	int GameStatusLoop = 0;
	while (bGameStatus == true)
	{
		if (bLoadHistory)
		{
			bReadHistory();
			bLoadHistory = false;
		}
		dHistory.push_back("---------------------------------------------- Loop number: " + std::to_string(GameStatusLoop) + " ---------------------------------");
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
				mHistory.push_back("END: White King in checkmate.");
				vGameLose();
			}
			else if (bBlackKingInCheck == true)
			{
				mHistory.push_back("END: Black King in checkmate.");
				vGameWin();
			}
			bGameStatus = false;
		}
		
	}
	dHistory.push_back("Game Ended on loop " + std::to_string(GameStatusLoop));
	return 0;
}	//		END bSinglePlayer()			//		END bSinglePlayer()			//		END bSinglePlayer()

bool bMultiPlayer()			//	--------------------------	MULTI-PLAYER GAME	-------------------------------------------------------	MULTI-PLAYER GAME --------------------------
{
	bGameStatus = true;
	int GameStatusLoop = 0;
	while (bGameStatus == true)
	{
		if (bLoadHistory)
		{
			bReadHistory();
			bLoadHistory = false;
		}
		dHistory.push_back("--------------------------------------------------- Loop number: " + std::to_string(GameStatusLoop) + " -----------------------------");
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
}	//		END bMultiPlayer()			//			END bMultiPlayer()			//		END bMultiPlayer()

void vGameWin()		//-------------vGameWin()------------------//-------------vGameWin()------------------//-------------vGameWin()------------------
{
	std::cout << std::endl;
	if (bWhiteKingInCheck == true)
	{
		mHistory.push_back("END: White King in checkmate.");
		std::cout << "Black ";
	}
	else if (bBlackKingInCheck == true)
	{
		mHistory.push_back("END: Black King in checkmate.");
		std::cout << "White ";
	}
	std::cout << "W O N the game!" << std::endl;
}	//		END vGameWin()			//			END vGameWin()			//		END vGameWin()
void vGameLose()	//-------------vGameLose()------------------//-------------vGameLose()------------------//-------------vGameLose()------------------
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
}	//		END vGameLose()			//			END vGameLose()			//		END vGameLose()

void vUsrInput()	//-------------vUsrInput()------------------//-------------vUsrInput()------------------//-------------vUsrInput()------------------
{

	std::string cOne;
	std::string cTwo;
	std::string cThree;
	std::string cFour;
	std::string cFive;
	std::string cSix;
	std::string cSeven;
	std::string cEight;

	std::string input;
	std::string dbgInput;

	std::getline(std::cin, input);
	dbgInput = input;
	vInputInitalization(input, &cOne, &cTwo, &cThree, &cFour, &cFive, &cSix, &cSeven, &cEight);

	dHistory.push_back("INFO: input: \"" + dbgInput +"\"\tcOne: \"" + cOne + "\"\tcTwo: \"" + cTwo + "\"\tcThree: \"" + cThree + "\".");

	if (cOne == "exit")			//		BEGIN COMMANDS			//			BEGIN COMMANDS			//		BEGIN COMMANDS		//
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
			std::cout << "\t    additionally, the input is NOT CaSe SeNsItIvE!" << std::endl;
			std::cout << "\tcheckmate\tChecks for checkmate, and ends the match" << std::endl;
			std::cout << "\tcolor\t\tChanges piece color on board" << std::endl;
			std::cout << "\tdebug\t\tControls debug settings" << std::endl;
			std::cout << "\texit\t\tExit's to the main menu, and loses all game progress" << std::endl;
			std::cout << "\thelp 'command'\tLists all commands, and provides context for commmands" << std::endl;
			std::cout << "\thistory\t\tPrints full game history to screen" << std::endl;
			std::cout << "\tmove 'from' to'\tMoves the 'from' piece to the 'to' location. Example: move A7 A5." << std::endl;
			std::cout << "\tcmoves 'from'\tCheck Moves - Shows the valid moves of the 'from' piece. Example: cmove A7" << std::endl;
			std::cout << "\trematch\t\tEnds the current match and starts a new one." << std::endl;
			std::cout << "\tsettings\t\tChanges game settings" << std::endl;
			std::cout << "\twhat\t\t(debug) Says name of piece at current location on all boards" << std::endl;
			std::cout << "\n\tOr try 'help list' for a list of all commands!" << std::endl;
		}
		else if (cTwo == "list")
		{
			dHistory.push_back("command HELP LIST issued");
			std::cout << "\texit" << std::endl;
			std::cout << "\thelp" << std::endl;
			std::cout << "\t\t\"\", " << std::endl;
			std::cout << "\t\tlist," << std::endl;
			std::cout << "\t\tcheckmate, " << std::endl;
			std::cout << "\t\tcolor (options), " << std::endl;
			std::cout << "\t\tdebug, " << std::endl;
			std::cout << "\t\texit, " << std::endl;
			std::cout << "\t\thistory[hist, h], " << std::endl;
			std::cout << "\t\tmove[mov, mv, m]" << std::endl;
			std::cout << "\t\tmcheck[mc, cmoves, cmove, cmv, cm]" << std::endl;
			std::cout << "\t\trematch," << std::endl;
			std::cout << "\t\tsettings[set]," << std::endl;
			std::cout << "\t\twhat[w]" << std::endl;
			std::cout << "\tcolor (color specified)" << std::endl;
			std::cout << "\t\tblack (color specified)" << std::endl;
			std::cout << "\t\twhite (color specified)" << std::endl;
			std::cout << "\tcheckmate" << std::endl;
			std::cout << "\tdebug[dbg] (value)" << std::endl;
			std::cout << "\t\tprint[p]," << std::endl;
			std::cout << "\t\t\tiboard[i]," << std::endl;
			std::cout << "\t\t\tsboard[s]," << std::endl;
			std::cout << "\t\t\tcheck[c]," << std::endl;
			std::cout << "\t\t\tcmoveboard[cmoves, cmove, cmov, cmv]" << std::endl;
			std::cout << "\tsave[s]," << std::endl;
			std::cout << "\tclear[c]," << std::endl;
			std::cout << "\thistory[hist, h]" << std::endl;
			std::cout << "\thistory[hist, h]" << std::endl;
			std::cout << "\t\t\"\"," << std::endl;
			std::cout << "\t\tsave[s]," << std::endl;
			std::cout << "\t\tdebug[dbg]" << std::endl;
			std::cout << "\t\t\t\"\"," << std::endl;
			std::cout << "\t\t\tsave[s]," << std::endl;
			std::cout << "\t\t\tclear[c]" << std::endl;
			std::cout << "\tmcheck[mc, cmoves, cmove, cmov, cmv, cms, cm] (value)" << std::endl;
			std::cout << "\trematch" << std::endl;
			std::cout << "\tmove[mov, mv, m]	(from) (to)" << std::endl;
			std::cout << "\tsettings[set]" << std::endl;
			std::cout << "\t\t\"\"," << std::endl;
			std::cout << "\t\tboard[b]," << std::endl;
			std::cout << "\t\t\tlarge[l]," << std::endl;
			std::cout << "\t\t\tsmall[s]" << std::endl;
			std::cout << "\tgraphics[g]," << std::endl;
			std::cout << "\t\t\ttrue[yes, y]," << std::endl;
			std::cout << "\t\t\tfalse[no, n]" << std::endl;
			std::cout << "\twhat[w] (value)" << std::endl;
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
					std::cout << "\t\tcolor 'color to change to'" << std::endl;
					std::cout << "\t\tcolor      blue" << std::endl;
					std::cout << "\tType 'help color options' to view all color options!" << std::endl;
				}
			}
			else
			{
				sErrorMsg = "Your current configuration doesn't support color changing!";
				dHistory.push_back("ERR: Color cannot be changed while bGraphics is false!");
				return;
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
			std::cout << "\tAliases:" << std::endl;
			std::cout << "\t\tdebug, dbg" << std::endl;

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
		else if (cTwo == "history" || cTwo == "hist" || cTwo == "h")
		{
			dHistory.push_back("command HELP HISTORY issued.");
			std::cout << "\n\n\t\t'history' Command help:" << std::endl;
			std::cout << "\tThe 'history' command is used to display all events of the current match" << std::endl;
			std::cout << "\tThe syntax for the move command is as follows:" << std::endl;
			std::cout << "\t\thistory option" << std::endl;
			std::cout << "\t\thistory debug" << std::endl;
			std::cout << "\t\thistory save" << std::endl;
			std::cout << "\tAliases:" << std::endl;
			std::cout << "\t\thistory, hist, h" << std::endl;
			std::cout << "\t\tSpecial Uses:" << std::endl;
			std::cout << "\t'Save to Files'" << std::endl;
			std::cout << "\t in the future I'll write what is supposed to be here." << std::endl;
		}
		else if (cTwo == "move" || cTwo == "mov" || cTwo == "mv" || cTwo == "m")
		{
			dHistory.push_back("command HELP MOVE issued.");
			std::cout << "\n\n\t\t'move' Command help:" << std::endl;
			std::cout << "\tThe 'move' command is used to move any piece from one location to another" << std::endl;
			std::cout << "\tThe syntax for the move command is as follows:" << std::endl;
			std::cout << "\t\tmove 'from'\t'to'" << std::endl;
			std::cout << "\t\tmove   A7 \tA5" << std::endl;
			std::cout << "\tThis moves the piece at location 'A7' to the 'A5'" << std::endl;
			std::cout << "\tThis command has input validation, and will ensure your move is legal." << std::endl;
			std::cout << "\tAliases:" << std::endl;
			std::cout << "\t\tmove, mov, mv, m" << std::endl;
			std::cout << "\t\tSpecial Uses:" << std::endl;
			std::cout << "\t'castling'" << std::endl;
		}
		else if (cTwo == "mcheck" || cTwo == "mc" || cTwo == "cmoves" || cTwo == "cmove" || cTwo == "cmv" || cTwo == "cm")
		{
			dHistory.push_back("command HELP CMOVE issued.");
			std::cout << "\n\n\t\t'cmove' Command help:" << std::endl;
			std::cout << "\tThe 'cmove' or 'check move' command is used to check the available moves for the selected piece." << std::endl;
			std::cout << "\tThe syntax for the cmove command is as follows:" << std::endl;
			std::cout << "\t\tcmove 'from'" << std::endl;
			std::cout << "\t\tcmove   A7" << std::endl;
			std::cout << "\tThis will show you all of the available moves for the piece located at A7." << std::endl;
			std::cout << "\tAliases:" << std::endl;
			std::cout << "\t\tmcheck, mc, cmoves, cmove, cmv, cm" << std::endl;
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
		else if (cTwo == "settings" || cTwo == "set")
		{
			dHistory.push_back("command HELP SETTINGS issued.");
			std::cout << "\n\n\t\t'settings' Command help:" << std::endl;
			std::cout << "\tThe 'settings' command is used to change game settings" << std::endl;
			std::cout << "\tThe syntax for the what command is as follows:" << std::endl;
			std::cout << "\t\tsettings 'parameter' 'option'" << std::endl;
			std::cout << "\t\tsettings    board     large" << std::endl;
			std::cout << "\tAliases:" << std::endl;
			std::cout << "\t\tsettings, set" << std::endl;
		}
		else if (cTwo == "what" || cTwo == "w")
		{
			dHistory.push_back("command HELP WHAT issued.");
			std::cout << "\n\n\t\t'what' Command help:" << std::endl;
			std::cout << "\tThe 'what' command is a debug command to show what values are at specific locations on the board" << std::endl;
			std::cout << "\tThe syntax for the what command is as follows:" << std::endl;
			std::cout << "\t\twhat location" << std::endl;
			std::cout << "\t\twhat    c0" << std::endl;
			std::cout << "\tAliases:" << std::endl;
			std::cout << "\t\twhat, w" << std::endl;
		}
		else
		{
			dHistory.push_back("command HELP \"" + cTwo + "\" was not found.");
			sErrorMsg = "Invalid help parameter / option";
			return;
		}
		dHistory.push_back("command HELP " + cTwo + cThree + " issued.");
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
				std::cout << "Current Color for white is: \033[" << iWhitePieceColor << "m!\033[0m(" << iWhitePieceColor << "). Black is: \033[" << iBlackPieceColor << "m!\033[0m(" << iBlackPieceColor << ")." << std::endl;
				return;
			}
			else if (cThree == "r" || cThree == "red" || cThree == "31" || cThree == "1" || cTwo == "r" || cTwo == "red" || cTwo == "31" || cTwo == "1")
			{
				if (cTwo == "black" || cTwo == "b")
					iBlackPieceColor = 31;
				else if (cTwo == "white" || cTwo == "w")
					iWhitePieceColor = 31;
				else
				{
					iBlackPieceColor = 31;
					iWhitePieceColor = 31;
				}
			}
			else if (cThree == "g" || cThree == "green" || cThree == "32" || cThree == "2" || cTwo == "g" || cTwo == "green" || cTwo == "32" || cTwo == "2")
			{
				if (cTwo == "black" || cTwo == "b")
					iBlackPieceColor = 32;
				else if (cTwo == "white" || cTwo == "w")
					iWhitePieceColor = 32;
				else
				{
					iBlackPieceColor = 32;
					iWhitePieceColor = 32;
				}
			}
			else if (cThree == "y" || cThree == "yellow" || cThree == "33" || cThree == "3" || cTwo == "y" || cTwo == "yellow" || cTwo == "33" || cTwo == "3")
			{
				if (cTwo == "black" || cTwo == "b")
					iBlackPieceColor = 33;
				else if (cTwo == "white" || cTwo == "w")
					iWhitePieceColor = 33;
				else
				{
					iBlackPieceColor = 33;
					iWhitePieceColor = 33;
				}
			}
			else if (cThree == "b" || cThree == "blue" || cThree == "34" || cThree == "4" || cTwo == "b" || cTwo == "blue" || cTwo == "34" || cTwo == "4")
			{
				if (cTwo == "black" || cTwo == "b")
					iBlackPieceColor = 34;
				else if (cTwo == "white" || cTwo == "w")
					iWhitePieceColor = 34;
				else
				{
					iBlackPieceColor = 34;
					iWhitePieceColor = 34;
				}
			}
			else if (cThree == "m" || cThree == "magenta" || cThree == "35" || cThree == "5" || cTwo == "m" || cTwo == "magenta" || cTwo == "35" || cTwo == "5")
			{
				if (cTwo == "black" || cTwo == "b")
					iBlackPieceColor = 35;
				else if (cTwo == "white" || cTwo == "w")
					iWhitePieceColor = 35;
				else
				{
					iBlackPieceColor = 35;
					iWhitePieceColor = 35;
				}
			}
			else if (cThree == "c" || cThree == "cyan" || cThree == "36" || cThree == "6" || cTwo == "c" || cTwo == "cyan" || cTwo == "36" || cTwo == "6")
			{
				if (cTwo == "black" || cTwo == "b")
					iBlackPieceColor = 36;
				else if (cTwo == "white" || cTwo == "w")
					iWhitePieceColor = 36;
				else
				{
					iBlackPieceColor = 36;
					iWhitePieceColor = 36;
				}
			}
			else if (cThree == "br" || cThree == "bred" || cThree == "91" || cThree == "7" || cTwo == "br" || cTwo == "bred" || cTwo == "91" || cTwo == "7")
			{
				if (cTwo == "black" || cTwo == "b")
					iBlackPieceColor = 91;
				else if (cTwo == "white" || cTwo == "w")
					iWhitePieceColor = 91;
				else
				{
					iBlackPieceColor = 91;
					iWhitePieceColor = 91;
				}
			}
			else if (cThree == "bg" || cThree == "bgreen" || cThree == "92" || cThree == "8" || cTwo == "bg" || cTwo == "bgreen" || cTwo == "92" || cTwo == "8")
			{
				if (cTwo == "black" || cTwo == "b")
					iBlackPieceColor = 92;
				else if (cTwo == "white" || cTwo == "w")
					iWhitePieceColor = 92;
				else
				{
					iBlackPieceColor = 92;
					iWhitePieceColor = 92;
				}
			}
			else if (cThree == "by" || cThree == "byellow" || cThree == "93" || cThree == "9" || cTwo == "by" || cTwo == "byellow" || cTwo == "93" || cTwo == "9")
			{
			if (cTwo == "black" || cTwo == "b")
				iBlackPieceColor = 93;
			else if (cTwo == "white" || cTwo == "w")
				iWhitePieceColor = 93;
			else
			{
				iBlackPieceColor = 93;
				iWhitePieceColor = 93;
			}
			}
			else if (cThree == "bb" || cThree == "bblue" || cThree == "94" || cThree == "10" || cTwo == "bb" || cTwo == "bblue" || cTwo == "94" || cTwo == "10")
			{
			if (cTwo == "black" || cTwo == "b")
				iBlackPieceColor = 94;
			else if (cTwo == "white" || cTwo == "w")
				iWhitePieceColor = 94;
			else
			{
				iBlackPieceColor = 94;
				iWhitePieceColor = 94;
			}
			}
			else if (cThree == "bm" || cThree == "bmagenta" || cThree == "95" || cThree == "11" || cTwo == "bm" || cTwo == "bmagenta" || cTwo == "95" || cTwo == "11")
			{
			if (cTwo == "black" || cTwo == "b")
				iBlackPieceColor = 95;
			else if (cTwo == "white" || cTwo == "w")
				iWhitePieceColor = 95;
			else
			{
				iBlackPieceColor = 95;
				iWhitePieceColor = 95;
			}
			}
			else if (cThree == "bc" || cThree == "bcyan" || cThree == "96" || cThree == "12" || cTwo == "bc" || cTwo == "bcyan" || cTwo == "96" || cTwo == "12")
			{
			if (cTwo == "black" || cTwo == "b")
				iBlackPieceColor = 96;
			else if (cTwo == "white" || cTwo == "w")
				iWhitePieceColor = 96;
			else
			{
				iBlackPieceColor = 96;
				iWhitePieceColor = 96;
			}
			}
			else
			{
				sErrorMsg = "That color could not be found";
				dHistory.push_back("ERR: invalid COLOR " + cThree);
				return;
			}
			dHistory.push_back("command COLOR " + cTwo + " issued");
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
		//	the stuff for checkmate should go here	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	
		sErrorMsg = "That command hasn't been implemented yet.";
		return;
	}
	else if (cOne == "debug" || cOne == "dbg")
	{
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
		else if (cTwo == "print" || cTwo == "p")
		{
			int bIndex = iBoardHeight;
			if (cThree == "iboard" || cThree == "i")
			{
				std::cout << "\t      A  B  C  D  E  F  G  H  " << std::endl;
				std::cout << "\t    ==========================";
				for (int height = 0; height < iBoardHeight; height++)
				{
					std::cout << std::endl;
					std::cout << "\t " << bIndex << " | ";
					bIndex--;
					for (int width = 0; width < iBoardWidth; width++)
					{
						int iBoardPrint = ((width + 1) + (height * iBoardHeight)) - 1;
						std::cout << " " << iBoard[iBoardPrint] << " ";
					}
				}
				dHistory.push_back("command DEBUG PRINT iBoard issued.");
			}
			else if (cThree == "sboard" || cThree == "s")
			{
				bool sPrint = false;
				std::cout << "      A\t\tB\tC\tD\tE\tF\tG\tH\t  " << std::endl;
				std::cout << "    ====================================================================";
				for (int height = 0; height < iBoardHeight; height++)
				{
					std::cout << std::endl;
					std::cout << " " << bIndex << " | ";
					bIndex--;
					for (int width = 0; width < iBoardWidth; width++)
					{
						int iBoardPrint = ((width + 1) + (height * iBoardHeight)) - 1;
						if (width == 0)
							std::cout << " " << sBoard[iBoardPrint];
						else
						{
							std::cout << "\t" << sBoard[iBoardPrint] << "";
						}
					}
				}
				dHistory.push_back("command DEBUG PRINT sBoard issued.");
			}
			else if (cThree == "check" || cThree == "c")
			{
				std::cout << "\t      A  B  C  D  E  F  G  H  "<< std::endl;
				std::cout << "\t    ==========================";
				for (int height = 0; height < iBoardHeight; height++)
				{
					std::cout << std::endl;
					std::cout << "\t " << bIndex << " | ";
					bIndex--;
					for (int width = 0; width < iBoardWidth; width++)
					{
						int iBoardPrint = ((width + 1) + (height * iBoardHeight)) - 1;
						std::cout << " " << CheckBoard[iBoardPrint] << " ";
					}
				}
				dHistory.push_back("command DEBUG PRINT CheckBoard issued.");
			}
			else if (cThree == "cmoveboard" || cThree == "cmoves" || cThree == "cmove" || cThree == "cmov" || cThree == "cmv")
			{
				std::cout << "\t      A  B  C  D  E  F  G  H  " << std::endl;
				std::cout << "\t    ==========================";
				for (int height = 0; height < iBoardHeight; height++)
				{
					std::cout << std::endl;
					std::cout << "\t " << bIndex << " | ";
					bIndex--;
					for (int width = 0; width < iBoardWidth; width++)
					{
						int iBoardPrint = ((width + 1) + (height * iBoardHeight)) - 1;
						std::cout << " " << cMoveBoard[iBoardPrint] << " ";
					}
				}
				dHistory.push_back("command DEBUG PRINT cMoveBoard issued.");
			}
			else
			{
				dHistory.push_back("ERR: Invalid command DEBUG PRINT " + cThree);
				sErrorMsg = "Invalid debug print option";
				return;
			}
			vPause();
		}
		else if (cTwo == "save" || cTwo == "s")
		{
			dHistory.push_back("command DEBUG SAVE issued.");
			vSaveDebug();
		}
		else if (cTwo == "clear" || cTwo == "c")
		{
			dHistory.push_back("command DEBUG CLEAR issued.");
			vClearDebug();
		}
		else if (cTwo == "history" || cTwo == "hist" || cTwo == "h")
		{
			dHistory.push_back("command DEBUG HISTORY issued.");
			for (long unsigned int i = 0; i < dHistory.size(); i++)
			{
				std::cout << "\t" << i + 1 << ".\t" << dHistory.at(i) << std::endl;
			}
			vPause();
		}
		else
		{
			dHistory.push_back("ERR: Invalid command DEBUG " + cTwo + cThree);
			sErrorMsg = "Invalid debug parameter / option";
		}
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
				vPause();
				return;
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
			vSaveHistory();
			return;
		}
		else if (cTwo == "clear" || cTwo == "c")
		{
			dHistory.push_back("command HISTORY CLEAR issued");
			vClearHistory();
			return;
		}
		else if (cTwo == "debug" || cTwo == "dbg")
		{
			if (cThree == "save" || cThree == "s")
			{
				std::cout << "To enable saving debug history to a file, use the command 'debug 2' or 'help debug'" << std::endl;
				return;
			}
			else if (cThree == "clear" || cThree == "c")
			{
				dHistory.push_back("command HISTORY DEBUG CLEAR issued.");
				vClearDebug();
				return;
			}
			else if (cThree == "")
			{
				dHistory.push_back("command HISTORY DEBUG issued.");
				for (long unsigned int i = 0; i < dHistory.size(); i++)
				{
					std::cout << "\t" << i + 1 << ".\t" << dHistory.at(i) << std::endl;
				}
				vPause();
				return;
			}
			else
			{
				dHistory.push_back("ERR: Invalid command HISTORY DEBUG " + cThree);
				sErrorMsg = "Invalid history debug option";
			}
		}
		else
		{
			dHistory.push_back("ERR: Invalid command HISTORY " + cTwo + cThree);
			sErrorMsg = "Invalid history parameter / option";
		}
		return;
	}
	else if (cOne == "mcheck" || cOne == "mc" || cOne == "cmoves" || cOne == "cmove" || cOne == "cmov" || cOne == "cmv" || cOne == "cms" || cOne == "cm")
	{
		int iAtIndex = 0;
		if (cTwo.size() == 2)
		{
			int iMovefWidth = 0;
			int iMovefHeight = 0;

			iMovefWidth = ChessLogic_H::iFromCharToInt1(cTwo, &iAtIndex);
			iMovefHeight = ChessLogic_H::iFromCharToInt2(cTwo, &iAtIndex);
			iMoveFrom = ((iMovefWidth)+((iMovefHeight - 1) * iBoardHeight)) - 1;
			dHistory.push_back("command CMOVE issued.\tiMoveFrom: " + std::to_string(iMoveFrom) + " from Width: " + std::to_string(iMovefWidth) + " and Height: " + std::to_string(iMovefHeight));

			ChessLogic_H::vMoveCheck();
		}
		else
		{
			dHistory.push_back("ERR: command CMOVE issued improperly.");
			sErrorMsg = "Improper use of the cmove command.";
		}
		return;
	}
	else if (cOne == "rematch")
	{
		char cUsrInput = ' ';
		dHistory.push_back("command REMATCH issued.");
		std::cout << "\n\nAre you sure?" << std::endl;
		cUsrInput = cInputValidation();
		if (cUsrInput == 'Y' || cUsrInput == 'y')
		{
			bGameStatus = false;
			bRematch = true;
		}
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
			iMovefWidth = ChessLogic_H::iFromCharToInt1(cTwo, &iAtIndex);
			iMovefHeight = ChessLogic_H::iFromCharToInt2(cTwo, &iAtIndex);
			iMoveFrom = ((iMovefWidth)+((iMovefHeight - 1) * iBoardHeight)) - 1;

			iMovetWidth = ChessLogic_H::iFromCharToInt1(cThree, &iAtIndex);
			iMovetHeight = ChessLogic_H::iFromCharToInt2(cThree, &iAtIndex);
			iMoveTo = ((iMovetWidth)+((iMovetHeight - 1) * iBoardHeight)) - 1;

			dHistory.push_back("INFO: iMoveFrom: " + std::to_string(iMoveFrom) + " from Width: " + std::to_string(iMovefWidth) + " and Height: " + std::to_string(iMovefHeight) + "\tiMoveTo: " + std::to_string(iMoveTo) + " from Width: " + std::to_string(iMovetWidth) + " and Height: " + std::to_string(iMovetHeight));
			ChessLogic_H::bSearchObj(sBoard[iMoveFrom]);	//	call function for moving piece
			return;
		}
		else
		{
			dHistory.push_back("ERR: Invalid move location " + cTwo + " to " + cThree + ".");
			sErrorMsg = "Invalid move location.";
			return;
		}
	}	//	END IF command is "move" 
	else if (cOne == "settings" || cOne == "set")
	{
		if (cTwo == "")
		{
			std::cout << "\t\tModifiable parameters and their options:" << std::endl;
			std::cout << "\tboard(b)\t/ large(l), small(s)" << std::endl;
			std::cout << "\tgraphics(g)\t/ true(yes, y), false(no, n)" << std::endl;
			vPause();
			return;
		}
		else if (cTwo == "board" || cTwo == "b")
		{
			if (cThree == "large" || cThree == "l")
				boardType = 'l';
			else if (cThree == "small" || cThree == "s")
				boardType = 's';
			else
			{
				dHistory.push_back("ERR: Invalid command SETTINGS BOARD " + cThree);
				sErrorMsg = "Invalid settings board option";
			}
		}
		else if (cTwo == "graphics" || cTwo == "g")
		{
			if (cThree == "true" || cThree == "yes" || cThree == "y")
				bGraphics = true;
			else if (cThree == "false" || cThree == "no" || cThree == "n")
				bGraphics = false;
			else
			{
				dHistory.push_back("ERR: Invalid command SETTINGS GRAPHICS " + cThree);
				sErrorMsg = "Invalid settings graphics option";
			}
		}
		else
		{
			dHistory.push_back("ERR: Unknown command SETTINGS " + cTwo + cThree);
			sErrorMsg = "Invalid settings parameter";
		}
		return;
	}
	else if (cOne == "what" || cOne == "w")
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

		iCheckWidth = ChessLogic_H::iFromCharToInt1(cTwo, &iAtIndex);
		iCheckHeight = ChessLogic_H::iFromCharToInt2(cTwo, &iAtIndex);
		iCheckLocation = ((iCheckWidth)+((iCheckHeight - 1) * iBoardHeight)) - 1;

		std::cout << "Location: " << iCheckLocation << " on board:" << std::endl;
		std::cout << "\tiBoard:\t\t\"" << iBoard[iCheckLocation] << "\"" << std::endl;
		std::cout << "\tsBoard:\t\t\"" << sBoard[iCheckLocation] << "\"" << std::endl;
		std::cout << "\tCheckBoard:\t\"" << CheckBoard[iCheckLocation] << "\"" << std::endl;
		std::cout << "\tcMoveBoard:\t\"" << cMoveBoard[iCheckLocation] << "\"" << std::endl;
		std::cout << "\tCheckmateBoard:\t\"" << CheckmateBoard[iCheckLocation] << "\"" << std::endl;
		vPause();
		return;
	}
	//clear stream
	dHistory.push_back("ERR: Unknown command issued...");
	std::cerr << "\tUnknown command!" << std::endl;
	std::cout << "\tTry typing 'help' for instructions." << std::endl;
	vPause();
	return;
}		//		END vUsrInput()			//			END vUsrInput()			//		END vUsrInput()		//

void vInputSanitization(std::string *cInput)	//----------vInputSanitization()----------//----------vInputSanitization----------
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
}//		END vInputSanitization()			//			END vInputSanitization()			//		END vInputSanitization()


void vSaveHistory()
{
	std::ofstream historymain;
	historymain.open("common/GN" + std::to_string(GameNumber) + " History");

	if (historymain.is_open())
	{
		for (unsigned int i = mHistoryReadNumber; i < mHistory.size(); i++)
		{
			historymain << i + 1 << ". " << mHistory.at(i) << std::endl;
			mHistoryReadNumber = i - 1;
		}
		historymain.close();
	}
	else
	{
		dHistory.push_back("ERR: Failed to open history file. GN" + std::to_string(GameNumber) + " History");
		sErrorMsg = "Failed to open file!";
	}
	return;
}
void vSaveDebug()
{
	std::ofstream debugmain;
	debugmain.open("common/debug/GN" + std::to_string(GameNumber) + " DEBUG", std::fstream::app);
	if (debugmain.is_open())
	{
		for (unsigned int i = dHistoryReadNumber; i < dHistory.size(); i++)
		{
			debugmain << i + 1 << ". " << dHistory.at(i) << std::endl;
			dHistoryReadNumber = i - 1;
		}
		debugmain.close();
	}
	else
	{
		dHistory.push_back("ERR: Failed to open debug file. GN" + std::to_string(GameNumber) + " Debug");
		std::cerr << "Failed to open debug file!" << std::endl;
	}
	return;
}

void vClearHistory()
{
	if (mHistory.size() != 0)
	{
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
		return;
	}
}
void vClearDebug()
{
	if (dHistory.size() != 0)
	{
		for (size_t j = (dHistory.size()); j > 0; j--)
		{
			dHistory.pop_back();
		}
		dHistoryReadNumber = 0;
	}
	else
	{
		sErrorMsg = "You have no debug history to clear!";
		dHistory.push_back("ERR: No debug history to clear!");
		return;
	}
}

bool bReadHistory()
{
	char cUsrInput = ' ';
	unsigned long iReadNumber = 0;
	std::string sCurrentLine;
	std::string rOne;
	std::string rTwo;
	std::string rThree;
	std::string rFour;
	std::string rFive;
	std::string rSix;
	std::string rSeven;
	std::string rEight;

	for (unsigned int i = 0; i < GameNumber + 1; i++)
	{
		std::ifstream testReadHistory("common/GN" + std::to_string(i) + " History", std::ios::in);
		if (testReadHistory.is_open())
			iValidReadValue.push_back(i);
		else
			testReadHistory.close();
	}
	std::cout << "\n\tWould you like to load a previous game?(Yes/No) > ";
	cUsrInput = cInputValidation();
	if (cUsrInput == 'Y' || cUsrInput == 'y')
	{
		for (unsigned int i = 0; i < iValidReadValue.size(); i++)
		{
			std::cout << "\t" << i + 1 << " " << std::endl;
		}
		std::cout << "\n\tWhich game would you like to load?";
		cUsrInput = cInputValidation();
		for (unsigned int i = 0; i < iValidReadValue.size(); i++)
		{
			if (cUsrInput == iValidReadValue.at(i) - 1)
			{
				rGameNumber = cUsrInput;
				rGameReadValid = true;
			}
			else
				rGameReadValid = false;
			if (rGameReadValid)
				break;
		}
		if (rGameReadValid)
		{
			std::ifstream ReadHistory("common/GN" + std::to_string(rGameNumber) + " History", std::ios::in);	//	Read history file to continue previous game
			if (ReadHistory.is_open())
			{
				std::cout << "\n\tWould you like to load your last played game?(Yes/No) > ";
				cUsrInput = cInputValidation();
				if (cUsrInput == 'Y' || cUsrInput == 'y')
				{
					bool bSeeMoves = false;
					std::cout << "\n\tWould you like to see all the moves?(Yes/No) > ";
					cUsrInput = cInputValidation();
					if (cUsrInput == 'Y' || cUsrInput == 'y')
						bSeeMoves = true;
					dHistory.push_back("------------------------- LOADING GN" + std::to_string(rGameNumber) + " History -----------------------------");
					while (getline(ReadHistory, sCurrentLine))
					{
						vInputInitalization(sCurrentLine, &rOne, &rTwo, &rThree, &rFour, &rFive, &rSix, &rSeven, &rEight);
						ChessLogic_H::vLoadHistory(rOne, rTwo, rThree, rFour, rFive, rSix, rSeven, rEight);
						if (bSeeMoves)
						{
							std::cout << "\n" << std::endl;
							printBoard();
							std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						}
						iReadNumber++;
					}
				}
				else
				{
					return false;
				}
				return true;
			}
		}
		else
		{
			std::cout << "That value didn't seem to work..." << std::endl;
		}
	}
	return false;
}	//	END vReadHistory()

void vInputInitalization(std::string usrInput, std::string* inputOne, std::string* inputTwo, std::string* inputThree, std::string* inputFour, std::string* inputFive, std::string* inputSix, std::string* inputSeven, std::string* inputEight)
{
	size_t lastPhrase = (usrInput.find_last_of(' '));
	size_t nLastPhrase = (usrInput.find_last_of(' '));
	int iEndInput = 0;

	if (!usrInput.empty())
	{
		if (lastPhrase > usrInput.size())
		{
			*inputEight = usrInput;
			iEndInput = 1;
			usrInput.erase();
		}
		else
		{
			*inputEight = usrInput.substr(lastPhrase + 1, usrInput.size());

			while (nLastPhrase == lastPhrase)
			{
				usrInput.pop_back();
				nLastPhrase = (usrInput.find_last_of(' '));
			}
		}
		vInputSanitization(&*inputEight);
	}
	else
	{
		sErrorMsg = "You didn't type anything!";
		return;
	}
	if (!usrInput.empty())
	{
		lastPhrase = (usrInput.find_last_of(' '));
		if (lastPhrase > usrInput.size())
		{
			*inputSeven = usrInput;
			iEndInput = 2;
			usrInput.erase();
		}
		else
		{
			*inputSeven = usrInput.substr(lastPhrase + 1, usrInput.size());

			while (nLastPhrase == lastPhrase)
			{
				usrInput.pop_back();
				nLastPhrase = (usrInput.find_last_of(' '));
			}
		}
		vInputSanitization(&*inputSeven);
	}
	else
	{
		*inputOne = *inputEight;
		*inputTwo = "";
		*inputThree = "";
		*inputFour = "";
		*inputFive = "";
		*inputSix = "";
		*inputSeven = "";
		*inputEight = "";
		return;
	}
	if (!usrInput.empty())
	{
		lastPhrase = (usrInput.find_last_of(' '));
		if (lastPhrase > usrInput.size())
		{
			*inputSix = usrInput;
			iEndInput = 3;
			usrInput.erase();
		}
		else
		{
			*inputSix = usrInput.substr(lastPhrase + 1, usrInput.size());

			while (nLastPhrase == lastPhrase)
			{
				usrInput.pop_back();
				nLastPhrase = (usrInput.find_last_of(' '));
			}
		}
		vInputSanitization(&*inputSix);
	}
	else
	{
		*inputOne = *inputSeven;
		*inputTwo = *inputEight;
		*inputThree = "";
		*inputFour = "";
		*inputFive = "";
		*inputSix = "";
		*inputSeven = "";
		*inputEight = "";
		return;
	}
	if (!usrInput.empty())
	{
		lastPhrase = (usrInput.find_last_of(' '));
		if (lastPhrase > usrInput.size())
		{
			*inputFive = usrInput;
			iEndInput = 4;
			usrInput.erase();
		}
		else
		{
			*inputFive = usrInput.substr(lastPhrase + 1, usrInput.size());

			while (nLastPhrase == lastPhrase)
			{
				usrInput.pop_back();
				nLastPhrase = (usrInput.find_last_of(' '));
			}
		}
		vInputSanitization(&*inputFive);
	}
	else
	{
		*inputOne = *inputSix;
		*inputTwo = *inputSeven;
		*inputThree = *inputEight;
		*inputFour = "";
		*inputFive = "";
		*inputSix = "";
		*inputSeven = "";
		*inputEight = "";
		return;
	}
	if (!usrInput.empty())
	{
		lastPhrase = (usrInput.find_last_of(' '));
		if (lastPhrase > usrInput.size())
		{
			*inputFour = usrInput;
			iEndInput = 5;
			usrInput.erase();
		}
		else
		{
			*inputFour = usrInput.substr(lastPhrase + 1, usrInput.size());

			while (nLastPhrase == lastPhrase)
			{
				usrInput.pop_back();
				nLastPhrase = (usrInput.find_last_of(' '));
			}
		}
		vInputSanitization(&*inputFour);
	}
	else
	{
		*inputOne = *inputFive;
		*inputTwo = *inputSix;
		*inputThree = *inputSeven;
		*inputFour = *inputEight;
		*inputFive = "";
		*inputSix = "";
		*inputSeven = "";
		*inputEight = "";
		return;
	}
	if (!usrInput.empty())
	{
		lastPhrase = (usrInput.find_last_of(' '));
		if (lastPhrase > usrInput.size())
		{
			*inputThree = usrInput;
			iEndInput = 6;
			usrInput.erase();
		}
		else
		{
			*inputThree = usrInput.substr(lastPhrase + 1, usrInput.size());

			while (nLastPhrase == lastPhrase)
			{
				usrInput.pop_back();
				nLastPhrase = (usrInput.find_last_of(' '));
			}
		}
		vInputSanitization(&*inputThree);
	}
	else
	{
		*inputOne = *inputFour;
		*inputTwo = *inputFive;
		*inputThree = *inputSix;
		*inputFour = *inputSeven;
		*inputFive = *inputEight;
		*inputSix = "";
		*inputSeven = "";
		*inputEight = "";
		return;
	}
	if (!usrInput.empty())
	{
		lastPhrase = (usrInput.find_last_of(' '));
		if (lastPhrase > usrInput.size())
		{
			*inputTwo = usrInput;
			iEndInput = 7;
			usrInput.erase();
		}
		else
		{
			*inputTwo = usrInput.substr(lastPhrase + 1, usrInput.size());

			while (nLastPhrase == lastPhrase)
			{
				usrInput.pop_back();
				nLastPhrase = (usrInput.find_last_of(' '));
			}
		}
		vInputSanitization(&*inputSix);
	}
	else
	{
		*inputOne = *inputThree;
		*inputTwo = *inputFour;
		*inputThree = *inputFive;
		*inputFour = *inputSix;
		*inputFive = *inputSeven;
		*inputSix = *inputEight;
		*inputSeven = "";
		*inputEight = "";
		return;
	}
	if (!usrInput.empty())
	{
		lastPhrase = (usrInput.find_last_of(' '));


		if (lastPhrase > usrInput.size())
		{
			*inputOne = usrInput;
			iEndInput = 8;
			usrInput.erase();
		}
		else
		{
			*inputOne = usrInput;

			while (nLastPhrase == lastPhrase)
			{
				usrInput.pop_back();
				nLastPhrase = (usrInput.find_last_of(' '));
			}

		}
		vInputSanitization(&*inputOne);
	}
	else
	{
		if (iEndInput != 1)
		{
			*inputOne = *inputTwo;
			*inputTwo = *inputThree;
			*inputThree = *inputFour;
			*inputFour = *inputFive;
			*inputFive = *inputSix;
			*inputSix = *inputSeven;
			*inputSeven = *inputEight;
			*inputEight = "";
			return;
		}
	}
	return;
}	//	END vInputInitalization()

void printBoard()	//----------printBoard()----------//----------printBoard()----------//----------printBoard()----------
{	
	std::string sTurn;
	std::string sScore;
	unsigned int bIndex = iBoardHeight;
	bool iBoardPrintPieceWhite = false;
	dHistory.push_back("printBoard: CurrentColorIsWhite: " + std::to_string(CurrentColorIsWhite) + "\tbMoveCheck: " + std::to_string(bMoveCheck) + "\twCheck: " + std::to_string(bWhiteKingInCheck) + "\tbCheck: " + std::to_string(bBlackKingInCheck));
	if (bGraphics == true)
	{
		sScore = "\tScore:\t \033[1;107;90mWHITE : " + std::to_string(iWhiteScore) + "\033[0m  /  \033[1;100;97mBLACK : " + std::to_string(iBlackScore) + "\033[0m";
	}
	else
	{
		sScore = "\tScore:\t WHITE : " + std::to_string(iWhiteScore) + "  /  BLACK : " + std::to_string(iBlackScore);
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
	}



	if (boardType == 'l')	//-	- - - - - - - - - boardType Large - - - - - - - - - - // - - - - - - - - - - - boardType Large - - - - - - - - - -
	{
		bool whiteSpace = false;
		int iSpaceNum = 0;
		if (bGraphics == true) { std::cout << "\t\033[1;31m" << sErrorMsg << "\033[0m" << std::endl; }
		else { std::cout << "\t" << sErrorMsg << std::endl; }
		std::cout << "\tc u r r e n t  t u r n: " << sTurn << std::endl;
		std::cout << "\t       A    B    C    D    E    F    G    H    " << sScore << std::endl;
		std::cout << "\t    ========================================== "<< "\tGame Commands\t\t   M O V E  H I S T O R Y";

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
				std::cout << "\t " << bIndex << " | ";
				bIndex--;
			}
			else
			{
				std::cout << "\t   | ";
				iSpaceNum++;
			}

			for (int width = 0; width < iBoardWidth; width++)
			{
				int iBoardPrint = ((width + 1) + ((height / 3) * iBoardHeight)) - 1;
				if (iBoard[iBoardPrint] == 'k' || iBoard[iBoardPrint] == 'q' || iBoard[iBoardPrint] == 'r' || iBoard[iBoardPrint] == 'b' || iBoard[iBoardPrint] == 'n' || iBoard[iBoardPrint] == 'p')
					iBoardPrintPieceWhite = false;
				else if (iBoard[iBoardPrint] == 'K' || iBoard[iBoardPrint] == 'Q' || iBoard[iBoardPrint] == 'R' || iBoard[iBoardPrint] == 'B' || iBoard[iBoardPrint] == 'N' || iBoard[iBoardPrint] == 'P')
					iBoardPrintPieceWhite = true;
				if (whiteSpace == false)
				{

					if ((height - 1) % 3 == 0)
					{
						if (bGraphics == true)
						{
							if (bWhiteKingInCheck == true && iBoard[iBoardPrint] == 'K')
							{
								std::cout << "\033[1;41m  \033[1;" << iWhitePieceColor << "m" << iBoard[iBoardPrint] << "  \033[0m";
							}
							else if (bBlackKingInCheck == true && iBoard[iBoardPrint] == 'k')
							{
								std::cout << "\033[1;41m  \033[1;" << iBlackPieceColor << "m" << iBoard[iBoardPrint] << "  \033[0m";
							}
							else if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] != ' ') && (iBoard[iBoardPrint] == ' '))
							{
								if (iBoardPrintPieceWhite)
									std::cout << "\033[1;42m  \033[1;" << iWhitePieceColor << "m" << iBoard[iBoardPrint] << "  \033[0m";
								else
									std::cout << "\033[1;42m  \033[1;" << iBlackPieceColor << "m" << iBoard[iBoardPrint] << "  \033[0m";
							}
							else
							{
								if (iBoardPrintPieceWhite)
									std::cout << "\033[1;47m  \033[1;" << iWhitePieceColor << "m" << iBoard[iBoardPrint] << "  \033[0m";
								else
									std::cout << "\033[1;47m  \033[1;" << iBlackPieceColor << "m" << iBoard[iBoardPrint] << "  \033[0m";
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
							else if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] != ' ') && (iBoard[iBoardPrint] == ' '))
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
							if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] != ' '))
							{
								if (iThisWhite == true && iBoard[iBoardPrint] != ' ' && !iBoardPrintPieceWhite)
								{
									std::cout << "\033[1;41m \033[0m   \033[1;41m \033[0m";
								}
								else if (iThisWhite == false && iBoard[iBoardPrint] != ' ' && iBoardPrintPieceWhite)
								{
									std::cout << "\033[1;41m \033[0m   \033[1;41m \033[0m";
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
							if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] != ' '))
							{
								if (iThisWhite == true && iBoard[iBoardPrint] != ' ' && !iBoardPrintPieceWhite)
								{
										std::cout << "*   *";
								}
								else if (iThisWhite == false && iBoard[iBoardPrint] != ' ' && iBoardPrintPieceWhite)
								{
										std::cout << "*   *";
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
								std::cout << "\033[1;41m  \033[1;" << iWhitePieceColor << "m" << iBoard[iBoardPrint] << "  \033[0m";
							}
							else if (bBlackKingInCheck == true && iBoard[iBoardPrint] == 'k')
							{
								std::cout << "\033[1;41m  \033[1;" << iBlackPieceColor << "m" << iBoard[iBoardPrint] << "  \033[0m";
							}
							else if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] != ' ') && (iBoard[iBoardPrint] == ' '))
							{
								if (iBoardPrintPieceWhite)
									std::cout << "\033[1;42m  \033[1;" << iWhitePieceColor << "m" << iBoard[iBoardPrint] << "  \033[0m";
								else
									std::cout << "\033[1;42m  \033[1;" << iBlackPieceColor << "m" << iBoard[iBoardPrint] << "  \033[0m";
							}
							else
							{
								if (iBoardPrintPieceWhite)
									std::cout << "\033[1;40m  \033[1;" << iWhitePieceColor << "m" << iBoard[iBoardPrint] << "  \033[0m";
								else
									std::cout << "\033[1;40m  \033[1;" << iBlackPieceColor << "m" << iBoard[iBoardPrint] << "  \033[0m";
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
							else if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] != ' ') && (iBoard[iBoardPrint] == ' '))
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
							if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] != ' '))
							{
								if (iThisWhite == true && iBoard[iBoardPrint] != ' ' && !iBoardPrintPieceWhite)
								{
									std::cout << "\033[1;41m \033[0m   \033[1;41m \033[0m";
								}
								else if (iThisWhite == false && iBoard[iBoardPrint] != ' ' && iBoardPrintPieceWhite)
								{
									std::cout << "\033[1;41m \033[0m   \033[1;41m \033[0m";
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
							if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] != ' '))
							{
								if (iThisWhite == true && iBoard[iBoardPrint] != ' ' && !iBoardPrintPieceWhite)
								{
									std::cout << "*---*";
								}
								else if (iThisWhite == false && iBoard[iBoardPrint] != ' ' && iBoardPrintPieceWhite)
								{
									std::cout << "*---*";
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
			if (height < iBoardHeight * 3 && height < sSidePrint.size())
				std::cout << sSidePrint[height];
			else
			{
				std::cout << "\t\t\t\t";
			}
			if (mHistory.size() < iBoardHeight * 3)
			{
				if (height < mHistory.size())
					std::cout << height + 1 << ". " << mHistory[height];
				else
					std::cout << "Make a move!";
			}
			else if (mHistory.size() > iBoardHeight * 3)
			{
				size_t iPrintHeight = ((mHistory.size()) - (iBoardHeight * 3)) - 1;
				std::cout << iPrintHeight + 1 << ". " << mHistory[iPrintHeight];
			}
		}

		std::cout << std::endl;
		bMoveCheck = false;
		sErrorMsg = "";
		return;
	}	//                      END boardType Large                     //                     END boardType Large

	if (boardType == 's')	// - - - - - - - - - - boardType Small - - - - - - - - - - - - // - - - - - - - - - - - - - boardType Small - - - - - - - - - - - - -
	{
		bool whiteSpace = false;
		std::cout << "\n\n\n\n" << std::endl;
		if (bGraphics == true) {std::cout << "\t\033[1;31m" << sErrorMsg << "\033[0m" << std::endl; }
		else {std::cout << "\t" << sErrorMsg << std::endl; }

		std::cout << "\tcurrent  turn: " << sTurn << std::endl;;
		std::cout << "\t      A  B  C  D  E  F  G  H   " << sScore << std::endl;
		std::cout << "\t    ========================== " << "\tGame Commands\t\t   M O V E  H I S T O R Y";

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
			std::cout << "\t " << bIndex << " | ";
			bIndex--;
			for (int width = 0; width < iBoardWidth; width++)
			{
				int iBoardPrint = ((width + 1) + (height * iBoardHeight)) - 1;
				if (iBoard[iBoardPrint] == 'k' || iBoard[iBoardPrint] == 'q' || iBoard[iBoardPrint] == 'r' || iBoard[iBoardPrint] == 'b' || iBoard[iBoardPrint] == 'n' || iBoard[iBoardPrint] == 'p')
					iBoardPrintPieceWhite = false;
				else if (iBoard[iBoardPrint] == 'K' || iBoard[iBoardPrint] == 'Q' || iBoard[iBoardPrint] == 'R' || iBoard[iBoardPrint] == 'B' || iBoard[iBoardPrint] == 'N' || iBoard[iBoardPrint] == 'P')
					iBoardPrintPieceWhite = true;
				if (whiteSpace == false)
				{
					if (bGraphics == true)
					{
						if (bWhiteKingInCheck == true && iBoard[iBoardPrint] == 'K')
						{
							std::cout << "\033[1;41m\033[1;" << iWhitePieceColor << "m";
						}
						else if (bBlackKingInCheck == true && iBoard[iBoardPrint] == 'k')
						{
							std::cout << "\033[1;41m\033[1;" << iBlackPieceColor << "m";
						}
						else if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] != ' '))
						{
							if (iThisWhite == true && iBoard[iBoardPrint] != ' ' && !iBoardPrintPieceWhite)
							{
								std::cout << "\033[1;42m\033[1;" << iBlackPieceColor << "m";
							}
							else if (iThisWhite == false && iBoard[iBoardPrint] != ' ' && iBoardPrintPieceWhite)
							{
								std::cout << "\033[1;42m\033[1;" << iWhitePieceColor << "m";
							}
							else
							{
								if (iBoardPrintPieceWhite)
									std::cout << "\033[1;42m\033[1;" << iWhitePieceColor << "m";
								else
									std::cout << "\033[1;42m\033[1;" << iBlackPieceColor << "m";
							}
						}
						else
						{
							if (iBoardPrintPieceWhite)
								std::cout << "\033[1;47m\033[1;" << iWhitePieceColor << "m";
							else
								std::cout << "\033[1;47m\033[1;" << iBlackPieceColor << "m";
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
						else if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] != ' '))
						{
							if (iThisWhite == true && iBoard[iBoardPrint] != ' ' && !iBoardPrintPieceWhite)
							{
								std::cout << "*" << iBoard[iBoardPrint] << "*";
							}
							else if (iThisWhite == false && iBoard[iBoardPrint] != ' ' && iBoardPrintPieceWhite)
							{
								std::cout << "*" << iBoard[iBoardPrint] << "*";
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
							std::cout << "\033[1;41m\033[1;" << iWhitePieceColor << "m";
						}
						else if (bBlackKingInCheck == true && iBoard[iBoardPrint] == 'k')
						{
							std::cout << "\033[1;41m\033[1;" << iBlackPieceColor << "m";
						}
						else if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] != ' '))
						{
							if (iThisWhite == true && iBoard[iBoardPrint] != ' ' && !iBoardPrintPieceWhite)
							{
								std::cout << "\033[1;42m\033[1;" << iBlackPieceColor << "m";
							}
							else if (iThisWhite == false && iBoard[iBoardPrint] != ' ' && iBoardPrintPieceWhite)
							{
								std::cout << "\033[1;42m\033[1;" << iWhitePieceColor << "m";
							}
							else
							{
								if (iBoardPrintPieceWhite)
									std::cout << "\033[1;42m\033[1;" << iWhitePieceColor << "m";
								else
									std::cout << "\033[1;42m\033[1;" << iBlackPieceColor << "m";
							}
						}
						else
						{
							if (iBoardPrintPieceWhite)
								std::cout << "\033[1;40m\033[1;" << iWhitePieceColor << "m";
							else
								std::cout << "\033[1;40m\033[1;" << iBlackPieceColor << "m";
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
						else if ((bMoveCheck == true) && (cMoveBoard[iBoardPrint] != ' '))
						{
							if (iThisWhite == true && iBoard[iBoardPrint] != ' ' && !iBoardPrintPieceWhite)
							{
								std::cout << "*" << iBoard[iBoardPrint] << "*";
							}
							else if (iThisWhite == false && iBoard[iBoardPrint] != ' ' && iBoardPrintPieceWhite)
							{
								std::cout << "*" << iBoard[iBoardPrint] << "*";
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
			if (height < iBoardHeight && height < sSidePrint.size())
				std::cout << sSidePrint[height];
			else
			{
				std::cout << "\t\t\t\t";
			}
			if (mHistory.size() < iBoardHeight)
			{
				if (height < mHistory.size())
					std::cout << height + 1 << ". " << mHistory[height];
				else
					std::cout << "Make a move!";
			}
			else if (mHistory.size() > iBoardHeight)
			{
				size_t iPrintHeight = ((mHistory.size()) - (iBoardHeight - 1));
				std::cout << iPrintHeight + 1 << ". " << mHistory[iPrintHeight];
			}
		}
		std::cout << "\n\n\n\n\n\n\n\n\n\n" << std::endl;
		bMoveCheck = false;
		sErrorMsg = "";
		return;
	}	//		END printType SMALL		//		END printType SMALL		//	END printType SMALL		//		END printType SMALL
}	//		END printBoard()		//		END printBoard()		//			END printBoard()		//			END printBoard()