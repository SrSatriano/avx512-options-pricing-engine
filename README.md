# AVX-512 Options Pricing Engine

Motor de precificação de derivativos que utiliza exclusivamente instruções vetoriais AVX-512 em CPUs multicore — Monte Carlo e Black-Scholes sem GPU.

## Stack

- C++20, Intel AVX-512 intrinsics
- Intel VTune (profiling)
- GCC / Clang

## Benchmarks de throughput

| Modo | Paths/s (1M simulações) | Speedup |
|------|---------------------------|---------|
| Scalar | ~2.1M | 1.0× |
| AVX-512 (8-wide) | ~14.8M | ~7.0× |

Executar: `./build/bench_pricing --paths=1000000 --mode=both`

## Cache misses (VTune)

1. Compile com `-g` e flags de debug info.
2. `vtune -collect memory-access ./build/bench_pricing`
3. Foco: L1 miss rate no loop de Box-Muller — ver [docs/VTUNE.md](docs/VTUNE.md)

## Compilação

```bash
# GCC
cmake -B build -DCMAKE_CXX_FLAGS="-O3 -march=native -mavx512f -mavx512dq"

# Clang
cmake -B build -DCMAKE_CXX_COMPILER=clang++ \
  -DCMAKE_CXX_FLAGS="-O3 -march=native -mavx512f"
```

Documentação: [docs/BENCHMARKS.md](docs/BENCHMARKS.md) | [docs/CACHE_ANALYSIS.md](docs/CACHE_ANALYSIS.md)

## Estrutura

| Pasta | Conteúdo |
|-------|----------|
| `src/scalar/` | Black-Scholes / MC referência |
| `src/avx512/` | Kernels vetorizados |
| `benchmarks/` | Comparativo scalar vs SIMD |
| `include/` | APIs públicas |
