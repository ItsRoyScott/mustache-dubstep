#pragma once

#include "Entry.hpp"
#include "Severity.hpp"
#include <sstream>
#include "Target.hpp"
#include <vector>

class Logger
{
public: // data

  EntryFormat DefaultFormat;
  std::vector<Target> Targets;

public:

  void AddTarget(
    std::function<void(EntryFormat const& format, EntryData const& data)> fn)
  {
    Targets.push_back(Target{ DefaultFormat, fn });
  }

  void AddTarget(
    std::function<void(EntryFormat const& format, EntryData const& data)> fn, 
    EntryFormat format)
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