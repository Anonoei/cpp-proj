#include "DAdbg.h"

////////////////////////////////////////////////////////////////////////////////
//  --------------------------------  DALog  -------------------------------  //
////////////////////////////////////////////////////////////////////////////////
#ifdef DA_USE_LOG
    void DAdbg::Log(Level severity, const char* message)
    {
        if (severity == Level::Critical)
            std::cout << "\033[1;31m[CRITICAL]: " << message << "\033[0m" << std::endl;
        else if (severity == Level::Error)
            std::cout << "\033[1;35m[ERROR]: " << message << "\033[0m" << std::endl;
        else if (severity == Level::Warn)
            std::cout << "\033[1;33m[WARN]: " << message << "\033[0m" << std::endl;
        else if (severity == Level::Info)
            std::cout << "\033[0;32m[info]: " << message << "\033[0m" << std::endl;
        else if (severity == Level::Trace)
            std::cout << "\033[0;37m[trace]: " << message << "\033[0m" << std::endl;
        return;
    }

    //  Overloads
    void DAdbg::Log(Level severity)
    { 
        Log(severity, "");
    }

    void DAdbg::Log(Level severity, std::string& message)
    {
        const char* msg = message.c_str();
        Log(severity, msg);
    }
#endif  //  DALog

////////////////////////////////////////////////////////////////////////////////
//  ------------------------------  DAClear  -------------------------------  //
////////////////////////////////////////////////////////////////////////////////
#ifdef DA_USE_CLEAR
    void DAdbg::ClearScreen()
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
        //  PUBLIC FUNCTIONS  //
    //	These print one thing with a style
    void DAdbg::DAPrint::Print(const char* message)
    {
        if (!DAPrint::s_Code.empty())
        {
            std::cout << s_Code << message << std::endl;
        }
        else
        {
            std::cout << message << std::endl;
        }
    }

    void DAdbg::DAPrint::Print(Color color, const char* message)
    {
        Print(Style::Null, color, Color::Null, message);
    }

    void DAdbg::DAPrint::Print(Style style, Color color, const char* message)
    {
        Print(style, color, Color::Null, message);
    }

    void DAdbg::DAPrint::Print(Location location, Color color, const char* message)
    {
        if (location == Location::Foreground)
            Print(Style::Null, color, Color::Null, message);
        else
            Print(Style::Null, Color::Null, color, message);
    }

    void DAdbg::DAPrint::Print(Style style, Color ForegroundColor, Color BackgroundColor, const char* message)
    {
        const char* fgColor;
        const char* bgColor;
        const char* cStyle;
        if (ForegroundColor != Color::Null)
        {
            fgColor = GetColor(ForegroundColor);
            if (style != Style::Null)
            {
                cStyle = GetStyle(style);
                if (BackgroundColor != Color::Null)
                {
                    bgColor = (char*)((long long)(GetColor(BackgroundColor)) + 10);
                    std::cout << "\033[" << bgColor << "m";
                    std::cout << "\033[" << cStyle << ";" << fgColor << "m" << message << "\033[0m";
                }
                else    //  No background color
                {
                    std::cout << "\033[" << cStyle << ";" << fgColor << "m" << message << "\033[0m";
                }
            }
            else    //  No style
            {
                if (BackgroundColor != Color::Null)
                {
                    bgColor = (char*)((long long)(GetColor(BackgroundColor)) + 10);
                    std::cout << "\033[" << bgColor << "m";
                    std::cout << "\033[" << "0" << ";" << fgColor << "m" << message << "\033[0m";
                }
                else    //  No style or background color
                {
                    std::cout << "\033[" << "0" << ";" << fgColor << "m" << message << "\033[0m";
                }
            }
        }
        else    //  No foreground color
        {
            if (style != Style::Null)
            {
                cStyle = GetStyle(style);
                if (BackgroundColor != Color::Null)
                {
                    bgColor = (char*)((long long)(GetColor(BackgroundColor)) + 10);
                    std::cout << "\033[" << bgColor << "m";
                    std::cout << "\033[" << cStyle << "m" << message << "\033[0m";
                }
                else    //  No foreground or background color
                {
                    std::cout << "\033[" << cStyle << "m" << message << "\033[0m";
                }
            }
            else    //  No foreground color or style
            {
                if (BackgroundColor != Color::Null)
                {
                    bgColor = (char*)((long long)(GetColor(BackgroundColor)) + 10);
                    std::cout << "\033[" << bgColor << "m" << message << "\033[0m";
                }
                else    //  No foreground color, background color, or style
                {
                    std::cout << message << "\033[0m";
                }
            }
        }
    }

    //	These set the current style
    void DAdbg::DAPrint::SetStyle(Color ForegroundColor)
    {

    }

    void DAdbg::DAPrint::SetStyle(Color ForegroundColor, Color BackgroundColor)
    {

    }

    void DAdbg::DAPrint::SetStyle(Style style)
    {

    }

    void DAdbg::DAPrint::SetStyle(Style style, Color ForegroundColor)
    {

    }

    void DAdbg::DAPrint::SetStyle(Style style, Color ForegroundColor, Color BackgroundColor)
    {

    }

    //	These add to the current style
    void DAdbg::DAPrint::AddStyle(Color color)
    {

    }

    void DAdbg::DAPrint::AddStyle(Location location, Color color)
    {

    }

    void DAdbg::DAPrint::AddStyle(Style style, Color ForegroundColor)
    {

    }

    void DAdbg::DAPrint::AddStyle(Location location, Style style, Color color)
    {

    }

    void DAdbg::DAPrint::ClearStyle()
    {

    }

        //  PRIVATE FUNCTIONS  //
    void DAdbg::DAPrint::SetCurrentStyle(Style style, Color ForegroundColor, Color BackgroundColor)
    {

    }

    void DAdbg::DAPrint::AddToCurrentStyle(Location location, Color color)
    {

    }

    void DAdbg::DAPrint::AddToCurrentStyle(Style style)
    {

    }

    const char* DAdbg::DAPrint::GetColor(Color color)
    {
        if (color == Color::Black)
            return "30";
        else if (color == Color::Red)
            return "31";
        else if (color == Color::Green)
            return "32";
        else if (color == Color::Yellow)
            return "33";
        else if (color == Color::Blue)
            return "34";
        else if (color == Color::Magenta)
            return "35";
        else if (color == Color::Cyan)
            return "36";
        else if (color == Color::White)
            return "37";
        else if (color == Color::BrightBlack)
            return "90";
        else if (color == Color::BrightRed)
            return "91";
        else if (color == Color::BrightGreen)
            return "92";
        else if (color == Color::BrightYellow)
            return "93";
        else if (color == Color::BrightBlue)
            return "94";
        else if (color == Color::BrightMagenta)
            return "95";
        else if (color == Color::BrightCyan)
            return "96";
        else if (color == Color::BrightWhite)
            return "97";
        else
            return "";
    }

    const char* DAdbg::DAPrint::GetStyle(Style style)
    {
        if (style == Style::Reset)
            return "0";
        else if (style == Style::Bold)
            return "1";
        else if (style == Style::Dim)
            return "2";
        else if (style == Style::Italic)
            return "3";
        else if (style == Style::Underline)
            return "4";
        else if (style == Style::Invert)
            return "7";
        else if (style == Style::Strikethrough)
            return "9";
        return "";
    }

#endif  //  DAPrint
