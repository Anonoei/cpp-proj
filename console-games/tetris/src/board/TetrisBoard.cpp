/////////////////////////////////////////////////////////////
//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++17
// Part of Tetris
//////////////////////////////
#include "TetrisBoard.h"

void TetrisBoard::Init()
{
	tPROFILE_FUNCTION();
	for (int i = 0; i < Height; i++)	//	Initalize board with no values
	{
		for (int j = 0; j < Width; j++)
		{
			this->Board[i][j] = { ' ' };
		}
	}
	for (int i = 0; i < Width; i++)	//	Initalize Heights with the board height
		this->Heights[i] = 20;
}

void TetrisBoard::Print(char nextPiece)
{
	tPROFILE_FUNCTION();
	if (this->NextPiece != nextPiece)
		UpdateNextPiece(nextPiece);
	
	ClearScreen();
	std::cout << "\n\tTetris: " << tVERSION;
	std::cout << "\n\t\t";
	for (int i = 0; i < (Width * 2) + 4; i++)
		std::cout << "=";
	std::cout << "=====================" << std::endl;
	for (int height = 0; height < Height; height++)
	{
		std::cout << "\t" << std::to_string(height + 1) << ".\t| ";
		for (int width = 0; width < Width; width++)
		{
			if (this->Board[height][width] == 'I')
				daPrintChar(bgBrightCyan, "  ");
			else if (this->Board[height][width] == 'J')
				daPrintChar(bgBlue, "  ");
			else if (this->Board[height][width] == 'L')
				daPrintChar(bgYellow, "  ");
			else if (this->Board[height][width] == 'O')
				daPrintChar(bgBrightYellow, "  ");
			else if (this->Board[height][width] == 'S')
				daPrintChar(bgBrightGreen, "  ");
			else if (this->Board[height][width] == 'Z')
				daPrintChar(bgRed, "  ");
			else if (this->Board[height][width] == 'T')
				daPrintChar(bgMagenta, "  ");
			else
				std::cout << this->Board[height][width] << " ";
		}
		std::cout << " |";
		if (height < 6 && height > 1)	//	Draw Next Piece
		{
			std::cout << "\t ";
			for (int width = 0; width < 4; width++)
			{
				if (this->DrawNextPiece[height - 2][width] == 'I')
					daPrintChar(bgBrightCyan, "  ");
				else if (this->DrawNextPiece[height - 2][width] == 'J')
					daPrintChar(bgBlue, "  ");
				else if (this->DrawNextPiece[height - 2][width] == 'L')
					daPrintChar(bgYellow, "  ");
				else if (this->DrawNextPiece[height - 2][width] == 'O')
					daPrintChar(bgBrightYellow, "  ");
				else if (this->DrawNextPiece[height - 2][width] == 'S')
					daPrintChar(bgBrightGreen, "  ");
				else if (this->DrawNextPiece[height - 2][width] == 'Z')
					daPrintChar(bgRed, "  ");
				else if (this->DrawNextPiece[height - 2][width] == 'T')
					daPrintChar(bgMagenta, "  ");
				else
					std::cout << this->DrawNextPiece[height - 2][width] << " ";
			}
			std::cout << "\t=";
		}
		else
		{
			if (height == 0)
				std::cout << "\tNext Piece: " << nextPiece << "\t=";
			else if (height == 1)
				std::cout << "\t\t\t=";
			else if (height == 6)
				std::cout << "=====================";
		}
		std::cout << std::endl;
	}
	std::cout << "\t\t";
	for (int i = 0; i < (Width * 2) + 4; i++)
		std::cout << "=";
	std::cout << "\n\t";
	for (int i = 0; i < Width; i++)
		std::cout << " " << this->Heights[i];
	std::cout << "\n\n\t";
	return;
}

void TetrisBoard::SpawnPoly(Points locations, Poly type)
{
	tPROFILE_FUNCTION();
	Point value;
	char visual;
	if (type == Poly::I)
		visual = 'I';
	else if (type == Poly::J)
		visual = 'J';
	else if (type == Poly::L)
		visual = 'L';
	else if (type == Poly::O)
		visual = 'O';
	else if (type == Poly::S)
		visual = 'S';
	else if (type == Poly::Z)
		visual = 'Z';
	else if (type == Poly::T)
		visual = 'T';
	else
		visual = 'X';

	for (int i = 0; i < locations.Size(); i++)
	{
		value = locations.Get(i);
		this->Board[value.y][value.x] = visual;
	}
}

