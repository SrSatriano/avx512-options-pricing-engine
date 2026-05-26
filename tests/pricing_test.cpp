#include "pricing/black_scholes.hpp"
#include "pricing/monte_carlo.hpp"

#include <cassert>
#include <cmath>
#include <cstdio>

int main() {
  const double spot = 100, strike = 100, rate = 0.05, vol = 0.2, t = 1.0;
  const double bs = pricing::black_scholes_call(spot, strike, rate, vol, t);
  const double mc =
      pricing::monte_carlo_scalar(spot, strike, rate, vol, t, 200000, 42);
  assert(bs > 0);
  assert(std::abs(bs - mc) < 2.0);
  std::printf("black_scholes=%.4f monte_carlo=%.4f\n", bs, mc);
  std::puts("pricing_test: OK");
  return 0;
}
