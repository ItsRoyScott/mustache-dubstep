#include "At.hpp"
#include "IndexOf.hpp"
#include "Insert.hpp"
#include "InsertList.hpp"
#include "List.hpp"
#include <type_traits>

int main()
{
  typedef List<char, int, float> TestList;

  static_assert(std::is_same<char, At_t<TestList, 0>>::value, "");
  static_assert(std::is_same<int, At_t<TestList, 1>>::value, "");
  static_assert(std::is_same<float, At_t<TestList, 2>>::value, "");

  static_assert(0 == IndexOf_t<TestList, char >::value, "");
  static_assert(1 == IndexOf_t<TestList, int  >::value, "");
  static_assert(2 == IndexOf_t<TestList, float>::value, "");

  static_assert(3 == IndexOf_t<TestList, short>::value, "");

  typedef Insert_t<TestList, double, 1> TestListWithDouble;
  typedef Insert_t<TestList, char*, 3> TestListWithCharPtr;

  static_assert(std::is_same<TestListWithDouble,  List<char, double, int, float> >::value, "");
  static_assert(std::is_same<TestListWithCharPtr, List<char, int, float, char*>  >::value, "");

  typedef InsertList_t<TestList, List<char[10], char[20]>, 0> TestListWithArrays;

  static_assert(std::is_same<TestListWithArrays, List<char[10], char[20], char, int, float>>::value, "");

  return 0;
}