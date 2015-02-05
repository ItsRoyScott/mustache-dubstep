#pragma once

#include <cstddef>
#include "List.hpp"

template <class TypeList, std::size_t Index>
struct At;

template <class Head, class... Tail, std::size_t Index>
struct At<List<Head, Tail...>, Index> :
  At<List<Tail...>, Index - 1>
{};

template <class Head, class... Tail>
struct At<List<Head, Tail...>, 0>
{
  typedef Head type;
};

template <class TypeList, std::size_t Index>
using At_t = typename At<TypeList, Index>::type;