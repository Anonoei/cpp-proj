/////////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves a cross-platform library for Logging, Asserts, Printing colored text(16-bit color!),
//    user input, etc!
//  This was made to allow transition to DAGGer more easy for ASCII apps
//    with a few added bonuses
//----=============================================================================----//
//----=------------------------------  verison 0.4.3  ----------------------------=----//
//----=============================================================================----//
/////////////////////////////
//  Additionally, some defines will modify what is included
//    #define DA_ALL.........Enable all libraries
//    #define DA_PRINT.......Include cross-platform color printing library
//    #define DA_INPUT.......Include cross-platform input library
//    #define DA_PROFILE.....Include function profiling library
//    #define DA_TIME........Include timestep library
//
/////////////////////////////
//  Defines to disable things
//    #define NO_DA_LOG       -   This disables DALog
//    #define NO_DA_ASSERT    -   This disables DAAsserts
//
/////////////////////////////
//  To be nice, this is how the above defines work:
//    #define DA_ALL
//    #include <DAdbg.h>
/////////////////////////////
//           Thanks for checking out my library!
////////////////////////////////////////////////////////////////////
#pragma once

#ifndef DADBG_H_HEADER_GUARD	//	DAdbg #include guards
	#define DADBG_H_HEADER_GUARD
	#define DAdbgVER   "0.4.3a"

//  Check for user define overrides
#ifdef DA_ALL
	#define DA_USE_CLEAR 1
	#define DA_USE_LOG 1
	#define DA_USE_ASSERT 1

	#define DA_USE_PRINT 1
	#define DA_USE_INPUT 1
	#define DA_USE_PROFILE 1
	#define DA_USE_TIME 1
#else
	#define DA_USE_CLEAR 1		//	Enable cross-platform clear screen

	#ifdef NO_DA_LOG
		#define DA_USE_LOG 0
	#else
		#define DA_USE_LOG 1		//	Enable logging
	#endif

	#ifdef NO_DA_ASSERT
		#define DA_USE_ASSERT 0
	#else
		#define DA_USE_ASSERT 1		//	Enable Asserts
	#endif


	//	These are disabled by default
	#ifdef DA_PRINT
		#define DA_USE_PRINT 1	//	Enable DAPrint
	#else
		#define DA_USE_PRINT 0
	#endif

	#ifdef DA_INPUT
		#define DA_USE_INPUT 1	//	Enable DAInput
	#else
		#define DA_USE_INPUT 0
	#endif

	#ifdef DA_PROFILE
		#define DA_USE_PROFILE 1	//	Enable DAProfile
	#else
		#define DA_USE_PROFILE 0
	#endif

	#ifdef DA_TIME
		#define DA_USE_TIME 1	//	Enable DATime
	#else
		#define DA_USE_TIME 0
	#endif
#endif

////////////////////////////////////////////////////////////////////
//  -                    Platform Detection                    -  //
////////////////////////////////////////////////////////////////////
#ifdef _WIN32	//	Win32
	#include <Windows.h>
	#ifdef _WIN64	//	Win64
			#define DAdbg_PLATFORM_WINDOWS
	#else
			#define DAdbg_PLATFORM_WINDOWS
	#endif
#elif defined(__APPLE__) || defined(__MACH__)   //  Apple Platforms
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#define DAdbg_PLATFORM_IOS_SIMULATOR
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

////////////////////////////////////////////////////////////////////
//  -    User defines - These are the defines you would use    -  //
////////////////////////////////////////////////////////////////////
	//	These are the defines used within functions
#define fgBlack              ::DAdbg::Internal::Foreground::DACOLOR::daColorBlack			//	(0)  Foreground Black
#define fgRed                ::DAdbg::Internal::Foreground::DACOLOR::daColorRed				//	(1)  Foreground Red
#define fgGreen              ::DAdbg::Internal::Foreground::DACOLOR::daColorGreen			//	(2)  Foreground Green
#define fgYellow             ::DAdbg::Internal::Foreground::DACOLOR::daColorYellow			//	(3)  Foreground Yellow
#define fgBlue               ::DAdbg::Internal::Foreground::DACOLOR::daColorBlue			//	(4)  Foreground Blue
#define fgMagenta            ::DAdbg::Internal::Foreground::DACOLOR::daColorMagenta			//	(5)  Foreground Magenta
#define fgCyan               ::DAdbg::Internal::Foreground::DACOLOR::daColorCyan			//	(6)  Foreground Cyan
#define fgWhite              ::DAdbg::Internal::Foreground::DACOLOR::daColorWhite			//	(7)  Foreground White
#define fgBrightBlack        ::DAdbg::Internal::Foreground::DACOLOR::daColorBrightBlack		//	(8)  Foreground Black
#define fgBrightRed          ::DAdbg::Internal::Foreground::DACOLOR::daColorBrightRed		//	(9)  Foreground Bright Red
#define fgBrightGreen        ::DAdbg::Internal::Foreground::DACOLOR::daColorBrightGreen		//	(10) Foreground Bright Green
#define fgBrightYellow       ::DAdbg::Internal::Foreground::DACOLOR::daColorBrightYellow	//	(11) Foreground Bright Yellow
#define fgBrightBlue         ::DAdbg::Internal::Foreground::DACOLOR::daColorBrightBlue		//	(12) Foreground Bright Blue
#define fgBrightMagenta      ::DAdbg::Internal::Foreground::DACOLOR::daColorBrightMagenta	//	(13) Foreground Bright Magenta
#define fgBrightCyan         ::DAdbg::Internal::Foreground::DACOLOR::daColorBrightCyan		//	(14) Foreground Bright Cyan
#define fgBrightWhite        ::DAdbg::Internal::Foreground::DACOLOR::daColorBrightWhite		//	(15) Foreground Bright White
#define fgUndefined          ::DAdbg::Internal::Foreground::DACOLOR::daColorUndefined		//	(16) Foreground Undefined

#define bgBlack              ::DAdbg::Internal::Background::DACOLOR::daColorBlack			//	(0)  Background Black
#define bgRed                ::DAdbg::Internal::Background::DACOLOR::daColorRed				//	(1)  Background Red
#define bgGreen              ::DAdbg::Internal::Background::DACOLOR::daColorGreen			//	(2)  Background Green
#define bgYellow             ::DAdbg::Internal::Background::DACOLOR::daColorYellow			//	(3)  Background Yellow
#define bgBlue               ::DAdbg::Internal::Background::DACOLOR::daColorBlue			//	(4)  Background Blue
#define bgMagenta            ::DAdbg::Internal::Background::DACOLOR::daColorMagenta			//	(5)  Background Magenta
#define bgCyan               ::DAdbg::Internal::Background::DACOLOR::daColorCyan			//	(6)  Background Cyan
#define bgWhite              ::DAdbg::Internal::Background::DACOLOR::daColorWhite			//	(7)  Background White
#define bgBrightBlack        ::DAdbg::Internal::Background::DACOLOR::daColorBrightBlack		//	(8)  Background Bright Black
#define bgBrightRed          ::DAdbg::Internal::Background::DACOLOR::daColorBrightRed		//	(9)  Background Bright Red
#define bgBrightGreen        ::DAdbg::Internal::Background::DACOLOR::daColorBrightGreen		//	(10) Background Bright Green
#define bgBrightYellow       ::DAdbg::Internal::Background::DACOLOR::daColorBrightYellow	//	(11) Background Bright Yellow
#define bgBrightBlue         ::DAdbg::Internal::Background::DACOLOR::daColorBrightBlue		//	(12) Background Bright Blue
#define bgBrightMagenta      ::DAdbg::Internal::Background::DACOLOR::daColorBrightMagenta	//	(13) Background Bright Magenta
#define bgBrightCyan         ::DAdbg::Internal::Background::DACOLOR::daColorBrightCyan		//	(14) Background Bright Cyan
#define bgBrightWhite        ::DAdbg::Internal::Background::DACOLOR::daColorBrightWhite		//	(15) Background Bright White
#define bgUndefined          ::DAdbg::Internal::Background::DACOLOR::daColorUndefined		//	(16) Background Undefined

#define FGColor              ::DAdbg::Internal::Foreground::DACOLOR	//	typedef enum for foreground colors
#define BGColor              ::DAdbg::Internal::Background::DACOLOR	//	typedef enum for background colors

#define FGdef                ::DAdbg::Internal::daFGColors	//	Array that stores the platform-specific implementation of foreground colors
#define BGdef                ::DAdbg::Internal::daBGColors	//	Array that stores the platform-specific implementation of background colors

//	These are just index values used in the daFG/BGColors array and shouldn't be used
constexpr int daBlack         = 0;	//	Black
constexpr int daRed           = 1;	//	Red
constexpr int daGreen         = 2;	//	Green
constexpr int daYellow        = 3;	//	Yellow
constexpr int daBlue          = 4;	//	Blue
constexpr int daMagenta       = 5;	//	Magenta
constexpr int daCyan          = 6;	//	Cyan
constexpr int daWhite         = 7;	//	White
constexpr int daBrightBlack   = 8;	//	Bright Black
constexpr int daBrightRed     = 9;	//	Bright Red
constexpr int daBrightGreen   = 10;	//	Bright Green
constexpr int daBrightYellow  = 11;	//	Bright Yellow
constexpr int daBrightBlue    = 12;	//	Bright Blue
constexpr int daBrightMagenta = 13;	//	Bright Magenta
constexpr int daBrightCyan    = 14;	//	Bright Cyan
constexpr int daBrightWhite   = 15;	//	Bright White
constexpr int daUndefined     = 16;	//	Undefined

