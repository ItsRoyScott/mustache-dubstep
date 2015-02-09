#pragma once

#include "Entry.hpp"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

struct DebugOutputWindowTarget
{
  void operator()(EntryFormat const& format, EntryData const& data)
  {
    OutputDebugStringA(format.FormatEntry(data).c_str());
  }
};