#pragma once

#include <memory>

namespace cppthings {
  /// Represents a heap-allocated object that should be deep copied
  template<typename T, typename Deleter = std::default_delete<T>>
  class boxed_ptr {
    template<typename U, typename E>
    friend class boxed_ptr;

  public:
    using pointer      = T*;
    using element_type = T;
    using deleter_type = Deleter;

  private:
    std::unique_ptr<element_type, deleter_type> box;

  public:
    inline    pointer get    ()                        const { return box.get();     }
    inline    void    swap   (boxed_ptr& other)       const { box.swap(other.box);  }
    inline    void    reset  (pointer ptr = pointer())       { box.reset(ptr);       }
    inline    pointer release()                              { return box.release(); }


    constexpr       element_type&  operator* () &      { return *box; }
    constexpr const element_type&  operator* () const& { return *box; }
    constexpr       element_type&& operator* () &&     { return *box; }
    constexpr       pointer        operator->() const  { return get(); }

    constexpr operator bool() const { return box.operator bool(); }

  public:
    constexpr       boxed_ptr() noexcept {}
    constexpr       boxed_ptr(decltype(nullptr)) noexcept : box{nullptr} {}
    inline explicit boxed_ptr(pointer p) : box{p} {}
    template<typename D>
    constexpr       boxed_ptr(pointer p, D&& d) : box{p, std::forward<D&&>(d)} {}
    constexpr       boxed_ptr(std::unique_ptr<element_type>&& base) : box{std::move(base)} {}

  public:
    template<typename U, typename E>
    inline boxed_ptr    (const boxed_ptr<U, E>& other) { box = decltype(box){new T(*other.box)}; }
    inline boxed_ptr    (const boxed_ptr      & other) { box = decltype(box){new T(*other.box)}; }
    template<typename U, typename E>
    boxed_ptr& operator=(const boxed_ptr<U, E>& other) { box = decltype(box){new T(*other.box)}; }
    boxed_ptr& operator=(const boxed_ptr      & other) { box = decltype(box){new T(*other.box)}; }

    boxed_ptr           (boxed_ptr&& other) = default;
    boxed_ptr& operator=(boxed_ptr&& other) = default;
  };

  template<typename T, typename... Args>
  inline boxed_ptr<T> make_boxed(Args&&... args) { return boxed_ptr<T>{ new T(std::forward<Args>(args)...) }; }
}
