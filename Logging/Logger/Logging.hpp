#pragma once

#include <cstdio>
#include <ctime>
#include <fstream>
#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <Windows.h>

enum class Severity : unsigned int
{
  Debug = 1 << 0,
  Info  = 1 << 1,
  Warn  = 1 << 2,
  Error = 1 << 3
};

inline Severity operator|(Severity a, Severity b)
{
  return static_cast<Severity>(static_cast<unsigned>(a) | static_cast<unsigned>(b));
}

inline bool IsFlagged(Severity severity, Severity flags)
{
  return (static_cast<unsigned>(flags) & static_cast<unsigned>(severity)) != 0;
}

inline std::string ToString(Severity severity)
{
  switch (severity)
  {
  case Severity::Debug: return "Debug";
  case Severity::Info:  return "Info";
  case Severity::Warn:  return "Warn";
  case Severity::Error: return "Error";
  default: return{};
  }
}

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

typedef std::function<void(EntryFormat const& format, EntryData const& data)> TargetFunction;

struct Target
{
  EntryFormat Format;
  TargetFunction Function;
};

class Logger
{
public: // data

  EntryFormat DefaultFormat;
  std::vector<Target> Targets;

public:

  void AddTarget(TargetFunction fn)
  {
    Targets.push_back(Target{ DefaultFormat, fn });
  }

  void AddTarget(TargetFunction fn, EntryFormat format)
  {
    Targets.push_back(Target{ format, fn });
  }

  void Log(std::string str, Severity severity)
  {
    EntryData data;
    data.Severity = severity;
    data.String = str;
    data.Time = std::time(nullptr);

    for (auto& target : Targets)
    {
      if (IsFlagged(data.Severity, target.Format.SeverityFlags))
      {
        target.Function(target.Format, data);
      }
    }
  }

  template <class... Args>
  void LogDebug(Args&&... args)
  {
    Log(FormatString(std::forward<Args>(args)...), Severity::Debug);
  }

  template <class... Args>
  void LogInfo(Args&&... args)
  {
    Log(FormatString(std::forward<Args>(args)...), Severity::Info);
  }

  template <class... Args>
  void LogWarn(Args&&... args)
  {
    Log(FormatString(std::forward<Args>(args)...), Severity::Warn);
  }

  template <class... Args>
  void LogError(Args&&... args)
  {
    Log(FormatString(std::forward<Args>(args)...), Severity::Error);
  }

private:

  template <class Arg>
  static void FillStringStream(std::stringstream& ss, Arg&& arg)
  {
    ss << std::forward<Arg>(arg);
  }

  template <class Arg0, class... Args>
  static void FillStringStream(std::stringstream& ss, Arg0&& arg0, Args&&... args)
  {
    ss << std::forward<Arg0>(arg0);
    FillStringStream(ss, std::forward<Args>(args)...);
  }

  template <class... Args>
  static std::string FormatString(Args&&... args)
  {
    std::stringstream ss;
    FillStringStream(ss, std::forward<Args>(args)...);
    return ss.str();
  }
};

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

class FileTarget
{
private:

  std::shared_ptr<std::ofstream> file = std::make_shared<std::ofstream>();

public:

  FileTarget(std::string fileName)
  {
    file->open(fileName.c_str());
  }

  void operator()(EntryFormat const& format, EntryData const& data)
  {
    *file << format.FormatEntry(data) << std::flush;
  }
};