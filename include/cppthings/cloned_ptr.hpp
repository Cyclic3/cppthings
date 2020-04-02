#pragma once

#include <memory>

namespace cppthings {
  /// Represents a heap-allocated object that should be deep copied
  template<typename T, typename Deleter = std::default_delete<T>>
  class cloned_ptr {
    template<typename U, typename E>
    friend class cloned_ptr;

  public:
    using pointer      = T*;
    using element_type = T;
    using deleter_type = Deleter;

  private:
    std::unique_ptr<element_type, deleter_type> box;

  public:
    inline    pointer get    ()                        const { return box.get();     }
    inline    void    swap   (cloned_ptr& other)       const { box.swap(other.box);  }
    inline    void    reset  (pointer ptr = pointer())       { box.reset(ptr);       }
    inline    pointer release()                              { return box.release(); }


    constexpr       element_type&  operator* () &      { return *box; }
    constexpr const element_type&  operator* () const& { return *box; }
    constexpr       element_type&& operator* () &&     { return *box; }
    constexpr       pointer        operator->() const  { return get(); }

    constexpr operator bool() const { return box.operator bool(); }

  public:
    constexpr       cloned_ptr() noexcept {}
    constexpr       cloned_ptr(decltype(nullptr)) noexcept : box{nullptr} {}
    inline explicit cloned_ptr(pointer p) : box{p} {}
    template<typename D>
    constexpr       cloned_ptr(pointer p, D&& d) : box{p, std::forward<D&&>(d)} {}
    constexpr       cloned_ptr(std::unique_ptr<element_type>&& base) : box{std::move(base)} {}

  public:
    template<typename U, typename E>
    inline cloned_ptr    (const cloned_ptr<U, E>& other) { box = decltype(box){new T(*other.box)}; }
    inline cloned_ptr    (const cloned_ptr      & other) { box = decltype(box){new T(*other.box)}; }
    template<typename U, typename E>
    cloned_ptr& operator=(const cloned_ptr<U, E>& other) { box = decltype(box){new T(*other.box)}; }
    cloned_ptr& operator=(const cloned_ptr      & other) { box = decltype(box){new T(*other.box)}; }

    cloned_ptr           (cloned_ptr&& other) = default;
    cloned_ptr& operator=(cloned_ptr&& other) = default;
  };

  template<typename T, typename... Args>
  inline cloned_ptr<T> make_cloned(Args&&... args) { return cloned_ptr<T>{ new T(std::forward<Args>(args)...) }; }
}
