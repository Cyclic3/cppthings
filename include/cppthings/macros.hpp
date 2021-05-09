#pragma once
//! I don't want a central file like this, but there really is no choice with macros
//!
//! Copy and paste these into the source if you need them

// SOURCE: https://stackoverflow.com/a/58168986
#if defined(__cplusplus) && __cplusplus > 201703L
#define CPPTHINGS_VA_OPT
#endif

// SO requires a copyright notice (and the user deserves one), so make sure to copy something to that effect into
// any cloned source file

// Most of this foreach implementation was modified/stolen from the brilliant answer at https://stackoverflow.com/a/11994395
#define _CPPTHINGS_FE_0(ACTION, SEP)
#define _CPPTHINGS_FE_1(ACTION, SEP, X)       ACTION(X)
#define _CPPTHINGS_FE_2(ACTION, SEP, X, ...)  ACTION(X) SEP _CPPTHINGS_FE_1(ACTION, SEP, __VA_ARGS__)
#define _CPPTHINGS_FE_3(ACTION, SEP, X, ...)  ACTION(X) SEP _CPPTHINGS_FE_2(ACTION, SEP, __VA_ARGS__)
#define _CPPTHINGS_FE_4(ACTION, SEP, X, ...)  ACTION(X) SEP _CPPTHINGS_FE_3(ACTION, SEP, __VA_ARGS__)
#define _CPPTHINGS_FE_5(ACTION, SEP, X, ...)  ACTION(X) SEP _CPPTHINGS_FE_4(ACTION, SEP, __VA_ARGS__)
#define _CPPTHINGS_FE_6(ACTION, SEP, X, ...)  ACTION(X) SEP _CPPTHINGS_FE_5(ACTION, SEP, __VA_ARGS__)
#define _CPPTHINGS_FE_7(ACTION, SEP, X, ...)  ACTION(X) SEP _CPPTHINGS_FE_6(ACTION, SEP, __VA_ARGS__)
#define _CPPTHINGS_FE_8(ACTION, SEP, X, ...)  ACTION(X) SEP _CPPTHINGS_FE_7(ACTION, SEP, __VA_ARGS__)
#define _CPPTHINGS_FE_9(ACTION, SEP, X, ...)  ACTION(X) SEP _CPPTHINGS_FE_8(ACTION, SEP, __VA_ARGS__)
#define _CPPTHINGS_FE_A(ACTION, SEP, X, ...)  ACTION(X) SEP _CPPTHINGS_FE_9(ACTION, SEP, __VA_ARGS__)
#define _CPPTHINGS_FE_B(ACTION, SEP, X, ...)  ACTION(X) SEP _CPPTHINGS_FE_A(ACTION, SEP, __VA_ARGS__)
#define _CPPTHINGS_FE_C(ACTION, SEP, X, ...)  ACTION(X) SEP _CPPTHINGS_FE_B(ACTION, SEP, __VA_ARGS__)
#define _CPPTHINGS_FE_D(ACTION, SEP, X, ...)  ACTION(X) SEP _CPPTHINGS_FE_C(ACTION, SEP, __VA_ARGS__)
#define _CPPTHINGS_FE_E(ACTION, SEP, X, ...)  ACTION(X) SEP _CPPTHINGS_FE_D(ACTION, SEP, __VA_ARGS__)
#define _CPPTHINGS_FE_F(ACTION, SEP, X, ...)  ACTION(X) SEP _CPPTHINGS_FE_E(ACTION, SEP, __VA_ARGS__)

