#include<cmath>
#include<cassert>
#include<array>
#include<numbers>

consteval auto Exp(const double eps) {
  double m = 1;
  double e = 0;
  for (int i = 1; m > eps; i++) {
    e += m;
    m /= i;
  }
  return e;
}

consteval auto AreEqual(double const & lhs, double const & rhs, double const & eps) {
  return (std::abs(lhs - rhs) < eps);
}

int main() {
  
  constexpr std::array<double, 3> epss{1e-2, 1e-8, 1e-16};

  static_assert(AreEqual(Exp(epss[1]), std::numbers::e, epss[1]));

  return 0;
}