#ifdef DA_USE_LOG	//  Log defines  //
	#define daLOG(severity, message)           ::DAdbg::Log(severity,        message)	//	Log with log level
	#define daLOG_CRITICAL(message)            ::DAdbg::Log(Level::Critical, message)	//	Log critical message
	#define daLOG_ERROR(message)               ::DAdbg::Log(Level::Error,    message)	//	Log error message
	#define daLOG_WARN(message)                ::DAdbg::Log(Level::Warn,     message)	//	Log warning message
	#define daLOG_INFO(message)                ::DAdbg::Log(Level::Info,     message)	//	Log information
	#define daLOG_TRACE(message)               ::DAdbg::Log(Level::Trace,    message)	//	Basically printing
#else	//	DALog isn't used - do nothing
	#define daLOG(severity, message)
	#define daLOG_CRITICAL(message)
	#define daLOG_ERROR(message)
	#define daLOG_WARN(message)
	#define daLOG_INFO(message)
	#define daLOG_TRACE(message)
#endif
#ifdef DA_USE_ASSERT	//  Assert defines  //
	#define daAssert(x, ...)               ::DAdbg::daASSERT(x, __VA_ARGS__)
#else	//	DAAssert isn't used - do nothing
	#define daAssert(x, ...)
#endif
#ifdef DA_USE_CLEAR		//  Clear defines  //
	#define daClearScreen()                ::DAdbg::ClearScreen()	//	Cross-platform clear screen
#endif
#ifdef DA_USE_PRINT		//  Print defines  //
	#define daPrint                        ::DAdbg::Print::Print		//	std::cout w/color 
	#define daPrintl                       ::DAdbg::Print::Printl		//	std::cout w/color and std::endl
	#define daPrintChar                    ::DAdbg::Print::PrintChar	//	std::cout w/color only for specified section
	#define daSetDefaultColor              ::DAdbg::Print::SetDefaults	//	Set the default printing color
	#ifdef DAdbg_PLATFORM_WINDOWS
		#define daPrintRBG                 ::DAdbg::Print::PrintRGB	//	Prints RBG value (Windows ONLY!)
	#endif
#endif
#ifdef DA_USE_INPUT		//  Input defines  //
	#define daEvent                 ::DAdbg::Input::Event
	#define daEventDispatcher       ::DAdbg::Input::EventDispatcher
	//	Key defines
	#define daKey                 ::DAdbg::Input::KeyCode				//	The KeyCode enum class
	#define daKeyEvent            ::DAdbg::Input::KeyEvent				//	A generic KeyEvent (shouldn't be used)
	#define daKeyPressedEvent     ::DAdbg::Input::KeyPressedEvent		//	When a key is pressed down (also contain's repeat count)
	#define daKeyReleasedEvent    ::DAdbg::Input::KeyReleasedEvent		//	When a key is released
	#define daKeyTypedEvent       ::DAdbg::Input::KeyTypedEvent			//	When a key is typed (modifiers applied differently)
	//	Mouse defines
	#define daMouseCode                ::DAdbg::Input::MouseCode				//	The MouseCode enum class
	#define daMouseMovedEvent          ::DAdbg::Input::MouseMovedEvent			//	When the mouse has moved
	#define daMouseScrolledEvent       ::DAdbg::Input::MouseScrolledEvent		//	When the mouse is scrolled
	#define daMouseButtonEvent         ::DAdbg::Input::MouseButtonEvent			//	A generic MouseButtonEvent (shouldn't be used)
	#define daMouseButtonPressedEvent  ::DAdbg::Input::MouseButtonPressedEvent	//	When a mouse button is pressed
	#define daMouseButtonReleasedEvent ::DAdbg::Input::MouseButtonReleasedEvent	//	When a mouse button is released

	#define DA_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#endif
#ifdef DA_USE_PROFILE	//  Profile defines  //
	// Resolve which function signature macro will be used. Note that this only
	// is resolved when the (pre)compiler starts, so the syntax highlighting
	// could mark the wrong one in your editor!
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define DA_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define DA_FUNC_SIG __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
		#define DA_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define DA_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define DA_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define DA_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define DA_FUNC_SIG __func__
	#else
		#define DA_FUNC_SIG "Dr_FUNC_SIG unknown!"
	#endif

	#define daPROFILE_BEGIN_SESSION(name, filepath) ::DAdbg::Profile::daInstrumentor::Get().BeginSession(name, filepath)
	#define daPROFILE_END_SESSION() ::DAdbg::Profile::daInstrumentor::Get().EndSession()
	#define daPROFILE_SCOPE(name) constexpr auto fixedName = ::DAdbg::Profile::daInstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
																			::DAdbg::Profile::daInstrumentationTimer timer##__LINE__(fixedName.Data)
	#define daPROFILE_FUNCTION() daPROFILE_SCOPE(DA_FUNC_SIG)

#else	//	not using DAProfile - do nothing
	#define daPROFILE_BEGIN_SESSION(name, filepath)
	#define daPROFILE_END_SESSION()
	#define daPROFILE_SCOPE(name)
	#define daPROFILE_FUNCTION()
#endif
#ifdef DA_USE_TIME	//  Time defines  //
	#define daTimer          ::DAdbg::Time::Timer
	#define daTimestep       ::DAdbg::Time::Timestep
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                           //
//                                            BEGIN DEFINITIONS                                              //
//                                                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <stdio.h>

#ifdef DA_USE_PROFILE
	#include <sstream>
	#include <algorithm>
	#include <chrono>
	#include <fstream>
	#include <iomanip>
	#include <thread>
	#include <mutex>
#else
	#ifdef DA_USE_TIME
		#include <chrono>
	#endif
#endif
#ifdef DA_USE_INPUT
	#include <ostream>
#endif

////////////////////////////////////////////////////////////////////////////////
//  --------------------------------  DAdbg  -------------------------------  //
////////////////////////////////////////////////////////////////////////////////
namespace DAdbg::Internal
{
	namespace Foreground
	{
		typedef enum class DACOLOR
		{
			daColorBlack         = 0,	//	Foreground Black
			daColorRed           = 1,	//	Foreground Red
			daColorGreen         = 2,	//	Foreground Green
			daColorYellow        = 3,	//	Foreground Yellow
			daColorBlue          = 4,	//	Foreground Blue
			daColorMagenta       = 5,	//	Foreground Magenta
			daColorCyan          = 6,	//	Foreground Cyan
			daColorWhite         = 7,	//	Foreground White

			daColorBrightBlack   = 8,	//	Foreground Bright Black
			daColorBrightRed     = 9,	//	Foreground Bright Red
			daColorBrightGreen   = 10,	//	Foreground Bright Green
			daColorBrightYellow  = 11,	//	Foreground Bright Yellow
			daColorBrightBlue    = 12,	//	Foreground Bright Blue
			daColorBrightMagenta = 13,	//	Foreground Bright Magenta
			daColorBrightCyan    = 14,	//	Foreground Bright Cyan
			daColorBrightWhite   = 15,	//	Foreground Bright White
			daColorUndefined     = 16	//	Foreground Undefined Color
		} daColor;
	}	//	END namespace Foreground

	namespace Background
	{
		typedef enum class DACOLOR
		{
			daColorBlack         = 0,	//	Background Black
			daColorRed           = 1,	//	Background Red
			daColorGreen         = 2,	//	Background Green
			daColorYellow        = 3,	//	Background Yellow
			daColorBlue          = 4,	//	Background Blue
			daColorMagenta       = 5,	//	Background Magenta
			daColorCyan          = 6,	//	Background Cyan
			daColorWhite         = 7,	//	Background White
			
			daColorBrightBlack   = 8,	//	Background Bright Black
			daColorBrightRed     = 9,	//	Background Bright Red
			daColorBrightGreen   = 10,	//	Background Bright Green
			daColorBrightYellow  = 11,	//	Background Bright Yellow
			daColorBrightBlue    = 12,	//	Background Bright Blue
			daColorBrightMagenta = 13,	//	Background Bright Magenta
			daColorBrightCyan    = 14,	//	Background Bright Cyan
			daColorBrightWhite   = 15,	//	Background Bright White
			daColorUndefined     = 16	//	Background Undefined Color
		} daColor;
	}	//	END namespace Background

	typedef struct DAATTRIBUTES	//	Possibly un-needed
	{
		#ifdef DAdbg_PLATFORM_WINDOWS
			WORD Foreground;
			WORD Background;
		#else
			const char* Foreground;
			const char* Background;
		#endif
	} daAttributes;

	//	These are user-end functions
	void daShowCursor(bool enable);

		//  These shouldn't be called by the user  //
	// For printing functionality, please #define DA_PRINT
	void Set(FGColor fgColor, BGColor bgColor);
	//	Print
	void Print(FGColor fgColor, BGColor bgColor, const char* message);
	//	Print line
	void Printl(FGColor fgColor, BGColor bgColor, const char* message);
	//	Print characters
	void PrintChar(FGColor fgColor, BGColor bgColor, const char* character);

