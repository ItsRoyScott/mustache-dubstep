#pragma once

template <template <class, class> class Operator, class Rhs>
struct Bind
{
  template <class Lhs>
  using type = Operator<Lhs, Rhs>;
};

template <template <class, class> class Operator, class Rhs>
using Bind_t = typename Bind<Operator, Rhs>::type;

template <template <class, class> class Operator, class Lhs>
struct BindLhs
{
  template <class Rhs>
  using type = Operator<Lhs, Rhs>;
};