#pragma once

#include "If.hpp"

template <class TypeList, template <class> class Predicate>
struct Where;

template <class TypeList, template <class> class Predicate>
using Where_t = typename Where<TypeList, Predicate>::type;

template <class Head, class... Tail, template <class> class Predicate>
struct Where<List<Head, Tail...>, Predicate>
{
  typedef Where_t<List<Tail...>, Predicate> rest;
  typedef typename If_t<Predicate<Head>, PushFront<rest, Head>, rest>::type type;
};

template <template <class> class Predicate>
struct Where<List<>, Predicate> :
  List<>
{};