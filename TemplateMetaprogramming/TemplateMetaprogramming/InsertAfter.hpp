#include <cstddef>
#include "List.hpp"
#include "PushFront.hpp"

template <class TypeList, class T, std::size_t Index>
struct InsertAfter;

template <class Head, class... Tail, class T, std::size_t Index>
struct InsertAfter<List<Head, Tail...>, T, Index> :
  PushFront_t<
    typename InsertAfter<List<Tail...>, T, Index - 1>::type,
    Head
  >
{};

template <class Head, class... Tail, class T>
struct InsertAfter<List<Head, Tail...>, T, 0> :
  List<Head, T, Tail...>
{};

template <class T>
struct InsertAfter<List<>, T, 0> :
  List<T>
{};

template <class TypeList, class T, std::size_t Index>
using InsertAfter_t = typename InsertAfter<TypeList, T, Index>::type;