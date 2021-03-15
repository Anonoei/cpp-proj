#include "debug/log.h"

void Logger::Log(Level severity, const char* message)
{
    if (severity == Level::Critical)
    {
        std::cout << "\033[1;31m[CRITICAL]: " << message << "\033[0m" << std::endl;
    }
    else if (severity == Level::Error)
    {
        std::cout << "\033[1;35m[ERROR]: " << message << "\033[0m" << std::endl;
    }
    else if (severity == Level::Warn)
    {
        std::cout << "\033[1;33m[WARN]: " << message << "\033[0m" << std::endl;
    }
    else if (severity == Level::Info)
    {
        std::cout << "\033[0;32m[info]: " << message << "\033[0m" << std::endl;
    }
    else if (severity == Level::Trace)
    {
        std::cout << "\033[0;37m[trace]: " << message << "\033[0m" << std::endl;
    }
}