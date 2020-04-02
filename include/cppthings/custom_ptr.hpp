#pragma once

#include <memory>
#include <type_traits>

namespace cppthings {
  template<typename T, auto deleter>
  using custom_ptr = std::unique_ptr<T, std::integral_constant<decltype(deleter), deleter>>;
}
