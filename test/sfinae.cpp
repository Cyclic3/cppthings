#include "gtest/gtest.h"

#include <cppthings/sfinae.hpp>

TEST (cppthings, SFINAEVaraint) {
  using T = std::variant<int, bool>;

  static_assert(cppthings::is_in_variant_v<int, T>, "int not in variant");
  static_assert(cppthings::is_in_variant_v<bool, T>, "bool not in variant");
  static_assert(!cppthings::is_in_variant_v<char, T>, "char in variant");
}
