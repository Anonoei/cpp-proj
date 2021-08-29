//////////////////////////////////////////////////////
// Author: Anonoei (https ://github.com/anonoei)
//  License: GPLv3
//  Language: C++17
//////////////////////////////////////
#pragma once

#define DAHL_PRINT
#define DAHL_PROFILE
#define DAHL_TIME
#define DAHL_UUID
#include <DAHL/DAHL.h>		//	Libraries
#include <DAELS/DAELS.h>	//	Lemmatization
#include <DAALS/DAALS.h>

#define aLOG(severity, message)   dahlLOG(severity, message)
#define aLOG_TRACE(message)       dahlLOG_TRACE(message)
#define aLOG_INFO(message)        dahlLOG_INFO(message)
#define aLOG_WARN(message)        dahlLOG_WARN(message)
#define aLOG_ERROR(message)       dahlLOG_ERROR(message)
#define aLOG_CRITICAL(message)    dahlLOG_CRITICAL(message)

#define aPROFILE_START(name, filepath) dahlPROFILE_BEGIN_SESSION(name, filepath)
#define aPROFILE_END()                 dahlPROFILE_END_SESSION()
#define aPROFILE_SCOPE(name)           dahlPROFILE_SCOPE(name)
#define aPROFILE_FUNCTION()            dahlPROFILE_FUNCTION()

#define aVERSION  "v0.0.2a";
