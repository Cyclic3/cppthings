#pragma once

//! GSL has a more complex version of this, but GSL is big

#include <memory>
#include <functional>

namespace cppthings {
  template<typename F>
  class deferred_call {
  private:
    F* f;

  public:
    void cancel() { f = nullptr; }

  public:
    inline deferred_call() : f{nullptr} {}
    inline deferred_call(F* f_) : f{std::move(f_)} {}

    inline ~deferred_call() {
      if (f)
        (*f)();
    }

  public:
    inline deferred_call& operator=(const deferred_call&) = delete;
    inline deferred_call(const deferred_call&) = delete;

    inline deferred_call& operator=(deferred_call&& other) {
      f = other.f;
      other.f = nullptr;
      return *this;
    }
    inline deferred_call(deferred_call&& other) : f{other.f} {
      other.f = nullptr;
    }
  };

  /// Returns an object, which when destroyed, calls a function
  template<typename Func>
  inline deferred_call<std::decay_t<Func>> defer(Func&& f) {
    return {&f};
  }
  template<typename Func>
  inline auto defer(Func* f) {
    return deferred_call{f};
  }
}
