cmake_minimum_required(VERSION 3.20)
project(avx512_options_pricing VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_library(pricing src/avx512/monte_carlo.cpp)
target_include_directories(pricing PUBLIC include)

add_executable(bench_pricing benchmarks/bench_pricing.cpp)
target_link_libraries(bench_pricing PRIVATE pricing)
