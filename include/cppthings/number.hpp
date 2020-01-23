#pragma once
#include <limits>
#include <cstdint>
#include <cstdlib>
#include <algorithm>

namespace cppthings::number {
  template<typename IntType>
  constexpr IntType divide_ceil(IntType dividend, IntType devisor) {
    return (dividend + devisor - 1) / devisor;
  }

  template<typename Rep, typename Ret = Rep>
  constexpr Ret int_log2(Rep value) {
    Ret ret = 0;

    for (Rep i = value; i != 0; i <<= 1) ++ret;

    return ret;
  }

  template<bool> struct range;

  template<size_t Bits, typename = range<true>>
  class integer;

  template<size_t Bits, typename = range<true>>
  class integer_fast;

  template<size_t Bits>
  using integer_t = typename integer<Bits>::type;

  template<size_t Bits>
  using integer_fast_t = typename integer_fast<Bits>::type;

  template<uint64_t MaxValue>
  using integer_upto_t = integer_t<int_log2(MaxValue)>;

  template<uint64_t MaxValue>
  using integer_fast_upto_t = integer_fast_t<int_log2(MaxValue)>;

  template<size_t Bits, typename = range<true>>
  class integer_signed;

  template<size_t Bits, typename = range<true>>
  class integer_signed_fast;

  template<size_t Bits>
  using integer_signed_t = typename integer_signed<Bits>::type;

  template<size_t Bits>
  using integer_signed_fast_t = typename integer_signed_fast<Bits>::type;

  template<uint64_t MaxValue>
  using integer_signed_upto_t = integer_signed_t<int_log2(MaxValue)>;

  template<uint64_t MaxValue>
  using integer_signed_fast_upto_t = integer_signed_fast_t<int_log2(MaxValue)>;

  template<typename T>
  using integer_opt_t = integer_fast_t<std::numeric_limits<T>::digits>;

  template<typename T>
  using integer_signed_opt_t = integer_signed_t<std::numeric_limits<T>::digits>;

#define CPPTHINGS_NUMBER_integer_TYPE(TYPE, MIN, MAX) \
  template<size_t Bits> \
  class integer<Bits, range<(Bits > MIN && Bits <= MAX)>> { \
    public: using type = TYPE; \
  };
#define CPPTHINGS_NUMBER_integer_FAST_TYPE(TYPE, MIN, MAX) \
  template<size_t Bits> \
  class integer_fast<Bits, range<(Bits > MIN && Bits <= MAX)>> { \
    public: using type = TYPE; \
  };

  CPPTHINGS_NUMBER_integer_TYPE(uint8_t,   0,  8)
  CPPTHINGS_NUMBER_integer_TYPE(uint16_t,  8, 16)
  CPPTHINGS_NUMBER_integer_TYPE(uint32_t, 16, 32)
  CPPTHINGS_NUMBER_integer_TYPE(uint64_t, 32, 64)

  CPPTHINGS_NUMBER_integer_FAST_TYPE(uint_fast8_t,   0,  8)
  CPPTHINGS_NUMBER_integer_FAST_TYPE(uint_fast16_t,  8, 16)
  CPPTHINGS_NUMBER_integer_FAST_TYPE(uint_fast32_t, 16, 32)
  CPPTHINGS_NUMBER_integer_FAST_TYPE(uint_fast64_t, 32, 64)

#define CPPTHINGS_NUMBER_integer_SIGNED_TYPE(TYPE, MIN, MAX) \
  template<size_t Bits> \
  class integer_signed<Bits, range<(Bits > MIN && Bits <= MAX)>> { \
    public: using type = TYPE; \
  };
#define CPPTHINGS_NUMBER_integer_SIGNED_FAST_TYPE(TYPE, MIN, MAX) \
  template<size_t Bits> \
  class integer_signed_fast<Bits, range<(Bits > MIN && Bits <= MAX)>> { \
    public: using type = TYPE; \
  };

  CPPTHINGS_NUMBER_integer_SIGNED_TYPE(int8_t,   0,  8)
  CPPTHINGS_NUMBER_integer_SIGNED_TYPE(int16_t,  8, 16)
  CPPTHINGS_NUMBER_integer_SIGNED_TYPE(int32_t, 16, 32)
  CPPTHINGS_NUMBER_integer_SIGNED_TYPE(int64_t, 32, 64)

  CPPTHINGS_NUMBER_integer_SIGNED_FAST_TYPE(int_fast8_t,   0,  8)
  CPPTHINGS_NUMBER_integer_SIGNED_FAST_TYPE(int_fast16_t,  8, 16)
  CPPTHINGS_NUMBER_integer_SIGNED_FAST_TYPE(int_fast32_t, 16, 32)
  CPPTHINGS_NUMBER_integer_SIGNED_FAST_TYPE(int_fast64_t, 32, 64)

#undef CPPTHINGS_NUMBER_integer_TYPE
#undef CPPTHINGS_NUMBER_integer_FAST_TYPE
}