	void daReset();
	void End();


}	//	END namespace DAdbg::Internal

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
		#ifdef DA_USE_LOG
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
	namespace DAdbg::Print
	{
		//	Print to screen
		void Print(const char* message);	//	This uses the user default colors
		void Print(FGColor fgColor, const char* message);
		void Print(BGColor bgColor, const char* message);
		void Print(FGColor fgColor, BGColor bgColor, const char* message);

		//	Print a single line to screen
		void Printl(const char* message);	//	This uses the user default colors
		void Printl(FGColor fgColor, const char* message);
		void Printl(BGColor bgColor, const char* message);
		void Printl(FGColor fgColor, BGColor bgColor, const char* message);

		//	Print colored characters to screen then resets
		void PrintChar(const char* character);	//	This uses the user's default colors
		void PrintChar(FGColor fgColor, const char* character);
		void PrintChar(BGColor bgColor, const char* character);
		void PrintChar(FGColor fgColor, BGColor bgColor, const char* character);

		void SetDefaults(FGColor fgColor, BGColor bgColor);
		inline void SetDefaults(FGColor fgColor) { SetDefaults(fgColor, bgUndefined); }
		inline void SetDefaults(BGColor bgColor) { SetDefaults(fgWhite, bgColor); }

		#ifdef DAdbg_PLATFORM_WINDOWS
			void PrintRGB(COLORREF rbgValue);
		#endif

		int daGetFGvalue(FGColor fgColor);
		int daGetBGvalue(BGColor bgColor);
	}	//	END namespace DAdbg::Print

#endif	//	DAPrint

