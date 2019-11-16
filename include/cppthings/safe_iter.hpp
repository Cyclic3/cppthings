#pragma once

#include <iterator>

namespace cppthings::safe_iter {
  template<typename Iter, typename DistanceT = typename std::iterator_traits<Iter>::distance_type>
  bool safe_advance(Iter& i, const Iter& end, DistanceT n) {
    if (end - i < n)
      return false;
    else {
      std::advance(i, n);
      return true;
    }
  }

  /// Applies repeated iteration, rather than advancing
  ///
  /// More efficient for when distance calculations are hard for some reason,
  /// and the distance is short
  template<typename Iter, typename DistanceT = typename std::iterator_traits<Iter>::distance_type>
  bool safe_forward_small(Iter& i, const Iter& end, DistanceT n) {
    if (i == end)
      return false;

    while (n != 0) {
      if (++i == end)
        return false;
      --n;
    }

    return true;
  }
}
