/////////////////////////////////////////////////////////////////
//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++
//  This file serves as definitions for the DAdbg namespace
//    Essentially, this serves as a lightweight logging/assert class
//    This was made to allow transition to DAGGer more easy for ASCII apps
/////////////////////////////
//
//  Additionally, some defines will modify what is included
//    #define DA_USE_CLEAR   -   Include cross-platform console clearing
//    #define DA_USE_PRINT   -   Include console-color printing library
//
/////////////////////////////
//  Defines to disable things
//    #define NO_DALog       -   This disables DALog
//    #define NO_DAAssert    -   This disables DAAsserts
//
#pragma once

//	TEMPORARY FOR TESTING **********
#define DA_USE_CLEAR 1
#define DA_USE_PRINT 1
/////////////////////////////////////

//  Check for user define overrides
#ifdef NO_DALog
	#define DA_USE_LOG 0
#else
	#define DA_USE_LOG 1		//	Enable logging
#endif

#ifdef NO_DAAssert
	#define DA_USE_ASSERT 0
#else
	#define DA_USE_ASSERT 1	//	Enable Asserts
#endif


////////////////////////////////////////////////////////////////////
//  -    User defines - These are the defines you would use    -  //
////////////////////////////////////////////////////////////////////
#ifdef DA_USE_LOG	//  Log defines  //
	#define daLOG(severity, message)           DAdbg::Log(severity, message)
	#define daLOG_TRACE(message, ...)      daLOG(Level::Trace,    std::to_string(__VA_ARGS__))
	#define daLOG_INFO(message, ...)       daLOG(Level::Info,     std::to_string(__VA_ARGS__))
	#define daLOG_WARN(message, ...)       daLOG(Level::Warn,     std::to_string(__VA_ARGS__))
	#define daLOG_ERROR(message, ...)      daLOG(Level::Error,    std::to_string(__VA_ARGS__))
	#define daLOG_CRITICAL(message, ...)   daLOG(Level::Critical, std::to_string(__VA_ARGS__))
#endif
#ifdef DA_USE_ASSERT	//  Assert defines  //
	#define daAssert(x, ...)               dadbg::daASSERT(x, __VA_ARGS__)
#endif
#ifdef DA_USE_CLEAR		//  Clear defines  //
	#define daClear()                      DAdbg::ClearScreen()
#endif
#ifdef DA_USE_PRINT		//  Print defines  //
	#define daPrint                        DAdbg::DAPrint
#endif

//  Platform detection
#ifdef _WIN32
		//  Windows x64/x86 //
	#ifdef _WIN64
			#define DAdbg_PLATFORM_WINDOWS
	#else
			#define DAdbg_PLATFORM_WINDOWS
	#endif
#elif defined(__APPLE__) || defined(__MACH__)   //  Apple Platforms
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error DAdbg_PLATFORM_IOS_SIMULATOR
	#elif TARGET_OS_IPHONE == 1
		#define DAdbg_PLATFORM_IOS     //  iOS
	#elif TARGET_OS_MAC == 1           //  MacOS
		#define DAdbg_PLATFORM_MACOS
	#else
		#error "Unknown Apple platform!"
	#endif
//  Android is based off the linux kernel, so __ANDROID__ must be checked first
#elif defined(__ANDROID__)              //  Android
	#define DAdbg_PLATFORM_ANDROID
	#elif defined(__linux__)            //  Linux
	#define DAdbg_PLATFORM_LINUX
#else	//  Unknown compiler/platform   //
	#error "Unknown platform!"
#endif  //    END platform detection

///////////////////////////////////////////////////////////////////////////////////////////////////
//  Begin Code

#include <iostream>
#include <string>

////////////////////////////////////////////////////////////////////////////////
//  --------------------------------  DALog  -------------------------------  //
////////////////////////////////////////////////////////////////////////////////
#ifdef DA_USE_LOG

	//	Enum Class for determining Log levels
	enum class Level
	{
		Trace    = 0,	//	Trace:		Unimportant, but worth logging?
		Info     = 1,	//	Info:		Log info to console
		Warn     = 2,	//	Warn:		A warning, something isn't quite right
		Error    = 3,	//	Error:		An error, something is wrong
		Critical = 4	//	Critical:	Critical, exit program
	};

	namespace DAdbg
	{

		void Log(Level severity, const char* message);

		//  Overloads
		void Log(Level severity);
		void Log(Level severity, std::string& message);

	}  //  END namespace DAdbg

#endif	//	DALog

