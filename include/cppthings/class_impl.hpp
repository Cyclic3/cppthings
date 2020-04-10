#pragma once

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


#if defined(__cplusplus) && __cplusplus > 201703L
#define CPPTHINGS_IMPL_SHALLOW_EQ(TYPE, ...) \
  inline bool operator==(const TYPE& other) const { return ::cppthings::check_shallow_equal(*this, other __VA_OPT__(,) __VA_ARGS__);  } \
  inline bool operator!=(const TYPE& other) const { return !::cppthings::check_shallow_equal(*this, other __VA_OPT__(,) __VA_ARGS__);  }

#define CPPTHINGS_IMPL_SHALLOW_EQ_NOEXCEPT(TYPE, ...) \
  inline bool operator==(const TYPE& other) const noexcept { return ::cppthings::check_shallow_equal(*this, other __VA_OPT__(,) __VA_ARGS__);  } \
  inline bool operator!=(const TYPE& other) const noexcept { return !::cppthings::check_shallow_equal(*this, other __VA_OPT__(,) __VA_ARGS__);  }
#elif defined(__GNUC__)
#define CPPTHINGS_IMPL_SHALLOW_EQ(TYPE, ...) \
  inline bool operator==(const TYPE& other) const { return ::cppthings::check_shallow_equal(*this, other, ##__VA_ARGS__);  } \
  inline bool operator!=(const TYPE& other) const { return !::cppthings::check_shallow_equal(*this, other, ##__VA_ARGS__);  }

#define CPPTHINGS_IMPL_SHALLOW_EQ_NOEXCEPT(TYPE, ...) \
  inline bool operator==(const TYPE& other) const noexcept { return ::cppthings::check_shallow_equal(*this, other, ##__VA_ARGS__);  } \
  inline bool operator!=(const TYPE& other) const noexcept { return !::cppthings::check_shallow_equal(*this, other, ##__VA_ARGS__);  }
#else
#define CPPTHINGS_IMPL_SHALLOW_EQ(TYPE, ...) \
  inline bool operator==(const TYPE& other) const { ::cppthings::check_shallow_equal(*this, other, __VA_ARGS__);  }
  inline bool operator!=(const TYPE& other) const { return !::cppthings::check_shallow_equal(*this, other, __VA_ARGS__);  }

#define CPPTHINGS_IMPL_SHALLOW_EQ_NOEXCEPT(TYPE, ...) \
  inline bool operator==(const TYPE& other) const noexcept { ::cppthings::check_shallow_equal(*this, other, __VA_ARGS__);  }
  inline bool operator!=(const TYPE& other) const noexcept { return !::cppthings::check_shallow_equal(*this, other, __VA_ARGS__);  }
#endif
