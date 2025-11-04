#include <iostream>
#include <vector>

unsigned long long int next_number(unsigned long long int const n_i) {
  return n_i % 2 == 1 ? 3 * n_i + 1 : n_i / 2;
}

std::size_t collatz_length(unsigned long long int const num) {
  static std::vector<std::size_t> lengths(100, 0);
  if (num == 1) {
    lengths[0] = 1;
  } else {
    auto nn = next_number(num); // nn - next_number
    if (nn > lengths.capacity()) {
      lengths.resize(nn);
    }
    std::vector<unsigned long long int> new_numbers(1, num);
    while (lengths[nn - 1] == 0) {
      new_numbers.push_back(nn);
      nn = next_number(nn);
      if (nn > lengths.capacity()) {
        lengths.resize(nn);
      }
    }
    auto kl = lengths[nn - 1];
    std::size_t inc = new_numbers.size();
    for (auto const &i : new_numbers) {
      lengths[i - 1] = kl + inc;
      inc--;
    }
  }
  return lengths[num-1];
}

int main() {
  collatz_length(1); //initialize lengths[0] in static vector
  std::size_t max_l = 0;
  for (std::size_t num = 1; num <= 100; num++){
    max_l = std::max(max_l, collatz_length(num));
  }
  std::cout << max_l << '\n';
  return 0;
}