#define _CPPTHINGS_FE_C_0(ACTION)
#define _CPPTHINGS_FE_C_1(ACTION, X)       ACTION(X)
#define _CPPTHINGS_FE_C_2(ACTION, X, ...)  ACTION(X), _CPPTHINGS_FE_C_1(ACTION, __VA_ARGS__)
#define _CPPTHINGS_FE_C_3(ACTION, X, ...)  ACTION(X), _CPPTHINGS_FE_C_2(ACTION, __VA_ARGS__)
#define _CPPTHINGS_FE_C_4(ACTION, X, ...)  ACTION(X), _CPPTHINGS_FE_C_3(ACTION, __VA_ARGS__)
#define _CPPTHINGS_FE_C_5(ACTION, X, ...)  ACTION(X), _CPPTHINGS_FE_C_4(ACTION, __VA_ARGS__)
#define _CPPTHINGS_FE_C_6(ACTION, X, ...)  ACTION(X), _CPPTHINGS_FE_C_5(ACTION, __VA_ARGS__)
#define _CPPTHINGS_FE_C_7(ACTION, X, ...)  ACTION(X), _CPPTHINGS_FE_C_6(ACTION, __VA_ARGS__)
#define _CPPTHINGS_FE_C_8(ACTION, X, ...)  ACTION(X), _CPPTHINGS_FE_C_7(ACTION, __VA_ARGS__)
#define _CPPTHINGS_FE_C_9(ACTION, X, ...)  ACTION(X), _CPPTHINGS_FE_C_8(ACTION, __VA_ARGS__)
#define _CPPTHINGS_FE_C_A(ACTION, X, ...)  ACTION(X), _CPPTHINGS_FE_C_9(ACTION, __VA_ARGS__)
#define _CPPTHINGS_FE_C_B(ACTION, X, ...)  ACTION(X), _CPPTHINGS_FE_C_A(ACTION, __VA_ARGS__)
#define _CPPTHINGS_FE_C_C(ACTION, X, ...)  ACTION(X), _CPPTHINGS_FE_C_B(ACTION, __VA_ARGS__)
#define _CPPTHINGS_FE_C_D(ACTION, X, ...)  ACTION(X), _CPPTHINGS_FE_C_C(ACTION, __VA_ARGS__)
#define _CPPTHINGS_FE_C_E(ACTION, X, ...)  ACTION(X), _CPPTHINGS_FE_C_D(ACTION, __VA_ARGS__)
#define _CPPTHINGS_FE_C_F(ACTION, X, ...)  ACTION(X), _CPPTHINGS_FE_C_E(ACTION, __VA_ARGS__)

#define _CPPTHINGS_GET_MACRO(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _A, _B, _C, _D, _E, _F, NAME, ...) NAME
#ifdef CPPTHINGS_VA_OPT
#define CPPTHINGS_FOR_EACH(action, ...) CPPTHINGS_FOR_EACH_SEP(action, __VA_OPT__(,) __VA_ARGS__)
#define CPPTHINGS_FOR_EACH_SEP(action, sep, ...) \
  _CPPTHINGS_GET_MACRO(_0 __VA_OPT__(,) __VA_ARGS__, \
            _CPPTHINGS_FE_F,_CPPTHINGS_FE_E,_CPPTHINGS_FE_D,_CPPTHINGS_FE_C, \
            _CPPTHINGS_FE_B,_CPPTHINGS_FE_A,_CPPTHINGS_FE_9,_CPPTHINGS_FE_8, \
            _CPPTHINGS_FE_7,_CPPTHINGS_FE_6,_CPPTHINGS_FE_5,_CPPTHINGS_FE_4, \
            _CPPTHINGS_FE_3,_CPPTHINGS_FE_2,_CPPTHINGS_FE_1,_CPPTHINGS_FE_0)(action, sep __VA_OPT__(,) __VA_ARGS__)
#define CPPTHINGS_FOR_EACH_COMMA(action, ...) \
  _CPPTHINGS_GET_MACRO(_0 __VA_OPT__(,) __VA_ARGS__, \
            _CPPTHINGS_FE_C_F,_CPPTHINGS_FE_C_E,_CPPTHINGS_FE_C_D,_CPPTHINGS_FE_C_C, \
            _CPPTHINGS_FE_C_B,_CPPTHINGS_FE_C_A,_CPPTHINGS_FE_C_9,_CPPTHINGS_FE_C_8, \
            _CPPTHINGS_FE_C_7,_CPPTHINGS_FE_C_6,_CPPTHINGS_FE_C_5,_CPPTHINGS_FE_C_4, \
            _CPPTHINGS_FE_C_3,_CPPTHINGS_FE_C_2,_CPPTHINGS_FE_C_1,_CPPTHINGS_FE_C_0)(action __VA_OPT__(,) __VA_ARGS__)
