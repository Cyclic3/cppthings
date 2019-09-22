#pragma once

//! GSL has a more complex version of this, but GSL is big

#include <memory>
#include <functional>

namespace cppthings {
  // I could write this myself, but I would mess it up. So let's hijack a completely different construct ;)
  inline std::unique_ptr<void, std::function<void(void)>> defer(std::function<void(void)> f) {
    return {nullptr, f};
  }
}

