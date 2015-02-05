#pragma once

#include <type_traits>

template <class Predicate, class IfTrue, class IfFalse>
struct If
{
  typedef typename Predicate::type predicateResult;
  typedef std::conditional_t<predicateResult::value, IfTrue, IfFalse> type;
};

template <class Predicate, class IfTrue, class IfFalse>
using If_t = typename If<Predicate, IfTrue, IfFalse>::type;