#else
#define CPPTHINGS_FOR_EACH(action, ...) CPPTHINGS_FOR_EACH_SEP(action, , __VA_ARGS__)
#define CPPTHINGS_FOR_EACH_SEP(action, sep, ...) \
  _CPPTHINGS_GET_MACRO(_0, __VA_ARGS__, \
            _CPPTHINGS_FE_F,_CPPTHINGS_FE_E,_CPPTHINGS_FE_D,_CPPTHINGS_FE_C, \
            _CPPTHINGS_FE_B,_CPPTHINGS_FE_A,_CPPTHINGS_FE_9,_CPPTHINGS_FE_8, \
            _CPPTHINGS_FE_7,_CPPTHINGS_FE_6,_CPPTHINGS_FE_5,_CPPTHINGS_FE_4, \
            _CPPTHINGS_FE_3,_CPPTHINGS_FE_2,_CPPTHINGS_FE_1,_CPPTHINGS_FE_0)(action, sep, __VA_ARGS__)
#define CPPTHINGS_FOR_EACH_COMMA(action, ...) \
  _CPPTHINGS_GET_MACRO(_0, __VA_ARGS__, \
            _CPPTHINGS_FE_C_F,_CPPTHINGS_FE_C_E,_CPPTHINGS_FE_C_D,_CPPTHINGS_FE_C_C, \
            _CPPTHINGS_FE_C_B,_CPPTHINGS_FE_C_A,_CPPTHINGS_FE_C_9,_CPPTHINGS_FE_C_8, \
            _CPPTHINGS_FE_C_7,_CPPTHINGS_FE_C_6,_CPPTHINGS_FE_C_5,_CPPTHINGS_FE_C_4, \
            _CPPTHINGS_FE_C_3,_CPPTHINGS_FE_C_2,_CPPTHINGS_FE_C_1,_CPPTHINGS_FE_C_0)(action, __VA_ARGS__)
#endif

#define _CPPTHINGS_FE_ARG_0(ACTION, SEP, ARG)
#define _CPPTHINGS_FE_ARG_1(ACTION, SEP, ARG, X)       ACTION(ARG, X)
#define _CPPTHINGS_FE_ARG_2(ACTION, SEP, ARG, X, ...)  ACTION(ARG, X) SEP _CPPTHINGS_FE_ARG_1(ACTION, SEP, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_3(ACTION, SEP, ARG, X, ...)  ACTION(ARG, X) SEP _CPPTHINGS_FE_ARG_2(ACTION, SEP, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_4(ACTION, SEP, ARG, X, ...)  ACTION(ARG, X) SEP _CPPTHINGS_FE_ARG_3(ACTION, SEP, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_5(ACTION, SEP, ARG, X, ...)  ACTION(ARG, X) SEP _CPPTHINGS_FE_ARG_4(ACTION, SEP, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_6(ACTION, SEP, ARG, X, ...)  ACTION(ARG, X) SEP _CPPTHINGS_FE_ARG_5(ACTION, SEP, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_7(ACTION, SEP, ARG, X, ...)  ACTION(ARG, X) SEP _CPPTHINGS_FE_ARG_6(ACTION, SEP, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_8(ACTION, SEP, ARG, X, ...)  ACTION(ARG, X) SEP _CPPTHINGS_FE_ARG_7(ACTION, SEP, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_9(ACTION, SEP, ARG, X, ...)  ACTION(ARG, X) SEP _CPPTHINGS_FE_ARG_8(ACTION, SEP, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_A(ACTION, SEP, ARG, X, ...)  ACTION(ARG, X) SEP _CPPTHINGS_FE_ARG_9(ACTION, SEP, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_B(ACTION, SEP, ARG, X, ...)  ACTION(ARG, X) SEP _CPPTHINGS_FE_ARG_A(ACTION, SEP, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_C(ACTION, SEP, ARG, X, ...)  ACTION(ARG, X) SEP _CPPTHINGS_FE_ARG_B(ACTION, SEP, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_D(ACTION, SEP, ARG, X, ...)  ACTION(ARG, X) SEP _CPPTHINGS_FE_ARG_C(ACTION, SEP, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_E(ACTION, SEP, ARG, X, ...)  ACTION(ARG, X) SEP _CPPTHINGS_FE_ARG_D(ACTION, SEP, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_F(ACTION, SEP, ARG, X, ...)  ACTION(ARG, X) SEP _CPPTHINGS_FE_ARG_E(ACTION, SEP, ARG, __VA_ARGS__)

