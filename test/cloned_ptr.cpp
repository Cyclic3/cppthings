#include "gtest/gtest.h"

#include <cppthings/cloned_ptr.hpp>

TEST (cppthings, ClonedPtrCopyMod) {
  cppthings::cloned_ptr<int> i = cppthings::make_cloned<int>(33);
  auto i_cpy = i;
  EXPECT_EQ(*i_cpy, *i);
  *i = 10;
  EXPECT_NE(*i_cpy, *i);
}


TEST (cppthings, ClonedPtrCopyCast) {
  cppthings::cloned_ptr<uint16_t> i = cppthings::make_cloned<int>(33);
  cppthings::cloned_ptr<uint8_t> i_cpy = i;
  EXPECT_EQ(*i_cpy, *i);
}

TEST (cppthings, ClonedPtrMove) {
  cppthings::cloned_ptr<uint16_t> i = cppthings::make_cloned<int>(33);
  auto ptr = i.get();
  cppthings::cloned_ptr<uint16_t> i_cpy = std::move(i);
  EXPECT_EQ(i.get(), nullptr);
  EXPECT_EQ(i_cpy.get(), ptr);
}

TEST (cppthings, ClonedPtrMoveCast) {
  cppthings::cloned_ptr<uint16_t> i = cppthings::make_cloned<int>(33);
  cppthings::cloned_ptr<uint8_t> i_cpy = std::move(i);
  EXPECT_EQ(*i_cpy, 33);
}

TEST (cppthings, ClonedPtrRelease) {
  uint16_t* ptr;
  {
    cppthings::cloned_ptr<uint16_t> i = cppthings::make_cloned<int>(33);
    ptr = i.release();
  }
  EXPECT_EQ(*ptr, 33);
  // Check that we can free
  delete ptr;
}
