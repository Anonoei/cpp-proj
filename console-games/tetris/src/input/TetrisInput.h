/////////////////////////////////////////////////////////////
//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++17
// Part of Tetris
//////////////////////////////
#pragma once

#include "TetrisBase.h"
#include <windows.h>

//	This is a temporary class (and only supports windows)
//		This will use DAGGer inputs when switched to there
namespace TetrisInput
{
	Translation CheckTranslationInput()
	{
		tPROFILE_FUNCTION();
		if (GetKeyState('A') & 0x8000)
			return Translation::Left;
		else if (GetKeyState('D') & 0x8000)
			return Translation::Right;
		else if (GetKeyState('S') & 0x8000)
			return Translation::DownPressed;
		return Translation::Null;
	}
	Rotation CheckRotationInput()
	{
		tPROFILE_FUNCTION();
		if (GetKeyState('Q') & 0x8000)
			return Rotation::Left;
		else if (GetKeyState('E') & 0x8000)
			return Rotation::Right;
		return Rotation::Null;
	}
}	//	END namespace TetrisInput