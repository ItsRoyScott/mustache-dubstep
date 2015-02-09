#pragma once

template <class Function>
struct Evaluate
{
  typedef typename Function::type type;

  typedef decltype(type::value) valueType;
  static const valueType value = type::value;
};
