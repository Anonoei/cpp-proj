/////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++17
// Part of Tetris
//////////////////////////////
#include "TetrisBase.h"

void ClearScreen()
{
#ifdef Dr_PLATFORM_WINDOWS
	std::system("cls");
#else
	std::system("clear");
#endif
}

///////////////////////////////////////////////////////////////
//  ---------------------  Point class  -------------------  //
///////////////////////////////////////////////////////////////
Point::Point()	//	Default constructor
	: x(0), y(0)
{}
Point::Point(int Y, int X)	//	Constructor with x and y value
	: x(X), y(Y)
{}

std::string Point::ToString()
{
	return "( " + std::to_string(this->x) + ", " + std::to_string(this->y) + " )";
}

//	fPoint
fPoint::fPoint()	//	Default constructor
	: x(0.0f), y(0.0f)
{}
fPoint::fPoint(float Y, float X)	//	Constructor with x and y value
	: x(X), y(Y)
{}

std::string fPoint::ToString()
{
	return "( " + std::to_string(this->x) + ", " + std::to_string(this->y) + " )";
}

///////////////////////////////////////////////////////////////
//  --------------------  Points class  -------------------  //
///////////////////////////////////////////////////////////////
//	Modify the vector
void Points::Add(Point p1)
{
	points.push_back(p1);
}
void Points::Remove()
{
	points.pop_back();
}
void Points::Clear()
{
	points.clear();
}

//	Getters
Point Points::Get(int index)           { return points[index];  }
void Points::Set(int index, Point p1) { points.at(index) = p1; }

//	Helper functions
int Points::Size()     { return (int)points.size();     }
int Points::Count()    { return (int)points.size() - 1; }
bool Points::IsEmpty() { return points.empty();    }
const int Points::Size() const { return (int)points.size(); }
const int Points::Count() const { return (int)points.size() - 1; };

auto Points::Begin()  { return points.begin();  }
auto Points::End()    { return points.end();    }
auto Points::rBegin() { return points.rbegin(); }
auto Points::rEnd()   { return points.rend();   }

std::string Points::ToString()
{
	std::string str;
	for (int i = 0; i < this->Size(); i++)
	{
		str += this->Get(i).ToString();
		if (i != this->Size() - 1)
			str += " , ";
	}
	return str;
}

Point& Points::operator[](int index)
{
	if (index < 0 || index > this->Count())
	{
		tLOG(Level::Error, "Index out of range!");
		abort();
	}
	return points[index];
}
const Point& Points::operator[](int index) const
{
	if (index < 0 || index > this->Count())
	{
		tLOG(Level::Error, "Index out of range!");
		abort();
	}
	return points[index];
}