#define _CPPTHINGS_FE_ARG_C_0(ACTION, ARG)
#define _CPPTHINGS_FE_ARG_C_1(ACTION, ARG, X)       ACTION(ARG, X)
#define _CPPTHINGS_FE_ARG_C_2(ACTION, ARG, X, ...)  ACTION(ARG, X), _CPPTHINGS_FE_ARG_C_1(ACTION, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_C_3(ACTION, ARG, X, ...)  ACTION(ARG, X), _CPPTHINGS_FE_ARG_C_2(ACTION, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_C_4(ACTION, ARG, X, ...)  ACTION(ARG, X), _CPPTHINGS_FE_ARG_C_3(ACTION, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_C_5(ACTION, ARG, X, ...)  ACTION(ARG, X), _CPPTHINGS_FE_ARG_C_4(ACTION, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_C_6(ACTION, ARG, X, ...)  ACTION(ARG, X), _CPPTHINGS_FE_ARG_C_5(ACTION, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_C_7(ACTION, ARG, X, ...)  ACTION(ARG, X), _CPPTHINGS_FE_ARG_C_6(ACTION, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_C_8(ACTION, ARG, X, ...)  ACTION(ARG, X), _CPPTHINGS_FE_ARG_C_7(ACTION, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_C_9(ACTION, ARG, X, ...)  ACTION(ARG, X), _CPPTHINGS_FE_ARG_C_8(ACTION, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_C_A(ACTION, ARG, X, ...)  ACTION(ARG, X), _CPPTHINGS_FE_ARG_C_9(ACTION, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_C_B(ACTION, ARG, X, ...)  ACTION(ARG, X), _CPPTHINGS_FE_ARG_C_A(ACTION, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_C_C(ACTION, ARG, X, ...)  ACTION(ARG, X), _CPPTHINGS_FE_ARG_C_B(ACTION, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_C_D(ACTION, ARG, X, ...)  ACTION(ARG, X), _CPPTHINGS_FE_ARG_C_C(ACTION, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_C_E(ACTION, ARG, X, ...)  ACTION(ARG, X), _CPPTHINGS_FE_ARG_C_D(ACTION, ARG, __VA_ARGS__)
#define _CPPTHINGS_FE_ARG_C_F(ACTION, ARG, X, ...)  ACTION(ARG, X), _CPPTHINGS_FE_ARG_C_E(ACTION, ARG, __VA_ARGS__)

