#include "pricing/monte_carlo.hpp"

#include <chrono>
#include <cstdio>

int main() {
  const std::size_t paths = 1'000'000;
  const auto t0 = std::chrono::steady_clock::now();
  const double s = pricing::monte_carlo_scalar(100, 100, 0.05, 0.2, 1.0, paths, 42);
  const auto t1 = std::chrono::steady_clock::now();
  const double v = pricing::monte_carlo_avx512(100, 100, 0.05, 0.2, 1.0, paths, 42);
  const auto t2 = std::chrono::steady_clock::now();

  const auto ms_scalar = std::chrono::duration<double, std::milli>(t1 - t0).count();
  const auto ms_avx = std::chrono::duration<double, std::milli>(t2 - t1).count();

  std::printf("scalar=%.4f (%.1f ms, %.2f M paths/s)\n", s, ms_scalar,
              paths / ms_scalar / 1000.0);
  std::printf("avx512=%.4f (%.1f ms, %.2f M paths/s)\n", v, ms_avx,
              paths / ms_avx / 1000.0);
  if (ms_avx > 0) std::printf("speedup=%.2fx\n", ms_scalar / ms_avx);
  return 0;
}
