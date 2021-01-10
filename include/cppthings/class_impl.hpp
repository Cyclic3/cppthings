#pragma once

// Feel free to just copy-paste the contents across instead
#ifndef CPPTHINGS_FORCE_NO_INCLUDES
#include <cppthings/macros.hpp>
#endif

#include <utility>

namespace cppthings {
  template<typename T>
  constexpr bool check_shallow_equal(const T&, const T&) {
    return true;
  }

  template<typename T, typename FirstType, typename... Args>
  constexpr bool check_shallow_equal(const T& a, const T& b, FirstType T::* first, Args... args) {
    return a.*first == b.*first && check_shallow_equal(a, b, args...);
  }
}

#define _CPPTHINGS_MEMBER_PTR(TYPE, X) ,&TYPE::X

#ifdef CPPTHINGS_VA_OPT
#define CPPTHINGS_IMPL_SHALLOW_EQ(TYPE, ...) \
  inline bool operator==(const TYPE& other) const { \
    return ::cppthings::check_shallow_equal(*this, other CPPTHINGS_FOR_EACH_ARG(_CPPTHINGS_MEMBER_PTR, TYPE __VA_OPT__(,) __VA_ARGS__));  \
  } \
  inline bool operator!=(const TYPE& other) const { \
    return !::cppthings::check_shallow_equal(*this, other CPPTHINGS_FOR_EACH_ARG(_CPPTHINGS_MEMBER_PTR, TYPE __VA_OPT__(,) __VA_ARGS__));  \
  }

#define CPPTHINGS_IMPL_SHALLOW_EQ_NOEXCEPT(TYPE, ...) \
  inline bool operator==(const TYPE& other) const noexcept { \
    return ::cppthings::check_shallow_equal(*this, other CPPTHINGS_FOR_EACH_ARG(_CPPTHINGS_MEMBER_PTR, TYPE __VA_OPT__(,) __VA_ARGS__));  \
  } \
  inline bool operator!=(const TYPE& other) const noexcept { \
    return !::cppthings::check_shallow_equal(*this, other CPPTHINGS_FOR_EACH_ARG(_CPPTHINGS_MEMBER_PTR, TYPE __VA_OPT__(,) __VA_ARGS__));  \
  }
#else
#define CPPTHINGS_IMPL_SHALLOW_EQ(TYPE, ...) \
  inline bool operator==(const TYPE& other) const { \
    return ::cppthings::check_shallow_equal(*this, other CPPTHINGS_FOR_EACH_ARG(_CPPTHINGS_MEMBER_PTR, TYPE, __VA_ARGS__));  \
  } \
  inline bool operator!=(const TYPE& other) const { \
    return !::cppthings::check_shallow_equal(*this, other CPPTHINGS_FOR_EACH_ARG(_CPPTHINGS_MEMBER_PTR, TYPE, __VA_ARGS__));  \
  }

#define CPPTHINGS_IMPL_SHALLOW_EQ_NOEXCEPT(TYPE, ...) \
  inline bool operator==(const TYPE& other) const noexcept { \
    return ::cppthings::check_shallow_equal(*this, other CPPTHINGS_FOR_EACH_ARG(_CPPTHINGS_MEMBER_PTR, TYPE, __VA_ARGS__));  \
  } \
  inline bool operator!=(const TYPE& other) const noexcept { \
    return !::cppthings::check_shallow_equal(*this, other CPPTHINGS_FOR_EACH_ARG(_CPPTHINGS_MEMBER_PTR, TYPE, __VA_ARGS__));  \
  }
#endif

#define CPPTHINGS_BEGIN_WRAPPER_STRUCT(NAME, VAL_TYPE, VAL_NAME)                              \
  struct NAME {                                                                               \
    VAL_TYPE VAL_NAME;                                                                        \
    inline operator       VAL_TYPE& ()      &  { return VAL_NAME; }                           \
    inline operator const VAL_TYPE& () const&  { return VAL_NAME; }                           \
    inline operator       VAL_TYPE&&()      && { return std::move(VAL_NAME); }                \
    NAME() = default;                                                                         \
    NAME(const NAME& ) = default;                                                             \
    NAME(      NAME&&) = default;                                                             \
    NAME& operator=(const NAME& ) = default;                                                  \
    NAME& operator=(      NAME&&) = default;                                                  \
    template<typename... Args>                                                                \
    inline NAME(Args&&... args) : VAL_NAME(std::forward<Args>(args)...) {}

#define _CPPTHINGS_MAKE_PARAMS(X) decltype(X)&& CPPTHINGS_CONCAT(X, _)
#define _CPPTHINGS_MAKE_CONSTRUCTOR(X) X{std::move(CPPTHINGS_CONCAT(X, _))}

#ifdef CPPTHINGS_VA_OPT
#define CPPTHINGS_EZ_CONSTRUCTOR(NAME, ...) \
  NAME(CPPTHINGS_FOR_EACH_COMMA(_CPPTHINGS_MAKE_PARAMS __VA_OPT__(,) __VA_ARGS__))  __VA_OPT__(:) CPPTHINGS_FOR_EACH_COMMA(_CPPTHINGS_MAKE_CONSTRUCTOR __VA_OPT__(,) __VA_ARGS__) {}
#else
#define CPPT