////////////////////////////////////////////////////////////////////////////////
//  -----------------------------  DAAssert  -------------------------------  //
////////////////////////////////////////////////////////////////////////////////
#ifdef DA_USE_ASSERT
	namespace DAdbg
	{
		#ifdef DALog
			#define daASSERT(x, ...) { if(!(x)) { daLOG(Level::Error, "Assertion Failed: " + std::to_string(__VA_ARGS__)); } }
		#else
			#define daASSERT(x, ...) { if(!(x)) { std::cout << "Assertion Failed: " << std::to_string(__VA_ARGS__)) << std::endl; } }
		#endif
	}	//	END namespace DAdbg

#endif	//	DAAssert

////////////////////////////////////////////////////////////////////////////////
//  ------------------------------  DAClear  -------------------------------  //
////////////////////////////////////////////////////////////////////////////////
#ifdef DA_USE_CLEAR
	namespace DAdbg
	{
		void ClearScreen();
	}	//	END namespace DAdbg
#endif	//	DAClear

////////////////////////////////////////////////////////////////////////////////
//  ------------------------------  DAPrint  -------------------------------  //
////////////////////////////////////////////////////////////////////////////////
#ifdef DA_USE_PRINT
	enum class Location
	{
		Foreground = 0,
		Background = 1
	};
	enum class Color
	{
		Black    = 0,
		Red      = 1,
		Green   = 2,
		Yellow   = 3,
		Blue     = 4,
		Magenta  = 5,
		Cyan     = 6,
		White    = 7,

		BrightBlack   = 10,
		BrightRed     = 11,
		BrightGreen   = 12,
		BrightYellow  = 13,
		BrightBlue    = 14,
		BrightMagenta = 15,
		BrightCyan    = 16,
		BrightWhite   = 17,

		Null
	};

	enum class Style
	{
		Reset = 0,
		Bold = 1,
		Dim = 2,
		Italic = 3,
		Underline = 4,
		Invert = 5,
		Strikethrough = 6,

		Null
	};

	namespace DAdbg
	{
		//	These allow you to use these instead of the full names
			//	Location 'aliases'	//
		constexpr Location fg = Location::Foreground;
		constexpr Location bg = Location::Background;

			//	Color 'aliases'	//
		constexpr Color Gray      = Color::BrightBlack;
		constexpr Color DarkGray  = Color::BrightBlack;
		constexpr Color LightGray = Color::White;
				//	"Bright" colors
		constexpr Color bBlack   = Color::BrightBlack;
		constexpr Color bRed     = Color::BrightRed;
		constexpr Color bGreen   = Color::BrightGreen;
		constexpr Color bYellow  = Color::BrightYellow;
		constexpr Color bBlue    = Color::BrightBlue;
		constexpr Color bMagenta = Color::BrightMagenta;
		constexpr Color bCyan    = Color::BrightCyan;
		constexpr Color bWhite   = Color::BrightWhite;

		class DAPrint
		{
		public:
			//	These print one thing with a style
			void Print(const char* message);		//	This prints with the set style
			void Print(Color ForegroundColor, const char* message);
			void Print(Style style, Color ForegroundColor, const char* message);
			void Print(Location location, Color color, const char* message);
			void Print(Style style, Color ForegroundColor, Color BackgroundColor, const char* message);

			//	These set the current style
			void SetStyle(Color ForegroundColor);
			void SetStyle(Color ForegroundColor, Color BackgroundColor);
			void SetStyle(Style style);
			void SetStyle(Style style, Color ForegroundColor);
			void SetStyle(Style style, Color ForegroundColor, Color BackgroundColor);
			void SetStyle() { ClearStyle(); }

			//	These add to the current style
			void AddStyle(Color color);
			void AddStyle(Location location, Color color);
			void AddStyle(Style style, Color ForegroundColor);
			void AddStyle(Location location, Style style, Color color);
			void AddStyle() { ClearStyle(); }

			void ClearStyle();
		private:
			//	Private functions
			void SetCurrentStyle(Style style, Color ForegroundColor, Color BackgroundColor);

			void AddToCurrentStyle(Location location, Color color);
			void AddToCurrentStyle(Style style);

			const char* GetColor(Color color);
			const char* GetStyle(Style style);

		private:
			std::string s_Code;	//	This is where the style is saved
			Color s_ForegroundColor = Color::Null;
			Color s_BackgroundColor = Color::Null;
			Style s_Style = Style::Null;

		};	//	END class Print

	}	//	END namespace DAdbg

#endif	//	DAPrint
