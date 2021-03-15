#include "Tetromino.h"

#include "PolyI.h"
#include "PolyJ.h"
#include "PolyL.h"
#include "PolyO.h"
#include "PolyS.h"
#include "PolyZ.h"
#include "PolyT.h"

Tetromino* Tetromino::Spawn(int SpawnNum)
{
	Tetromino* tetro;
	if (SpawnNum == 0)
		tetro = new PolyI();
	else if (SpawnNum == 1)
		tetro = new PolyJ();
	else if (SpawnNum == 2)
		tetro = new PolyL();
	else if (SpawnNum == 3)
		tetro = new PolyO();
	else if (SpawnNum == 4)
		tetro = new PolyS();
	else if (SpawnNum == 5)
		tetro = new PolyZ();
	else	//	Type is T
		tetro = new PolyT();

	SetTetro(tetro);

	IsMoving = true;
	return GetTetro();
}

bool Tetromino::Rotate(Rotation rotation, Point& value, int index)
{
	//	The values are valid - checked by TetrisLogic
	Point valueBuffer = value;
	if (rotation == Rotation::Clockwise)
	{
		value.x = (int)(valueBuffer.x * cos(tPI / 2) - valueBuffer.y * sin(tPI / 2));
		value.y = (int)(valueBuffer.x * sin(tPI / 2) + valueBuffer.y * cos(tPI / 2));
	}
	else if (rotation == Rotation::CounterClockwise)
	{
		value.x = (int)(valueBuffer.x * sin(tPI / 2) + valueBuffer.y * cos(tPI / 2));
		value.y = (int)(valueBuffer.x * cos(tPI / 2) - valueBuffer.y * sin(tPI / 2));
	}
	return false;
}

bool Tetromino::Translate(Translation translate, Point& value)
{
	if (translate == Translation::Down)
		value.y += 1;	//	Increment Y axis (higher number, lower down)
	else if (translate == Translation::DownPressed)
		value.y += 2;	//	Increment Y axis (higher number, lower down)
	else if (translate == Translation::Left)
		value.x -= 1;	//	Decrement X axis (move left)
	else if (translate == Translation::Right)
		value.x += 1;	//	Increment X axis (move right)

	return false;
}