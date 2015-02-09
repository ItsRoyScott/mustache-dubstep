#include "ColoredConsoleTarget.hpp"
#include "DebugOutputWindowTarget.hpp"
#include "Entry.hpp"
#include "FileTarget.hpp"
#include "Logger.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <VersionHelpers.h>

int main()
{
  Logger logger;

  logger.AddTarget(DebugOutputWindowTarget());
  logger.AddTarget(FileTarget("Log.txt"));

  EntryFormat format;
  format.IncludeSeverity = false;
  format.TimeFormat.clear();
  format.SeverityFlags = Severity::Info | Severity::Warn | Severity::Error;
  logger.AddTarget(ColoredConsoleTarget(), format);

  // Get the computer name.
  char buffer[256];
  DWORD bufferSize = sizeof(buffer);
  GetComputerNameA(buffer, &bufferSize);
  auto computerName = std::string(buffer);

  // Get the width and height of this desktop.
  auto width = GetSystemMetrics(SM_CXSCREEN);
  auto height = GetSystemMetrics(SM_CYSCREEN);

  auto windows8OrGreater = IsWindows8OrGreater();

  // Get the last Win32 API error code and format it into a string.
  auto lastErrorCode = GetLastError();
  FormatMessageA(
    FORMAT_MESSAGE_FROM_SYSTEM,
    nullptr,
    lastErrorCode,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
    buffer,
    sizeof(buffer),
    nullptr);
  auto lastError = std::string(buffer);

  logger.LogDebug("Starting up on ", computerName);
  logger.LogInfo("This desktop's resolution is ", width, " x ", height);
  if (windows8OrGreater)
  {
    logger.LogWarn("You're using a newish version of Windows.");
  }

  logger.LogError("Error occurred! - Code: ", lastErrorCode, " - Message: ", lastError);

  return 0;
}