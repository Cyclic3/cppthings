  template<typename T>
  class movable_ptr {
  private:
    T* ptr;

  public:
    constexpr T* get() { return ptr; }
    constexpr const T* get() const { return ptr; }

    constexpr T* reset(T* p = nullptr) { T* ret = ptr; ptr = p; return ret; }

    constexpr operator T*() { return ptr; }
    constexpr operator const T*() const { return ptr; }
    constexpr T& operator*() { return *ptr; }
    constexpr const T& operator*() const { return *ptr; }
    constexpr T* operator->() { return ptr; }
    constexpr const T* operator->() const { return ptr; }
    constexpr operator bool() const { return ptr != nullptr; }

  public:
    constexpr movable_ptr(T* ptr) : ptr{ptr} {}

    movable_ptr(const movable_ptr&) = delete;
    movable_ptr& operator=(const movable_ptr&) = delete;

    constexpr movable_ptr(movable_ptr&& other) {
      ptr = other.ptr;
      other.ptr = nullptr;
    }
    constexpr movable_ptr& operator=(movable_ptr&& other) {
      new (this) movable_ptr(std::move(other));
      return *this;
    }

  public:
    constexpr bool operator==(const movable_ptr& other) { return ptr == other.ptr; }
    constexpr bool operator==(const T* other)           { return ptr == other; }
    constexpr bool operator< (const movable_ptr& other) { return ptr <  other.ptr; }
    constexpr bool operator< (const T* other)           { return ptr <  other; }
    constexpr bool operator> (const movable_ptr& other) { return ptr >  other.ptr; }
    constexpr bool operator> (const T* other)           { return ptr >  other; }
    constexpr bool operator<=(const movable_ptr& other) { return ptr <= other.ptr; }
    constexpr bool operator<=(const T* other)           { return ptr <= other; }
    constexpr bool operator>=(const movable_ptr& other) { return ptr >= other.ptr; }
    constexpr bool operator>=(const T* other)           { return ptr >= other; }
  };
