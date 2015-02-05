#pragma once

#include "List.hpp"

template <class TypeList, class T>
struct PushBack;

template <class... Types, class T>
struct PushBack<List<Types...>, T> :
  List<Types..., T>
{};

template <class TypeList, class T>
using PushBack_t = typename PushBack<TypeList, T>::type;