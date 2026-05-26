# Análise de cache misses

## Hipóteses

1. Loop scalar: branch mispredict em `max(S-K,0)`
2. AVX-512: alinhamento de 64 bytes nas cargas de `z[]`
3. RNG: gargalo compartilhado — considerar Philox SIMD

## VTune

```bash
vtune -collect memory-access -result-dir vtune_mem -- ./build/bench_pricing
```

Interpretar **DRAM Bound** vs **L1 Bound** no Bottom-up.
