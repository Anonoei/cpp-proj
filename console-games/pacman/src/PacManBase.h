#pragma once

#define DA_PRINT
#define DA_PROFILE
#define DA_TIME
#include <DAdbg/DAdbg.h>

#define pLOG_CRITICAL(message) daLOG_CRITICAL(message)
#define pLOG_ERROR(message)    daLOG_ERROR(message)
#define pLOG_WARN(message)     daLOG_WARN(message)
#define pLOG_INFO(message)     daLOG_INFO(message)
#define pLOG_TRACE(message)    daLOG_TRACE(message)

#define pPROFILE_START(name, filepath) daPROFILE_BEGIN_SESSION(name, filepath)
#define pPROFILE_END()        daPROFILE_END_SESSION()
#define pPROFILE_SCOPE(name)  daPROFILE_SCOPE(name)
#define pPROFILE_FUNCTION()   daPROFILE_FUNCTION()

#define pClearScreen()        daClearScreen()

#define pVERSION  "v0.0.1a"

enum class PacDirection
{
	Up = 0,
	Right = 1,
	Down = 2,
	Left = 3
};

class Point
{
public:
	inline Point()
		: x(0), y(0)
	{}
	inline Point(int X, int Y)
		: x(X), y(Y)
	{}

	inline std::string ToString()
	{
		return "( " + std::to_string(this->x) + ", " + std::to_string(this->y) + " )";
	}

	int x, y;
};

class fPoint
{
public:
	inline fPoint()
		: x(0.0f), y(0.0f)
	{}
	inline fPoint(float X, float Y)
		: x(X), y(Y)
	{}

	inline std::string ToString()
	{
		return "( " + std::to_string(this->x) + ", " + std::to_string(this->y) + " )";
	}

	float x, y;
};

#include <vector>
class Points
{
public:
	Points() {}
	~Points() {}

	//	Modify the vector
	inline void Add(Point p1)
	{
		points.push_back(p1);
	}
	inline void Points::Remove()
	{
		points.pop_back();
	}
	inline void Points::Clear()
	{
		points.clear();
	}
	//	Get/Set
	inline Point Get(int index) { return points[index]; }
	inline void Set(int index, Point p1) { points.at(index) = p1; }

	//	Helper functions
	inline int Size()              { return (int)points.size(); }
	inline int Count()             { return (int)points.size() - 1; }
	inline bool IsEmpty()          { return points.empty(); }
	inline const int Size() const  { return (int)points.size(); }
	inline const int Count() const { return (int)points.size() - 1; };

	//	Iterator functions
	inline auto Begin()  { return points.begin(); }
	inline auto End()    { return points.end(); }
	inline auto rBegin() { return points.rbegin(); }
	inline auto rEnd()   { return points.rend(); }

	inline std::string ToString()
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

	inline Point& operator[](int index)
	{
		if (index < 0 || index > this->Count())
		{
			pLOG_ERROR("Index out of range!");
			abort();
		}
		return points[index];
	}
	inline const Point& operator[](int index) const
	{
		if (index < 0 || index > this->Count())
		{
			pLOG_ERROR("Index out of range!");
			abort();
		}
		return points[index];
	}

private:
	std::vector<Point> points;
};