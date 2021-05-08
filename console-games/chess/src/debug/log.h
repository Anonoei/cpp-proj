#pragma once

//  This class is temporary, until this is game is created in DAGGer

#include <iostream>

enum class Level
{
  Trace = 0,
  Info = 1,
  Warn = 2,
  Error = 3,
  Critical = 4
};

namespace Logger
{
    void Log(Level severity, const char* message);

};  //  END class Logger
