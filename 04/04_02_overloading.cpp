//NOTHING EVER WORKS WITH THIS ONE 

#include <algorithm>
#include <cassert>
#include <cmath>
#include <type_traits>

template <typename T, typename... Ts>
consteval double SumofDoubles(T d, Ts... args) {
  return SumofDoubles(args...);
}


template <typename... Ts> consteval double SumofDoubles(double d, Ts... args) {
  return d + SumofDoubles(args...);
}
template <> consteval double SumofDoubles<double>(double d) { return d; }

consteval bool AreEqual(double const &lhs, double const &rhs, double const &e) {
  return (lhs > rhs - e && lhs < rhs + e);
}

consteval void RunTests() {
  constexpr double e = 1e-3;

  constexpr double res = SumofDoubles(1.1, 5, 5, 2.5, 2.0);
  static_assert(AreEqual(res, 6.0, e));
}
int main() {
  RunTests();
  return 0;
}
