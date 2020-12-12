#include "gtest/gtest.h"

#include <cppthings/registry.hpp>

#include <string>

CPPTHINGS_EXPOSE_REGISTRY(reg, int, int);
CPPTHINGS_IMPL_REGISTRY(reg);

CPPTHINGS_EXPOSE_REGISTRY(reg_concurrent, int, int);
CPPTHINGS_IMPL_REGISTRY_CONCURRENT(reg_concurrent);

CPPTHINGS_EXPOSE_REGISTRY(reg_str, std::string, int);
CPPTHINGS_IMPL_REGISTRY(reg_str);

CPPTHINGS_REGISTER(reg, 1, 2)
CPPTHINGS_REGISTER(reg, 2, 3)
CPPTHINGS_REGISTER(reg, 3, 4)

CPPTHINGS_REGISTER(reg_concurrent, 1, 2)
CPPTHINGS_REGISTER(reg_concurrent, 2, 3)
CPPTHINGS_REGISTER(reg_concurrent, 3, 4)

CPPTHINGS_REGISTER(reg_str, "a", 2)
CPPTHINGS_REGISTER(reg_str, "b", 3)


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

TEST (cppthings, RegistryPolymorphism) {
  auto res = CPPTHINGS_LOOKUP(reg_str, std::string_view{"a"});
  EXPECT_EQ(res, 2);
  auto res_2 = CPPTHINGS_LOOKUP(reg_str, std::string_view{"d"});
  EXPECT_EQ(res_2, std::nullopt);
}
