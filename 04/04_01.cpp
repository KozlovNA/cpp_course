#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

struct Player {
    std::size_t eff = 0;
    std::size_t num = 0;
};

auto operator<(Player const& lhs, Player const& rhs) {
    return lhs.eff < rhs.eff;
}

template<typename T>
void order(std::vector<T> &vector, std::size_t left, std::size_t right) {
  for (auto i = left + 1; i <= right; ++i) {
    for (auto j = i; j > left; --j) {
      if (vector[j] < vector[j - 1]) {
        std::swap(vector[j], vector[j - 1]);
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
void quick_sort(std::vector<T> &arr, int low, int high) {
  if (low < high) {
    if (high - low + 1 <= 16) {
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

    quick_sort(arr, low, i);
    quick_sort(arr, i + 2, high);
  }
}

int main() {
  auto size = 1'000uz;
  std::vector<Player> vector(size);

  for (std::size_t i = 0; i < size; ++i) {
    vector[i].num = i;
    std::uniform_int_distribution<> dist(0, 100);
    vector[i].eff = dist(gen); 
  }

  quick_sort(vector, 0, static_cast<int>(vector.size() - 1));

  assert(std::ranges::is_sorted(vector, [](auto lhs, auto rhs){return lhs < rhs;}));
  return 0;
}


