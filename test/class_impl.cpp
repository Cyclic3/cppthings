#include "gtest/gtest.h"

#include <cppthings/class_impl.hpp>

struct int_wrapper {
  int value;

  CPPTHINGS_IMPL_SHALLOW_EQ_NOEXCEPT(int_wrapper, value);
};

struct int_data {
  int value;

  inline CPPTHINGS_EZ_CONSTRUCTOR(int_data, value);
};

#define __CPPTHINGS_MEMBER_PTR_1(TYPE, X) &TYPE::X

#define CPPTHINGS_TEST_MACRO(X) int X;
#define CPPTHINGS_TEST(...) \
  CPPTHINGS_FOR_EACH(CPPTHINGS_TEST_MACRO, __VA_ARGS__)

#define FOO(TYPE, ...) \
  void test(CPPTHINGS_FOR_EACH_1(__CPPTHINGS_MEMBER_PTR_1, TYPE, __VA__ARGS__))

TEST (cppthings, ClassImplEq) {
  int_wrapper a{2}, b{2}, c{3};
  EXPECT_EQ(a, b);
  EXPECT_NE(a, c);

  int_data d{1};
  EXPECT_EQ(d.value, 1);
}
