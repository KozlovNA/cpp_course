//////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <numeric>
#include <ranges>
#include <iostream>
#include <type_traits>

//////////////////////////////////////////////////////////////////////////////////////////

template <int N = 0, int D = 1> struct Ratio {
  constexpr static auto num = N;

  constexpr static auto den = D;
};

//////////////////////////////////////////////////////////////////////////////////////////

template <typename R1, typename R2> struct Sum {
  constexpr static auto num = R1::num * R2::den + R2::num * R1::den;

  constexpr static auto den = R1::den * R2::den;

  constexpr static auto common_divisor = std::gcd(num, den);

  //  ------------------------------------------------------------------

  using type = Ratio<num / common_divisor, den / common_divisor>;
};

template <typename R1, typename R2> struct Mul {
  constexpr static auto num = R1::num * R2::num;
  constexpr static auto den = R1::den * R2::den;
  constexpr static auto common_divisor = std::gcd(num, den);
  using type = Ratio<num / common_divisor, den / common_divisor>;
};

template <typename R1, typename R2> struct Sub {
  using type = Sum<R1, Mul<R2, Ratio<-1>>>::type;
};

template <typename R1, typename R2> struct Div {
  static_assert(R2::num != 0);
  using type = Mul<R1, Ratio<R2::den, R2::num>>::type;
};

//////////////////////////////////////////////////////////////////////////////////////////

template <typename R1, typename R2> using sum      = typename Sum<R1, R2>::type;
template <typename R1, typename R2> using mul      = typename Mul<R1, R2>::type;
template <typename R1, typename R2> using sub      = typename Sub<R1, R2>::type;
template <typename R1, typename R2> using divide = typename Div<R1, R2>::type;

//////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename R = Ratio<1>> struct Duration {
  T x = T();
};

//////////////////////////////////////////////////////////////////////////////////////////

template <typename T1, typename R1,

          typename T2, typename R2>
constexpr auto operator+(Duration<T1, R1> const &lhs,
                         Duration<T2, R2> const &rhs) {
  using ratio_t = Ratio<1, sum<R1, R2>::den>;

  auto x = (lhs.x * ratio_t::den / R1::den * R1::num +

            rhs.x * ratio_t::den / R2::den * R2::num);

  return Duration<decltype(x), ratio_t>(x);
}

template <typename T1, typename R1,

          typename T2, typename R2>
constexpr auto operator-(Duration<T1, R1> const &lhs,
                         Duration<T2, R2> const &rhs) {
  auto tmp = rhs;
  tmp.x *= -1;
  return lhs+tmp;
}

//////////////////////////////////////////////////////////////////////////////////////////

int main() {
  auto x = 1, y = 2;

  //  ----------------------------------------------------------------------

  Duration<int, Ratio<1, 2>> duration_1(x);

  Duration<int, Ratio<1, 3>> duration_2(y);

  //  ----------------------------------------------------------------------

  Duration<int, Ratio<1, 6>> duration_3 = duration_1 + duration_2;

  //  ----------------------------------------------------------------------

  assert(duration_3.x == 7);

  Duration<int, Ratio<1,6>> duration_4 = duration_2 - duration_1;
  assert(duration_4.x == 1);

  //  ----------------------------------------------------------------------
  
  using ratio_1 = Ratio<1,2>;
  using ratio_2 = Ratio<1,3>;

  static_assert(std::is_same_v<sum    <ratio_1, ratio_2>, Ratio<5, 6>>);
  static_assert(std::is_same_v<sub    <ratio_1, ratio_2>, Ratio<1, 6>>);
  static_assert(std::is_same_v<mul    <ratio_1, ratio_2>, Ratio<1, 6>>);
  static_assert(std::is_same_v<divide <ratio_1, ratio_2>, Ratio<3, 2>>);
}

//////////////////////////////////////////////////////////////////////////////////////////
