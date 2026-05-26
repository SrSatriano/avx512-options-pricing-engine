#pragma once

#include <cstddef>
#include <cstdint>

namespace pricing {

double monte_carlo_scalar(double spot, double strike, double rate, double vol,
                          double t, std::size_t paths, std::uint64_t seed);

double monte_carlo_avx512(double spot, double strike, double rate, double vol,
                          double t, std::size_t paths, std::uint64_t seed);

}  // namespace pricing
