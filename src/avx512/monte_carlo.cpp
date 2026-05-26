#include "pricing/monte_carlo.hpp"

#if defined(__AVX512F__)
#include <immintrin.h>
#endif

#include <cmath>
#include <random>

namespace pricing {

double monte_carlo_scalar(double spot, double strike, double rate, double vol,
                          double t, std::size_t paths, std::uint64_t seed) {
  std::mt19937_64 rng(seed);
  std::normal_distribution<double> normal(0.0, 1.0);
  double sum = 0.0;
  const double drift = (rate - 0.5 * vol * vol) * t;
  const double diffusion = vol * std::sqrt(t);
  for (std::size_t i = 0; i < paths; ++i) {
    const double z = normal(rng);
    const double st = spot * std::exp(drift + diffusion * z);
    sum += std::max(st - strike, 0.0);
  }
  return std::exp(-rate * t) * (sum / static_cast<double>(paths));
}

#if defined(__AVX512F__)
double monte_carlo_avx512(double spot, double strike, double rate, double vol,
                        double t, std::size_t paths, std::uint64_t seed) {
  const std::size_t width = 8;
  const std::size_t blocks = paths / width;
  const double drift = (rate - 0.5 * vol * vol) * t;
  const double diffusion = vol * std::sqrt(t);
  const __m512d v_spot = _mm512_set1_pd(spot);
  const __m512d v_strike = _mm512_set1_pd(strike);
  const __m512d v_drift = _mm512_set1_pd(drift);
  const __m512d v_diff = _mm512_set1_pd(diffusion);
  const __m512d v_zero = _mm512_setzero_pd();

  std::mt19937_64 rng(seed);
  std::normal_distribution<double> normal(0.0, 1.0);
  double sum = 0.0;

  for (std::size_t b = 0; b < blocks; ++b) {
    alignas(64) double z[width];
    for (std::size_t i = 0; i < width; ++i) z[i] = normal(rng);
    __m512d v_z = _mm512_load_pd(z);
    __m512d log_s = _mm512_fmadd_pd(v_diff, v_z, v_drift);
    __m512d s = _mm512_mul_pd(v_spot, _mm512_exp_pd(log_s));
    __m512d payoff = _mm512_sub_pd(s, v_strike);
    payoff = _mm512_max_pd(payoff, v_zero);
    sum += _mm512_reduce_add_pd(payoff);
  }
  return std::exp(-rate * t) * (sum / static_cast<double>(paths));
}
#else
double monte_carlo_avx512(double spot, double strike, double rate, double vol,
                        double t, std::size_t paths, std::uint64_t seed) {
  return monte_carlo_scalar(spot, strike, rate, vol, t, paths, seed);
}
#endif

}  // namespace pricing
