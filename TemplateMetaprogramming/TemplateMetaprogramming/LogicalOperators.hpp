#pragma once

#include "Evaluate.hpp"
#include "If.hpp"
#include "List.hpp"
#include "ValueTypes.hpp"

template <class T>
using Not = Bool<!Evaluate<T>::value>;
template <class T>
using Not_t = Not<T>;

namespace detail
{
  template <class TypeList>
  struct And;

  template <class Head, class... Tail>
  struct And<List<Head, Tail...>> :
    If_t<
      Head,
      And<List<Tail...>>,
      std::false_type
    >
  {};

  template <>
  struct And<List<>> :
    std::true_type
  {};
}

template <class... Args>
using And = detail::And<List<Args...>>;
template <class... Args>
using And_t = typename And<Args...>::type;

namespace detail
{
  template <class TypeList>
  struct Or;

  template <class Head, class... Tail>
  struct Or<List<Head, Tail...>> :
    If_t<
      Head,
      std::true_type,
      Or<List<Tail...>>
    >
  {};

  template <>
  struct Or<List<>> :
    std::false_type
  {};
}

template <class... Args>
using Or = detail::Or<List<Args...>>;
template <class... Args>
using Or_t = typename Or<Args...>::type;