#include <cmath>
#include <iostream>

int main() {
  double a = 0, b = 0, c = 0;
  std::cin >> a >> b >> c;
  double const eps = 1e-6;
  double D = b * b - 4 * a * c;

  if (std::abs(a) < eps) {
    if (std::abs(b) < eps) {
      if (std::abs(c) < eps) {
        std::cout << "x_1, x_2 = (-inf, +inf) \n";
      } else {
        std::cout << "no roots\n";
      }
    } else {
      if (std::abs(c) < eps) {
        std::cout << "x_1, x_2 = 0\n";
      } else {
        std::cout << "x_1, x_2 = " << -c / b << '\n';
      }
    }
  } else {
    if (std::abs(D) < eps) {
      std::cout << "x_1, x_2 = " << (-b) / (2 * a) << '\n';
    } else if (D < 0) {
      std::cout << "no real roots : D < 0 \n";
    } else if (D > 0) {
      double sqrt_D = std::sqrt(D);
      std::cout << "x_1 = " << (-b + sqrt_D) / (2 * a) << '\n';
      std::cout << "x_2 = " << (-b - sqrt_D) / (2 * a) << '\n';
    }
  }
}
