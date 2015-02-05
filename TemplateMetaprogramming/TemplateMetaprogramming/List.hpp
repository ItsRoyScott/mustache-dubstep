#pragma once

template <class... Types>
struct List
{
  typedef List<Types...> type;
};