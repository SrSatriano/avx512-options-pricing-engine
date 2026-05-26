# Benchmarks

## Metodologia

- CPU pinned: `taskset -c 0-7`
- Governor performance
- 5 runs, reportar mediana

## Métricas

- **Throughput**: paths / segundo
- **Latência**: tempo para N paths fixo
- **Speedup**: scalar_time / avx_time

## Black-Scholes

Benchmark separado em `bench_black_scholes` (futuro) para call europeu fechado.
