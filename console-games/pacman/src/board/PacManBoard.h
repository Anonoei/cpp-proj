#pragma once
#include <string>
#include "../PacManBase.h"
/*
    0   2   4   6   8  10  12  14  16  18  20  22  24  26
	| 1 | 3 | 5 | 7 | 9 |11 |13 |15 |17 |19 |21 |23 |25 |27
0	W W W W W W W W W W W W W W W W W W W W W W W W W W W W		0
1	W * * * * * * * * * * * * W W * * * * * * * * * * * * W		1
2	W * W W W W * W W W W W * W W * W W W W W * W W W W * W		2
3	W @ W W W W * W W W W W * W W * W W W W W * W W W W @ W		3
4	W * W W W W * W W W W W * W W * W W W W W * W W W W * W		4
5	W * * * * * * * * * * * * * * * * * * * * * * * * * * W		5
6	W * W W W W * W W * W W W W W W W W * W W * W W W W * W		6
7	W * W W W W * W W * W W W W W W W W * W W * W W W W * W		7
8	W * * * * * * W W * * * * W W * * * * W W * * * * * * W		8
9	W W W W W W * W W W W W - W W - W W W W W * W W W W W W		9
10	W W W W W W * W W W W W - W W - W W W W W * W W W W W W		10
11	W W W W W W * W W - - - - - - - - - - W W * W W W W W W		11
12	W W W W W W * W W - W W W W W W W W - W W * W W W W W W		12
13	- - - - - - * - - - W x x x x x x W - - - * - - - - - -		13
14	W W W W W W * W W - W x x x x x x W - W W * W W W W W W		14
15	W W W W W W * W W - W x x x x x x W - W W * W W W W W W		15
16	W W W W W W * W W - W W W W W W W W - W W * W W W W W W		16
17	W W W W W W * W W - - - - - - - - - - W W * W W W W W W		17
18	W W W W W W * W W - W W W W W W W W - W W * W W W W W W		18
19	W * * * * * * * * * * * * W W * * * * * * * * * * * * W		19
20	W * W W W W * W W W W W * W W * W W W W W * W W W W * W		20
21	W * W W W W * W W W W W * W W * W W W W W * W W W W * W		21
22	W @ * * W W * * * * * * * P P * * * * * * * W W * * @ W		22
23	W W W * W W * W W * W W W W W W W W * W W * W W * W W W		23
24	W W W * W W * W W * W W W W W W W W * W W * W W * W W W		24
25	W * * * * * * W W * * * * W W * * * * W W * * * * * * W		25
26	W * W W W W W W W W W W * W W * W W W W W W W W W W * W		26
27	W * W W W W W W W W W W * W W * W W W W W W W W W W * W		27
28	W * * * * * * * * * * * * * * * * * * * * * * * * * * W		28
29	W W W W W W W W W W W W W W W W W W W W W W W W W W W W		29
	0 | 2 | 4 | 6 | 8 |10 |12 |14 |16 |18 |20 |22 |24 |26 |
	| 1 | 3 | 5 | 7 | 9 |11 |13 |15 |17 |19 |21 |23 |25 |27
*/

class PacManBoard
{
public:
	PacManBoard() {}
	~PacManBoard() {}

	void Init();
	void Draw(PacDirection direction);
	void Shutdown();

	void Add(Points location);
	void Remove(Points location);
private:
	static const int Width = 28;
	static const int Height = 30;
	static const int Size = Height * Width;
	char Board[Height][Width] = { ' ' };
};

