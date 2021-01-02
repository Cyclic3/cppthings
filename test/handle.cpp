#include "gtest/gtest.h"

#include <cppthings/handle.hpp>

class foo {};

TEST(cppthings, Handle) {
  cppthings::handle<foo, false> fake_handle;

  foo base;
  cppthings::handle<foo, true> handle;
  handle = base;
  handle = &base;
  handle = std::make_shared<foo>(base);
  handle = cppthings::make_boxed<foo>(base);
}