////////////////////////////////////////////////////////////////////////////////
//  ------------------------------  DAInput  -------------------------------  //
////////////////////////////////////////////////////////////////////////////////
#ifdef DA_USE_INPUT
	namespace DAdbg::Input
	{
		//	Defines keycodes
		typedef enum class KeyCode : uint16_t
		{
		#ifdef DAdbg_PLATFORM_WINDOWS
			Space        = VK_SPACE,
			Apostrophe   = NULL,
			Comma        = NULL,
			Minus        = NULL,
			Period       = NULL,
			Slash        = NULL,

			D0           = 0x30,
			D1           = 0x31,
			D2           = 0x32,
			D3           = 0x33,
			D4           = 0x34,
			D5           = 0x35,
			D6           = 0x36,
			D7           = 0x37,
			D8           = 0x38,
			D9           = 0x39,

			Semicolon    = NULL,
			Equal        = NULL,

			A            = 0x41,
			B            = 0x42,
			C            = 0x43,
			D            = 0x44,
			E            = 0x45,
			F            = 0x46,
			G            = 0x47,
			H            = 0x48,
			I            = 0x49,
			J            = 0x4A,
			K            = 0x4B,
			L            = 0x4C,
			M            = 0x4D,
			N            = 0x4E,
			O            = 0x4F,
			P            = 0x50,
			Q            = 0x51,
			R            = 0x52,
			S            = 0x53,
			T            = 0x54,
			U            = 0x55,
			V            = 0x56,
			W            = 0x57,
			X            = 0x58,
			Y            = 0x59,
			Z            = 0x5A,

			LeftBracket  = NULL,
			BackSlash    = NULL,
			RightBracket = NULL,
			GraveAccent  = NULL,

			World1       = NULL,
			World2       = NULL,

			//  Function Keys  //	= 
			Escape       = VK_ESCAPE,
			Enter        = VK_RETURN,
			Tab          = VK_TAB,
			Backspace    = VK_BACK,
			Insert       = VK_INSERT,
			Delete       = VK_DELETE,
			Right        = VK_RIGHT,
			Left         = VK_LEFT,
			Down         = VK_DOWN,
			Up           = VK_UP,
			PageUp       = VK_PRIOR,
			PageDown     = VK_NEXT,
			Home         = VK_HOME,
			End          = VK_END,
			CapsLock     = VK_CAPITAL,
			ScrollLock   = VK_SCROLL,
			NumLock      = VK_NUMLOCK,
			PrintScreen  = VK_SNAPSHOT,
			Pause        = VK_PAUSE,
			F1           = VK_F1,
			F2           = VK_F2,
			F3           = VK_F3,
			F4           = VK_F4,
			F5           = VK_F5,
			F6           = VK_F6,
			F7           = VK_F7,
			F8           = VK_F8,
			F9           = VK_F9,
			F10          = VK_F10,
			F11          = VK_F11,
			F12          = VK_F12,
			F13          = VK_F13,
			F14          = VK_F14,
			F15          = VK_F15,
			F16          = VK_F16,
			F17          = VK_F17,
			F18          = VK_F18,
			F19          = VK_F19,
			F20          = VK_F20,
			F21          = VK_F21,
			F22          = VK_F22,
			F23          = VK_F23,
			F24          = VK_F24,
			F25          = NULL,

			//  Keypad //
			KP0          = VK_NUMPAD0,
			KP1          = VK_NUMPAD1,
			KP2          = VK_NUMPAD2,
			KP3          = VK_NUMPAD3,
			KP4          = VK_NUMPAD4,
			KP5          = VK_NUMPAD5,
			KP6          = VK_NUMPAD6,
			KP7          = VK_NUMPAD7,
			KP8          = VK_NUMPAD8,
			KP9          = VK_NUMPAD9,
			KPDecimal    = VK_DECIMAL,
			KPDivide     = VK_DIVIDE,
			KPMultiply   = VK_MULTIPLY,
			KPSubtract   = VK_SUBTRACT,
			KPAdd        = VK_ADD,
			KPEnter      = VK_RETURN,
			KPEqual      = NULL,

			LeftShift    = VK_LSHIFT,
			LeftControl  = VK_LCONTROL,
			LeftAlt      = VK_LMENU,
			LeftSuper    = VK_LWIN,
			RightShift   = VK_RSHIFT,
			RightControl = VK_RCONTROL,
			RightAlt     = VK_RMENU,
			RightSuper   = VK_RWIN,
			Menu         = VK_MENU
#else
			Space        = "SPCE",
			Apostrophe   = "AC11",
			Comma        = "AB08",
			Minus        = "AE11",
			Period       = "AB09",
			Slash        = "AB10",

			D0           = "AE10",
			D1           = "AE01",
			D2           = "AE02",
			D3           = "AE03",
			D4           = "AE04",
			D5           = "AE05",
			D6           = "AE06",
			D7           = "AE07",
			D8           = "AE08",
			D9           = "AE09",

			Semicolon    = "AC10",
			Equal        = "AE12",

			A            = "AC01",
			B            = "AB05",
			C            = "AB03",
			D            = "AC03",
			E            = "AD03",
			F            = "AC04",
			G            = "AC05",
			H            = "AC06",
			I            = "AD08",
			J            = "AC07",
			K            = "AC08",
			L            = "AC09",
			M            = "AB07",
			N            = "AB06",
			O            = "AD09",
			P            = "AD10",
			Q            = "AD01",
			R            = "AD04",
			S            = "AC02",
			T            = "AD05",
			U            = "AD07",
			V            = "AB04",
			W            = "AD02",
			X            = "AB02",
			Y            = "AD06",
			Z            = "AB01",

			LeftBracket  = "AD11",
			BackSlash    = "BKSL",
			RightBracket = "AD12",
			GraveAccent  = "TLDE",

			World1       = "LSGT",
			World2       = "",

			//  Function Keys  //	= 
			Escape       = "ESC",
			Enter        = "RTRN",
			Tab          = "TAB",
			Backspace    = "BKSP",
			Insert       = "INS",
			Delete       = "DELE",
			Right        = "RGHT",
			Left         = "LEFT",
			Down         = "DOWN",
			Up           = "UP",
			PageUp       = "PGUP",
			PageDown     = "PGDN",
			Home         = "HOME",
			End          = "END",
			CapsLock     = "CAPS",
			ScrollLock   = "SCLK",
			NumLock      = "NMLK",
			PrintScreen  = "PRSC",
			Pause        = "PAUS",
			F1           = "FK01",
			F2           = "FK02",
			F3           = "FK03",
			F4           = "FK04",
			F5           = "FK05",
			F6           = "FK06",
			F7           = "FK07",
			F8           = "FK08",
			F9           = "FK09",
			F10          = "FK10",
			F11          = "FK11",
			F12          = "FK12",
			F13          = "FK13",
			F14          = "FK14",
			F15          = "FK15",
			F16          = "FK16",
			F17          = "FK17",
			F18          = "FK18",
			F19          = "FK19",
			F20          = "FK20",
			F21          = "FK21",
			F22          = "FK22",
			F23          = "FK23",
			F24          = "FK24",
			F25          = "FK25",

			//  Keypad //
			KP0          = "KP0",
			KP1          = "KP1",
			KP2          = "KP2",
			KP3          = "KP3",
			KP4          = "KP4",
			KP5          = "KP5",
			KP6          = "KP6",
			KP7          = "KP7",
			KP8          = "KP8",
			KP9          = "KP9",
			KPDecimal    = "KPDL",
			KPDivide     = "KPDV",
			KPMultiply   = "KPMU",
			KPSubtract   = "KPSU",
			KPAdd        = "KPAD",
			KPEnter      = "KPEN",
			KPEqual      = "KPEQ",

			LeftShift    = "LFSH",
			LeftControl  = "LCTL",
			LeftAlt      = "LALT",
			LeftSuper    = "LWIN",
			RightShift   = "RTSH",
			RightControl = "RCTL",
			RightAlt     = "RALT",
			RightSuper   = "RWIN",
			Menu         = "MENU"
		#endif
		} Key;

		inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
		{
			os << static_cast<int32_t>(keyCode);
			return os;
		}

		//	Abstracted Key defines
	#define DA_KEY_SPACE           ::DAdbg::Input::daKey::Space
	#define DA_KEY_APOSTROPHE      ::DAdbg::Input::daKey::Apostrophe    /* ' */
	#define DA_KEY_COMMA           ::DAdbg::Input::daKey::Comma         /* , */
	#define DA_KEY_MINUS           ::DAdbg::Input::daKey::Minus         /* - */
	#define DA_KEY_PERIOD          ::DAdbg::Input::daKey::Period        /* . */
	#define DA_KEY_SLASH           ::DAdbg::Input::daKey::Slash         /* / */
	#define DA_KEY_0               ::DAdbg::Input::daKey::D0
	#define DA_KEY_1               ::DAdbg::Input::daKey::D1
	#define DA_KEY_2               ::DAdbg::Input::daKey::D2
	#define DA_KEY_3               ::DAdbg::Input::daKey::D3
	#define DA_KEY_4               ::DAdbg::Input::daKey::D4
	#define DA_KEY_5               ::DAdbg::Input::daKey::D5
	#define DA_KEY_6               ::DAdbg::Input::daKey::D6
	#define DA_KEY_7               ::DAdbg::Input::daKey::D7
	#define DA_KEY_8               ::DAdbg::Input::daKey::D8
	#define DA_KEY_9               ::DAdbg::Input::daKey::D9
	#define DA_KEY_SEMICOLON       ::DAdbg::Input::daKey::Semicolon     /* ; */
	#define DA_KEY_EQUAL           ::DAdbg::Input::daKey::Equal         /* = */
	#define DA_KEY_A               ::DAdbg::Input::daKey::A
	#define DA_KEY_B               ::DAdbg::Input::daKey::B
	#define DA_KEY_C               ::DAdbg::Input::daKey::C
	#define DA_KEY_D               ::DAdbg::Input::daKey::D
	#define DA_KEY_E               ::DAdbg::Input::daKey::E
	#define DA_KEY_F               ::DAdbg::Input::daKey::F
	#define DA_KEY_G               ::DAdbg::Input::daKey::G
	#define DA_KEY_H               ::DAdbg::Input::daKey::H
	#define DA_KEY_I               ::DAdbg::Input::daKey::I
	#define DA_KEY_J               ::DAdbg::Input::daKey::J
	#define DA_KEY_K               ::DAdbg::Input::daKey::K
	#define DA_KEY_L               ::DAdbg::Input::daKey::L
	#define DA_KEY_M               ::DAdbg::Input::daKey::M
	#define DA_KEY_N               ::DAdbg::Input::daKey::N
	#define DA_KEY_O               ::DAdbg::Input::daKey::O
	#define DA_KEY_P               ::DAdbg::Input::daKey::P
	#define DA_KEY_Q               ::DAdbg::Input::daKey::Q
	#define DA_KEY_R               ::DAdbg::Input::daKey::R
	#define DA_KEY_S               ::DAdbg::Input::daKey::S
	#define DA_KEY_T               ::DAdbg::Input::daKey::T
	#define DA_KEY_U               ::DAdbg::Input::daKey::U
	#define DA_KEY_V               ::DAdbg::Input::daKey::V
	#define DA_KEY_W               ::DAdbg::Input::daKey::W
	#define DA_KEY_X               ::DAdbg::Input::daKey::X
	#define DA_KEY_Y               ::DAdbg::Input::daKey::Y
	#define DA_KEY_Z               ::DAdbg::Input::daKey::Z
	#define DA_KEY_LEFT_BRACKET    ::DAdbg::Input::daKey::LeftBracket   /* [ */
	#define DA_KEY_BACKSLASH       ::DAdbg::Input::daKey::BackSlash     /* \ */
	#define DA_KEY_RIGHT_BRACKET   ::DAdbg::Input::daKey::RightBracket  /* ] */
	#define DA_KEY_GRAVE_ACCENT    ::DAdbg::Input::daKey::GraveAccent   /* ` */
	#define DA_KEY_WORLD_1         ::DAdbg::Input::daKey::World1        /* non-US #1 */
	#define DA_KEY_WORLD_2         ::DAdbg::Input::daKey::World2        /* non-US #2 */

			/* Function keys */
	#define DA_KEY_ESCAPE          ::DAdbg::Input::daKey::Escape
	#define DA_KEY_ENTER           ::DAdbg::Input::daKey::Enter
	#define DA_KEY_TAB             ::DAdbg::Input::daKey::Tab
	#define DA_KEY_BACKSPACE       ::DAdbg::Input::daKey::Backspace
	#define DA_KEY_INSERT          ::DAdbg::Input::daKey::Insert
	#define DA_KEY_DELETE          ::DAdbg::Input::daKey::Delete
	#define DA_KEY_RIGHT           ::DAdbg::Input::daKey::Right
	#define DA_KEY_LEFT            ::DAdbg::Input::daKey::Left
	#define DA_KEY_DOWN            ::DAdbg::Input::daKey::Down
	#define DA_KEY_UP              ::DAdbg::Input::daKey::Up
	#define DA_KEY_PAGE_UP         ::DAdbg::Input::daKey::PageUp
	#define DA_KEY_PAGE_DOWN       ::DAdbg::Input::daKey::PageDown
	#define DA_KEY_HOME            ::DAdbg::Input::daKey::Home
	#define DA_KEY_END             ::DAdbg::Input::daKey::End
	#define DA_KEY_CAPS_LOCK       ::DAdbg::Input::daKey::CapsLock
	#define DA_KEY_SCROLL_LOCK     ::DAdbg::Input::daKey::ScrollLock
	#define DA_KEY_NUM_LOCK        ::DAdbg::Input::daKey::NumLock
	#define DA_KEY_PRINT_SCREEN    ::DAdbg::Input::daKey::PrintScreen
	#define DA_KEY_PAUSE           ::DAdbg::Input::daKey::Pause
	#define DA_KEY_F1              ::DAdbg::Input::daKey::F1
	#define DA_KEY_F2              ::DAdbg::Input::daKey::F2
	#define DA_KEY_F3              ::DAdbg::Input::daKey::F3
	#define DA_KEY_F4              ::DAdbg::Input::daKey::F4
	#define DA_KEY_F5              ::DAdbg::Input::daKey::F5
	#define DA_KEY_F6              ::DAdbg::Input::daKey::F6
	#define DA_KEY_F7              ::DAdbg::Input::daKey::F7
	#define DA_KEY_F8              ::DAdbg::Input::daKey::F8
	#define DA_KEY_F9              ::DAdbg::Input::daKey::F9
	#define DA_KEY_F10             ::DAdbg::Input::daKey::F10
	#define DA_KEY_F11             ::DAdbg::Input::daKey::F11
	#define DA_KEY_F12             ::DAdbg::Input::daKey::F12
	#define DA_KEY_F13             ::DAdbg::Input::daKey::F13
	#define DA_KEY_F14             ::DAdbg::Input::daKey::F14
	#define DA_KEY_F15             ::DAdbg::Input::daKey::F15
	#define DA_KEY_F16             ::DAdbg::Input::daKey::F16
	#define DA_KEY_F17             ::DAdbg::Input::daKey::F17
	#define DA_KEY_F18             ::DAdbg::Input::daKey::F18
	#define DA_KEY_F19             ::DAdbg::Input::daKey::F19
	#define DA_KEY_F20             ::DAdbg::Input::daKey::F20
	#define DA_KEY_F21             ::DAdbg::Input::daKey::F21
	#define DA_KEY_F22             ::DAdbg::Input::daKey::F22
	#define DA_KEY_F23             ::DAdbg::Input::daKey::F23
	#define DA_KEY_F24             ::DAdbg::Input::daKey::F24
	#define DA_KEY_F25             ::DAdbg::Input::daKey::F25

	/* Keypad */
	#define DA_KEY_KP_0            ::DAdbg::Input::daKey::KP0
	#define DA_KEY_KP_1            ::DAdbg::Input::daKey::KP1
	#define DA_KEY_KP_2            ::DAdbg::Input::daKey::KP2
	#define DA_KEY_KP_3            ::DAdbg::Input::daKey::KP3
	#define DA_KEY_KP_4            ::DAdbg::Input::daKey::KP4
	#define DA_KEY_KP_5            ::DAdbg::Input::daKey::KP5
	#define DA_KEY_KP_6            ::DAdbg::Input::daKey::KP6
	#define DA_KEY_KP_7            ::DAdbg::Input::daKey::KP7
	#define DA_KEY_KP_8            ::DAdbg::Input::daKey::KP8
	#define DA_KEY_KP_9            ::DAdbg::Input::daKey::KP9
	#define DA_KEY_KP_DECIMAL      ::DAdbg::Input::daKey::KPDecimal
	#define DA_KEY_KP_DIVIDE       ::DAdbg::Input::daKey::KPDivide
	#define DA_KEY_KP_MULTIPLY     ::DAdbg::Input::daKey::KPMultiply
	#define DA_KEY_KP_SUBTRACT     ::DAdbg::Input::daKey::KPSubtract
	#define DA_KEY_KP_ADD          ::DAdbg::Input::daKey::KPAdd
	#define DA_KEY_KP_ENTER        ::DAdbg::Input::daKey::KPEnter
	#define DA_KEY_KP_EQUAL        ::DAdbg::Input::daKey::KPEqual

	#define DA_KEY_LEFT_SHIFT      ::DAdbg::Input::daKey::LeftShift
	#define DA_KEY_LEFT_CONTROL    ::DAdbg::Input::daKey::LeftControl
	#define DA_KEY_LEFT_ALT        ::DAdbg::Input::daKey::LeftAlt
	#define DA_KEY_LEFT_SUPER      ::DAdbg::Input::daKey::LeftSuper
	#define DA_KEY_RIGHT_SHIFT     ::DAdbg::Input::daKey::RightShift
	#define DA_KEY_RIGHT_CONTROL   ::DAdbg::Input::daKey::RightControl
	#define DA_KEY_RIGHT_ALT       ::DAdbg::Input::daKey::RightAlt
	#define DA_KEY_RIGHT_SUPER     ::DAdbg::Input::daKey::RightSuper
	#define DA_KEY_MENU            ::DAdbg::Input::daKey::Menu

		//	Defines MouseCodes
		typedef enum class MouseCode : uint16_t
		{
			Button0 = 0,
			Button1 = 1,
			Button2 = 2,
			Button3 = 3,
			Button4 = 4,
			Button5 = 5,
			Button6 = 6,
			Button7 = 7,

			ButtonLast = Button7,
			ButtonLeft = Button0,
			ButtonRight = Button1,
			ButtonMiddle = Button2
		} Mouse;

		inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
		{
			os << static_cast<int32_t>(mouseCode);
			return os;
		}

	#define DA_MOUSE_BUTTON_0		::DAdbg::Input::daMouse::Button0
	#define DA_MOUSE_BUTTON_1		::DAdbg::Input::daMouse::Button1
	#define DA_MOUSE_BUTTON_2		::DAdbg::Input::daMouse::Button2
	#define DA_MOUSE_BUTTON_3		::DAdbg::Input::daMouse::Button3
	#define DA_MOUSE_BUTTON_4		::DAdbg::Input::daMouse::Button4
	#define DA_MOUSE_BUTTON_5		::DAdbg::Input::daMouse::Button5
	#define DA_MOUSE_BUTTON_6		::DAdbg::Input::daMouse::Button6
	#define DA_MOUSE_BUTTON_7		::DAdbg::Input::daMouse::Button7
	#define DA_MOUSE_BUTTON_LAST	::DAdbg::Input::daMouse::ButtonLast
	#define DA_MOUSE_BUTTON_LEFT	::DAdbg::Input::daMouse::ButtonLeft
	#define DA_MOUSE_BUTTON_RIGHT	::DAdbg::Input::daMouse::ButtonRight
	#define DA_MOUSE_BUTTON_MIDDLE	::DAdbg::Input::daMouse::ButtonMiddle

		enum class EventType
		{
			None = 0,
			KeyPressed, KeyReleased, KeyTyped,
			MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
		};

		enum EventCategory
		{
			None = 0,
			EventCategoryInput = 0x00,
			EventCategoryKeyboard = 0x01,
			EventCategoryMouse = 0x02,
			EventCategoryMouseButton = 0x03
		};

	#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
																virtual EventType GetEventType() const override { return GetStaticType(); }\
																virtual const char* GetName() const override { return #type; }

	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

		// Events
		class Event
		{
		public:
			virtual ~Event() = default;

			bool Handled = false;

			virtual EventType GetEventType() const = 0;
			virtual const char* GetName() const = 0;
			virtual int GetCategoryFlags() const = 0;
			virtual std::string ToString() const { return GetName(); }

			inline bool IsInCategory(EventCategory category)
			{
				return GetCategoryFlags() & category;
			}
		};

		class EventDispatcher
		{
		public:
			inline EventDispatcher(Event& event)
				: m_Event(event)
			{}

			//	F is deduced by compiler
			template<typename T, typename F>
			inline bool Dispatch(const F& func)
			{
				if (m_Event.GetEventType() == T::GetStaticType())
				{
					m_Event.Handled |= func(static_cast<T&>(m_Event));
					return true;
				}
				return false;
			}
		private:
			Event& m_Event;
		};

		inline std::ostream& operator<<(std::ostream& os, const Event& e)
		{
			return os << e.ToString();
		}

		// Input
		class Input
		{
		public:
			static bool IsKeyPressed(KeyCode key);

			static bool IsMouseButtonPressed(MouseCode button);
			static std::pair<float, float> GetMousePosition();
			static float GetMouseX();
			static float GetMouseY();
		};

		// KeyEvents
		class KeyEvent : public Event
		{
		public:
			inline KeyCode GetKeyCode() const { return m_KeyCode; }

			EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		protected:
			inline KeyEvent(KeyCode keycode)
				: m_KeyCode(keycode) {}

			KeyCode m_KeyCode;
		};

		class KeyPressedEvent : public KeyEvent
		{
		public:
			inline KeyPressedEvent(KeyCode keycode, int repeatCount)
				: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

			inline int GetRepeatCount() const { return m_RepeatCount; }

			inline std::string ToString() const override
			{
				std::stringstream ss;
				ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
				return ss.str();
			}

			EVENT_CLASS_TYPE(KeyPressed)
		private:
			int m_RepeatCount;
		};

		class KeyReleasedEvent : public KeyEvent
		{
			inline KeyReleasedEvent(KeyCode keycode)
				: KeyEvent(keycode) {}

			inline std::string ToString() const override
			{
				std::stringstream ss;
				ss << "KeyReleasedEvent: " << m_KeyCode;
				return ss.str();
			}

			EVENT_CLASS_TYPE(KeyReleased)
		};

		class KeyTypedEvent : public KeyEvent
		{
		public:
			inline KeyTypedEvent(KeyCode keycode)
				: KeyEvent(keycode) {}

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "KeyTypedEvent: " << m_KeyCode;
				return ss.str();
			}

			EVENT_CLASS_TYPE(KeyTyped)
		};


		//	MouseEvent 

		class MouseMovedEvent : public Event
		{
			inline MouseMovedEvent(float x, float y)
				: m_MouseX(x), m_MouseY(y) {}

			inline float GetX() const { return m_MouseX; }
			inline float GetY() const { return m_MouseY; }

			inline std::string ToString() const override
			{
				std::stringstream ss;
				ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
				return ss.str();
			}

			EVENT_CLASS_TYPE(MouseMoved)
				EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
		private:
			float m_MouseX, m_MouseY;
		};

		class MouseScrolledEvent : public Event
		{
		public:
			inline MouseScrolledEvent(float xOffset, float yOffset)
				: m_XOffset(xOffset), m_YOffset(yOffset) {}

			inline float GetXOffset() const { return m_XOffset; }
			inline float GetYOffset() const { return m_YOffset; }

			inline std::string ToString() const override
			{
				std::stringstream ss;
				ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
				return ss.str();
			}

			EVENT_CLASS_TYPE(MouseScrolled)
				EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		private:
			float m_XOffset, m_YOffset;
		};

		class MouseButtonEvent : public Event
		{
		public:
			inline MouseCode GetMouseButton() const { return m_Button; }

			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		protected:
			MouseButtonEvent(MouseCode button)
				: m_Button(button) {}

			MouseCode m_Button;
		};

		class MouseButtonPressedEvent : public MouseButtonEvent
		{
		public:
			inline MouseButtonPressedEvent(MouseCode button)
				: MouseButtonEvent(button) {}

			inline std::string ToString() const override
			{
				std::stringstream ss;
				ss << "MouseButtonPressedEvent: " << m_Button;
				return ss.str();
			}

			EVENT_CLASS_TYPE(MouseButtonPressed)
		};

		class MouseButtonReleasedEvent : public MouseButtonEvent
		{
		public:
			inline MouseButtonReleasedEvent(MouseCode button)
				: MouseButtonEvent(button) {}

			inline std::string ToString() const override
			{
				std::stringstream ss;
				ss << "MouseButtonReleasedEvent: " << m_Button;
				return ss.str();
			}

			EVENT_CLASS_TYPE(MouseButtonReleased)
		};

	}	//	END namespace DAdbg::Input
