/////////////////////////////////////////////////////////////
//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++17
// Part of Tetris
//////////////////////////////
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
	tPROFILE_FUNCTION();
	Tetromino* tetro;
	Poly type;
	if (SpawnNum == 0)
	{
		tetro = new PolyI();
		type = Poly::I;
	}
	else if (SpawnNum == 1)
	{
		tetro = new PolyJ();
		type = Poly::J;
	}
	else if (SpawnNum == 2)
	{
		tetro = new PolyL();
		type = Poly::L;
	}
	else if (SpawnNum == 3)
	{
		tetro = new PolyO();
		type = Poly::O;
	}
	else if (SpawnNum == 4)
	{
		tetro = new PolyS();
		type = Poly::S;
	}
	else if (SpawnNum == 5)
	{
		tetro = new PolyZ();
		type = Poly::Z;
	}
	else	//	Type is T
	{
		tetro = new PolyT();
		type = Poly::T;
	}

	SetTetro(tetro);

	IsMoving = true;
	Tetromino* thisTetro = GetTetro();
	thisTetro->SetType(type);
	return thisTetro;
}

bool Tetromino::Rotate(Rotation rotation, Point& value, int index)
{
	tPROFILE_FUNCTION();
	//	The values are valid - checked by TetrisLogic
	Point TranslationCoordinate = Point(value.x - GetOrigin().x, value.y - GetOrigin().y);
	Point rotatedCoordinates = TranslationCoordinate;
	TranslationCoordinate.y *= -1;	//	The board values are stored upside down (higher number, lower down)
	if (rotation == Rotation::Clockwise)
	{
		rotatedCoordinates.x = (int)(TranslationCoordinate.x * cos(tPI / 2) - TranslationCoordinate.y * sin(tPI / 2));
		rotatedCoordinates.y = (int)(TranslationCoordinate.x * sin(tPI / 2) + TranslationCoordinate.y * cos(tPI / 2));
	}
	else if (rotation == Rotation::CounterClockwise)
	{
		rotatedCoordinates.x = (int)(TranslationCoordinate.x * sin(tPI / 2) + TranslationCoordinate.y * cos(tPI / 2));
		rotatedCoordinates.y = (int)(TranslationCoordinate.x * cos(tPI / 2) - TranslationCoordinate.y * sin(tPI / 2));
	}
	rotatedCoordinates.y *= -1;
	rotatedCoordinates.x += GetOrigin().x;
	rotatedCoordinates.y += GetOrigin().y;
	value = rotatedCoordinates;
	return true;
}

bool Tetromino::Translate(Translation translate, Point& value)
{
	tPROFILE_FUNCTION();
	if (translate == Translation::Down)
		value.y += 1;	//	Increment Y axis (higher number, lower down)
	else if (translate == Translation::Left)
		value.x -= 1;	//	Decrement X axis (move left)
	else if (translate == Translation::Right)
		value.x += 1;	//	Increment X axis (move right)

	return false;
}