#pragma once

#include <algorithm>
#include <array>
#include <utility>
#include <iterator>

namespace cppthings {
  template<typename T>
  class iota_iter {
  public:
    using difference_type = T;
    using value_type = T;
    using pointer = const T*;
    using reference = const T&;
    using iterator_category = std::random_access_iterator_tag;
  private:
    using nl = std::numeric_limits<T>;

  public:
    T base;
    bool is_end;

  public:
    constexpr bool is_max() const {
      return base == nl::max();
    }

  public:
    constexpr const T& operator*() const { return base; }
    constexpr iota_iter operator++(int) { auto cpy = *this; ++*this; return cpy; }
    constexpr iota_iter& operator++() {
      if (is_max())
        is_end = true;
      else
        ++base;
      return *this;
    }
    constexpr iota_iter operator--(int) { auto cpy = *this; --*this; return cpy;  }
    constexpr iota_iter& operator--() {
      if (is_end) {
        base = nl::max();
        is_end = false;
      }
      else
        --base;
      return *this;
    }
    constexpr iota_iter& operator+=(T n) {
      if (nl::max - base < n)
        is_end = true;
      else
        base += n;
      return *this;
    }
    constexpr iota_iter& operator-=(T n) {
      if (is_end && n != 0) {
        base = nl::max() - n + 1;
        is_end = true;
      }
      else
        base -= n;
      return *this;
    }
    constexpr iota_iter operator+(T n) const {
      return nl::max() - base < n ? iota_iter{} : iota_iter{base + n};
    }
    constexpr iota_iter operator-(T n) const {
      return is_end ? iota_iter{nl::max() - n + 1} : iota_iter{base - n};
    }
    constexpr T operator-(const iota_iter& other) {
      if (is_end) {
        if (other.is_end)
          return 0;
        else
          return nl::max() - other.base + 1;
      }
      else if (other.is_end)
        return base - nl::max() - 1;
      else
        return base - other.base;
    }
    constexpr const T& operator[](T i) const { return base + i; }
    constexpr bool operator==(const iota_iter& other) const { return base == other.base; }
    constexpr bool operator!=(const iota_iter& other) const { return base != other.base; }
    constexpr bool operator<=(const iota_iter& other) const { return base <= other.base; }
    constexpr bool operator>=(const iota_iter& other) const { return base >= other.base; }
    constexpr bool operator< (const iota_iter& other) const { return base <  other.base; }
    constexpr bool operator> (const iota_iter& other) const { return base >  other.base; }

  public:
    iota_iter(const iota_iter&) = default;
    iota_iter(iota_iter&&) = default;

    iota_iter& operator=(const iota_iter&) = default;
    iota_iter& operator=(iota_iter&&) = default;

    constexpr iota_iter(T&& base) : base{std::forward<T&&>(base)}, is_end{false} {}
    constexpr iota_iter() : is_end{true} {}
  };

  template<typename T> iota_iter(iota_iter<T>) -> iota_iter<T>;
  template<typename T> iota_iter(T) -> iota_iter<T>;

  /// iota iter for unsigned, little endian arrays. Go wild.
  template<typename Elem, size_t Count>
  class iota_iter_arr_le {
  public:
    using T = std::array<Elem, Count>;
    using difference_type = T;
    using value_type = T;
    using pointer = const T*;
    using reference = const T&;
    using iterator_category = std::bidirectional_iterator_tag;
  private:
    using nl = std::numeric_limits<Elem>;

  public:
    T base;
    bool is_end;

  public:
    constexpr bool is_max() const {
      return std::all_of(base.begin(), base.end(), [&](auto i) { return i == nl::max(); });
    }
  private:
    static constexpr T max_base() {
      T ret;
      std::fill(ret.base.begin(), ret.base.end(), nl::max());
      return ret;
    }