#endif	//	DAInput

////////////////////////////////////////////////////////////////////////////////
//  -----------------------------  DAProfile  ------------------------------  //
////////////////////////////////////////////////////////////////////////////////
#ifdef DA_USE_PROFILE
	namespace DAdbg::Profile
	{
		using daFloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

		struct daProfileResult
		{
			std::string Name;

			daFloatingPointMicroseconds Start;
			std::chrono::microseconds ElapsedTime;
			std::thread::id ThreadID;
		};

		struct daInstrumentationSession
		{
			std::string Name;
		};

		class daInstrumentor
		{
		private:
			std::mutex m_Mutex;
			daInstrumentationSession* m_CurrentSession;
			std::ofstream m_OutputStream;
		public:
			inline daInstrumentor()
				: m_CurrentSession(nullptr)
			{
			}

			void BeginSession(const std::string& name, const std::string& filepath = "results.json");
			void EndSession();
			_Acquires_lock_(m_Mutex) void WriteProfile(const daProfileResult& result);
			inline static daInstrumentor& Get()
			{
				static daInstrumentor instance;
				return instance;
			}
		private:
			void WriteHeader();
			void WriteFooter();
			void InternalEndSession();
		};

		class daInstrumentationTimer
		{
		public:
			inline daInstrumentationTimer(const char* name)
				: m_Name(name), m_Stopped(false)
			{
				m_StartTimepoint = std::chrono::steady_clock::now();
			}

			inline ~daInstrumentationTimer()
			{
				if (!m_Stopped)
					Stop();
			}

			void Stop();
		private:
			const char* m_Name;
			std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
			bool m_Stopped;

		};

		namespace daInstrumentorUtils
		{
			template <size_t N>
			struct ChangeResult
			{
				char Data[N];
			};

			template <size_t N, size_t K>
			inline constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
			{
				ChangeResult<N> result = {};

				size_t srcIndex = 0;
				size_t dstIndex = 0;
				while (srcIndex < N)
				{
					size_t matchIndex = 0;
					while ((matchIndex < K - 1) && (srcIndex + matchIndex < N - 1) && (expr[srcIndex + matchIndex] == remove[matchIndex]))
						matchIndex++;
					if (matchIndex == K - 1)
						srcIndex += matchIndex;
					result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
					srcIndex++;
				}
				return result;
			}

		}	//	END namespace daInstrumentorUtils

	}	//	END namespace DAdbg::Profile
