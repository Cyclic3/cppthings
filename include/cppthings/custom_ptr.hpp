#pragma once

#include <memory>
#include <type_traits>

namespace cppthings {
  template<typename T, auto deleter>
  using custom_ptr<T, std::integral_constant<decltype(deleter), deleter>>;
  template<typename T, auto F, typename... Args>
  inline custom_ptr<T, F> make_custom(Args&&... args) {
    return new T(std::forward<Args>(args)...);
  }
}
