#pragma once

#include <cppthings/boxed_ptr.hpp>

#include <memory>
#include <utility>
#include <variant>

namespace cppthings {
  /// Allows a runtime decision about whether and how to pass ownership
  ///
  /// or allows classes to not worry about who owns what
  template<typename T, bool enable_unalloced = false>
  class handle {
  private:
    template<bool unalloced = enable_unalloced>
    struct base_t;
    template<>
    struct base_t<true > { using type = std::variant<std::nullptr_t, T*, std::shared_ptr<T>, boxed_ptr<T>, T>; };
    template<>
    struct base_t<false> { using type = std::variant<std::nullptr_t, T*, std::shared_ptr<T>, boxed_ptr<T>   >; };

  private:
    typename base_t<enable_unalloced>::type base;

  public:
    inline T& operator* () {
      return std::visit([](auto&& x){
        if constexpr (std::is_same_v<std::remove_reference_t<decltype(x)>, T>) // constexpr ignored if not enabled_unalloced
          return x;
        else
          return *x;
      }, base);
    }
    inline T* operator->() {
      return std::visit([](auto&& x){
        using U = std::remove_reference_t<decltype(x)>;
        if constexpr (std::is_same_v<U, T*>)
          return x;
        else if constexpr (std::is_same_v<U, std::shared_ptr<T>> || std::is_same_v<U, boxed_ptr<T>>)
          return x.get();
        else // constexpr ignored if not enabled_unalloced
          return &x;
      }, base);
    }
    inline operator bool() const {
      return std::visit([](auto&& x){
        if constexpr (std::is_same_v<std::remove_cv_t<std::remove_reference_t<decltype(x)>>, T>) // constexpr ignored if not enabled_unalloced
          return true;
        else
          return static_cast<bool>(x);
      }, base);
    }

  public:
    handle() = default;
    template<typename... Args>
    inline handle(Args&&... args) : base{std::forward<Args>(args)...} {}
  };
}