#ifdef CPPTHINGS_VA_OPT
#define CPPTHINGS_FOR_EACH_ARG(action, ARG, ...) CPPTHINGS_FOR_EACH_SEP_ARG(action, , ARG __VA_OPT__(,) __VA_ARGS__)
#define CPPTHINGS_FOR_EACH_SEP_ARG(action, SEP, ARG, ...) \
  _CPPTHINGS_GET_MACRO(_0 __VA_OPT__(,) __VA_ARGS__, \
            _CPPTHINGS_FE_ARG_F,_CPPTHINGS_FE_ARG_E,_CPPTHINGS_FE_ARG_D,_CPPTHINGS_FE_ARG_C, \
            _CPPTHINGS_FE_ARG_B,_CPPTHINGS_FE_ARG_A,_CPPTHINGS_FE_ARG_9,_CPPTHINGS_FE_ARG_8, \
            _CPPTHINGS_FE_ARG_7,_CPPTHINGS_FE_ARG_6,_CPPTHINGS_FE_ARG_5,_CPPTHINGS_FE_ARG_4, \
            _CPPTHINGS_FE_ARG_3,_CPPTHINGS_FE_ARG_2,_CPPTHINGS_FE_ARG_1,_CPPTHINGS_FE_ARG_0)(action, SEP, ARG __VA_OPT__(,) __VA_ARGS__)
#define CPPTHINGS_FOR_EACH_COMMA_ARG(action, ARG, ...) \
  _CPPTHINGS_GET_MACRO(_0 __VA_OPT__(,) __VA_ARGS__, \
            _CPPTHINGS_FE_ARG_C_F,_CPPTHINGS_FE_ARG_C_E,_CPPTHINGS_FE_ARG_C_D,_CPPTHINGS_FE_ARG_C_C, \
            _CPPTHINGS_FE_ARG_C_B,_CPPTHINGS_FE_ARG_C_A,_CPPTHINGS_FE_ARG_C_9,_CPPTHINGS_FE_ARG_C_8, \
            _CPPTHINGS_FE_ARG_C_7,_CPPTHINGS_FE_ARG_C_6,_CPPTHINGS_FE_ARG_C_5,_CPPTHINGS_FE_ARG_C_4, \
            _CPPTHINGS_FE_ARG_C_3,_CPPTHINGS_FE_ARG_C_2,_CPPTHINGS_FE_ARG_C_1,_CPPTHINGS_FE_ARG_C_0)(action, ARG __VA_OPT__(,) __VA_ARGS__)
#else
#define CPPTHINGS_FOR_EACH_ARG(action, ARG, ...) CPPTHINGS_FOR_EACH_SEP_ARG(action, , ARG, __VA_ARGS__)
#define CPPTHINGS_FOR_EACH_SEP_ARG(action, SEP, ARG, ...) \
  _CPPTHINGS_GET_MACRO(_0, __VA_ARGS__, \
            _CPPTHINGS_FE_ARG_F,_CPPTHINGS_FE_ARG_E,_CPPTHINGS_FE_ARG_D,_CPPTHINGS_FE_ARG_C, \
            _CPPTHINGS_FE_ARG_B,_CPPTHINGS_FE_ARG_A,_CPPTHINGS_FE_ARG_9,_CPPTHINGS_FE_ARG_8, \
            _CPPTHINGS_FE_ARG_7,_CPPTHINGS_FE_ARG_6,_CPPTHINGS_FE_ARG_5,_CPPTHINGS_FE_ARG_4, \
            _CPPTHINGS_FE_ARG_3,_CPPTHINGS_FE_ARG_2,_CPPTHINGS_FE_ARG_1,_CPPTHINGS_FE_ARG_0)(action, SEP, ARG, __VA_ARGS__)
#define CPPTHINGS_FOR_EACH_COMMA_ARG(action, ARG, ...) \
  _CPPTHINGS_GET_MACRO(_0, __VA_ARGS__, \
            _CPPTHINGS_FE_ARG_C_F,_CPPTHINGS_FE_ARG_C_E,_CPPTHINGS_FE_ARG_C_D,_CPPTHINGS_FE_ARG_C_C, \
            _CPPTHINGS_FE_ARG_C_B,_CPPTHINGS_FE_ARG_C_A,_CPPTHINGS_FE_ARG_C_9,_CPPTHINGS_FE_ARG_C_8, \
            _CPPTHINGS_FE_ARG_C_7,_CPPTHINGS_FE_ARG_C_6,_CPPTHINGS_FE_ARG_C_5,_CPPTHINGS_FE_ARG_C_4, \
            _CPPTHINGS_FE_ARG_C_3,_CPPTHINGS_FE_ARG_C_2,_CPPTHINGS_FE_ARG_C_1,_CPPTHINGS_FE_ARG_C_0)(action, ARG, __VA_ARGS__)
