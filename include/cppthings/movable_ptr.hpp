#pragma once

#include <utility>

namespace cppthings {
  template<typename T>
  class movable_ptr {
  private:
    T* ptr;

  public:
    constexpr T*& get() { return ptr; }
    constexpr const T* const& get() const { return ptr; }

    constexpr T* reset(T* p = nullptr) { T* ret = ptr; ptr = p; return ret; }

    constexpr operator T*&() noexcept { return ptr; }
    constexpr operator T* const&() const noexcept { return ptr; }
    constexpr T& operator*() noexcept { return *ptr; }
    constexpr const T& operator*() const noexcept { return *ptr; }
    constexpr T*& operator->() noexcept { return ptr; }
    constexpr const T* const& operator->() const noexcept { return ptr; }
    constexpr operator bool() const noexcept { return ptr != nullptr; }

  public:
    constexpr movable_ptr(T* ptr_ = nullptr) noexcept : ptr{ptr_} {}

    movable_ptr(const movable_ptr&) = delete;
    movable_ptr& operator=(const movable_ptr&) = delete;

    constexpr movable_ptr(movable_ptr&& other) noexcept {
      ptr = other.ptr;
      other.ptr = nullptr;
    }
    constexpr movable_ptr& operator=(movable_ptr&& other) noexcept {
      ptr = other.ptr;
      other.ptr = nullptr;
      return *this;
    }

  public:
    constexpr bool operator==(const movable_ptr& other) const noexcept { return ptr == other.ptr; }
    constexpr bool operator==(const T* other)           const noexcept { return ptr == other; }
    constexpr bool operator< (const movable_ptr& other) const noexcept { return ptr <  other.ptr; }
    constexpr bool operator< (const T* other)           const noexcept { return ptr <  other; }
    constexpr bool operator> (const movable_ptr& other) const noexcept { return ptr >  other.ptr; }
    constexpr bool operator> (const T* other)           const noexcept { return ptr >  other; }
    constexpr bool operator<=(const movable_ptr& other) const noexcept { return ptr <= other.ptr; }
    constexpr bool operator<=(const T* other)           const noexcept { return ptr <= other; }
    constexpr bool operator>=(const movable_ptr& other) const noexcept { return ptr >= other.ptr; }
    constexpr bool operator>=(const T* other)           const noexcept { return ptr >= other; }

    template<typename Int, typename = std::enable_if<std::is_integral_v<Int>>>
    constexpr T* operator+ (Int i) const noexcept { return ptr + i; }
    template<typename Int, typename = std::enable_if<std::is_integral_v<Int>>>
    constexpr T* operator- (Int i) const noexcept { return ptr - i; }

  public:
    template<typename U>
    constexpr operator movable_ptr<U>() const noexcept { return {static_cast<movable_ptr<U>>(ptr)}; }
  };

  template<>
  class movable_ptr<void> {
  private:
    using T = void;

  private:
    void* ptr;

  public:
    constexpr T*& get() { return ptr; }
    constexpr const T* const& get() const { return ptr; }

    constexpr T* reset(T* p = nullptr) { T* ret = ptr; ptr = p; return ret; }

    constexpr operator T*&() noexcept { return ptr; }
    constexpr operator T* const&() const noexcept { return ptr; }
    constexpr operator bool() const noexcept { return ptr != nullptr; }

  public:
    constexpr movable_ptr(T* ptr_ = nullptr) noexcept : ptr{ptr_} {}

    movable_ptr(const movable_ptr&) = delete;
    movable_ptr& operator=(const movable_ptr&) = delete;

    constexpr movable_ptr(movable_ptr&& other) noexcept {
      ptr = other.ptr;
      other.ptr = nullptr;
    }
    constexpr movable_ptr& operator=(movable_ptr&& other) noexcept {
      ptr = other.ptr;
      other.ptr = nullptr;
      return *this;
    }

  public:
    constexpr bool operator==(const movable_ptr& other) const noexcept { return ptr == other.ptr; }
    constexpr bool operator==(const T* other)           const noexcept { return ptr == other; }
    constexpr bool operator< (const movable_ptr& other) const noexcept { return ptr <  other.ptr; }
    constexpr bool operator< (const T* other)           const noexcept { return ptr <  other; }
    constexpr bool operator> (const movable_ptr& other) const noexcept { return ptr >  other.ptr; }
    constexpr bool operator> (const T* other)           const noexcept { return ptr >  other; }
    constexpr bool operator<=(const movable_ptr& other) const noexcept { return ptr <= other.ptr; }
    constexpr bool operator<=(const T* other)           const noexcept { return ptr <= other; }
    constexpr bool operator>=(const movable_ptr& other) const noexcept { return ptr >= other.ptr; }
    constexpr bool operator>=(const T* other)           const noexcept { return ptr >= other; }

    template<typename Int, typename = std::enable_if<std::is_integral_v<Int>>>
    constexpr T* operator+ (Int i) const noexcept { return ptr + i; }
    template<typename Int, typename = std::enable_if<std::is_integral_v<Int>>>
    constexpr T* operator- (Int i) const noexcept { return ptr - i; }

  public:
    template<typename U>
    constexpr operator movable_ptr<U>() noexcept { return {static_cast<U*>(ptr)}; }
    template<typename U>
    constexpr operator movable_ptr<const U>() const noexcept { return {static_cast<U const*>(ptr)}; }
  };
}
