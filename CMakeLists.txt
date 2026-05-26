cmake_minimum_required(VERSION 3.20)
project(avx512_options_pricing VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_library(pricing
  src/avx512/monte_carlo.cpp
  src/scalar/black_scholes.cpp
)
target_include_directories(pricing PUBLIC include)

add_executable(bench_pricing benchmarks/bench_pricing.cpp)
target_link_libraries(bench_pricing PRIVATE pricing)

add_executable(pricing_test tests/pricing_test.cpp)
target_link_libraries(pricing_test PRIVATE pricing)

enable_testing()
add_test(NAME pricing_unit COMMAND pricing_test)
