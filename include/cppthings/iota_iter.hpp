#pragma once

#include <utility>
#include <iterator>

namespace cppthings {
  // An exclusive integer iterator. Cannot cover the entire range
  template<typename T>
  class iota_iter {
  public:
    using difference_type = T;
    using value_type = T;
    using pointer = const T*;
    using reference = const T&;
    using iterator_category = std::random_access_iterator_tag;

  public:
    T base;

  public:
    constexpr const T& operator*() const { return base; }
    constexpr iota_iter operator++() { return {base++}; }
    constexpr iota_iter& operator++(int) { ++base; }
    constexpr iota_iter& operator+=(T n) { base += n; }
    constexpr iota_iter& operator-=(T n) { base -= n; }
    constexpr T operator-(const iota_iter& other) { return base - other.base; }
    constexpr const T& operator[](T i) { return base + i; }
    constexpr bool operator==(const iota_iter& other) { return base == other.base; }
    constexpr bool operator!=(const iota_iter& other) { return base != other.base; }
    constexpr bool operator<=(const iota_iter& other) { return base <= other.base; }
    constexpr bool operator>=(const iota_iter& other) { return base >= other.base; }
    constexpr bool operator< (const iota_iter& other) { return base <  other.base; }
    constexpr bool operator> (const iota_iter& other) { return base >  other.base; }

  public:
    iota_iter(const iota_iter&) = default;
    iota_iter(iota_iter&&) = default;

    iota_iter& operator=(const iota_iter&) = default;
    iota_iter& operator=(iota_iter&&) = default;

//    template<typename... Args>
//    inline constexpr iota_iter(Args&&... args) : base{std::forward<Args&&>(args)...} {}
  };

  template<typename T> iota_iter(iota_iter<T>) -> iota_iter<T>;
  template<typename T> iota_iter(iota_iter<T>) -> iota_iter<T>;
  template<typename T> iota_iter(T) -> iota_iter<T>;
}
