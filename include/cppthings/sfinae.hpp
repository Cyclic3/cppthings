#pragma once

#include <utility>
#include <variant>

//! A bunch of SFINAE that I stole from SO

namespace cppthings {
  // SOURCE: based off https://stackoverflow.com/a/45892305
  template<typename T, typename Variant>
  struct is_in_variant;

  // SOURCE: based off https://stackoverflow.com/a/45892305
  template<typename T, typename... AllT>
  struct is_in_variant<T, std::variant<AllT...>>
    : public std::disjunction<std::is_same<T, AllT>...> {};

  template<typename T, typename Variant>
  constexpr bool is_in_variant_v = is_in_variant<T, Variant>::value;
}
