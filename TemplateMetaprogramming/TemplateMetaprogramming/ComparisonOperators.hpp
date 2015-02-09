#pragma once

#include "Evaluate.hpp"
#include "ValueTypes.hpp"

template <class T1, class T2>
using EqualTo = Bool< (Evaluate<T1>::value == Evaluate<T2>::value) >;
template <class T1, class T2>
using EqualTo_t = EqualTo<T1, T2>;

template <class T1, class T2>
using NotEqualTo = Bool< (Evaluate<T1>::value != Evaluate<T2>::value) >;
template <class T1, class T2>
using NotEqualTo_t = NotEqualTo<T1, T2>;

template <class T1, class T2>
using GreaterThan = Bool< (Evaluate<T1>::value > Evaluate<T2>::value) >;
template <class T1, class T2>
using GreaterThan_t = GreaterThan<T1, T2>;

template <class T1, class T2>
using GreaterThanOrEqualTo = Bool< (Evaluate<T1>::value >= Evaluate<T2>::value) >;
template <class T1, class T2>
using GreaterThanOrEqualTo_t = GreaterThanOrEqualTo<T1, T2>;

template <class T1, class T2>
using LessThan = Bool< (Evaluate<T1>::value < Evaluate<T2>::value) >;
template <class T1, class T2>
using LessThan_t = LessThan<T1, T2>;

template <class T1, class T2>
using LessThanOrEqualTo = Bool< (Evaluate<T1>::value <= Evaluate<T2>::value) >;
template <class T1, class T2>
using LessThanOrEqualTo_t = LessThanOrEqualTo<T1, T2>;