#endif	//	DA_PROFILE

////////////////////////////////////////////////////////////////////////////////
//  -------------------------------  DATime  -------------------------------  //
////////////////////////////////////////////////////////////////////////////////
#ifdef DA_USE_TIME
	namespace DAdbg::Time
	{
		class Timestep
		{
		public:
			inline Timestep(float time = 0.0f)
				: m_Time(time)
			{}

			inline operator float() const { return m_Time; }

			inline float GetSeconds() const { return m_Time; }
			inline float GetMilliseconds() const { return m_Time * 1000.0f; }
		private:
			float m_Time;
		};

		class Timer
		{
		public:
			inline Timer()
			{
				Reset();
			}

			inline void Timer::Reset()
			{
				m_Start = std::chrono::high_resolution_clock::now();
			}

			inline float Timer::Elapsed()
			{
				return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_Start).count() * 0.001f * 0.001f * 0.001f;
			}

			inline float Timer::ElapsedMillis()
			{
				return Elapsed() * 1000.0f;
			}
		private:
			std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
		};
	}	//	END namespace DAdbg::Time
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                           //
//                                          BEGIN IMPLEMENTATION                                             //
//                                                                                                           //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//  --------------------------------  DAdbg  -------------------------------  //
////////////////////////////////////////////////////////////////////////////////
namespace DAdbg::Internal
{
	#ifdef DAdbg_PLATFORM_WINDOWS
		static short int daFGColors[17];
		static short int daBGColors[17];
	#else
		static const char* BreakSeq = "\033[";
		static const char* daFGColors[17];
		static const char* daBGColors[17];
	#endif
	static void daInitColors()
	{
		#ifdef DAdbg_PLATFORM_WINDOWS
			//	These are organized in order of value for Windows
			daFGColors[daBlack]         = 0;																			// 0	0x00
			daFGColors[daBlue]          = FOREGROUND_BLUE;																// 1	0x01
			daFGColors[daGreen]         = FOREGROUND_GREEN;																// 2	0x02
			daFGColors[daCyan]          = FOREGROUND_BLUE | FOREGROUND_GREEN;											// 3	0x03
			daFGColors[daRed]           = FOREGROUND_RED;																// 4	0x04
			daFGColors[daMagenta]       = FOREGROUND_BLUE | FOREGROUND_RED;												// 5	0x05
			daFGColors[daYellow]        = FOREGROUND_RED | FOREGROUND_GREEN;											// 6	0x06
			daFGColors[daWhite]         = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;							// 7	0x07
			daFGColors[daBrightBlack]   = FOREGROUND_INTENSITY;															// 8	0x08
			daFGColors[daBrightBlue]    = FOREGROUND_INTENSITY | FOREGROUND_BLUE;										// 9	0x09
			daFGColors[daBrightGreen]   = FOREGROUND_INTENSITY | FOREGROUND_GREEN;										// 10	0x0A
			daFGColors[daBrightCyan]    = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN;					// 11	0x0B
			daFGColors[daBrightRed]     = FOREGROUND_INTENSITY | FOREGROUND_RED;										// 12	0x0C
			daFGColors[daBrightMagenta] = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED;						// 13	0x0D
			daFGColors[daBrightYellow]  = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE;						// 14	0x0E
			daFGColors[daBrightWhite]   = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;	// 15	0x0F
			daFGColors[daUndefined]     = 0;

			daBGColors[daBlack]         = 0;																			// 0	0x00
			daBGColors[daBlue]          = BACKGROUND_BLUE;																// 16	0x10
			daBGColors[daGreen]         = BACKGROUND_GREEN;																// 32	0x20
			daBGColors[daCyan]          = BACKGROUND_BLUE | BACKGROUND_GREEN;											// 48	0x30
			daBGColors[daRed]           = BACKGROUND_RED;																// 64	0x40
			daBGColors[daMagenta]       = BACKGROUND_BLUE | BACKGROUND_RED;												// 80	0x50
			daBGColors[daYellow]        = BACKGROUND_RED | BACKGROUND_GREEN;											// 96	0x60
			daBGColors[daWhite]         = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;							// 112	0x70
			daBGColors[daBrightBlack]   = BACKGROUND_INTENSITY;															// 128	0x80
			daBGColors[daBrightBlue]    = BACKGROUND_INTENSITY | BACKGROUND_BLUE;										// 144	0x90
			daBGColors[daBrightGreen]   = BACKGROUND_INTENSITY | BACKGROUND_GREEN;										// 160	0xA0
			daBGColors[daBrightCyan]    = BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN;					// 176	0xB0
			daBGColors[daBrightRed]     = BACKGROUND_INTENSITY | BACKGROUND_RED;										// 192	0xC0
			daBGColors[daBrightMagenta] = BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_RED;						// 208	0xD0
			daBGColors[daBrightYellow]  = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN;						// 224	0xE0
			daBGColors[daBrightWhite]   = BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;	// 240	0xF0
			daBGColors[daUndefined]     = 0;
		#else
			daFGColors[daBlack]         = "\033[30m";
			daFGColors[daRed]           = "\033[31m";
			daFGColors[daGreen]         = "\033[32m";
			daFGColors[daYellow]        = "\033[33m";
			daFGColors[daBlue]          = "\033[34m";
			daFGColors[daMagenta]       = "\033[35m";
			daFGColors[daCyan]          = "\033[36m";
			daFGColors[daWhite]         = "\033[37m";
			daFGColors[daBrightBlack]   = "\033[90m";
			daFGColors[daBrightRed]     = "\033[91m";
			daFGColors[daBrightGreen]   = "\033[92m";
			daFGColors[daBrightYellow]  = "\033[93m";
			daFGColors[daBrightBlue]    = "\033[94m";
			daFGColors[daBrightMagenta] = "\033[95m";
			daFGColors[daBrightCyan]    = "\033[96m";
			daFGColors[daBrightWhite]   = "\033[97m";
			daFGColors[daUndefined]     = "\033[30m";

			daBGColors[daBlack]         = "\033[40m";
			daBGColors[daRed]           = "\033[41m";
			daBGColors[daGreen]         = "\033[42m";
			daBGColors[daYellow]        = "\033[43m";
			daBGColors[daBlue]          = "\033[44m";
			daBGColors[daMagenta]       = "\033[45m";
			daBGColors[daCyan]          = "\033[46m";
			daBGColors[daWhite]         = "\033[47m";
			daBGColors[daBrightBlack]   = "\033[100m";
			daBGColors[daBrightRed]     = "\033[101m";
			daBGColors[daBrightGreen]   = "\033[102m";
			daBGColors[daBrightYellow]  = "\033[103m";
			daBGColors[daBrightBlue]    = "\033[104m";
			daBGColors[daBrightMagenta] = "\033[105m";
			daBGColors[daBrightCyan]    = "\033[106m";
			daBGColors[daBrightWhite]   = "\033[107m";
			daBGColors[daUndefined]     = "\033[40m";
		#endif
	}

	static daAttributes DAlibAttrib;
	static bool DAdbgActive = false;

