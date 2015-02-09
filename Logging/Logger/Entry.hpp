#pragma once

#include <ctime>
#include "Severity.hpp"
#include <string>

struct EntryData
{
  Severity    Severity;
  std::string String;
  std::time_t Time;
};

struct EntryFormat
{
  bool          IncludeSeverity = true;
  std::string   NewLine = "\n";
  Severity      SeverityFlags = static_cast<Severity>(-1);
  std::string   TimeFormat = "%X";

  std::string FormatEntry(EntryData const& data) const
  {
    auto str = std::string();

    if (!TimeFormat.empty())
    {
      char buffer[128];
      std::strftime(buffer, sizeof(buffer), TimeFormat.c_str(), std::localtime(&data.Time));
      str += buffer;
      str += " ";
    }

    if (IncludeSeverity)
    {
      str += "[" + ToString(data.Severity) + "] ";
    }

    str += data.String;

    if (!NewLine.empty())
    {
      str += NewLine;
    }

    return std::move(str);
  }
};