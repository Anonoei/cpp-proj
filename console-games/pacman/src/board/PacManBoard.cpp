#include "PacManBoard.h"

void PacManBoard::Init()
{
	std::string CopyBoard  = "WWWWWWWWWWWWWWWWWWWWWWWWWWWW";	//	0
				CopyBoard += "W************WW************W";	//	1
				CopyBoard += "W*WWWW*WWWWW*WW*WWWWW*WWWW*W";	//	2
				CopyBoard += "W@WWWW*WWWWW*WW*WWWWW*WWWW@W";	//	3
				CopyBoard += "W*WWWW*WWWWW*WW*WWWWW*WWWW*W";	//	4
				CopyBoard += "W**************************W";	//	5
				CopyBoard += "W*WWWW*WW*WWWWWWWW*WW*WWWW*W";	//	6
				CopyBoard += "W*WWWW*WW*WWWWWWWW*WW*WWWW*W";	//	7
				CopyBoard += "W******WW****WW****WW******W";	//	8
				CopyBoard += "WWWWWW*WWWWW-WW-WWWWW*WWWWWW";	//	9
				CopyBoard += "WWWWWW*WWWWW-WW-WWWWW*WWWWWW";	//	10
				CopyBoard += "WWWWWW*WW----------WW*WWWWWW";	//	11
				CopyBoard += "WWWWWW*WW-WWWXXWWW-WW*WWWWWW";	//	12
				CopyBoard += "------*---Wx1xx2xW---*------";	//	13
				CopyBoard += "WWWWWW*WW-WxxxxxxW-WW*WWWWWW";	//	14
				CopyBoard += "WWWWWW*WW-Wx3xx4xW-WW*WWWWWW";	//	15
				CopyBoard += "WWWWWW*WW-WWWWWWWW-WW*WWWWWW";	//	16
				CopyBoard += "WWWWWW*WW----------WW*WWWWWW";	//	17
				CopyBoard += "WWWWWW*WW-WWWWWWWW-WW*WWWWWW";	//	18
				CopyBoard += "W************WW************W";	//	19
				CopyBoard += "W*WWWW*WWWWW*WW*WWWWW*WWWW*W";	//	20
				CopyBoard += "W*WWWW*WWWWW*WW*WWWWW*WWWW*W";	//	21
				CopyBoard += "W@**WW*******-P*******WW**@W";	//	22
				CopyBoard += "WWW*WW*WW*WWWWWWWW*WW*WW*WWW";	//	23
				CopyBoard += "WWW*WW*WW*WWWWWWWW*WW*WW*WWW";	//	24
				CopyBoard += "W******WW****WW****WW******W";	//	25
				CopyBoard += "W*WWWWWWWWWW*WW*WWWWWWWWWW*W";	//	26
				CopyBoard += "W*WWWWWWWWWW*WW*WWWWWWWWWW*W";	//	27
				CopyBoard += "W**************************W";	//	28
				CopyBoard += "WWWWWWWWWWWWWWWWWWWWWWWWWWWW";	//	29

	int CheckNumber = 0;
	for (int height = 0; height < this->Height; height++)
	{
		for (int width = 0; width < this->Width; width++)
		{
			this->Board[height][width] = CopyBoard[CheckNumber + width];
		}
		CheckNumber += 28;
	}

	pLOG_INFO("Initalized Logic!");
}

void PacManBoard::Draw(PacDirection direction)
{
	daClearScreen();
	for (int height = 0; height < this->Height; height++)
	{
		std::cout << "\t";
		for (int width = 0; width < this->Width; width++)
		{
			if (this->Board[height][width] == 'W')
				daPrintChar(bgBlue, "   ");
			else if (this->Board[height][width] == '*')
			{
				std::cout << " ";
				daPrintChar(fgWhite, "*");
				std::cout << " ";
			}
			else if (this->Board[height][width] == 'P')
			{
				std::cout << " ";
				switch (direction)
				{
					case PacDirection::Up:
					{
						daPrintChar(bgBrightYellow, "V");
						break;
					}
					case PacDirection::Left:
					{
						daPrintChar(bgBrightYellow, ">");
						break;
					}
					case PacDirection::Down:
					{
						daPrintChar(bgBrightYellow, "^");
						break;
					}
					case PacDirection::Right:
					{
						daPrintChar(bgBrightYellow, "<");
						break;
					}
				}
				std::cout << " ";
			}
			else if (this->Board[height][width] == '1')	//	Blinky
			{
				std::cout << " ";
				daPrintChar(bgRed, "M");
				std::cout << " ";
			}
			else if (this->Board[height][width] == '2')	//	Pinky
			{
				std::cout << " ";
				daPrintChar(bgBrightRed, "M");
				std::cout << " ";
			}
			else if (this->Board[height][width] == '3')	//	Inky
			{
				std::cout << " ";
				daPrintChar(bgCyan, "M");
				std::cout << " ";
			}
			else if (this->Board[height][width] == '4')	//	Clyde
			{
				std::cout << " ";
				daPrintChar(bgYellow, "M");
				std::cout << " ";
			}
			else if (this->Board[height][width] == '@')
			{
				std::cout << " ";
				daPrintChar(fgBlack, bgWhite, "@");
				std::cout << " ";
			}
			else if (this->Board[height][width] == 'X')
				daPrintChar(bgWhite, "   ");
			else
				std::cout << "   ";
			//std::cout << this->Board[height][width] << this->Board[height][width] << this->Board[height][width];
		}
		if (height != this->Height - 1)
			std::cout << std::endl;
	}
}
void PacManBoard::Shutdown()
{

}