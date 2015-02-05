#pragma once#pragma once

#include "List.hpp"

template <class TypeList, class T>
struct PushFront;

template <class... Types, class T>
struct PushFront<List<Types...>, T> :
  List<T, Types...>
{};

template <class TypeList, class T>
using PushFront_t = typename PushFront<TypeList, T>::type;