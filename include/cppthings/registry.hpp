#pragma once

#include <shared_mutex>
#include <map>
#include <optional>
// For monostate
#include <variant>

#ifndef CPPTHINGS_CONCAT
#define CPPTHINGS_CONCAT_(A, B) A ## B
#define CPPTHINGS_CONCAT(A, B) CPPTHINGS_CONCAT_(A, B)
#endif

namespace cppthings {
#define CPPTHINGS_EXPOSE_REGISTRY(NAME, KEY_T, VALUE_T) \
  namespace NAME { \
    using key_t = KEY_T; using value_t = VALUE_T; \
    std::map<key_t, value_t, std::less<>>& get_registry(); \
    inline void do_register(key_t key, value_t value) { get_registry().emplace(std::move(key), std::move(value)); } \
    template<typename T> \
    inline std::optional<value_t> do_lookup(T&& key) { \
      auto& reg = get_registry(); \
      auto iter = reg.find(key); \
      return (iter == reg.end()) ? std::nullopt : std::optional<value_t>{iter->second}; \
    } \
  }

#define CPPTHINGS_EXPOSE_CONCURRENT_REGISTRY(NAME, KEY_T, VALUE_T) \
  namespace NAME { \
    using key_t = KEY_T; using value_t = VALUE_T; \
    std::map<key_t, value_t, std::less<>>& get_registry(); \
    std::shared_mutex& get_mutex(); \
    inline void do_register(key_t key, value_t value) { \
      std::shared_lock lock{get_mutex()}; \
      get_registry().emplace(std::move(key), std::move(value)); \
    } \
    template<typename T> \
    inline std::optional<value_t> do_lookup(T&& key) { \
      std::unique_lock lock{get_mutex()}; \
      auto& reg = get_registry(); \
      auto iter = reg.find(key); \
      return (iter == reg.end()) ? std::nullopt : std::optional<value_t>{iter->second}; \
    } \
  }

#define CPPTHINGS_REGISTER(NAME, KEY, VALUE) \
  static std::monostate CPPTHINGS_CONCAT(_cppthings_reged_, __COUNTER__) = (NAME::do_register(KEY, VALUE), std::monostate{});

#define CPPTHINGS_LOOKUP(NAME, KEY) NAME::do_lookup(KEY)

#define CPPTHINGS_IMPL_REGISTRY(NAME) \
  namespace NAME { \
    std::map<key_t, value_t, std::less<>>& get_registry() { \
      static std::map<key_t, value_t, std::less<>> map; \
      return map; \
    } \
  }

#define CPPTHINGS_IMPL_REGISTRY_CONCURRENT(NAME) \
  namespace NAME { \
    std::map<key_t, value_t, std::less<>>& get_registry() { \
      static std::map<key_t, value_t, std::less<>> map; \
      return map; \
    } \
    std::shared_mutex& get_mutex() { \
      static std::shared_mutex mutex; \
      return mutex; \
    } \
  }
}
