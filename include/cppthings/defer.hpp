#pragma once

//! GSL has a more complex version of this, but GSL is big

#include <memory>
#include <functional>

namespace cppthings {
  class deferred_call {
  private:
    std::function<void(void)> f;

  public:
    inline deferred_call() {}
    inline deferred_call(decltype(f)&& f_) : f{std::move(f_)} {}

    inline ~deferred_call() {
      if (f)
        f();
    }

  public:
    inline deferred_call& operator=(const deferred_call&) = delete;
    inline deferred_call(const deferred_call&) = delete;

    inline deferred_call& operator=(deferred_call&& other) {
      f = std::move(other.f);
      other.f = {};
      return *this;
    }
    inline deferred_call(deferred_call&& other) : f{std::move(other.f)} {
      other.f = {};
    }
  };

  /// Returns an object, which when destroyed, calls a function
  template<typename... Args>
  inline deferred_call defer(Args&&... args) {
    return {args...};
  }
}
