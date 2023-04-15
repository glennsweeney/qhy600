
#include "qhy.hpp"

#include <benchmark/benchmark.h>

static void BM_QHY(benchmark::State& state) {
    for (auto _ : state) {
        bool ret = qhy();

        benchmark::DoNotOptimize(ret);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_QHY);