void TetrisBoard::Draw(Points NewLocations, Poly type)
{
	tPROFILE_FUNCTION();
	Point NewLocation;
	char visual;
	if (type == Poly::I)
		visual = 'I';
	else if (type == Poly::J)
		visual = 'J';
	else if (type == Poly::L)
		visual = 'L';
	else if (type == Poly::O)
		visual = 'O';
	else if (type == Poly::S)
		visual = 'S';
	else if (type == Poly::Z)
		visual = 'Z';
	else if (type == Poly::T)
		visual = 'T';
	else
		visual = 'X';

	for (int i = 0; i < NewLocations.Size(); i++)
	{
		NewLocation = NewLocations.Get(i);
		this->Board[NewLocation.y][NewLocation.x] = visual;
	}
}

void TetrisBoard::Erase(Points OldLocations)
{
	tPROFILE_FUNCTION();
	Point OldLocation;
	for (int i = 0; i < OldLocations.Size(); i++)
	{
		OldLocation = OldLocations.Get(i);
		this->Board[OldLocation.y][OldLocation.x] = ' ';
	}
}

void TetrisBoard::EraseRow(int PosY)
{
	for (int i = 0; i < GetWidth(); i++)
	{
		for (int j = 0; j < GetWidth(); j++)
			this->Board[PosY][j] = { ' ' };
	}
}

void TetrisBoard::SetMaxHeight(Point point)
{
	tPROFILE_FUNCTION();
	bool CheckingHeight = true;
	int LowestValue = 20;
	for (int i = 20; i >= 0; i--)
	{
		if (this->Board[i][point.x] == ' ')
			continue;
		else
		{
			if (i < LowestValue)
				LowestValue = i;
		}
	}
	if (this->Heights[point.x] > LowestValue)
		this->Heights[point.x] = LowestValue;
}

int TetrisBoard::GetMaxHeight(int PosX)
{
	tPROFILE_FUNCTION();
	//	PosX is the index we are checking
	int value = this->Heights[PosX];
	return value;
}

bool TetrisBoard::GetFullRow(int PosY)
{
	tPROFILE_FUNCTION();
	//	PosY is the y we are checking
	bool fullrow = true;
	for (int i = 0; i < this->Width; i++)
	{
		if (this->Board[PosY][i] == ' ')
			fullrow = false;
	}
	return fullrow;
}

void TetrisBoard::UpdateNextPiece(char nextPiece)
{
	this->NextPiece = nextPiece;
	for (int i = 0; i < 4; i++)	//	Initalize board with no values
	{
		for (int j = 0; j < 4; j++)
		{
			this->DrawNextPiece[i][j] = { ' ' };
		}
	}

	if (nextPiece == 'I')
	{
		DrawNextPiece[1][0] = 'I';
		DrawNextPiece[1][1] = 'I';
		DrawNextPiece[1][2] = 'I';
		DrawNextPiece[1][3] = 'I';
	}
	else if (nextPiece == 'J')
	{
		DrawNextPiece[1][1] = 'J';
		DrawNextPiece[2][1] = 'J';
		DrawNextPiece[2][2] = 'J';
		DrawNextPiece[2][3] = 'J';
	}
	else if (nextPiece == 'L')
	{
		DrawNextPiece[1][3] = 'L';
		DrawNextPiece[2][1] = 'L';
		DrawNextPiece[2][2] = 'L';
		DrawNextPiece[2][3] = 'L';
	}
	else if (nextPiece == 'O')
	{
		DrawNextPiece[1][1] = 'O';
		DrawNextPiece[1][2] = 'O';
		DrawNextPiece[2][1] = 'O';
		DrawNextPiece[2][2] = 'O';
	}
	else if (nextPiece == 'S')
	{
		DrawNextPiece[1][1] = 'S';
		DrawNextPiece[1][2] = 'S';
		DrawNextPiece[2][0] = 'S';
		DrawNextPiece[2][1] = 'S';
	}
	else if (nextPiece == 'Z')
	{
		DrawNextPiece[1][1] = 'Z';
		DrawNextPiece[1][2] = 'Z';
		DrawNextPiece[2][2] = 'Z';
		DrawNextPiece[2][3] = 'Z';
	}
	else if (nextPiece == 'T')
	{
		DrawNextPiece[1][2] = 'T';
		DrawNextPiece[2][1] = 'T';
		DrawNextPiece[2][2] = 'T';
		DrawNextPiece[2][3] = 'T';
	}
}