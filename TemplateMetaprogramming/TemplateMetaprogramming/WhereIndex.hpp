#pragma once

#include <cstddef>

namespace detail
{
  template <class TypeList, template <std::size_t> class Predicate, std::size_t CurrIndex = 0>
  struct WhereIndex;

  template <class Head, class... Tail, template <std::size_t> class Predicate, std::size_t CurrIndex>
  struct WhereIndex<List<Head, Tail...>, Predicate, CurrIndex>
  {
    typedef typename WhereIndex<List<Tail...>, Predicate, CurrIndex + 1>::type rest;
    typedef typename If_t<Predicate<CurrIndex>, PushFront<rest, Head>, rest>::type type;
  };

  template <template <std::size_t> class Predicate, std::size_t CurrIndex>
  struct WhereIndex<List<>, Predicate, CurrIndex> :
    List<>
  {};
}

template <class TypeList, template <std::size_t> class Predicate>
using WhereIndex = detail::WhereIndex<TypeList, Predicate>;

template <class TypeList, template <std::size_t> class Predicate>
using WhereIndex_t = typename detail::WhereIndex<TypeList, Predicate>::type;