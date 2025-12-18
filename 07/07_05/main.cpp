#include <algorithm>
#include <vector>
#include <random>
#include <benchmark/benchmark.h>

template<typename T>
void order(std::vector<T> &vector, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        for (int j = i; j > left; --j) {
            if (vector[j] < vector[j - 1]) {
                std::swap(vector[j], vector[j - 1]);
            } else {
                break; 
            }
        }
    }
}

static std::random_device rd;
static std::mt19937 gen(rd());

int generateRandomPivot(int low, int high) {
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

template<typename T>
void quick_sort(std::vector<T> &arr, int low, int high, int threshold) {
    if (low < high) {
        if (high - low + 1 <= threshold) {
            order(arr, low, high);
            return;
        }

        int pivotIndex = generateRandomPivot(low, high);
        T pivotValue = arr[pivotIndex];

        std::swap(arr[pivotIndex], arr[high]);

        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivotValue) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }

        std::swap(arr[i + 1], arr[high]);

        quick_sort(arr, low, i, threshold);
        quick_sort(arr, i + 2, high, threshold);
    }
}

static void BM_HybridSort_ReverseSorted(benchmark::State& state) {
    const size_t N = 100000;
    
    int threshold = state.range(0);

    std::vector<double> src(N);
    for (size_t i = 0; i < N; ++i) {
        src[i] = static_cast<double>(N - i);
    }

    for (auto _ : state) {
        state.PauseTiming();
        std::vector<double> data = src;
        state.ResumeTiming();

        quick_sort(data, 0, static_cast<int>(data.size() - 1), threshold);
    }
    
    state.SetItemsProcessed(state.iterations() * N);
}

BENCHMARK(BM_HybridSort_ReverseSorted)
    ->Arg(0)
    ->Arg(1)
    ->Arg(2)
    ->Arg(3)
    ->Arg(4)
    ->Arg(5)
    ->Arg(6)
    ->Arg(7)
    ->Arg(8)
    ->Arg(16)  
    ->Arg(32)
    ->Arg(64)
    ->Arg(128);

BENCHMARK_MAIN();
