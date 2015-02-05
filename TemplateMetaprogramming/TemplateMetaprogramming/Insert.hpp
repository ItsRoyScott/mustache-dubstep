#pragma once

#include <cstddef>
#include "List.hpp"
#include "PushFront.hpp"

template <class TypeList, class T, std::size_t Index>
struct Insert;

template <class TypeList, class T, std::size_t Index>
using Insert_t = typename Insert<TypeList, T, Index>::type;

template <class Head, class... Tail, class T, std::size_t Index>
struct Insert<List<Head, Tail...>, T, Index> :
  PushFront_t<
    typename Insert<List<Tail...>, T, Index - 1>::type,
    Head
  >
{};

template <class Head, class... Tail, class T>
struct Insert<List<Head, Tail...>, T, 0> :
  List<T, Head, Tail...>
{};

template <class T>
struct Insert<List<>, T, 0> :
  List<T>
{};
