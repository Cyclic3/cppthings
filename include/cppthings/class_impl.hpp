#pragma once

// Feel free to just copy-paste the contents across instead
#ifndef CPPTHINGS_FORCE_NO_INCLUDES
#include <cppthings/macros.hpp>
#endif

namespace cppthings {
  template<typename T>
  constexpr bool check_shallow_equal(const T&, const T&) {
    return true;
  }

  template<typename T, typename FirstType, typename... Args>
  constexpr bool check_shallow_equal(const T& a, const T& b, FirstType T::* first, Args*... args) {
    return a.*first == b.*first && check_shallow_equal(a, b, args...);
  }
}

#define __CPPTHINGS_MEMBER_PTR(TYPE, X) &TYPE::X

#if defined(__cplusplus) && __cplusplus > 201703L
#define CPPTHINGS_IMPL_SHALLOW_EQ(TYPE, ...) \
  inline bool operator==(const TYPE& other) const { return ::cppthings::check_shallow_equal(*this, other __VA_OPT__(,) __VA_ARGS__);  } \
  inline bool operator!=(const TYPE& other) const { return !::cppthings::check_shallow_equal(*this, other __VA_OPT__(,) __VA_ARGS__);  }

#define CPPTHINGS_IMPL_SHALLOW_EQ_NOEXCEPT(TYPE, ...) \
  inline bool operator==(const TYPE& other) const noexcept { return ::cppthings::check_shallow_equal(*this, other __VA_OPT__(,) __VA_ARGS__);  } \
  inline bool operator!=(const TYPE& other) const noexcept { return !::cppthings::check_shallow_equal(*this, other __VA_OPT__(,) __VA_ARGS__);  }
#else
#define CPPTHINGS_IMPL_SHALLOW_EQ(TYPE, ...) \
  inline bool operator==(const TYPE& other) const { \
    return ::cppthings::check_shallow_equal(*this, other, CPPTHINGS_FOR_EACH_ARG(__CPPTHINGS_MEMBER_PTR, TYPE, __VA_ARGS__));  \
  } \
  inline bool operator!=(const TYPE& other) const { \
    return !::cppthings::check_shallow_equal(*this, other, CPPTHINGS_FOR_EACH_ARG(__CPPTHINGS_MEMBER_PTR, TYPE, __VA_ARGS__)); \
  }

#define CPPTHINGS_IMPL_SHALLOW_EQ_NOEXCEPT(TYPE, ...) \
  inline bool operator==(const TYPE& other) const noexcept { \
    return ::cppthings::check_shallow_equal(*this, other, CPPTHINGS_FOR_EACH_ARG(__CPPTHINGS_MEMBER_PTR, TYPE, __VA_ARGS__)); \
  } \
  inline bool operator!=(const TYPE& other) const noexcept { \
    return !::cppthings::check_shallow_equal(*this, other, CPPTHINGS_FOR_EACH_ARG(__CPPTHINGS_MEMBER_PTR, TYPE, __VA_ARGS__)); \
  }
#endif
