#include "gtest/gtest.h"

#include <cppthings/defer.hpp>

TEST (cppthings, Defer) {
  int i = 0;
  {
    cppthings::defer([&]() { i = 33; });
  }
  EXPECT_EQ(i, 33);
}
