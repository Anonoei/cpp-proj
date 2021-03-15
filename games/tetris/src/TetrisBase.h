//	This file includes basic classes for Tetris, and some helper functions
#pragma once

#include <DAdbg/DAdbg.h>

#define tLOG(severity, message)   daLOG(severity, message)
#define tLOG_TRACE(message)       daLOG_TRACE(message)
#define tLOG_INFO(message)        daLOG_INFO(message)
#define tLOG_WARN(message)        daLOG_WARN(message)
#define tLOG_ERROR(message)       daLOG_ERROR(message)
#define tLOG_CRITICAL(message)    daLOG_CRITICAL(message)

#define tVERSION    "v0.0.1a"

#define tPI           3.14159265358979323

void ClearScreen();


enum class Translation
{
	Down = 0,
	Left = 1,
	Right = 2,
	DownPressed = 3,
	Null
};

enum class Rotation
{
	Up = 0,		//	The piece is facing up
	Right = 1,	//	The piece is facing right
	Down = 2,	//	The piece is facing down
	Left = 3,	//	The piece is facing left
	Clockwise = 4,			//	Move the piece clockwise
	CounterClockwise = 5,	//	Move the piece counter-clockwise
	Null
};

class Point
{
public:
	Point();
	Point(int y, int x);	//	Ordered backwards due to 2-dimentional array

	int x, y;

	std::string ToString();

	bool operator==(Point p2);
	bool operator!=(Point p2);
};

#include <vector>
class Points
{
public:
	Points() {}
	~Points() {}

	//	Modify the vector
	void Add(Point p1);
	void Remove();
	void Clear();

	//	Get/Set
	Point Get(int index);
	void Set(int index, Point p1);

	//	Helper functions
	int Size();
	int Count();
	bool IsEmpty();
	const int Size() const;
	const int Count() const;

	//	Iterator functions
	auto Begin();
	auto End();
	auto rBegin();
	auto rEnd();

	std::string ToString();

	Point& operator[](int index);
	const Point& operator[](int index) const;

private:
	std::vector<Point> points;

};