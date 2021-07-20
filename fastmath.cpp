#include "fastmath.hpp"
#include <immintrin.h>
#include <xmmintrin.h>

std::array<float, 4> fast::sqrt_x4(const std::array<float, 4>& in) {
  std::array<float, 4> out;
  __m128 a = _mm_load_ps(&in[0]);
  a = _mm_sqrt_ps(a);
  _mm_store_ps(&out[0], a);
  return out;
}

std::array<float, 4>& fast::sqrt_x4_ip(std::array<float, 4>& in) {
  __m128 a = _mm_load_ps(&in[0]);
  a = _mm_sqrt_ps(a);
  _mm_store_ps(&in[0], a);
  return in;
}