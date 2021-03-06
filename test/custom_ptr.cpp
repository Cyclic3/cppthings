#include "gtest/gtest.h"

#include <cppthings/custom_ptr.hpp>

void contrived_deleter(int* i) { *i = 33; }

TEST (cppthings, CustomPtrContrived) {
  int result = 0;
  {
    auto ptr = cppthings::custom_ptr<int, contrived_deleter>{&result};
  }
  EXPECT_EQ(result, 33);
}