#endif

// because you need like a million concats
#define CPPTHINGS_CONCAT_(A, B) A ## B
#define CPPTHINGS_CONCAT(A, B) CPPTHINGS_CONCAT_(A, B)

#define _CPPTHINGS_DL_0
#define _CPPTHINGS_DL_1(_0, ...) _0
#define _CPPTHINGS_DL_2(_0, _1, ...) _0, _1
#define _CPPTHINGS_DL_3(_0, _1, _2, ...) _0, _1, _2
#define _CPPTHINGS_DL_4(_0, _1, _2, _3, ...) _0, _1, _2, _3
#define _CPPTHINGS_DL_5(_0, _1, _2, _3, _4, ...) _0, _1, _2, _3, _4
#define _CPPTHINGS_DL_6(_0, _1, _2, _3, _4, _5, ...) _0, _1, _2, _3, _4, _5
#define _CPPTHINGS_DL_7(_0, _1, _2, _3, _4, _5, _6, ...) _0, _1, _2, _3, _4, _5, _6
#define _CPPTHINGS_DL_8(_0, _1, _2, _3, _4, _5, _6, _7, ...) _0, _1, _2, _3, _4, _5, _6, _7
#define _CPPTHINGS_DL_9(_0, _1, _2, _3, _4, _5, _6, _7, _8, ...) _0, _1, _2, _3, _4, _5, _6, _7, _8
#define _CPPTHINGS_DL_A(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, ...) _0, _1, _2, _3, _4, _5, _6, _7, _8, _9
#define _CPPTHINGS_DL_B(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _A, ...) _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _A
#define _CPPTHINGS_DL_C(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _A, _B, ...) _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _A, _B
#define _CPPTHINGS_DL_D(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _A, _B, _C, ...) _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _A, _B, _C
#define _CPPTHINGS_DL_E(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _A, _B, _C, _D, ...) _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _A, _B, _C, _D
#define _CPPTHINGS_DL_F(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _A, _B, _C, _D, _E, ...) _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _A, _B, _C, _D, _E

#ifdef CPPTHINGS_VA_OPT
#define CPPTHINGS_DROP_LAST(...) \
  _CPPTHINGS_GET_MACRO(_0 __VA_OPT__(,) __VA_ARGS__, \
      _CPPTHINGS_DL_F,_CPPTHINGS_DL_E,_CPPTHINGS_DL_D,_CPPTHINGS_DL_C, \
      _CPPTHINGS_DL_B,_CPPTHINGS_DL_A,_CPPTHINGS_DL_9,_CPPTHINGS_DL_8, \
      _CPPTHINGS_DL_7,_CPPTHINGS_DL_6,_CPPTHINGS_DL_5,_CPPTHINGS_DL_4, \
      _CPPTHINGS_DL_3,_CPPTHINGS_DL_2,_CPPTHINGS_DL_1,_CPPTHINGS_DL_0)(__VA_ARGS__)
#else
#define CPPTHINGS_DROP_LAST(...) \
  _CPPTHINGS_GET_MACRO(_0, __VA_ARGS__, \
      _CPPTHINGS_DL_F,_CPPTHINGS_DL_E,_CPPTHINGS_DL_D,_CPPTHINGS_DL_C, \
      _CPPTHINGS_DL_B,_CPPTHINGS_DL_A,_CPPTHINGS_DL_9,_CPPTHINGS_DL_8, \
      _CPPTHINGS_DL_7,_CPPTHINGS_DL_6,_CPPTHINGS_DL_5,_CPPTHINGS_DL_4, \
      _CPPTHINGS_DL_3,_CPPTHINGS_DL_2,_CPPTHINGS_DL_1,_CPPTHINGS_DL_0)(__VA_ARGS__)
#endif

#define CPPTHINGS_COMMA ,
