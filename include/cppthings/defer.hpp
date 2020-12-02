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

  /// Represents a sequence of actions that can be rolled back in reverse order. By default, this happens on deconstruction
  class transaction {
    std::vector<std::function<void(void)>> states;
    bool auto_rollback;

  public:
    inline void add(decltype(states)::value_type&& val) {
      states.emplace_back(std::move(val));
    }

    inline void commit() {
      states.clear();
    }

    inline void rollback() {
      for (auto iter = states.rbegin(); iter != states.rend(); ++iter)
        (*iter)();
      states.clear();
    }

    inline bool get_auto_rollback() const { return auto_rollback; }
    inline void set_auto_rollback(bool b) { auto_rollback = b; }

  public:
    inline transaction(bool auto_rollback_ = true) : auto_rollback{auto_rollback_} {}

    inline ~transaction() {
      if (auto_rollback)
        rollback();
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