	static inline void daInit()
	{
		if (!DAdbgActive)
		{
			daInitColors();

			DAlibAttrib.Foreground = daFGColors[daWhite];
			DAlibAttrib.Background = daBGColors[daBlack];
			DAdbgActive = true;
		}
		return;
	}
	inline void DAdbg::Internal::daReset()
	{
		#ifdef DAdbg_PLATFORM_WINDOWS
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, DAlibAttrib.Foreground);
		#else
			std::cout << "\033[0m";
		#endif
	}
	inline void DAdbg::Internal::daShowCursor(bool enable)
	{
		daInit();
		#ifdef DAdbg_PLATFORM_WINDOWS
			CONSOLE_CURSOR_INFO info;

			info.dwSize = 10;
			info.bVisible = (BOOL)enable;
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
		#else
			printf("%s?25%c", BreakSeq, enable ? 'h' : '1');
		#endif
	}

	inline void DAdbg::Internal::Set(FGColor fgColor, BGColor bgColor)
	{
	#ifdef DAdbg_PLATFORM_WINDOWS
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (fgColor == fgBlack)
			SetConsoleTextAttribute(hConsole, FGdef[daBlack]);
		else if (fgColor == fgRed)
			SetConsoleTextAttribute(hConsole, FGdef[daRed]);
		else if (fgColor == fgGreen)
			SetConsoleTextAttribute(hConsole, FGdef[daGreen]);
		else if (fgColor == fgYellow)
			SetConsoleTextAttribute(hConsole, FGdef[daYellow]);
		else if (fgColor == fgBlue)
			SetConsoleTextAttribute(hConsole, FGdef[daBlue]);
		else if (fgColor == fgMagenta)
			SetConsoleTextAttribute(hConsole, FGdef[daMagenta]);
		else if (fgColor == fgCyan)
			SetConsoleTextAttribute(hConsole, FGdef[daCyan]);
		else if (fgColor == fgWhite)
			SetConsoleTextAttribute(hConsole, FGdef[daWhite]);
		else if (fgColor == fgBrightBlack)
			SetConsoleTextAttribute(hConsole, FGdef[daBrightBlack]);
		else if (fgColor == fgBrightRed)
			SetConsoleTextAttribute(hConsole, FGdef[daBrightRed]);
		else if (fgColor == fgBrightGreen)
			SetConsoleTextAttribute(hConsole, FGdef[daBrightGreen]);
		else if (fgColor == fgBrightYellow)
			SetConsoleTextAttribute(hConsole, FGdef[daBrightYellow]);
		else if (fgColor == fgBrightBlue)
			SetConsoleTextAttribute(hConsole, FGdef[daBrightBlue]);
		else if (fgColor == fgBrightMagenta)
			SetConsoleTextAttribute(hConsole, FGdef[daBrightMagenta]);
		else if (fgColor == fgBrightCyan)
			SetConsoleTextAttribute(hConsole, FGdef[daBrightCyan]);
		else if (fgColor == fgBrightWhite)
			SetConsoleTextAttribute(hConsole, FGdef[daWhite]);
		else
			SetConsoleTextAttribute(hConsole, DAlibAttrib.Foreground);
		if (bgColor != bgUndefined)
		{
			if (bgColor == bgBlack)
				SetConsoleTextAttribute(hConsole, BGdef[daBlack]);
			else if (bgColor == bgRed)
				SetConsoleTextAttribute(hConsole, BGdef[daRed]);
			else if (bgColor == bgGreen)
				SetConsoleTextAttribute(hConsole, BGdef[daGreen]);
			else if (bgColor == bgYellow)
				SetConsoleTextAttribute(hConsole, BGdef[daYellow]);
			else if (bgColor == bgBlue)
				SetConsoleTextAttribute(hConsole, BGdef[daBlue]);
			else if (bgColor == bgMagenta)
				SetConsoleTextAttribute(hConsole, BGdef[daMagenta]);
			else if (bgColor == bgCyan)
				SetConsoleTextAttribute(hConsole, BGdef[daCyan]);
			else if (bgColor == bgWhite)
				SetConsoleTextAttribute(hConsole, BGdef[daWhite]);
			else if (bgColor == bgBrightBlack)
				SetConsoleTextAttribute(hConsole, BGdef[daBrightBlack]);
			else if (bgColor == bgBrightRed)
				SetConsoleTextAttribute(hConsole, BGdef[daBrightRed]);
			else if (bgColor == bgBrightGreen)
				SetConsoleTextAttribute(hConsole, BGdef[daBrightGreen]);
			else if (bgColor == bgBrightYellow)
				SetConsoleTextAttribute(hConsole, BGdef[daBrightYellow]);
			else if (bgColor == bgBrightBlue)
				SetConsoleTextAttribute(hConsole, BGdef[daBrightBlue]);
			else if (bgColor == bgBrightMagenta)
				SetConsoleTextAttribute(hConsole, BGdef[daBrightMagenta]);
			else if (bgColor == bgBrightCyan)
				SetConsoleTextAttribute(hConsole, BGdef[daBrightCyan]);
			else if (bgColor == bgBrightWhite)
				SetConsoleTextAttribute(hConsole, BGdef[daBrightWhite]);
		}
	#else
		if (fgColor == fgBlack)
			std::cout << FGdef[daBlack];
		else if (fgColor == fgRed)
			std::cout << FGdef[daRed];
		else if (fgColor == fgGreen)
			std::cout << FGdef[daGreen];
		else if (fgColor == fgYellow)
			std::cout << FGdef[daYellow];
		else if (fgColor == fgBlue)
			std::cout << FGdef[daBlue];
		else if (fgColor == fgMagenta)
			std::cout << FGdef[daMagenta];
		else if (fgColor == fgCyan)
			std::cout << FGdef[daCyan];
		else if (fgColor == fgWhite)
			std::cout << FGdef[daWhite];
		else if (fgColor == fgBrightBlack)
			std::cout << FGdef[daBrightBlack];
		else if (fgColor == fgBrightRed)
			std::cout << FGdef[daBrightRed];
		else if (fgColor == fgBrightGreen)
			std::cout << FGdef[daBrightGreen];
		else if (fgColor == fgBrightYellow)
			std::cout << FGdef[daBrightYellow];
		else if (fgColor == fgBrightBlue)
			std::cout << FGdef[daBrightBlue];
		else if (fgColor == fgBrightMagenta)
			std::cout << FGdef[daBrightMagenta];
		else if (fgColor == fgBrightCyan)
			std::cout << FGdef[daBrightCyan];
		else if (fgColor == fgWhite)
			std::cout << FGdef[daBrightWhite];
		else
			std::cout << FGdef[fgUndefined];
		if (bgColor != bgUndefined)
		{
			if (bgColor == bgBlack)
				std::cout << BGdef[daBlack];
			else if (bgColor == bgRed)
				std::cout << BGdef[daRed];
			else if (bgColor == bgGreen)
				std::cout << BGdef[daGreen];
			else if (bgColor == bgYellow)
				std::cout << BGdef[daYellow];
			else if (bgColor == bgBlue)
				std::cout << BGdef[daBlue];
			else if (bgColor == bgMagenta)
				std::cout << BGdef[daMagenta];
			else if (bgColor == bgCyan)
				std::cout << BGdef[daCyan];
			else if (bgColor == bgWhite)
				std::cout << BGdef[daWhite];
			else if (bgColor == bgBrightBlack)
				std::cout << BGdef[daBrightBlack];
			else if (bgColor == bgBrightRed)
				std::cout << BGdef[daBrightRed];
			else if (bgColor == bgBrightGreen)
				std::cout << BGdef[daBrightGreen];
			else if (bgColor == bgBrightYellow)
				std::cout << BGdef[daBrightYellow];
			else if (bgColor == bgBrightBlue)
				std::cout << BGdef[daBrightBlue];
			else if (bgColor == bgBrightMagenta)
				std::cout << BGdef[daBrightMagenta];
			else if (bgColor == bgBrightCyan)
				std::cout << BGdef[daBrightCyan];
			else if (bgColor == bgBrightWhite)
				std::cout << BGdef[daBrightWhite];
		}
	#endif
		return;
	}

	inline void DAdbg::Internal::Print(FGColor fgColor, BGColor bgColor, const char* message)
	{
		Set(fgColor, bgColor);
		std::cout << message;
		daReset();
	}

	inline void DAdbg::Internal::Printl(FGColor fgColor, BGColor bgColor, const char* message)
	{
		Print(fgColor, bgColor, message);
		std::cout << std::endl;
	}

	inline void DAdbg::Internal::PrintChar(FGColor fgColor, BGColor bgColor, const char* characters)
	{
		Print(fgColor, bgColor, characters);
	}

	inline void DAdbg::Internal::End()
	{
		// uh...
	}
}	//	END namespace DAdbg::Internal

////////////////////////////////////////////////////////////////////////////////
//  --------------------------------  DALog  -------------------------------  //
////////////////////////////////////////////////////////////////////////////////
#ifdef DA_USE_LOG
	inline void DAdbg::Log(Level severity, const char* message)
	{
		DAdbg::Internal::daInit();
		
		if (severity == Level::Critical)
		{
			DAdbg::Internal::Set(fgRed, bgUndefined);
			std::cout << "[CRITICAL]: " << message << std::endl;
		}
		else if (severity == Level::Error)
		{
			DAdbg::Internal::Set(fgYellow, bgUndefined);
			std::cout << "[ERROR]: " << message << std::endl;
		}
		else if (severity == Level::Warn)
		{
			DAdbg::Internal::Set(fgMagenta, bgUndefined);
			std::cout << "[WARN]: " << message << std::endl;
		}
		else if (severity == Level::Info)
		{
			DAdbg::Internal::Set(fgGreen, bgUndefined);
			std::cout << "[info]: " << message << std::endl;
		}
		else if (severity == Level::Trace)
		{
			DAdbg::Internal::Set(fgWhite, bgUndefined);
			std::cout << "[trace]: " << message << std::endl;
		}
		DAdbg::Internal::daReset();
		return;
	}

	//  Overloads
	inline void DAdbg::Log(Level severity)
	{
		Log(severity, "");
	}

	inline void DAdbg::Log(Level severity, std::string& message)
	{
		const char* msg = message.c_str();
		Log(severity, msg);
	}
