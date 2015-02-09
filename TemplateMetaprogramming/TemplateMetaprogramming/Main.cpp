#include "At.hpp"
#include "ComparisonOperators.hpp"
#include "IndexOf.hpp"
#include "Insert.hpp"
#include "InsertList.hpp"
#include "LogicalOperators.hpp"
#include "List.hpp"
#include <type_traits>
#include "Where.hpp"
#include "WhereIndex.hpp"

template <std::size_t Rhs>
struct IsGreaterThan
{
  template <std::size_t Lhs>
  using type = std::conditional_t<
    (Lhs > Rhs),
    std::true_type,
    std::false_type
  >;
};

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

  typedef Where_t<TestList, std::is_integral> IntegralTestList;
  typedef WhereIndex_t<TestList, IsGreaterThan<0>::type> LastTwoElementsOfTestList;

  static_assert(std::is_same<IntegralTestList,          List<char, int> >::value, "");
  static_assert(std::is_same<LastTwoElementsOfTestList, List<int, float>>::value, "");

  static_assert(EqualTo_t<Int<5>, Int<5>>::value, "");
  static_assert(NotEqualTo_t<Int<3>, Int<5>>::value, "");
  static_assert(GreaterThan_t<Int<7>, Int<5>>::value, "");
  static_assert(
    GreaterThanOrEqualTo_t<Int<7>, Int<5>>::value && 
    GreaterThanOrEqualTo_t<Int<5>, Int<5>>::value, "");
  static_assert(LessThan_t<Int<3>, Int<5>>::value, "");
  static_assert(
    LessThanOrEqualTo_t<Int<3>, Int<5>>::value &&
    LessThanOrEqualTo_t<Int<5>, Int<5>>::value, "");

  static_assert(Not_t<Bool<false>>::value == true, "");
  static_assert(Not_t<Bool<true>>::value == false, "");
  static_assert(And_t<Bool<true>, Bool<false>, Bool<true>>::value == false, "");
  static_assert(And_t<Bool<true>, Bool<true>, Bool<true>>::value == true, "");
  static_assert(Or_t<Bool<false>, Bool<false>, Bool<true>>::value == true, "");
  static_assert(Or_t<Bool<false>, Bool<false>, Bool<false>>::value == false, "");

  return 0;
}