#pragma once

#include "Entry.hpp"
#include <functional>

typedef std::function<void(EntryFormat const& format, EntryData const& data)> TargetFunction;

struct Target
{
  EntryFormat Format;
  TargetFunction Function;
};
