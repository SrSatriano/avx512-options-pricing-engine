#include "pricing/black_scholes.hpp"

#include <cmath>

namespace pricing {

namespace {
double norm_cdf(double x) { return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0))); }
}  // namespace

double black_scholes_call(double spot, double strike, double rate, double vol, double t) {
  if (t <= 0.0 || vol <= 0.0) return std::max(spot - strike, 0.0);
  const double sqrt_t = std::sqrt(t);
  const double d1 =
      (std::log(spot / strike) + (rate + 0.5 * vol * vol) * t) / (vol * sqrt_t);
  const double d2 = d1 - vol * sqrt_t;
  return spot * norm_cdf(d1) - strike * std::exp(-rate * t) * norm_cdf(d2);
}

}  // namespace pricing
