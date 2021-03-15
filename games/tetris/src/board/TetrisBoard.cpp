#include "TetrisBoard.h"

void TetrisBoard::Init()
{
	for (int i = 0; i < Height; i++)	//	Initalize board with no values
	{
		for (int j = 0; j < Width; j++)
		{
			this->Board[i][j] = { ' ' };
		}
	}
	for (int i = 0; i < Width; i++)	//	Initalize Heights with the board height
		this->Heights.Add(Point(Height, i));
}

void TetrisBoard::Clear(int rows)
{

}

void TetrisBoard::Print(char nextPiece)
{
	ClearScreen();
	std::cout << "\n\tTetris: " << tVERSION << "\n\t\t";
	for (int i = 0; i < (Width * 2) + 4; i++)
		std::cout << "=";
	std::cout << "\tNext Piece: " << nextPiece << std::endl;
	for (int height = 0; height < Height; height++)
	{
		std::cout << "\t" << std::to_string(height + 1) << ".\t| ";
		for (int width = 0; width < Width; width++)
		{
			std::cout << this->Board[height][width] << " ";
		}
		std::cout << " |" << std::endl;
	}
	std::cout << "\t\t";
	for (int i = 0; i < (Width * 2) + 4; i++)
		std::cout << "=";
	std::cout << "\n\n\t";
	return;
}

void TetrisBoard::SpawnPoly(Points locations)
{
	Point value;
	for (int i = 0; i < locations.Size(); i++)
	{
		value = locations.Get(i);
		this->Board[value.y][value.x] = 'X';
	}
}

void TetrisBoard::Draw(Points NewLocations)
{
	Point NewLocation;
	for (int i = 0; i < NewLocations.Size(); i++)
	{
		NewLocation = NewLocations.Get(i);
		this->Board[NewLocation.y][NewLocation.x] = 'X';
	}
}

void TetrisBoard::Erase(Points OldLocations)
{
	Point OldLocation;
	for (int i = 0; i < OldLocations.Size(); i++)
	{
		OldLocation = OldLocations.Get(i);
		this->Board[OldLocation.y][OldLocation.x] = ' ';
	}
}

void TetrisBoard::SetMaxHeight(Point point)
{
	this->Heights[point.x].y = point.y - 1;
}

int TetrisBoard::GetMaxHeight(int PosX)
{
	//	PosX is the index we are checking
	Point value = this->Heights.Get(PosX);
	return value.y;
}