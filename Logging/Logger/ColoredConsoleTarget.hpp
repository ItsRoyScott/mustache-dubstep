#pragma once

#include <cstdio>
#include "Entry.hpp"
#include "Severity.hpp"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class ColoredConsoleTarget
{
private:

  HANDLE consoleHandle;

public:

  ColoredConsoleTarget()
  {
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  }

  void operator()(EntryFormat const& format, EntryData const& data)
  {
    WORD color = 0;

    switch (data.Severity)
    {
    case Severity::Debug:
      color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
      break;

    case Severity::Info:
      color = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
      break;

    case Severity::Warn:
      color = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
      break;

    case Severity::Error:
      color = FOREGROUND_INTENSITY | FOREGROUND_RED;

    default:
      break;
    }

    SetConsoleTextAttribute(consoleHandle, color);
    std::fputs(format.FormatEntry(data).c_str(), stdout);
  }
};