#pragma once

#include <cstddef>
#include "List.hpp"
#include <type_traits>

template <bool b>
using Bool = std::integral_constant<bool, b>;
template <bool... b>
using BoolList = List<Bool<b>...>;

template <int i>
using Int = std::integral_constant<int, i>;
template <int... i>
using IntList = List<Int<i>...>;

template <std::size_t s>
using Size_t = std::integral_constant<std::size_t, s>;
template <std::size_t... s>
using Size_tList = List<Size_t<s>...>;