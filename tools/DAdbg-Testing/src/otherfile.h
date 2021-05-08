#pragma once
#define DA_ALL
#include "DAdbg/DAdbg.h"

inline void DoSomething()
{
	daPROFILE_SCOPE("otherfile");
	daPrintl(fgMagenta, "\tDid something!");
}