  public:
    constexpr const T& operator*() const { return base; }
    constexpr iota_iter_arr_le operator++(int) { auto cpy = *this; ++*this; return cpy; }
    constexpr iota_iter_arr_le& operator++() {
      // A check for is_max would require a pass anyway, so don't use it
      //
      // We also won't check for is_end, because UB. Get rekt.
      for (auto& i : base) {
        if (i == nl::max())
          i = nl::min(); // We might as well do this explicitly, as we are branching anyway
        else {
          ++i;
          return *this;
        }
      }
      is_end = true;
      return *this;
    }
    constexpr iota_iter_arr_le operator--(int) { auto cpy = *this; --*this; return cpy;  }
    constexpr iota_iter_arr_le& operator--() {
      for (auto & i : base) {
        if (i == nl::min())
          i = nl::max(); // We might as well do this explicitly, as we are branching anyway
        else {
          --i;
          return *this;
        }
      }
      // You screwed up if we got here, have some UB
      throw std::logic_error("Tried to go before the start of an iota_iter_arr_le");
    }

    constexpr bool operator==(const iota_iter_arr_le& other) { return base == other.base; }
    constexpr bool operator!=(const iota_iter_arr_le& other) { return base != other.base; }

  public:
    iota_iter_arr_le(const iota_iter_arr_le&) = default;
    iota_iter_arr_le(iota_iter_arr_le&&) = default;

    iota_iter_arr_le& operator=(const iota_iter_arr_le&) = default;
    iota_iter_arr_le& operator=(iota_iter_arr_le&&) = default;

    iota_iter_arr_le(T&& base) : base{std::forward<T&&>(base)}, is_end{false} {}
    template<typename... Args>
    iota_iter_arr_le(std::in_place_t, Args... args) : base{static_cast<Elem>(args)...}, is_end{false} {}
    iota_iter_arr_le() : is_end{true} {}
  };

  /// iota iter for unsigned, big endian arrays. Go wild.
  template<typename Elem, size_t Count>
  class iota_iter_arr_be {
  public:
    using T = std::array<Elem, Count>;
    using difference_type = T;
    using value_type = T;
    using pointer = const T*;
    using reference = const T&;
    using iterator_category = std::bidirectional_iterator_tag;
  private:
    using nl = std::numeric_limits<Elem>;

  public:
    T base;
    bool is_end;

  public:
    constexpr bool is_max() const {
      return std::all_of(base.begin(), base.end(), [&](auto i) { return i == nl::max(); });
    }
  private:
    static constexpr T max_base() {
      T ret;
      std::fill(ret.base.begin(), ret.base.end(), nl::max());
      return ret;
    }

  public:
    constexpr const T& operator*() const { return base; }
    constexpr iota_iter_arr_be operator++(int) { auto cpy = *this; ++*this; return cpy; }
    constexpr iota_iter_arr_be& operator++() {
      // A check for is_max would require a pass anyway, so don't use it
      //
      // We also won't check for is_end, because UB. Get rekt.
      for (auto iter = base.rbegin(); iter != base.rend(); ++iter) {
        if (*iter == nl::max())
          *iter = nl::min(); // We might as well do this explicitly, as we are branching anyway
        else {
          ++*iter;
          return *this;
        }
      }
      is_end = true;
      return *this;
    }
    constexpr iota_iter_arr_be operator--(int) { auto cpy = *this; --*this; return cpy;  }
    constexpr iota_iter_arr_be& operator--() {
      for (auto iter = base.rbegin(); iter != base.rend(); ++iter) {
        if (*iter == nl::min())
          *iter = nl::max(); // We might as well do this explicitly, as we are branching anyway
        else {
          --*iter;
          return *this;
        }
      }
      // You screwed up if we got here, have some UB
      throw std::logic_error("Tried to go before the start of an iota_iter_arr_le");
    }

    constexpr bool operator==(const iota_iter_arr_be& other) { return base == other.base; }
    constexpr bool operator!=(const iota_iter_arr_be& other) { return base != other.base; }

  public:
    iota_iter_arr_be(const iota_iter_arr_be&) = default;
    iota_iter_arr_be(iota_iter_arr_be&&) = default;

    iota_iter_arr_be& operator=(const iota_iter_arr_be&) = default;
    iota_iter_arr_be& operator=(iota_iter_arr_be&&) = default;

    iota_iter_arr_be(T&& base) : base{std::forward<T&&>(base)}, is_end{false} {}
    template<typename... Args>
    iota_iter_arr_be(std::in_place_t, Args... args) : base{static_cast<Elem>(args)...}, is_end{false} {}
    iota_iter_arr_be() : is_end{true} {}
  };
}
