#include "gtest/gtest.h"

#include <cppthings/class_impl.hpp>

struct int_wrapper {
  int value;

  CPPTHINGS_IMPL_SHALLOW_EQ_NOEXCEPT(int_wrapper, &int_wrapper::value);
};

TEST (cppthings, ClassImplEq) {
  int_wrapper a{2}, b{2}, c{3};
  EXPECT_EQ(a, b);
  EXPECT_NE(a, c);
}
