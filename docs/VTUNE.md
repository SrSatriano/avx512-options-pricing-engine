# Intel VTune

## Instalação

Instale oneAPI Base Toolkit e VTune Profiler.

## Fluxo

1. Build Release com `-g`
2. Profile Hotspots → identificar `monte_carlo_*`
3. Memory Access → cache lines por kernel
4. Comparar scalar vs AVX-512 no mesmo hardware
