#include "gtest/gtest.h"

#include <cppthings/registry.hpp>

CPPTHINGS_EXPOSE_REGISTRY(reg, int, int);
CPPTHINGS_IMPL_REGISTRY(reg);

CPPTHINGS_EXPOSE_REGISTRY(reg_concurrent, int, int);
CPPTHINGS_IMPL_REGISTRY_CONCURRENT(reg_concurrent);

CPPTHINGS_REGISTER(reg, 1, 2)
CPPTHINGS_REGISTER(reg, 2, 3)
CPPTHINGS_REGISTER(reg, 3, 4)

CPPTHINGS_REGISTER(reg_concurrent, 1, 2)
CPPTHINGS_REGISTER(reg_concurrent, 2, 3)
CPPTHINGS_REGISTER(reg_concurrent, 3, 4)

TEST (cppthings, Registry) {
  auto res = CPPTHINGS_LOOKUP(reg, 1);
  EXPECT_EQ(res, 2);
  auto res_2 = CPPTHINGS_LOOKUP(reg, 4);
  EXPECT_EQ(res_2, std::nullopt);
}

TEST (cppthings, RegistryConcurrent) {
  auto res = CPPTHINGS_LOOKUP(reg_concurrent, 1);
  EXPECT_EQ(res, 2);
  auto res_2 = CPPTHINGS_LOOKUP(reg_concurrent, 4);
  EXPECT_EQ(res_2, std::nullopt);
}
