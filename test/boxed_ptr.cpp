#include "gtest/gtest.h"

#include <cppthings/boxed_ptr.hpp>

TEST (cppthings, BoxedPtrCopyMod) {
  cppthings::boxed_ptr<int> i = cppthings::make_boxed<int>(33);
  auto i_cpy = i;
  EXPECT_EQ(*i_cpy, *i);
  *i = 10;
  EXPECT_NE(*i_cpy, *i);
}


TEST (cppthings, BoxedPtrCopyCast) {
  cppthings::boxed_ptr<uint16_t> i = cppthings::make_boxed<int>(33);
  cppthings::boxed_ptr<uint8_t> i_cpy = i;
  EXPECT_EQ(*i_cpy, *i);
}

TEST (cppthings, BoxedPtrMove) {
  cppthings::boxed_ptr<uint16_t> i = cppthings::make_boxed<int>(33);
  auto ptr = i.get();
  cppthings::boxed_ptr<uint16_t> i_cpy = std::move(i);
  EXPECT_EQ(i.get(), nullptr);
  EXPECT_EQ(i_cpy.get(), ptr);
}

TEST (cppthings, BoxedPtrMoveCast) {
  cppthings::boxed_ptr<uint16_t> i = cppthings::make_boxed<int>(33);
  cppthings::boxed_ptr<uint8_t> i_cpy = std::move(i);
  EXPECT_EQ(*i_cpy, 33);
}

TEST (cppthings, BoxedPtrRelease) {
  uint16_t* ptr;
  {
    cppthings::boxed_ptr<uint16_t> i = cppthings::make_boxed<int>(33);
    ptr = i.release();
  }
  EXPECT_EQ(*ptr, 33);
  // Check that we can free
  delete ptr;
}
