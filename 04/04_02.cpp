#include <algorithm>
#include <cassert>
#include <cmath>
#include <type_traits>

template <typename... Ts> consteval double SumofDoubles(Ts... args) {
  return (... + (std::is_same_v<Ts, double> ? args : 0.0));
}

template <typename... Ts> consteval int CountDoubles([[maybe_unused]] Ts... args) {
  return (... + (std::is_same_v<Ts, double> ? 1 : 0));
}

template <typename... Ts> consteval double AverageOfDoubles(Ts... args) {
  return SumofDoubles(args...) / CountDoubles(args...);
}

template <typename T, typename... Ts>
consteval double MaxOfDoubles(T num, Ts... args) {
  if constexpr (sizeof...(args) > 0) {
    if constexpr (std::is_same_v<T, double>) {
      return std::max(num, MaxOfDoubles(args...));
    } else {
      return MaxOfDoubles(args...);
    }
  } else {
    if constexpr (std::is_same_v<T, double>) {
      return num;
    } else {
      return -INFINITY;
    }
  }
}

template <typename T, typename... Ts>
consteval double MinOfDoubles(T num, Ts... args) {
  if constexpr (sizeof...(args) > 0) {
    if constexpr (std::is_same_v<T, double>) {
      return std::min(num, MinOfDoubles(args...));
    } else {
      return MinOfDoubles(args...);
    }
  } else {
    if constexpr (std::is_same_v<T, double>) {
      return num;
    } else {
      return INFINITY;
    }
  }
}

consteval bool AreEqual(double const &lhs, double const &rhs, double const &e) {
  return (lhs > rhs - e && lhs < rhs + e);
}

consteval void RunTests() {
  constexpr double e = 1e-3;

  constexpr double res = SumofDoubles(1.5, 5, 5, 2.5, 2.0);
  static_assert(AreEqual(res, 6.0, e));

  constexpr double avg_of_doubles = AverageOfDoubles(1.5, 5, 5, 2.5, 2.0);
  static_assert(AreEqual(avg_of_doubles, 2.0, e));

  constexpr double max_of_doubles = MaxOfDoubles(1.0, 2.5, 5, 0.5, 0.5, 3.5, 3);
  static_assert(AreEqual(max_of_doubles, 3.5, e));

  constexpr double min_of_doubles = MinOfDoubles(1.0, 2.5, 5, 0.5, 3.5);
  static_assert(AreEqual(min_of_doubles, 0.5, e));
}

int main() {
  RunTests();
  return 0;
}