#endif  //  DALog

////////////////////////////////////////////////////////////////////////////////
//  ------------------------------  DAClear  -------------------------------  //
////////////////////////////////////////////////////////////////////////////////
#ifdef DA_USE_CLEAR
	inline void DAdbg::ClearScreen()
	{
		#ifdef DAdbg_PLATFORM_WINDOWS
				std::system("cls");
			#else
				std::system("clear");
		#endif
	}
#endif  //  DAClear

////////////////////////////////////////////////////////////////////////////////
//  ------------------------------  DAPrint  -------------------------------  //
////////////////////////////////////////////////////////////////////////////////
#ifdef DA_USE_PRINT
	//	Print to screen

	inline int DAdbg::Print::daGetFGvalue(FGColor fgColor)
	{
		if (fgColor == fgBlack)
			return daBlack;
		else if (fgColor == fgRed)
			return daRed;
		else if (fgColor == fgGreen)
			return daGreen;
		else if (fgColor == fgYellow)
			return daYellow;
		else if (fgColor == fgBlue)
			return daBlue;
		else if (fgColor == fgMagenta)
			return daMagenta;
		else if (fgColor == fgCyan)
			return daCyan;
		else if (fgColor == fgWhite)
			return daWhite;
		else if (fgColor == fgBrightBlack)
			return daBrightBlack;
		else if (fgColor == fgBrightRed)
			return daBrightRed;
		else if (fgColor == fgBrightGreen)
			return daBrightGreen;
		else if (fgColor == fgBrightYellow)
			return daBrightYellow;
		else if (fgColor == fgBrightBlue)
			return daBrightBlue;
		else if (fgColor == fgBrightMagenta)
			return daBrightMagenta;
		else if (fgColor == fgBrightCyan)
			return daBrightCyan;
		else if (fgColor == fgBrightWhite)
			return daBrightWhite;
		else if (fgColor == fgUndefined)
			return daUndefined;
		else
			return -1;
	}
	inline int DAdbg::Print::daGetBGvalue(BGColor bgColor)
	{
		if (bgColor == bgBlack)
			return daBlack;
		else if (bgColor == bgRed)
			return daRed;
		else if (bgColor == bgGreen)
			return daGreen;
		else if (bgColor == bgYellow)
			return daYellow;
		else if (bgColor == bgBlue)
			return daBlue;
		else if (bgColor == bgMagenta)
			return daMagenta;
		else if (bgColor == bgCyan)
			return daCyan;
		else if (bgColor == bgWhite)
			return daWhite;
		else if (bgColor == bgBrightBlack)
			return daBrightBlack;
		else if (bgColor == bgBrightRed)
			return daBrightRed;
		else if (bgColor == bgBrightGreen)
			return daBrightGreen;
		else if (bgColor == bgBrightYellow)
			return daBrightYellow;
		else if (bgColor == bgBrightBlue)
			return daBrightBlue;
		else if (bgColor == bgBrightMagenta)
			return daBrightMagenta;
		else if (bgColor == bgBrightCyan)
			return daBrightCyan;
		else if (bgColor == bgBrightWhite)
			return daBrightWhite;
		else if (bgColor == bgUndefined)
			return daUndefined;
		else
			return -1;
	}

	inline void DAdbg::Print::SetDefaults(FGColor fgColor, BGColor bgColor)
	{
		DAdbg::Internal::DAlibAttrib.Foreground = FGdef[daGetFGvalue(fgColor)];
		DAdbg::Internal::DAlibAttrib.Background = BGdef[daGetBGvalue(bgColor)];
	}

	inline void DAdbg::Print::Print(const char* message)	//	Make this use the user-set colors
	{
		DAdbg::Internal::Set(fgWhite, bgUndefined);
		std::cout << message;
	}
	inline void DAdbg::Print::Print(FGColor fgColor, const char* message)
	{
		DAdbg::Internal::Set(fgColor, bgUndefined);
		std::cout << message;
	}
	inline void DAdbg::Print::Print(BGColor bgColor, const char* message)
	{
		DAdbg::Internal::Set(fgUndefined, bgColor);
		std::cout << message;
	}
	inline void DAdbg::Print::Print(FGColor fgColor, BGColor bgColor, const char* message)
	{
		DAdbg::Internal::Set(fgColor, bgColor);
		std::cout << message;
	}

	//	Print a single line to screen
	inline void DAdbg::Print::Printl(const char* message)
	{
		DAdbg::Print::Print(message);
		std::cout << std::endl;
		DAdbg::Internal::daReset();
	}
	inline void DAdbg::Print::Printl(FGColor fgColor, const char* message)
	{
		DAdbg::Print::Print(fgColor, message);
		std::cout << std::endl;
		DAdbg::Internal::daReset();
	}
	inline void DAdbg::Print::Printl(BGColor bgColor, const char* message)
	{
		DAdbg::Print::Print(bgColor, message);
		std::cout << std::endl;
		DAdbg::Internal::daReset();
	}
	inline void DAdbg::Print::Printl(FGColor fgColor, BGColor bgColor, const char* message)
	{
		DAdbg::Print::Print(fgColor, bgColor, message);
		std::cout << std::endl;
		DAdbg::Internal::daReset();
	}

	//	Print a single colored character to screen
	inline void DAdbg::Print::PrintChar(const char* character)
	{
		DAdbg::Print::Print(character);
		DAdbg::Internal::daReset();
	}
	inline void DAdbg::Print::PrintChar(FGColor fgColor, const char* character)
	{
		DAdbg::Print::Print(fgColor, character);
		DAdbg::Internal::daReset();
	}
	inline void DAdbg::Print::PrintChar(BGColor bgColor, const char* character)
	{
		DAdbg::Print::Print(bgColor, character);
		DAdbg::Internal::daReset();
	}
	inline void DAdbg::Print::PrintChar(FGColor fgColor, BGColor bgColor, const char* character)
	{
		DAdbg::Print::Print(fgColor, bgColor, character);
		DAdbg::Internal::daReset();
	}

	#ifdef DAdbg_PLATFORM_WINDOWS
		inline void DAdbg::Print::PrintRGB(COLORREF rgbValue)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (WORD)rgbValue);
		}
	#endif

#endif  //  DAPrint

////////////////////////////////////////////////////////////////////////////////
//  ------------------------------  DAInput  -------------------------------  //
////////////////////////////////////////////////////////////////////////////////
#ifdef DA_USE_INPUT

#endif	//	DAInput


////////////////////////////////////////////////////////////////////////////////
//  -----------------------------  DAProfile  ------------------------------  //
////////////////////////////////////////////////////////////////////////////////
#ifdef DA_USE_PROFILE

		inline void DAdbg::Profile::daInstrumentor::BeginSession(const std::string& name, const std::string& filepath)
		{
			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession)
			{
				// If there is already a current session, then close it before beginning new one.
				// Subsequent profiling output meant for the original session will end up in the
				// newly opened session instead.  That's better than having badly formatted
				// profiling output.
				InternalEndSession();
			}
			m_OutputStream.open(filepath);

			if (m_OutputStream.is_open())
			{
				m_CurrentSession = new daInstrumentationSession({ name });
				WriteHeader();
			}
			else
			{
				daLOG_ERROR(" [DAProfile] Instrumentator could not open results file!");
			}
		}
		inline void DAdbg::Profile::daInstrumentor::EndSession()
		{
			std::lock_guard lock(m_Mutex);
			InternalEndSession();
		}
		_Acquires_lock_(m_Mutex) inline void DAdbg::Profile::daInstrumentor::WriteProfile(const daProfileResult& result)
		{
			std::stringstream json;

			json << std::setprecision(3) << std::fixed;
			json << (",{");
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
			json << "\"name\":\"" << result.Name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.ThreadID << ",";
			json << "\"ts\":" << result.Start.count();
			json << "}";

			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession)
			{
				m_OutputStream << json.str();
				m_OutputStream.flush();
			}
		}

		//	Private functions
		inline void DAdbg::Profile::daInstrumentor::WriteHeader()
		{
			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
			m_OutputStream.flush();
		}
		inline void DAdbg::Profile::daInstrumentor::WriteFooter()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}
		inline void DAdbg::Profile::daInstrumentor::InternalEndSession()
		{
			if (m_CurrentSession)
			{
				WriteFooter();
				m_OutputStream.close();
				delete m_CurrentSession;
				m_CurrentSession = nullptr;
			}
		}

		inline void DAdbg::Profile::daInstrumentationTimer::Stop()
		{
			auto endTimepoint = std::chrono::steady_clock::now();
			auto highResStart = daFloatingPointMicroseconds{ m_StartTimepoint.time_since_epoch() };
			auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

			daInstrumentor::Get().WriteProfile({ m_Name, highResStart, elapsedTime, std::this_thread::get_id() });

			m_Stopped = true;
		}

#endif	//	DAProfile


#endif	//	DAdbg #include guards