#pragma once

#include <cstddef>
#include "Identity.hpp"
#include "If.hpp"
#include "List.hpp"
#include <type_traits>

namespace detail
{
  template <class TypeList, class T, std::size_t CurrIndex = 0>
  struct IndexOf;

  template <class Head, class... Tail, class T, std::size_t CurrIndex>
  struct IndexOf<List<Head, Tail...>, T, CurrIndex> :
    If_t<
      std::is_same<Head, T>,
      Identity<std::integral_constant<std::size_t, CurrIndex>>,
      IndexOf<List<Tail...>, T, CurrIndex + 1>
    >
  {};

  template <class T, std::size_t CurrIndex>
  struct IndexOf<List<>, T, CurrIndex> :
    Identity<std::integral_constant<std::size_t, CurrIndex>>
  {};
}

template <class TypeList, class T>
using IndexOf = detail::IndexOf<TypeList, T>;

template <class TypeList, class T>
using IndexOf_t = typename detail::IndexOf<TypeList, T>::type;