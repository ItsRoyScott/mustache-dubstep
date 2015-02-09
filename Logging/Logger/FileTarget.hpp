#pragma once

#include "Entry.hpp"
#include <fstream>
#include <memory>
#include <string>

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