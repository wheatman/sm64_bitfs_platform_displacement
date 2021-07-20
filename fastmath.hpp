/*
 * A bunch of fast math functions. And I mean REALLY fast.
 * 
 */
 
#ifndef _FASTMATH_HPP_
#define _FASTMATH_HPP_

#include <array>
#include <utility>

namespace fast {
  /**
   * Finds sqrt(x) for up to 4 simultaneous values, returning a new array.
   */
  std::array<float, 4> sqrt_x4(const std::array<float, 4>& in);
  
  /**
   * Finds sqrt(x) for up to 4 simultaneous values. Returns results in-place.
   */
  std::array<float, 4>& sqrt_x4_ip(std::array<float, 4>& in);
}
void test() {
  fast::sqrt_x4({1, 4, 9});
}

#endif