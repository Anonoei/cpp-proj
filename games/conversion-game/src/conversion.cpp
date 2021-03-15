#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <iomanip>

using namespace std;

// This game is meant to help memorize various ASCII equivalances, and maybe Unicode in the future
// This supports hexadecimal, binary, and octal
//
// There are different game modes/difficulties, and hopefully that keeps it entertaining
//
// Created by Devon Adams ("https://github.com/devonadamsofficial/cpp-games")
// Last modified 2020-10-28

void numLogic(string*, string*, int, int, int);	//function prototype declaration for the number logic
void wordpool(string*, string*, int, int);	//function prototype declaration for the ASCII word pool
void wlmsg(int);	//function prototype declaration for the win/lose message logic
void gameBoard(int, int, string*, string*, int, unsigned int*);	//function prototype declaration for gameBoard
int getUsrChoice(int);



int main(void)
{
	srand(time(NULL));	// seed random number for future calculation
	bool game = true;		// declare variable game for the game to be played
	bool nestedGame = false;	// declare variable for nested games
	string codeAnswer = "default";	// declare variable for the source Binary/Octal/Hexadecimal
	string answer = "default";	// declare variable for the correct answer
	int numAnswer = 1;			// declare how many ASCII characters are in the answer
	int gameMode = 0;		// declare integer for how the board will be drawn
	int gameType = 0;		// declare integer for how many conversions will be called
	int cLength = 1;			// declare number of cLength for a specific game type
	unsigned int score = 0;		// declare integer for game score
	string endmsg = "default";	// declare variable for the end message
	string usrInput = "00";		// declare user input variable
	int intUsrInput = 0;	// user input variable

	while (game == true)
	{
		std::cout << "\n\t============================================================" << endl;
		std::cout << "\t=                  Conversion Game v0.0.1                  =" << endl;
		std::cout << "\t============================================================" << endl;
		std::cout << "\t=          < Your current score is: " << score << " points! >    " << endl;
		std::cout << "\t=      Please select your game mode! (type -1 to quit!) > " << endl;
		std::cout << "\t=     1) Single ASCII value" << endl;
		std::cout << "\t=     2) Multiple ASCII values" << endl;
		std::cout << "\t=     3) Tournament Rounds" << endl;
		std::cout << "\t=     4) Random" << endl << endl;
		std::cout << "\t=     >  ";
		intUsrInput = getUsrChoice(intUsrInput);
		if (intUsrInput == 1)
		{
			nestedGame = true;
			while (nestedGame == true)
			{
				cLength = 1;
				system("cls"); // change to system("clear") for Linux!
				std::cout << "\n\t============================================================" << endl;
				std::cout << "\t=           s i n g l e  A S C I I  v a l u e              =" << endl;
				std::cout << "\t============================================================" << endl;
				std::cout << "\t=          < Your current score is: " << score << " points! >    " << endl;
				std::cout << "\t=     What conversions would you like? (type -1 to quit) > " << endl;
				std::cout << "\t=    1) Binary" << endl;
				std::cout << "\t=    2) Octal" << endl;
				std::cout << "\t=    3) Hexadecimal" << endl;
				std::cout << "\t=      <h i n t>: type multiple values! (ie 13 / 23 / 123)" << endl;
				std::cout << "\t=     >  ";
				intUsrInput = getUsrChoice(intUsrInput);
				system("cls"); // change to system("clear") for Linux!

				if (intUsrInput == 1)	// binary only
				{
					gameBoard(gameMode = 1, gameType = 1, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 2)	// Octal only
				{
					gameBoard(gameMode = 1, gameType = 2, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 3)	// Hexadecimal only
				{
					gameBoard(gameMode = 1, gameType = 3, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 12)	// Binary and Octal
				{
					gameBoard(gameMode = 1, gameType = 12, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 13)	// Binary and Hexadecimal
				{
					gameBoard(gameMode = 1, gameType = 13, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 23) // Octal and Hexadecimal
				{
					gameBoard(gameMode = 1, gameType = 23, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 123) // All three
				{
					gameBoard(gameMode = 1, gameType = 123, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == -1)
				{
					std::cout << "\n\n\tAre you sure you want to return to the main menu?" << endl;
					cin >> usrInput;
					if (usrInput == "YES" | usrInput == "Yes" | usrInput == "yes" | usrInput == "Y" | usrInput == "y")
					{
						system("cls"); // change to system("clear") for Linux!
						nestedGame = false;
					}
					else
					{
						system("cls"); // change to system("clear") for Linux!}
					}
				}	// end usrInput -1
				else	// catch all
				{
					std::cout << "\n\nThat response didn't seem to work.." << endl;
					system("pause");	// change to system("read"); for linux
					cin >> usrInput;
					usrInput = "default";
				}

			} // end of nestedGame

		}	// --------------------------------------------------------------  end of usrInput 1 --------------------------------------------------------------------------------
		else if (intUsrInput == 2)
		{
			nestedGame = true;
			std::cout << "\n\tWhat would you like your maximum ASCII length to be? (ie 1 / 5 / 7)" << endl;
			cLength = getUsrChoice(intUsrInput);
			while (nestedGame == true)
			{
				system("cls"); // change to system("clear") for Linux!
				std::cout << "\n\t============================================================" << endl;
				std::cout << "\t=          m u l t i p l e  A S C I I  v a l u e           =" << endl;
				std::cout << "\t============================================================" << endl;
				std::cout << "\t=          < Your current score is: " << score << " points! >    " << endl;
				std::cout << "\t=     What conversions would you like? (type -1 to quit) > " << endl;
				std::cout << "\t=    1) Binary" << endl;
				std::cout << "\t=    2) Octal" << endl;
				std::cout << "\t=    3) Hexadecimal" << endl;
				std::cout << "\t=      <h i n t>: type multiple values! (ie 13 / 23 / 123)" << endl;
				std::cout << "\t=     >  ";
				intUsrInput = getUsrChoice(intUsrInput);
				system("cls"); // change to system("clear") for Linux!

				if (intUsrInput == 1)	// binary only
				{
					gameBoard(gameMode = 2, gameType = 1, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 2)	// Octal only
				{
					gameBoard(gameMode = 2, gameType = 2, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 3)	// Hexadecimal only
				{
					gameBoard(gameMode = 2, gameType = 3, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 12)	// Binary and Octal
				{
					gameBoard(gameMode = 2, gameType = 12, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 13)	// Binary and Hexadecimal
				{
					gameBoard(gameMode = 2, gameType = 13, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 23) // Octal and Hexadecimal
				{
					gameBoard(gameMode = 2, gameType = 23, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 123) // All three
				{
					gameBoard(gameMode = 2, gameType = 123, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == -1)
				{
					std::cout << "\n\n\tAre you sure you want to return to the main menu?" << endl;
					cin >> usrInput;
					if (usrInput == "YES" | usrInput == "Yes" | usrInput == "yes" | usrInput == "Y" | usrInput == "y")
					{
						system("cls"); // change to system("clear") for Linux!
						nestedGame = false;
					}
					else
					{
						system("cls"); // change to system("clear") for Linux!}
					}
				}	// end usrInput -1
				else	// catch all
				{
					std::cout << "\n\nThat response didn't seem to work.." << endl;
					system("pause");	// change to system("read"); for linux
					cin >> usrInput;
					usrInput = "default";
				}

			}	// end of nestedGame

		}	// --------------------------------------------------------------  end of usrInput 2 --------------------------------------------------------------------------------
		else if (intUsrInput == 3)
		{
			nestedGame = true;
			std::cout << "\n\tWhat would you like your maximum ASCII length to be? (ie 1 / 5 / 7)" << endl;
			cin >> cLength;
			while (nestedGame == true)
			{
				system("cls"); // change to system("clear") for Linux!
				std::cout << "\n\t============================================================" << endl;
				std::cout << "\t=       ! ! !  t o u r n a m e n t  g a m e  ! ! !         =" << endl;
				std::cout << "\t============================================================" << endl;
				std::cout << "\t=          < Your current score is: " << score << " points! >    " << endl;
				std::cout << "\t=     What conversions would you like? (type -1 to quit) > " << endl;
				std::cout << "\t=    1) Binary" << endl;
				std::cout << "\t=    2) Octal" << endl;
				std::cout << "\t=    3) Hexadecimal" << endl;
				std::cout << "\t=      <h i n t>: type multiple values! (ie 13 / 23 / 123)" << endl;
				std::cout << "\t=     >  ";
				intUsrInput = getUsrChoice(intUsrInput);
				system("cls"); // change to system("clear") for Linux!

				if (intUsrInput == 1)	// binary only
				{
					gameBoard(gameMode = 3, gameType = 1, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 2)	// Octal only
				{
					gameBoard(gameMode = 3, gameType = 2, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 3)	// Hexadecimal only
				{
					gameBoard(gameMode = 3, gameType = 3, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 12)	// Binary and Octal
				{
					gameBoard(gameMode = 3, gameType = 12, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 13)	// Binary and Hexadecimal
				{
					gameBoard(gameMode = 3, gameType = 13, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 23) // Octal and Hexadecimal
				{
					gameBoard(gameMode = 3, gameType = 23, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 123) // All three
				{
					gameBoard(gameMode = 3, gameType = 123, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == -1)
				{
					std::cout << "\n\n\tAre you sure you want to return to the main menu?" << endl;
					cin >> usrInput;
					if (usrInput == "YES" | usrInput == "Yes" | usrInput == "yes" | usrInput == "Y" | usrInput == "y")
					{
						system("cls"); // change to system("clear") for Linux!
						nestedGame = false;
					}
					else
					{
						system("cls"); // change to system("clear") for Linux!}
					}
				}	// end usrInput -1
				else	// catch all
				{
					std::cout << "\n\nThat response didn't seem to work.." << endl;
					system("pause");	// change to system("read"); for linux
					cin >> usrInput;
					usrInput = "default";
				}

			}	// end of nestedGame

		}	// --------------------------------------------------------------  end of usrInput 3 --------------------------------------------------------------------------------
		else if (usrInput == "4")
		{
			nestedGame = true;
			while (nestedGame == true)
			{
				system("cls"); // change to system("clear") for Linux!
				std::cout << "\n\t============================================================" << endl;
				std::cout << "\t=                   r a n d o m  g a m e                   =" << endl;
				std::cout << "\t============================================================" << endl;
				std::cout << "\t=          < Your current score is: " << score << " points! >    " << endl;
				std::cout << "\t=     What conversions would you like? (type -1 to quit) > " << endl;
				std::cout << "\t=    1) Binary" << endl;
				std::cout << "\t=    2) Octal" << endl;
				std::cout << "\t=    3) Hexadecimal" << endl;
				std::cout << "\t=      <h i n t>: type multiple values! (ie 13 / 23 / 123)" << endl;
				std::cout << "\t=     >  ";
				intUsrInput = getUsrChoice(intUsrInput);
				system("cls"); // change to system("clear") for Linux!

				if (intUsrInput == 1)	// binary only
				{
					gameBoard(gameMode = 4, gameType = 1, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 2)	// Octal only
				{
					gameBoard(gameMode = 4, gameType = 2, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 3)	// Hexadecimal only
				{
					gameBoard(gameMode = 4, gameType = 3, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 12)	// Binary and Octal
				{
					gameBoard(gameMode = 4, gameType = 12, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 13)	// Binary and Hexadecimal
				{
					gameBoard(gameMode = 4, gameType = 13, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 23) // Octal and Hexadecimal
				{
					gameBoard(gameMode = 4, gameType = 23, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == 123) // All three
				{
					gameBoard(gameMode = 4, gameType = 123, &answer, &codeAnswer, cLength, &score);	// call the gameBoard function
				}
				else if (intUsrInput == -1)
				{
					std::cout << "\n\n\tAre you sure you want to return to the main menu?" << endl;
					cin >> usrInput;
					if (usrInput == "YES" | usrInput == "Yes" | usrInput == "yes" | usrInput == "Y" | usrInput == "y")
					{
						system("cls"); // change to system("clear") for Linux!
						nestedGame = false;
					}
					else
					{
						system("cls"); // change to system("clear") for Linux!}
					}
				}	// end usrInput -1
				else	// catch all
				{
					std::cout << "\n\nThat response didn't seem to work.." << endl;
					system("pause");	// change to system("read"); for linux
					cin >> usrInput;
					usrInput = "default";
				}

			}	// end of nestedGame

		}	// --------------------------------------------------------------  end of usrInput 4 --------------------------------------------------------------------------------
		else if (intUsrInput == -1)	// if user requests to exit game
		{
			std::cout << "\n\tAre you sure you want to quit?" << endl;
			cin >> usrInput;
			if (usrInput == "Yes" | usrInput == "yes" | usrInput == "Y" | usrInput == "y")
			{
				system("cls"); // change to system("clear") for Linux!
				game = false;
			} 

		}
		else // catch all
		{
			std::cout << "\n\nThat response didn't seem to work.." << endl;
			system("pause");	// change to system("read"); for linux
			cin >> usrInput;
			usrInput = "default";
		}


	} // end of game loop	


	system("cls");
	std::cout << "Thanks for playing!" << endl;
	return 0;

}	// end of main


int getUsrChoice(int choice)
{
	cin >> setw(1) >> choice;

	
	while (!cin.good())	// error check
	{
		std::cout << "Invalid Input! Try again." << endl;

		//	clear stream
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		std::cout << "Enter your choice again." << endl;
		cin >> setw(1) >> choice;

	}
	//clear stream
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	cout << "User input was " << choice << endl;

	return choice;

}	// end of getUsrChoice



void numLogic(string* answer, string* codeAnswer, int Ansindex, int functionType, int codeAnsLocal)
{
	bool randnumCheck = true;
	int randnum = 0;
	for (int index = 1; Ansindex >= index; index++)
	{
		randnumCheck = true;
		while (randnumCheck == true)
		{
			
			int randnum = rand() % 122 + 48;	// generate pseudo-random number for crunching
			codeAnsLocal = randnum;


			if (randnum >= 48 && randnum <= 57) // check if decimal value is equivalent to an ASCII number and set it
			{
				if (randnum == 48) { *answer = "0"; }
				else if (randnum == 49) { *answer = *answer + "1"; }
				else if (randnum == 50) { *answer = *answer + "2"; }
				else if (randnum == 51) { *answer = *answer + "3"; }
				else if (randnum == 52) { *answer = *answer + "4"; }
				else if (randnum == 53) { *answer = *answer + "5"; }
				else if (randnum == 54) { *answer = *answer + "6"; }
				else if (randnum == 55) { *answer = *answer + "7"; }
				else if (randnum == 56) { *answer = *answer + "8"; }
				else if (randnum == 57) { *answer = *answer + "9"; }


				randnumCheck = false;
			}
			else if (randnum >= 65 && randnum <= 90)	// check if decimal value is equivalent to an ASCII uppercase letter and set it
			{
				if (randnum == 65) { *answer = *answer + "A"; }
				else if (randnum == 66) { *answer = *answer + "B"; }
				else if (randnum == 67) { *answer = *answer + "C"; }
				else if (randnum == 68) { *answer = *answer + "D"; }
				else if (randnum == 69) { *answer = *answer + "E"; }
				else if (randnum == 70) { *answer = *answer + "F"; }
				else if (randnum == 71) { *answer = *answer + "G"; }
				else if (randnum == 72) { *answer = *answer + "H"; }
				else if (randnum == 73) { *answer = *answer + "I"; }
				else if (randnum == 74) { *answer = *answer + "J"; }
				else if (randnum == 75) { *answer = *answer + "K"; }
				else if (randnum == 76) { *answer = *answer + "L"; }
				else if (randnum == 77) { *answer = *answer + "M"; }
				else if (randnum == 78) { *answer = *answer + "N"; }
				else if (randnum == 79) { *answer = *answer + "O"; }
				else if (randnum == 80) { *answer = *answer + "P"; }
				else if (randnum == 81) { *answer = *answer + "Q"; }
				else if (randnum == 82) { *answer = *answer + "R"; }
				else if (randnum == 83) { *answer = *answer + "S"; }
				else if (randnum == 84) { *answer = *answer + "T"; }
				else if (randnum == 85) { *answer = *answer + "U"; }
				else if (randnum == 86) { *answer = *answer + "V"; }
				else if (randnum == 87) { *answer = *answer + "W"; }
				else if (randnum == 88) { *answer = *answer + "X"; }
				else if (randnum == 89) { *answer = *answer + "Y"; }
				else if (randnum == 90) { *answer = *answer + "Z"; }


				randnumCheck = false;
			}
			else if (randnum >= 97 && randnum <= 122)	// check if decimal value is equivalent to an ASCII lowercase letter and set it
			{
				if (randnum == 97) { *answer = *answer + "a"; }
				else if (randnum == 98) { *answer = *answer + "b"; }
				else if (randnum == 99) { *answer = *answer + "c"; }
				else if (randnum == 100) { *answer = *answer + "d"; }
				else if (randnum == 101) { *answer = *answer + "e"; }
				else if (randnum == 102) { *answer = *answer + "f"; }
				else if (randnum == 103) { *answer = *answer + "g"; }
				else if (randnum == 104) { *answer = *answer + "h"; }
				else if (randnum == 105) { *answer = *answer + "i"; }
				else if (randnum == 106) { *answer = *answer + "j"; }
				else if (randnum == 107) { *answer = *answer + "k"; }
				else if (randnum == 108) { *answer = *answer + "l"; }
				else if (randnum == 109) { *answer = *answer + "m"; }
				else if (randnum == 110) { *answer = *answer + "n"; }
				else if (randnum == 111) { *answer = *answer + "o"; }
				else if (randnum == 112) { *answer = *answer + "p"; }
				else if (randnum == 113) { *answer = *answer + "q"; }
				else if (randnum == 114) { *answer = *answer + "r"; }
				else if (randnum == 115) { *answer = *answer + "s"; }
				else if (randnum == 116) { *answer = *answer + "t"; }
				else if (randnum == 117) { *answer = *answer + "u"; }
				else if (randnum == 118) { *answer = *answer + "v"; }
				else if (randnum == 119) { *answer = *answer + "w"; }
				else if (randnum == 120) { *answer = *answer + "x"; }
				else if (randnum == 121) { *answer = *answer + "y"; }
				else if (randnum == 122) { *answer = *answer + "z"; }


				randnumCheck = false;
			}
			else
			{
				randnumCheck = true;
			}

		}	// end randnumCheck

		if (functionType == 1)					// if codeAnswer should be in Binary
		{
			if (codeAnsLocal == 48) { *codeAnswer = *codeAnswer + "00110000"; }
			else if (codeAnsLocal == 49) { *codeAnswer = *codeAnswer + "00110001"; }
			else if (codeAnsLocal == 50) { *codeAnswer = *codeAnswer + "00110010"; }
			else if (codeAnsLocal == 51) { *codeAnswer = *codeAnswer + "00110011"; }
			else if (codeAnsLocal == 52) { *codeAnswer = *codeAnswer + "00110100"; }
			else if (codeAnsLocal == 53) { *codeAnswer = *codeAnswer + "00110101"; }
			else if (codeAnsLocal == 54) { *codeAnswer = *codeAnswer + "00110110"; }
			else if (codeAnsLocal == 55) { *codeAnswer = *codeAnswer + "00110111"; }
			else if (codeAnsLocal == 56) { *codeAnswer = *codeAnswer + "00111000"; }
			else if (codeAnsLocal == 57) { *codeAnswer = *codeAnswer + "00111001"; }

			else if (codeAnsLocal == 65) { *codeAnswer = *codeAnswer + "01000001"; }
			else if (codeAnsLocal == 66) { *codeAnswer = *codeAnswer + "01000010"; }
			else if (codeAnsLocal == 67) { *codeAnswer = *codeAnswer + "01000011"; }
			else if (codeAnsLocal == 68) { *codeAnswer = *codeAnswer + "01000100"; }
			else if (codeAnsLocal == 69) { *codeAnswer = *codeAnswer + "01000101"; }
			else if (codeAnsLocal == 70) { *codeAnswer = *codeAnswer + "01000110"; }
			else if (codeAnsLocal == 71) { *codeAnswer = *codeAnswer + "01000111"; }
			else if (codeAnsLocal == 72) { *codeAnswer = *codeAnswer + "01001000"; }
			else if (codeAnsLocal == 73) { *codeAnswer = *codeAnswer + "01001001"; }
			else if (codeAnsLocal == 74) { *codeAnswer = *codeAnswer + "01001010"; }
			else if (codeAnsLocal == 75) { *codeAnswer = *codeAnswer + "01001011"; }
			else if (codeAnsLocal == 76) { *codeAnswer = *codeAnswer + "01001100"; }
			else if (codeAnsLocal == 77) { *codeAnswer = *codeAnswer + "01001101"; }
			else if (codeAnsLocal == 78) { *codeAnswer = *codeAnswer + "01001110"; }
			else if (codeAnsLocal == 79) { *codeAnswer = *codeAnswer + "01001111"; }
			else if (codeAnsLocal == 80) { *codeAnswer = *codeAnswer + "01010000"; }
			else if (codeAnsLocal == 81) { *codeAnswer = *codeAnswer + "01010001"; }
			else if (codeAnsLocal == 82) { *codeAnswer = *codeAnswer + "01010010"; }
			else if (codeAnsLocal == 83) { *codeAnswer = *codeAnswer + "01010011"; }
			else if (codeAnsLocal == 84) { *codeAnswer = *codeAnswer + "01010100"; }
			else if (codeAnsLocal == 85) { *codeAnswer = *codeAnswer + "01010101"; }
			else if (codeAnsLocal == 86) { *codeAnswer = *codeAnswer + "01010110"; }
			else if (codeAnsLocal == 87) { *codeAnswer = *codeAnswer + "01010111"; }
			else if (codeAnsLocal == 88) { *codeAnswer = *codeAnswer + "01011000"; }
			else if (codeAnsLocal == 89) { *codeAnswer = *codeAnswer + "01011001"; }
			else if (codeAnsLocal == 90) { *codeAnswer = *codeAnswer + "01011010"; }

			else if (codeAnsLocal == 97) { *codeAnswer = *codeAnswer + "01100001"; }
			else if (codeAnsLocal == 98) { *codeAnswer = *codeAnswer + "01100010"; }
			else if (codeAnsLocal == 99) { *codeAnswer = *codeAnswer + "01100011"; }
			else if (codeAnsLocal == 100) { *codeAnswer = *codeAnswer + "01100100"; }
			else if (codeAnsLocal == 101) { *codeAnswer = *codeAnswer + "01100101"; }
			else if (codeAnsLocal == 102) { *codeAnswer = *codeAnswer + "01100110"; }
			else if (codeAnsLocal == 103) { *codeAnswer = *codeAnswer + "01100111"; }
			else if (codeAnsLocal == 104) { *codeAnswer = *codeAnswer + "01101000"; }
			else if (codeAnsLocal == 105) { *codeAnswer = *codeAnswer + "01101001"; }
			else if (codeAnsLocal == 106) { *codeAnswer = *codeAnswer + "01101010"; }
			else if (codeAnsLocal == 107) { *codeAnswer = *codeAnswer + "01101011"; }
			else if (codeAnsLocal == 108) { *codeAnswer = *codeAnswer + "01101100"; }
			else if (codeAnsLocal == 109) { *codeAnswer = *codeAnswer + "01101101"; }
			else if (codeAnsLocal == 110) { *codeAnswer = *codeAnswer + "01101110"; }
			else if (codeAnsLocal == 111) { *codeAnswer = *codeAnswer + "01101111"; }
			else if (codeAnsLocal == 112) { *codeAnswer = *codeAnswer + "01110000"; }
			else if (codeAnsLocal == 113) { *codeAnswer = *codeAnswer + "01110001"; }
			else if (codeAnsLocal == 114) { *codeAnswer = *codeAnswer + "01110010"; }
			else if (codeAnsLocal == 115) { *codeAnswer = *codeAnswer + "01110011"; }
			else if (codeAnsLocal == 116) { *codeAnswer = *codeAnswer + "01110100"; }
			else if (codeAnsLocal == 117) { *codeAnswer = *codeAnswer + "01110101"; }
			else if (codeAnsLocal == 118) { *codeAnswer = *codeAnswer + "01110110"; }
			else if (codeAnsLocal == 119) { *codeAnswer = *codeAnswer + "01110111"; }
			else if (codeAnsLocal == 120) { *codeAnswer = *codeAnswer + "01111000"; }
			else if (codeAnsLocal == 121) { *codeAnswer = *codeAnswer + "01111001"; }
			else if (codeAnsLocal == 122) { *codeAnswer = *codeAnswer + "01111010"; }
		}
		else if (functionType == 2)				// if codeAnswer should be in Octal
		{
			if (codeAnsLocal == 48) { *codeAnswer = *codeAnswer + "61"; }
			else if (codeAnsLocal == 49) { *codeAnswer = *codeAnswer + "62"; }
			else if (codeAnsLocal == 50) { *codeAnswer = *codeAnswer + "63"; }
			else if (codeAnsLocal == 51) { *codeAnswer = *codeAnswer + "64"; }
			else if (codeAnsLocal == 52) { *codeAnswer = *codeAnswer + "65"; }
			else if (codeAnsLocal == 53) { *codeAnswer = *codeAnswer + "66"; }
			else if (codeAnsLocal == 54) { *codeAnswer = *codeAnswer + "67"; }
			else if (codeAnsLocal == 55) { *codeAnswer = *codeAnswer + "70"; }
			else if (codeAnsLocal == 56) { *codeAnswer = *codeAnswer + "71"; }
			else if (codeAnsLocal == 57) { *codeAnswer = *codeAnswer + "72"; }

			else if (codeAnsLocal == 65) { *codeAnswer = *codeAnswer + "101"; }
			else if (codeAnsLocal == 66) { *codeAnswer = *codeAnswer + "102"; }
			else if (codeAnsLocal == 67) { *codeAnswer = *codeAnswer + "103"; }
			else if (codeAnsLocal == 68) { *codeAnswer = *codeAnswer + "104"; }
			else if (codeAnsLocal == 69) { *codeAnswer = *codeAnswer + "105"; }
			else if (codeAnsLocal == 70) { *codeAnswer = *codeAnswer + "106"; }
			else if (codeAnsLocal == 71) { *codeAnswer = *codeAnswer + "107"; }
			else if (codeAnsLocal == 72) { *codeAnswer = *codeAnswer + "110"; }
			else if (codeAnsLocal == 73) { *codeAnswer = *codeAnswer + "111"; }
			else if (codeAnsLocal == 74) { *codeAnswer = *codeAnswer + "112"; }
			else if (codeAnsLocal == 75) { *codeAnswer = *codeAnswer + "113"; }
			else if (codeAnsLocal == 76) { *codeAnswer = *codeAnswer + "114"; }
			else if (codeAnsLocal == 77) { *codeAnswer = *codeAnswer + "115"; }
			else if (codeAnsLocal == 78) { *codeAnswer = *codeAnswer + "116"; }
			else if (codeAnsLocal == 79) { *codeAnswer = *codeAnswer + "117"; }
			else if (codeAnsLocal == 80) { *codeAnswer = *codeAnswer + "120"; }
			else if (codeAnsLocal == 81) { *codeAnswer = *codeAnswer + "121"; }
			else if (codeAnsLocal == 82) { *codeAnswer = *codeAnswer + "122"; }
			else if (codeAnsLocal == 83) { *codeAnswer = *codeAnswer + "123"; }
			else if (codeAnsLocal == 84) { *codeAnswer = *codeAnswer + "124"; }
			else if (codeAnsLocal == 85) { *codeAnswer = *codeAnswer + "125"; }
			else if (codeAnsLocal == 86) { *codeAnswer = *codeAnswer + "126"; }
			else if (codeAnsLocal == 87) { *codeAnswer = *codeAnswer + "127"; }
			else if (codeAnsLocal == 88) { *codeAnswer = *codeAnswer + "130"; }
			else if (codeAnsLocal == 89) { *codeAnswer = *codeAnswer + "131"; }
			else if (codeAnsLocal == 90) { *codeAnswer = *codeAnswer + "132"; }

			else if (codeAnsLocal == 97) { *codeAnswer = *codeAnswer + "141"; }
			else if (codeAnsLocal == 98) { *codeAnswer = *codeAnswer + "142"; }
			else if (codeAnsLocal == 99) { *codeAnswer = *codeAnswer + "143"; }
			else if (codeAnsLocal == 100) { *codeAnswer = *codeAnswer + "144"; }
			else if (codeAnsLocal == 101) { *codeAnswer = *codeAnswer + "145"; }
			else if (codeAnsLocal == 102) { *codeAnswer = *codeAnswer + "146"; }
			else if (codeAnsLocal == 103) { *codeAnswer = *codeAnswer + "147"; }
			else if (codeAnsLocal == 104) { *codeAnswer = *codeAnswer + "150"; }
			else if (codeAnsLocal == 105) { *codeAnswer = *codeAnswer + "151"; }
			else if (codeAnsLocal == 106) { *codeAnswer = *codeAnswer + "152"; }
			else if (codeAnsLocal == 107) { *codeAnswer = *codeAnswer + "153"; }
			else if (codeAnsLocal == 108) { *codeAnswer = *codeAnswer + "154"; }
			else if (codeAnsLocal == 109) { *codeAnswer = *codeAnswer + "155"; }
			else if (codeAnsLocal == 110) { *codeAnswer = *codeAnswer + "156"; }
			else if (codeAnsLocal == 111) { *codeAnswer = *codeAnswer + "157"; }
			else if (codeAnsLocal == 112) { *codeAnswer = *codeAnswer + "160"; }
			else if (codeAnsLocal == 113) { *codeAnswer = *codeAnswer + "161"; }
			else if (codeAnsLocal == 114) { *codeAnswer = *codeAnswer + "162"; }
			else if (codeAnsLocal == 115) { *codeAnswer = *codeAnswer + "163"; }
			else if (codeAnsLocal == 116) { *codeAnswer = *codeAnswer + "164"; }
			else if (codeAnsLocal == 117) { *codeAnswer = *codeAnswer + "165"; }
			else if (codeAnsLocal == 118) { *codeAnswer = *codeAnswer + "166"; }
			else if (codeAnsLocal == 119) { *codeAnswer = *codeAnswer + "167"; }
			else if (codeAnsLocal == 120) { *codeAnswer = *codeAnswer + "170"; }
			else if (codeAnsLocal == 121) { *codeAnswer = *codeAnswer + "171"; }
			else if (codeAnsLocal == 122) { *codeAnswer = *codeAnswer + "172"; }
		}
		else if (functionType == 3)			// if codeAnswer should be in Hexadecimal
		{
			if (codeAnsLocal == 48) { *codeAnswer = *codeAnswer + "30"; }
			else if (codeAnsLocal == 49) { *codeAnswer = *codeAnswer + "31"; }
			else if (codeAnsLocal == 50) { *codeAnswer = *codeAnswer + "32"; }
			else if (codeAnsLocal == 51) { *codeAnswer = *codeAnswer + "33"; }
			else if (codeAnsLocal == 52) { *codeAnswer = *codeAnswer + "34"; }
			else if (codeAnsLocal == 53) { *codeAnswer = *codeAnswer + "35"; }
			else if (codeAnsLocal == 54) { *codeAnswer = *codeAnswer + "36"; }
			else if (codeAnsLocal == 55) { *codeAnswer = *codeAnswer + "37"; }
			else if (codeAnsLocal == 56) { *codeAnswer = *codeAnswer + "38"; }
			else if (codeAnsLocal == 57) { *codeAnswer = *codeAnswer + "39"; }

			else if (codeAnsLocal == 65) { *codeAnswer = *codeAnswer + "41"; }
			else if (codeAnsLocal == 66) { *codeAnswer = *codeAnswer + "42"; }
			else if (codeAnsLocal == 67) { *codeAnswer = *codeAnswer + "43"; }
			else if (codeAnsLocal == 68) { *codeAnswer = *codeAnswer + "44"; }
			else if (codeAnsLocal == 69) { *codeAnswer = *codeAnswer + "45"; }
			else if (codeAnsLocal == 70) { *codeAnswer = *codeAnswer + "46"; }
			else if (codeAnsLocal == 71) { *codeAnswer = *codeAnswer + "47"; }
			else if (codeAnsLocal == 72) { *codeAnswer = *codeAnswer + "48"; }
			else if (codeAnsLocal == 73) { *codeAnswer = *codeAnswer + "49"; }
			else if (codeAnsLocal == 74) { *codeAnswer = *codeAnswer + "4A"; }
			else if (codeAnsLocal == 75) { *codeAnswer = *codeAnswer + "4B"; }
			else if (codeAnsLocal == 76) { *codeAnswer = *codeAnswer + "4C"; }
			else if (codeAnsLocal == 77) { *codeAnswer = *codeAnswer + "4D"; }
			else if (codeAnsLocal == 78) { *codeAnswer = *codeAnswer + "4E"; }
			else if (codeAnsLocal == 79) { *codeAnswer = *codeAnswer + "4F"; }
			else if (codeAnsLocal == 80) { *codeAnswer = *codeAnswer + "50"; }
			else if (codeAnsLocal == 81) { *codeAnswer = *codeAnswer + "51"; }
			else if (codeAnsLocal == 82) { *codeAnswer = *codeAnswer + "52"; }
			else if (codeAnsLocal == 83) { *codeAnswer = *codeAnswer + "53"; }
			else if (codeAnsLocal == 84) { *codeAnswer = *codeAnswer + "54"; }
			else if (codeAnsLocal == 85) { *codeAnswer = *codeAnswer + "55"; }
			else if (codeAnsLocal == 86) { *codeAnswer = *codeAnswer + "56"; }
			else if (codeAnsLocal == 87) { *codeAnswer = *codeAnswer + "57"; }
			else if (codeAnsLocal == 88) { *codeAnswer = *codeAnswer + "58"; }
			else if (codeAnsLocal == 89) { *codeAnswer = *codeAnswer + "59"; }
			else if (codeAnsLocal == 90) { *codeAnswer = *codeAnswer + "5A"; }

			else if (codeAnsLocal == 97) { *codeAnswer = *codeAnswer + "61"; }
			else if (codeAnsLocal == 98) { *codeAnswer = *codeAnswer + "62"; }
			else if (codeAnsLocal == 99) { *codeAnswer = *codeAnswer + "63"; }
			else if (codeAnsLocal == 100) { *codeAnswer = *codeAnswer + "64"; }
			else if (codeAnsLocal == 101) { *codeAnswer = *codeAnswer + "65"; }
			else if (codeAnsLocal == 102) { *codeAnswer = *codeAnswer + "66"; }
			else if (codeAnsLocal == 103) { *codeAnswer = *codeAnswer + "67"; }
			else if (codeAnsLocal == 104) { *codeAnswer = *codeAnswer + "68"; }
			else if (codeAnsLocal == 105) { *codeAnswer = *codeAnswer + "69"; }
			else if (codeAnsLocal == 106) { *codeAnswer = *codeAnswer + "6A"; }
			else if (codeAnsLocal == 107) { *codeAnswer = *codeAnswer + "6B"; }
			else if (codeAnsLocal == 108) { *codeAnswer = *codeAnswer + "6C"; }
			else if (codeAnsLocal == 109) { *codeAnswer = *codeAnswer + "6D"; }
			else if (codeAnsLocal == 110) { *codeAnswer = *codeAnswer + "6E"; }
			else if (codeAnsLocal == 111) { *codeAnswer = *codeAnswer + "6F"; }
			else if (codeAnsLocal == 112) { *codeAnswer = *codeAnswer + "70"; }
			else if (codeAnsLocal == 113) { *codeAnswer = *codeAnswer + "71"; }
			else if (codeAnsLocal == 114) { *codeAnswer = *codeAnswer + "72"; }
			else if (codeAnsLocal == 115) { *codeAnswer = *codeAnswer + "73"; }
			else if (codeAnsLocal == 116) { *codeAnswer = *codeAnswer + "74"; }
			else if (codeAnsLocal == 117) { *codeAnswer = *codeAnswer + "75"; }
			else if (codeAnsLocal == 118) { *codeAnswer = *codeAnswer + "76"; }
			else if (codeAnsLocal == 119) { *codeAnswer = *codeAnswer + "77"; }
			else if (codeAnsLocal == 120) { *codeAnswer = *codeAnswer + "78"; }
			else if (codeAnsLocal == 121) { *codeAnswer = *codeAnswer + "79"; }
			else if (codeAnsLocal == 122) { *codeAnswer = *codeAnswer + "7A"; }

		}
		else
		{
			*codeAnswer = codeAnsLocal;
		}

	} // end of FOR loop

	return;
} // end number logic


void wordpool(string* answer, string* codeAnswer, int Ansindex, int functionType)
{
	int randWord = rand() % 20 + 1;
	if (Ansindex == 2)
	{
		if (randWord == 1) { numLogic(answer, codeAnswer, 1, functionType, 65); numLogic(answer, codeAnswer, 1, functionType, 84); }	// ASCII AT
		else if (randWord == 2) { numLogic(answer, codeAnswer, 1, functionType, 97); numLogic(answer, codeAnswer, 1, functionType, 116); }	// ASCII at
		else if (randWord == 3) { numLogic(answer, codeAnswer, 1, functionType, 97); numLogic(answer, codeAnswer, 1, functionType, 116); }	// ASCII IF
		else if (randWord == 4) { numLogic(answer, codeAnswer, 1, functionType, 97); numLogic(answer, codeAnswer, 1, functionType, 116); }	// ASCII if
		else if (randWord == 5) { numLogic(answer, codeAnswer, 1, functionType, 97); numLogic(answer, codeAnswer, 1, functionType, 116); }	// ASCII MY
		else if (randWord == 6) { numLogic(answer, codeAnswer, 1, functionType, 97); numLogic(answer, codeAnswer, 1, functionType, 116); }	// ASCII my
		else if (randWord == 7) { numLogic(answer, codeAnswer, 1, functionType, 97); numLogic(answer, codeAnswer, 1, functionType, 116); }	// ASCII at
		else if (randWord == 8) { numLogic(answer, codeAnswer, 1, functionType, 97); numLogic(answer, codeAnswer, 1, functionType, 116); }	// ASCII at
		else if (randWord == 9) { numLogic(answer, codeAnswer, 1, functionType, 97); numLogic(answer, codeAnswer, 1, functionType, 116); }	// ASCII at
		else if (randWord == 10) { numLogic(answer, codeAnswer, 1, functionType, 97); numLogic(answer, codeAnswer, 1, functionType, 116); }	// ASCII at
		else if (randWord == 11) { numLogic(answer, codeAnswer, 1, functionType, 97); numLogic(answer, codeAnswer, 1, functionType, 116); }	// ASCII at
		else if (randWord == 12) { numLogic(answer, codeAnswer, 1, functionType, 97); numLogic(answer, codeAnswer, 1, functionType, 116); }	// ASCII at
		else if (randWord == 13) { numLogic(answer, codeAnswer, 1, functionType, 97); numLogic(answer, codeAnswer, 1, functionType, 116); }	// ASCII at
		else if (randWord == 14) { numLogic(answer, codeAnswer, 1, functionType, 97); numLogic(answer, codeAnswer, 1, functionType, 116); }	// ASCII at
		else if (randWord == 15) { numLogic(answer, codeAnswer, 1, functionType, 97); numLogic(answer, codeAnswer, 1, functionType, 116); }	// ASCII at
		else if (randWord == 16) { numLogic(answer, codeAnswer, 1, functionType, 97); numLogic(answer, codeAnswer, 1, functionType, 116); }	// ASCII at
		else if (randWord == 17) { numLogic(answer, codeAnswer, 1, functionType, 97); numLogic(answer, codeAnswer, 1, functionType, 116); }	// ASCII at
		else if (randWord == 18) { numLogic(answer, codeAnswer, 1, functionType, 97); numLogic(answer, codeAnswer, 1, functionType, 116); }	// ASCII at
		else if (randWord == 19) { numLogic(answer, codeAnswer, 1, functionType, 97); numLogic(answer, codeAnswer, 1, functionType, 116); }	// ASCII at
		else if (randWord == 20) { numLogic(answer, codeAnswer, 1, functionType, 97); numLogic(answer, codeAnswer, 1, functionType, 116); }	// ASCII at

	}

}	// end word pool

void wlmsg(int wlInt)
{

} // end win / lose message logic

void gameBoard(int gameMode, int gameType, string* answer, string* codeAnswer, int index, unsigned int *score)
{
	bool gameLoop = true;	// set looping function for the "rounds" variable
	int fGameType = 0;	// set function game type so the main gametype doesn't need to be modified
	int randWoR = 0;	// set random Word or Random choice to 0, meaning randomly generated ASCII values
	bool gameWin = false;	// set game win to false
	string fUsrInput = "0";	// set function user input string
	*codeAnswer = "";	// set codeAnswer to nothing
	*answer = "";		// set answer to nothing

	// gameType 1 = binary
	// gameType 2 = Octal
	// gameType 3 = Hexadecimal
	// gameType 0 = decimal

		int randAoC = rand() % 3 + 1;	// set random for the answer being in code or decimal
		unsigned int randIndex = rand() % index + 1;	// set random number for the amount of ASCII characters to use
		if (gameType == 1)		// logic for picking the binary/octal/hexadecimal question/response
		{
			fGameType = 1;
		} // end BINARY game type
		else if (gameType == 2)
		{
			fGameType = 2;
		} // end OCTAL game type
		else if (gameType == 3)
		{
			fGameType = 3;
		} // end HEXADECIMAL game type
		else if (gameType == 12)
		{
			fGameType = rand() % 2 + 1;
			if (fGameType == 1)
			{
				fGameType = 1;
			}
			else if (fGameType == 2)
			{
				fGameType = 2;
			}

		} // end random BINARY / OCTAL game type
		else if (gameType == 13)
		{
			fGameType = rand() % 2 + 1;
			if (fGameType == 1)
			{
				fGameType = 1;
			}
			else if (fGameType == 2)
			{
				fGameType = 3;
			}
		} // end random BINARY / HEXADECIMAL game type
		else if (gameType == 23)
		{
			fGameType = rand() % 2 + 1;
			if (fGameType == 1)
			{
				fGameType = 2;
			}
			else if (fGameType == 2)
			{
				fGameType = 3;
			}
		} // end random OCTAL / HEXADECIMAL game type
		else if (gameType == 123)
		{
			fGameType = rand() % 3 + 1;
			if (fGameType == 1)
			{
				fGameType = 1;
			}
			else if (fGameType == 2)
			{
				fGameType = 2;
			}
			else if (fGameType == 3)
			{
				fGameType = 3;
			}
		} // end random BINARY / OCTAL / HEXADECIMAL game type

			// SYNTAX FOR CALLING LOGIC FUNCTION
			//
			//numLogic(memory address of answer, memory address of codeAnswer, number of ASCII characters, decimal/binary/octal/hexadecimal, wordpool value);
			//numLogic(answer, codeAnswer, index, 0/1/2/3, 0);

		if (gameType == 1)		// if gametype is only BINARY
		{
			std::cout << "\n\t============================================================" << endl;
			std::cout << "\t=            b i n a r y  c o n v e r s i o n              =" << endl;
			std::cout << "\t============================================================\n" << endl;
			numLogic(answer, codeAnswer, randIndex, 1, 0);		// call logic function
			if (randAoC == 1)
			{
				std::cout << "What is binary \"" << *codeAnswer << "\" in ASCII?" << endl;
				cin >> setw(randIndex) >> fUsrInput;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				if (fUsrInput == *answer)
				{
					gameWin = true;
				}
			}
			else
			{
				std::cout << "What is ASCII \"" << *answer << "\" in BINARY?" << endl;
				cin >> setw(randIndex * 8) >> fUsrInput;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				if (fUsrInput == *codeAnswer)
				{
					gameWin = true;
				}
			}

		}
		else if (gameType == 2)		// if gametype is only OCTAL
		{
			std::cout << "\n\t============================================================" << endl;
			std::cout << "\t=              o c t a l  c o n v e r s i o n              =" << endl;
			std::cout << "\t============================================================\n" << endl;
			numLogic(answer, codeAnswer, randIndex, 2, 0);	// call logic function
			if (randAoC == 1)
			{
				std::cout << "What is octal \"" << *codeAnswer << "\" in ASCII?" << endl;
				cin >> setw(randIndex) >> fUsrInput;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				if (fUsrInput == *answer)
				{
					gameWin = true;
				}
			}
			else
			{
				std::cout << "What is ASCII \"" << *answer << "\" in OCTAL?" << endl;
				cin >> setw(randIndex * 3) >> fUsrInput;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				if (fUsrInput == *codeAnswer)
				{
					gameWin = true;
				}
			}
		}
		else if (gameType == 3)		 // if gametype is HEXADECIMAL
		{
			std::cout << "\n\t============================================================" << endl;
			std::cout << "\t=       h e x a d e c i m a l  c o n v e r s i o n         =" << endl;
			std::cout << "\t============================================================\n" << endl;
			numLogic(answer, codeAnswer, randIndex, 3, 0);	// call logic function
			if (randAoC == 1)
			{
				std::cout << "What is hexadecimal \"" << *codeAnswer << "\" in ASCII?" << endl;
				cin >> setw(randIndex) >> fUsrInput;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				if (fUsrInput == *answer)
				{
					gameWin = true;
				}
			}
			else
			{
				std::cout << "What is ASCII \"" << *answer << "\" in HEXADECIMAL?" << endl;
				cin >> setw(randIndex * 2) >> fUsrInput;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				if (fUsrInput == *codeAnswer)
				{
					gameWin = true;
				}
			}

		}
		else
		{
			// randWoR = rand() % 2 + 1;
			int randIndex = rand() % 10 + 1;
			std::cout << "\n\t============================================================" << endl;
			std::cout << "\t=            d e c i m a l  c o n v e r s i o n            =" << endl;
			std::cout << "\t============================================================\n" << endl;
			numLogic(answer, codeAnswer, randIndex, 0, 0);	// call logic function
			if (randAoC == 1)
			{
				std::cout << "What is \"" << *codeAnswer << "\" in ASCII?" << endl;
				cin >> setw(randIndex) >> fUsrInput;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				if (fUsrInput == *answer)
				{
					gameWin = true;
				}
			}
			else
			{
				std::cout << "What is \"" << *answer << "\" in DECIMAL?" << endl;
				cin >> setw(randIndex) >> fUsrInput;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				if (fUsrInput == *codeAnswer)
				{
					gameWin = true;
				}
			}


		}


		if (gameWin == true)
		{
			std::cout << "You're right!\n\"" << *codeAnswer << "\" is \"" << *answer << "\" in ASCII!" << endl;
			std::cout << "You gained " << (randIndex * 10) << " points!" << endl;
			*score = *score + (index * 10);
			system("pause");	// change to system("read"); for linux
		}
		else
		{
			std::cout << "That's not right...\n\"" << *codeAnswer << "\" is \"" << *answer << "\" in ASCII" << endl;
			std::cout << "You lost " << (randIndex * 5) << " points" << endl;

			if (*score <= randIndex * 5)
			{
				*score = 0;
			}
			else
			{
				
				*score = *score - (index * 5);
			}
			system("pause");
		}



	return;

} // end gameboard draw logic