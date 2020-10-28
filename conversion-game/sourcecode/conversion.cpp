#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

// This game is meant to help memorize various ASCII equivalances, and maybe Unicode in the future
// This supports hexadecimal, binary, and octal
//
// There are different game modes/difficulties, and hopefully that keeps it entertaining
//
// Created by Devon Adams ("https://github.com/devonadamsofficial/cpp-games")
// Last modified 2020-10-28

void numLogic(string*, string*, int, int);	//function prototype declaration for the number logic
void wordpool(string*, int);	//function prototype declaration for the ASCII word pool
void wlmsg();	//function prototype declaration for the win/lose message logic
void gameBoard(int, int, string*, string*, int);	//function prototype declaration for gameBoard


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
	int rounds = 1;			// declare number of rounds for a specific game type
	int score = 0;		// declare integer for game score
	string endmsg = "default";	// declare variable for the end message
	string usrInput = "00";		// declare user input variable

	while (game == true)
	{
		cout << "\n\t============================================================" << endl;
		cout << "\t=                  Conversion Game v0.0.1                  =" << endl;
		cout << "\t============================================================" << endl;
		cout << "\t=          < Your current score is: " << score << " points! >    " << endl;
		cout << "\t=      Please select your game mode! (type -1 to quit!) > " << endl;
		cout << "\t=     1) Single ASCII value" << endl;
		cout << "\t=     2) Multiple ASCII values" << endl;
		cout << "\t=     3) Tournament Rounds" << endl;
		cout << "\t=     4) Random" << endl << endl;
		cout << "\t=     >  ";
		cin >> usrInput;
		system("cls"); // change to system("clear") for Linux!
		if (usrInput == "1")
		{
			nestedGame = true;
			while (nestedGame == true)
			{
				cout << "\n\t============================================================" << endl;
				cout << "\t=           s i n g l e  A S C I I  v a l u e              =" << endl;
				cout << "\t============================================================" << endl;
				cout << "\t=          < Your current score is: " << score << " points! >    " << endl;
				cout << "\t=     What conversions would you like? (type -1 to quit) > " << endl;
				cout << "\t=    1) Binary" << endl;
				cout << "\t=    2) Octal" << endl;
				cout << "\t=    3) Hexadecimal" << endl;
				cout << "\t=      <h i n t>: type multiple values! (ie 13 / 23 / 123)" << endl;
				cout << "\t=     >  ";
				cin >> usrInput;
				system("cls"); // change to system("clear") for Linux!

				if (usrInput == "1")	// binary only
				{
					gameBoard(gameMode = 1, gameType = 1, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "2")	// Octal only
				{
					gameBoard(gameMode = 1, gameType = 2, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "3")	// Hexadecimal only
				{
					gameBoard(gameMode = 1, gameType = 3, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "12")	// Binary and Octal
				{
					gameBoard(gameMode = 1, gameType = 12, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "13")	// Binary and Hexadecimal
				{
					gameBoard(gameMode = 1, gameType = 13, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "23") // Octal and Hexadecimal
				{
					gameBoard(gameMode = 1, gameType = 23, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "123") // All three
				{
					gameBoard(gameMode = 1, gameType = 123, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "-1")
				{
					cout << "\n\n\tAre you sure you want to return to the main menu?" << endl;
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
					cout << "\n\nThat response didn't seem to work.." << endl;
					cout << "Press enter to continue" << endl;
					cin >> usrInput;
					usrInput = "default";
				}

			} // end of nestedGame

		}	// --------------------------------------------------------------  end of usrInput 1 --------------------------------------------------------------------------------
		else if (usrInput == "2")
		{
			nestedGame = true;
			while (nestedGame == true)
			{
				cout << "\n\t============================================================" << endl;
				cout << "\t=          m u l t i p l e  A S C I I  v a l u e           =" << endl;
				cout << "\t============================================================" << endl;
				cout << "\t=          < Your current score is: " << score << " points! >    " << endl;
				cout << "\t=     What conversions would you like? (type -1 to quit) > " << endl;
				cout << "\t=    1) Binary" << endl;
				cout << "\t=    2) Octal" << endl;
				cout << "\t=    3) Hexadecimal" << endl;
				cout << "\t=      <h i n t>: type multiple values! (ie 13 / 23 / 123)" << endl;
				cout << "\t=     >  ";
				cin >> usrInput;
				system("cls"); // change to system("clear") for Linux!

				if (usrInput == "1")	// binary only
				{
					gameBoard(gameMode = 2, gameType = 1, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "2")	// Octal only
				{
					gameBoard(gameMode = 2, gameType = 2, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "3")	// Hexadecimal only
				{
					gameBoard(gameMode = 2, gameType = 3, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "12")	// Binary and Octal
				{
					gameBoard(gameMode = 2, gameType = 12, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "13")	// Binary and Hexadecimal
				{
					gameBoard(gameMode = 2, gameType = 13, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "23") // Octal and Hexadecimal
				{
					gameBoard(gameMode = 2, gameType = 23, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "123") // All three
				{
					gameBoard(gameMode = 2, gameType = 123, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "-1")
				{
					cout << "\n\n\tAre you sure you want to return to the main menu?" << endl;
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
					cout << "\n\nThat response didn't seem to work.." << endl;
					cout << "Press enter to continue" << endl;
					cin >> usrInput;
					usrInput = "default";
				}

			}	// end of nestedGame

		}	// --------------------------------------------------------------  end of usrInput 2 --------------------------------------------------------------------------------
		else if (usrInput == "3")
		{
			nestedGame = true;
			while (nestedGame == true)
			{
				cout << "\n\t============================================================" << endl;
				cout << "\t=       ! ! !  t o u r n a m e n t  g a m e  ! ! !         =" << endl;
				cout << "\t============================================================" << endl;
				cout << "\t=          < Your current score is: " << score << " points! >    " << endl;
				cout << "\t=     What conversions would you like? (type -1 to quit) > " << endl;
				cout << "\t=    1) Binary" << endl;
				cout << "\t=    2) Octal" << endl;
				cout << "\t=    3) Hexadecimal" << endl;
				cout << "\t=      <h i n t>: type multiple values! (ie 13 / 23 / 123)" << endl;
				cout << "\t=     >  ";
				cin >> usrInput;
				if (usrInput != "-1")
				{
					cout << "\t=    How many rounds do you want to play?" << endl;
					cin >> rounds;
				}
				system("cls"); // change to system("clear") for Linux!

				if (usrInput == "1")	// binary only
				{
					gameBoard(gameMode = 3, gameType = 1, &answer, &codeAnswer, rounds);	// call the gameBoard function
				}
				else if (usrInput == "2")	// Octal only
				{
					gameBoard(gameMode = 3, gameType = 2, &answer, &codeAnswer, rounds);	// call the gameBoard function
				}
				else if (usrInput == "3")	// Hexadecimal only
				{
					gameBoard(gameMode = 3, gameType = 3, &answer, &codeAnswer, rounds);	// call the gameBoard function
				}
				else if (usrInput == "12")	// Binary and Octal
				{
					gameBoard(gameMode = 3, gameType = 12, &answer, &codeAnswer, rounds);	// call the gameBoard function
				}
				else if (usrInput == "13")	// Binary and Hexadecimal
				{
					gameBoard(gameMode = 3, gameType = 13, &answer, &codeAnswer, rounds);	// call the gameBoard function
				}
				else if (usrInput == "23") // Octal and Hexadecimal
				{
					gameBoard(gameMode = 3, gameType = 23, &answer, &codeAnswer, rounds);	// call the gameBoard function
				}
				else if (usrInput == "123") // All three
				{
					gameBoard(gameMode = 3, gameType = 123, &answer, &codeAnswer, rounds);	// call the gameBoard function
				}
				else if (usrInput == "-1")
				{
					cout << "\n\n\tAre you sure you want to return to the main menu?" << endl;
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
					cout << "\n\nThat response didn't seem to work.." << endl;
					cout << "Press enter to continue" << endl;
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
				cout << "\n\t============================================================" << endl;
				cout << "\t=                   r a n d o m  g a m e                   =" << endl;
				cout << "\t============================================================" << endl;
				cout << "\t=          < Your current score is: " << score << " points! >    " << endl;
				cout << "\t=     What conversions would you like? (type -1 to quit) > " << endl;
				cout << "\t=    1) Binary" << endl;
				cout << "\t=    2) Octal" << endl;
				cout << "\t=    3) Hexadecimal" << endl;
				cout << "\t=      <h i n t>: type multiple values! (ie 13 / 23 / 123)" << endl;
				cout << "\t=     >  ";
				cin >> usrInput;
				system("cls"); // change to system("clear") for Linux!

				if (usrInput == "1")	// binary only
				{
					gameBoard(gameMode = 4, gameType = 1, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "2")	// Octal only
				{
					gameBoard(gameMode = 4, gameType = 2, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "3")	// Hexadecimal only
				{
					gameBoard(gameMode = 4, gameType = 3, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "12")	// Binary and Octal
				{
					gameBoard(gameMode = 4, gameType = 12, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "13")	// Binary and Hexadecimal
				{
					gameBoard(gameMode = 4, gameType = 13, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "23") // Octal and Hexadecimal
				{
					gameBoard(gameMode = 4, gameType = 23, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "123") // All three
				{
					gameBoard(gameMode = 4, gameType = 123, &answer, &codeAnswer, rounds = 1);	// call the gameBoard function
				}
				else if (usrInput == "-1")
				{
					cout << "\n\n\tAre you sure you want to return to the main menu?" << endl;
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
					cout << "\n\nThat response didn't seem to work.." << endl;
					cout << "Press enter to continue" << endl;
					cin >> usrInput;
					usrInput = "default";
				}

			}	// end of nestedGame

		}	// --------------------------------------------------------------  end of usrInput 4 --------------------------------------------------------------------------------
		else if (usrInput == "-1")	// if user requests to exit game
		{
			cout << "\n\tAre you sure you want to quit?" << endl;
			cin >> usrInput;
			if (usrInput == "Yes" | usrInput == "yes" | usrInput == "Y" | usrInput == "y")
			{
				system("cls"); // change to system("clear") for Linux!
				game = false;
			} 

		}
		else // catch all
		{
			cout << "\n\nThat response didn't seem to work.." << endl;
			cout << "Press enter to continue" << endl;
			cin >> usrInput;
			usrInput = "default";
		}


	} // end of game loop	


	system("cls");
	cout << "Thanks for playing!" << endl;
	return 0;

}	// end of main



void numLogic(string* answer, string* codeAnswer, int Ansindex, int functionType)
{
	bool randnumCheck = true;
	int codeAnsLocal = 0;
	for (int index = 1; Ansindex > index; index++)
	{
		while (randnumCheck == true)
		{
			int randnum = rand() % 122 + 48;	// generate pseudo-random number for crunching
			codeAnsLocal = randnum;

			if (randnum >= 48 && randnum <= 57) // check if decimal value is equivalent to an ASCII number and set it
			{
				if (randnum == 48) { *answer = "0"; }
				else if (randnum == 49) { *answer = "1"; }
				else if (randnum == 50) { *answer = "2"; }
				else if (randnum == 51) { *answer = "3"; }
				else if (randnum == 52) { *answer = "4"; }
				else if (randnum == 53) { *answer = "5"; }
				else if (randnum == 54) { *answer = "6"; }
				else if (randnum == 55) { *answer = "7"; }
				else if (randnum == 56) { *answer = "8"; }
				else if (randnum == 57) { *answer = "9"; }

				randnumCheck = false;
			}
			else if (randnum >= 65 && randnum <= 90)	// check if decimal value is equivalent to an ASCII uppercase letter and set it
			{
				if (randnum == 65) { *answer = "A"; }
				else if (randnum == 66) { *answer = "B"; }
				else if (randnum == 67) { *answer = "C"; }
				else if (randnum == 68) { *answer = "D"; }
				else if (randnum == 69) { *answer = "E"; }
				else if (randnum == 70) { *answer = "F"; }
				else if (randnum == 71) { *answer = "G"; }
				else if (randnum == 72) { *answer = "H"; }
				else if (randnum == 73) { *answer = "I"; }
				else if (randnum == 74) { *answer = "J"; }
				else if (randnum == 75) { *answer = "K"; }
				else if (randnum == 76) { *answer = "L"; }
				else if (randnum == 77) { *answer = "M"; }
				else if (randnum == 78) { *answer = "N"; }
				else if (randnum == 79) { *answer = "O"; }
				else if (randnum == 80) { *answer = "P"; }
				else if (randnum == 81) { *answer = "Q"; }
				else if (randnum == 82) { *answer = "R"; }
				else if (randnum == 83) { *answer = "S"; }
				else if (randnum == 84) { *answer = "T"; }
				else if (randnum == 85) { *answer = "U"; }
				else if (randnum == 86) { *answer = "V"; }
				else if (randnum == 87) { *answer = "W"; }
				else if (randnum == 88) { *answer = "X"; }
				else if (randnum == 89) { *answer = "Y"; }
				else if (randnum == 90) { *answer = "Z"; }

				randnumCheck = false;
			}
			else if (randnum >= 97 && randnum <= 122)	// check if decimal value is equivalent to an ASCII lowercase letter and set it
			{
				if (randnum == 97) { *answer = "a"; }
				else if (randnum == 98) { *answer = "b"; }
				else if (randnum == 99) { *answer = "c"; }
				else if (randnum == 100) { *answer = "d"; }
				else if (randnum == 101) { *answer = "e"; }
				else if (randnum == 102) { *answer = "f"; }
				else if (randnum == 103) { *answer = "g"; }
				else if (randnum == 104) { *answer = "h"; }
				else if (randnum == 105) { *answer = "i"; }
				else if (randnum == 106) { *answer = "j"; }
				else if (randnum == 107) { *answer = "k"; }
				else if (randnum == 108) { *answer = "l"; }
				else if (randnum == 109) { *answer = "m"; }
				else if (randnum == 110) { *answer = "n"; }
				else if (randnum == 111) { *answer = "o"; }
				else if (randnum == 112) { *answer = "p"; }
				else if (randnum == 113) { *answer = "q"; }
				else if (randnum == 114) { *answer = "r"; }
				else if (randnum == 115) { *answer = "s"; }
				else if (randnum == 116) { *answer = "t"; }
				else if (randnum == 117) { *answer = "u"; }
				else if (randnum == 118) { *answer = "v"; }
				else if (randnum == 119) { *answer = "w"; }
				else if (randnum == 120) { *answer = "x"; }
				else if (randnum == 121) { *answer = "y"; }
				else if (randnum == 122) { *answer = "z"; }

				randnumCheck = false;
			}

		}	// end randnumCheck

		if (functionType == 1)					// if codeAnswer should be in Binary
		{
			if (codeAnsLocal == 48) { *codeAnswer = "00110000"; }
			else if (codeAnsLocal == 49) { *codeAnswer = "00110001"; }
			else if (codeAnsLocal == 50) { *codeAnswer = "00110010"; }
			else if (codeAnsLocal == 51) { *codeAnswer = "00110011"; }
			else if (codeAnsLocal == 52) { *codeAnswer = "00110100"; }
			else if (codeAnsLocal == 53) { *codeAnswer = "00110101"; }
			else if (codeAnsLocal == 54) { *codeAnswer = "00110110"; }
			else if (codeAnsLocal == 55) { *codeAnswer = "00110111"; }
			else if (codeAnsLocal == 56) { *codeAnswer = "00111000"; }
			else if (codeAnsLocal == 57) { *codeAnswer = "00111001"; }

			else if (codeAnsLocal == 65) { *codeAnswer = "01000001"; }
			else if (codeAnsLocal == 66) { *codeAnswer = "01000010"; }
			else if (codeAnsLocal == 67) { *codeAnswer = "01000011"; }
			else if (codeAnsLocal == 68) { *codeAnswer = "01000100"; }
			else if (codeAnsLocal == 69) { *codeAnswer = "01000101"; }
			else if (codeAnsLocal == 70) { *codeAnswer = "01000110"; }
			else if (codeAnsLocal == 71) { *codeAnswer = "01000111"; }
			else if (codeAnsLocal == 72) { *codeAnswer = "01001000"; }
			else if (codeAnsLocal == 73) { *codeAnswer = "01001001"; }
			else if (codeAnsLocal == 74) { *codeAnswer = "01001010"; }
			else if (codeAnsLocal == 75) { *codeAnswer = "01001011"; }
			else if (codeAnsLocal == 76) { *codeAnswer = "01001100"; }
			else if (codeAnsLocal == 77) { *codeAnswer = "01001101"; }
			else if (codeAnsLocal == 78) { *codeAnswer = "01001110"; }
			else if (codeAnsLocal == 79) { *codeAnswer = "01001111"; }
			else if (codeAnsLocal == 80) { *codeAnswer = "01010000"; }
			else if (codeAnsLocal == 81) { *codeAnswer = "01010001"; }
			else if (codeAnsLocal == 82) { *codeAnswer = "01010010"; }
			else if (codeAnsLocal == 83) { *codeAnswer = "01010011"; }
			else if (codeAnsLocal == 84) { *codeAnswer = "01010100"; }
			else if (codeAnsLocal == 85) { *codeAnswer = "01010101"; }
			else if (codeAnsLocal == 86) { *codeAnswer = "01010110"; }
			else if (codeAnsLocal == 87) { *codeAnswer = "01010111"; }
			else if (codeAnsLocal == 88) { *codeAnswer = "01011000"; }
			else if (codeAnsLocal == 89) { *codeAnswer = "01011001"; }
			else if (codeAnsLocal == 90) { *codeAnswer = "01011010"; }

			else if (codeAnsLocal == 97) { *codeAnswer = "01100001"; }
			else if (codeAnsLocal == 98) { *codeAnswer = "01100010"; }
			else if (codeAnsLocal == 99) { *codeAnswer = "01100011"; }
			else if (codeAnsLocal == 100) { *codeAnswer = "01100100"; }
			else if (codeAnsLocal == 101) { *codeAnswer = "01100101"; }
			else if (codeAnsLocal == 102) { *codeAnswer = "01100110"; }
			else if (codeAnsLocal == 103) { *codeAnswer = "01100111"; }
			else if (codeAnsLocal == 104) { *codeAnswer = "01101000"; }
			else if (codeAnsLocal == 105) { *codeAnswer = "01101001"; }
			else if (codeAnsLocal == 106) { *codeAnswer = "01101010"; }
			else if (codeAnsLocal == 107) { *codeAnswer = "01101011"; }
			else if (codeAnsLocal == 108) { *codeAnswer = "01101100"; }
			else if (codeAnsLocal == 109) { *codeAnswer = "01101101"; }
			else if (codeAnsLocal == 110) { *codeAnswer = "01101110"; }
			else if (codeAnsLocal == 111) { *codeAnswer = "01101111"; }
			else if (codeAnsLocal == 112) { *codeAnswer = "01110000"; }
			else if (codeAnsLocal == 113) { *codeAnswer = "01110001"; }
			else if (codeAnsLocal == 114) { *codeAnswer = "01110010"; }
			else if (codeAnsLocal == 115) { *codeAnswer = "01110011"; }
			else if (codeAnsLocal == 116) { *codeAnswer = "01110100"; }
			else if (codeAnsLocal == 117) { *codeAnswer = "01110101"; }
			else if (codeAnsLocal == 118) { *codeAnswer = "01110110"; }
			else if (codeAnsLocal == 119) { *codeAnswer = "01110111"; }
			else if (codeAnsLocal == 120) { *codeAnswer = "01111000"; }
			else if (codeAnsLocal == 121) { *codeAnswer = "01111001"; }
			else if (codeAnsLocal == 122) { *codeAnswer = "01111010"; }
		}
		else if (functionType == 2)				// if codeAnswer should be in Octal
		{
			if (codeAnsLocal == 48) { *codeAnswer = "61"; }
			else if (codeAnsLocal == 49) { *codeAnswer = "62"; }
			else if (codeAnsLocal == 50) { *codeAnswer = "63"; }
			else if (codeAnsLocal == 51) { *codeAnswer = "64"; }
			else if (codeAnsLocal == 52) { *codeAnswer = "65"; }
			else if (codeAnsLocal == 53) { *codeAnswer = "66"; }
			else if (codeAnsLocal == 54) { *codeAnswer = "67"; }
			else if (codeAnsLocal == 55) { *codeAnswer = "70"; }
			else if (codeAnsLocal == 56) { *codeAnswer = "71"; }
			else if (codeAnsLocal == 57) { *codeAnswer = "72"; }

			else if (codeAnsLocal == 65) { *codeAnswer = "101"; }
			else if (codeAnsLocal == 66) { *codeAnswer = "102"; }
			else if (codeAnsLocal == 67) { *codeAnswer = "103"; }
			else if (codeAnsLocal == 68) { *codeAnswer = "104"; }
			else if (codeAnsLocal == 69) { *codeAnswer = "105"; }
			else if (codeAnsLocal == 70) { *codeAnswer = "106"; }
			else if (codeAnsLocal == 71) { *codeAnswer = "107"; }
			else if (codeAnsLocal == 72) { *codeAnswer = "110"; }
			else if (codeAnsLocal == 73) { *codeAnswer = "111"; }
			else if (codeAnsLocal == 74) { *codeAnswer = "112"; }
			else if (codeAnsLocal == 75) { *codeAnswer = "113"; }
			else if (codeAnsLocal == 76) { *codeAnswer = "114"; }
			else if (codeAnsLocal == 77) { *codeAnswer = "115"; }
			else if (codeAnsLocal == 78) { *codeAnswer = "116"; }
			else if (codeAnsLocal == 79) { *codeAnswer = "117"; }
			else if (codeAnsLocal == 80) { *codeAnswer = "120"; }
			else if (codeAnsLocal == 81) { *codeAnswer = "121"; }
			else if (codeAnsLocal == 82) { *codeAnswer = "122"; }
			else if (codeAnsLocal == 83) { *codeAnswer = "123"; }
			else if (codeAnsLocal == 84) { *codeAnswer = "124"; }
			else if (codeAnsLocal == 85) { *codeAnswer = "125"; }
			else if (codeAnsLocal == 86) { *codeAnswer = "126"; }
			else if (codeAnsLocal == 87) { *codeAnswer = "127"; }
			else if (codeAnsLocal == 88) { *codeAnswer = "130"; }
			else if (codeAnsLocal == 89) { *codeAnswer = "131"; }
			else if (codeAnsLocal == 90) { *codeAnswer = "132"; }

			else if (codeAnsLocal == 97) { *codeAnswer = "141"; }
			else if (codeAnsLocal == 98) { *codeAnswer = "142"; }
			else if (codeAnsLocal == 99) { *codeAnswer = "143"; }
			else if (codeAnsLocal == 100) { *codeAnswer = "144"; }
			else if (codeAnsLocal == 101) { *codeAnswer = "145"; }
			else if (codeAnsLocal == 102) { *codeAnswer = "146"; }
			else if (codeAnsLocal == 103) { *codeAnswer = "147"; }
			else if (codeAnsLocal == 104) { *codeAnswer = "150"; }
			else if (codeAnsLocal == 105) { *codeAnswer = "151"; }
			else if (codeAnsLocal == 106) { *codeAnswer = "152"; }
			else if (codeAnsLocal == 107) { *codeAnswer = "153"; }
			else if (codeAnsLocal == 108) { *codeAnswer = "154"; }
			else if (codeAnsLocal == 109) { *codeAnswer = "155"; }
			else if (codeAnsLocal == 110) { *codeAnswer = "156"; }
			else if (codeAnsLocal == 111) { *codeAnswer = "157"; }
			else if (codeAnsLocal == 112) { *codeAnswer = "160"; }
			else if (codeAnsLocal == 113) { *codeAnswer = "161"; }
			else if (codeAnsLocal == 114) { *codeAnswer = "162"; }
			else if (codeAnsLocal == 115) { *codeAnswer = "163"; }
			else if (codeAnsLocal == 116) { *codeAnswer = "164"; }
			else if (codeAnsLocal == 117) { *codeAnswer = "165"; }
			else if (codeAnsLocal == 118) { *codeAnswer = "166"; }
			else if (codeAnsLocal == 119) { *codeAnswer = "167"; }
			else if (codeAnsLocal == 120) { *codeAnswer = "170"; }
			else if (codeAnsLocal == 121) { *codeAnswer = "171"; }
			else if (codeAnsLocal == 122) { *codeAnswer = "172"; }
		}
		else if (functionType == 3)			// if codeAnswer should be in Hexadecimal
		{
			if (codeAnsLocal == 48) { *codeAnswer = "30"; }
			else if (codeAnsLocal == 49) { *codeAnswer = "31"; }
			else if (codeAnsLocal == 50) { *codeAnswer = "32"; }
			else if (codeAnsLocal == 51) { *codeAnswer = "33"; }
			else if (codeAnsLocal == 52) { *codeAnswer = "34"; }
			else if (codeAnsLocal == 53) { *codeAnswer = "35"; }
			else if (codeAnsLocal == 54) { *codeAnswer = "36"; }
			else if (codeAnsLocal == 55) { *codeAnswer = "37"; }
			else if (codeAnsLocal == 56) { *codeAnswer = "38"; }
			else if (codeAnsLocal == 57) { *codeAnswer = "39"; }

			else if (codeAnsLocal == 65) { *codeAnswer = "41"; }
			else if (codeAnsLocal == 66) { *codeAnswer = "42"; }
			else if (codeAnsLocal == 67) { *codeAnswer = "43"; }
			else if (codeAnsLocal == 68) { *codeAnswer = "44"; }
			else if (codeAnsLocal == 69) { *codeAnswer = "45"; }
			else if (codeAnsLocal == 70) { *codeAnswer = "46"; }
			else if (codeAnsLocal == 71) { *codeAnswer = "47"; }
			else if (codeAnsLocal == 72) { *codeAnswer = "48"; }
			else if (codeAnsLocal == 73) { *codeAnswer = "49"; }
			else if (codeAnsLocal == 74) { *codeAnswer = "4A"; }
			else if (codeAnsLocal == 75) { *codeAnswer = "4B"; }
			else if (codeAnsLocal == 76) { *codeAnswer = "4C"; }
			else if (codeAnsLocal == 77) { *codeAnswer = "4D"; }
			else if (codeAnsLocal == 78) { *codeAnswer = "4E"; }
			else if (codeAnsLocal == 79) { *codeAnswer = "4F"; }
			else if (codeAnsLocal == 80) { *codeAnswer = "50"; }
			else if (codeAnsLocal == 81) { *codeAnswer = "51"; }
			else if (codeAnsLocal == 82) { *codeAnswer = "52"; }
			else if (codeAnsLocal == 83) { *codeAnswer = "53"; }
			else if (codeAnsLocal == 84) { *codeAnswer = "54"; }
			else if (codeAnsLocal == 85) { *codeAnswer = "55"; }
			else if (codeAnsLocal == 86) { *codeAnswer = "56"; }
			else if (codeAnsLocal == 87) { *codeAnswer = "57"; }
			else if (codeAnsLocal == 88) { *codeAnswer = "58"; }
			else if (codeAnsLocal == 89) { *codeAnswer = "59"; }
			else if (codeAnsLocal == 90) { *codeAnswer = "5A"; }

			else if (codeAnsLocal == 97) { *codeAnswer = "61"; }
			else if (codeAnsLocal == 98) { *codeAnswer = "62"; }
			else if (codeAnsLocal == 99) { *codeAnswer = "63"; }
			else if (codeAnsLocal == 100) { *codeAnswer = "64"; }
			else if (codeAnsLocal == 101) { *codeAnswer = "65"; }
			else if (codeAnsLocal == 102) { *codeAnswer = "66"; }
			else if (codeAnsLocal == 103) { *codeAnswer = "67"; }
			else if (codeAnsLocal == 104) { *codeAnswer = "68"; }
			else if (codeAnsLocal == 105) { *codeAnswer = "69"; }
			else if (codeAnsLocal == 106) { *codeAnswer = "6A"; }
			else if (codeAnsLocal == 107) { *codeAnswer = "6B"; }
			else if (codeAnsLocal == 108) { *codeAnswer = "6C"; }
			else if (codeAnsLocal == 109) { *codeAnswer = "6D"; }
			else if (codeAnsLocal == 110) { *codeAnswer = "6E"; }
			else if (codeAnsLocal == 111) { *codeAnswer = "6F"; }
			else if (codeAnsLocal == 112) { *codeAnswer = "70"; }
			else if (codeAnsLocal == 113) { *codeAnswer = "71"; }
			else if (codeAnsLocal == 114) { *codeAnswer = "72"; }
			else if (codeAnsLocal == 115) { *codeAnswer = "73"; }
			else if (codeAnsLocal == 116) { *codeAnswer = "74"; }
			else if (codeAnsLocal == 117) { *codeAnswer = "75"; }
			else if (codeAnsLocal == 118) { *codeAnswer = "76"; }
			else if (codeAnsLocal == 119) { *codeAnswer = "77"; }
			else if (codeAnsLocal == 120) { *codeAnswer = "78"; }
			else if (codeAnsLocal == 121) { *codeAnswer = "79"; }
			else if (codeAnsLocal == 122) { *codeAnswer = "7A"; }

		}
		else
		{
			*codeAnswer = codeAnsLocal;
		}

	} // end of FOR loop

} // end number logic


void wordpool(string* answer, int Ansindex)
{


}	// end word pool

void wlmsg()
{

} // end win / lose message logic

void gameBoard(int gameMode, int gameType, string* answer, string* codeAnswer, int index)
{
	int fGameType = 0;

	if (gameType == 1)		// if gametype is SINGLE ASCII
	{


	}
	else if (gameType == 2)		// if gametype is MULTIPLE ASCII
	{

	}
	else if (gameType == 3)		// if gametype is TOURNAMENT
	{

	}
	else if (gameType == 4)		// if gametype is RANDOM
	{

	}
	else     // catch all
	{


	}

	numLogic(answer, codeAnswer, 0, fGameType);		// call logic function

} // end gameboard draw logic