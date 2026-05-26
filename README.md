<div align="center">

# Motor de precificação de opções AVX-512

**Motor de precificação de opções AVX-512**

<p>
  <a href="https://github.com/SrSatriano/avx512-options-pricing-engine"><img src="https://img.shields.io/badge/GitHub-avx512-options-pricing-engine-24292e?style=for-the-badge&logo=github&logoColor=white" alt="GitHub" /></a>
</p>

<p>
  <img src="https://img.shields.io/badge/versão-1.0.0-0ea5e9?style=flat-square" alt="versão" />
  <img src="https://img.shields.io/badge/licença-MIT-22c55e?style=flat-square" alt="licença" />
  <img src="https://img.shields.io/badge/idioma-pt--BR-blue?style=flat-square" alt="idioma" />
  <img src="https://img.shields.io/badge/CI-GitHub_Actions-8b5cf6?style=flat-square" alt="ci" />
</p>

<p><strong>Monte Carlo e Black-Scholes vetorizados sem GPU.</strong></p>

<p>
  Autor: <a href="https://github.com/SrSatriano">@SrSatriano</a> ·
  Release <strong>1.0.0</strong> (2026-03-26)
</p>

</div>

---

## Índice

1. [Visão geral](#visão-geral)
2. [Problema e solução](#problema-e-solução)
3. [Para quem é](#para-quem-é)
4. [Casos de uso](#casos-de-uso)
5. [Funcionalidades](#funcionalidades)
6. [Stack tecnológica](#stack-tecnológica)
7. [Arquitetura](#arquitetura)
8. [Estrutura do repositório](#estrutura-do-repositório)
9. [Pré-requisitos](#pré-requisitos)
10. [Instalação e execução](#instalação-e-execução)
11. [Configuração](#configuração)
12. [Testes](#testes)
13. [Performance](#performance)
14. [Deploy e operação](#deploy-e-operação)
15. [Limitações conhecidas](#limitações-conhecidas)
16. [Roadmap](#roadmap)
17. [Documentação complementar](#documentação-complementar)
18. [Segurança e licença](#segurança-e-licença)

---

## Visão geral

Este repositório faz parte do **portfólio de engenharia** mantido por [@SrSatriano](https://github.com/SrSatriano). A versão **1.0.0** entrega implementação do núcleo do produto, testes automatizados, pipeline de integração contínua e documentação operacional em **português brasileiro**.

O objetivo é permitir que você clone, execute e evolua o projeto com clareza — do desenvolvimento local ao deploy em produção.

## Problema e solução

| | |
|---|---|
| **Problema** | Precificar milhões de cenários em CPU pura é lento sem SIMD. |
| **Solução** | Kernels 8-wide com fallback escalar e benchmarks comparativos. |

## Para quem é

Quants, engenheiros de performance e desks de opções.

## Casos de uso

- Greeks em batch
- Stress de volatilidade

## Funcionalidades

- [x] Black-Scholes escalar e vetorizado
- [x] Monte Carlo AVX-512
- [x] Benchmark integrado
- [x] Flags GCC/Clang documentadas
- [x] Fallback automático sem AVX-512

## Stack tecnológica

| Camada | Tecnologias |
|--------|-------------|
| **Principal** | C++20, AVX-512, CMake |

## Arquitetura

```mermaid
flowchart LR
  IN[Parâmetros opções] --> SC[Kernel escalar]
  IN --> AVX[Kernel AVX-512]
  SC --> BEN[Benchmark]
  AVX --> BEN
```

Detalhamento de componentes, fluxos de dados e decisões de design: [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md).

## Estrutura do repositório

| Caminho | Descrição |
|---------|-----------|
| `src/scalar/` | Implementação de referência |
| `src/avx512/` | Kernels SIMD |
| `tests/pricing_test.cpp` | Testes |

## Pré-requisitos

CMake 3.20+, CPU com AVX-512 (opcional; usa escalar).

## Instalação e execução

```bash
git clone https://github.com/SrSatriano/avx512-options-pricing-engine.git
cd avx512-options-pricing-engine
```

```bash
cmake -B build && cmake --build build
./build/bench_pricing
```

## Configuração

_Este projeto não exige variáveis obrigatórias além das credenciais locais em `.env`._

> **Importante:** nunca faça commit de arquivos `.env` com segredos reais. Use `.env.example` como referência.

## Testes

Execute a suíte de testes antes de abrir pull requests:

```bash
ctest --test-dir build
```

A pipeline [`.github/workflows/ci.yml`](.github/workflows/ci.yml) repete build e testes em cada push para `main`.

## Performance

| Speedup AVX-512 | 7,0× vs escalar |

Metodologia, hardware de referência e flags de compilação: [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md).

## Deploy e operação

| Guia | Conteúdo |
|------|----------|
| [docs/DEPLOYMENT.md](docs/DEPLOYMENT.md) | Homologação, produção e rollback |
| [docs/OPERATIONS.md](docs/OPERATIONS.md) | Monitoramento, alertas e incidentes |

## Limitações conhecidas

- Resultados numéricos variam levemente por ordem SIMD

## Roadmap

- Suporte a americana via árvore binomial SIMD

## Documentação complementar

| Documento | Descrição |
|-----------|-----------|
| [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) | Arquitetura e decisões técnicas |
| [docs/DEPLOYMENT.md](docs/DEPLOYMENT.md) | Deploy passo a passo |
| [docs/OPERATIONS.md](docs/OPERATIONS.md) | Runbook operacional |
| [CONTRIBUTING.md](CONTRIBUTING.md) | Como contribuir |
| [CHANGELOG.md](CHANGELOG.md) | Histórico de versões |
| [SECURITY.md](SECURITY.md) | Política de segurança |
| [AUTHORS.md](AUTHORS.md) | Créditos |

## Segurança e licença

- Dependências revisadas na release **1.0.0**
- Vulnerabilidades: siga [SECURITY.md](SECURITY.md)
- Licença: [MIT](LICENSE) © SrSatriano 2026

---

<p align="center">Desenvolvido com foco em clareza e engenharia de produção · <a href="https://github.com/SrSatriano/avx512-options-pricing-engine">Ver no GitHub</a></p>
