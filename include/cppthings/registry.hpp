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
    void do_register(key_t key, value_t value); \
    std::optional<value_t> do_lookup(key_t key); \
  }

#define CPPTHINGS_REGISTER(NAME, KEY, VALUE) \
  static std::monostate CPPTHINGS_CONCAT(_cppthings_reged_, __COUNTER__) = (NAME::do_register(KEY, VALUE), std::monostate{});

#define CPPTHINGS_LOOKUP(NAME, KEY) NAME::do_lookup(KEY);

#define CPPTHINGS_IMPL_REGISTRY(NAME) \
  namespace NAME { \
    static std::map<key_t, value_t>& get_registry() { \
      static std::map<key_t, value_t> map; \
      return map; \
    } \
    void do_register(key_t key, value_t value) { get_registry().emplace(std::move(key), std::move(value)); } \
    std::optional<value_t> do_lookup(key_t key) { \
      auto& reg = get_registry(); \
      auto iter = reg.find(key); \
      return (iter == reg.end()) ? std::nullopt : std::optional<value_t>{iter->second}; \
    } \
  }

#define CPPTHINGS_IMPL_REGISTRY_CONCURRENT(NAME) \
  namespace NAME { \
    static std::map<key_t, value_t>& get_registry() { \
      static std::map<key_t, value_t> map; \
      return map; \
    } \
    static std::shared_mutex& get_mutex() { \
      static std::shared_mutex mutex; \
      return mutex; \
    } \
    void do_register(key_t key, value_t value) { \
      std::shared_lock lock{get_mutex()}; \
      get_registry().emplace(std::move(key), std::move(value)); \
    } \
    std::optional<value_t> do_lookup(key_t key) { \
      std::unique_lock lock{get_mutex()}; \
      auto& reg = get_registry(); \
      auto iter = reg.find(key); \
      return (iter == reg.end()) ? std::nullopt : std::optional<value_t>{iter->second}; \
    } \
  }
}
