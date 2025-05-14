#include <benchmark/benchmark.h>
#include <vector>

void do_something()
{
    std::vector<int> vec;
    for (int i = 0; i < 1000; ++i)
    {
        vec.push_back(i); // 每次调用 push_back
    }
}

static void loop_test(benchmark::State &state)
{
    for (auto _ : state)
    {
        do_something();
    }
}
BENCHMARK(loop_test);

// 主函数，初始化并运行基准测试
BENCHMARK_MAIN();
