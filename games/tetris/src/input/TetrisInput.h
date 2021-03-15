#pragma once

#include "TetrisBase.h"
#include <windows.h>

//	This is a temporary class (and only supports windows)
//		This will use DAGGer inputs when switched to there
namespace TetrisInput
{
	Translation CheckTranslationInput()
	{
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
		if (GetKeyState('Q') & 0x8000)
			return Rotation::Left;
		else if (GetKeyState('E') & 0x8000)
			return Rotation::Right;
		return Rotation::Null;
	}
}	//	END namespace TetrisInput