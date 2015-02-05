#pragma once

#include <cstddef>
#include "List.hpp"
#include "PushFront.hpp"

template <class TypeList, class OtherList, std::size_t Index>
struct InsertList;

template <class TypeList, class OtherList, std::size_t Index>
using InsertList_t = typename InsertList<TypeList, OtherList, Index>::type;

template <class Head, class... Tail, class OtherList, std::size_t Index>
struct InsertList<List<Head, Tail...>, OtherList, Index> :
  PushFront_t<
  typename InsertList<List<Tail...>, OtherList, Index - 1>::type,
  Head
  >
{};

template <class Head, class... Tail, class... OtherTypes>
struct InsertList<List<Head, Tail...>, List<OtherTypes...>, 0> :
  List<OtherTypes..., Head, Tail...>
{};

template <class... OtherTypes>
struct InsertList<List<>, List<OtherTypes...>, 0> :
  List<OtherTypes...>
{};