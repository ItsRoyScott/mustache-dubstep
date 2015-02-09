#pragma once

#include <string>

enum class Severity : unsigned int
{
  Debug = 1 << 0,
  Info = 1 << 1,
  Warn = 1 << 2,
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
