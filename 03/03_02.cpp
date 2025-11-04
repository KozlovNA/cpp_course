#include <cassert>
#include <cmath>
#include <iostream>

class Triangle {
public:
  Triangle(double const a, double const b, double const c)
      : a_m(a), b_m(b), c_m(c) {}

  auto area() {
    double p = a_m / 2 + b_m / 2 + c_m / 2;
    return std::sqrt(p * (p - a_m) * (p - b_m) * (p - c_m));
  }

  auto perimeter() { return a_m + b_m + c_m; }

private:
  double const a_m;
  double const b_m;
  double const c_m;
};

class Square {
public:
  Square(double const a) : a_m(a) {}

  auto area() { return a_m * a_m; }

  auto perimeter() { return 4 * a_m; }

private:
  double const a_m;
};

class Circle {
public:
  Circle(double const r) : r_m(r) {}

  auto area() { return std::numbers::pi * r_m * r_m; }

  auto perimeter() { return 2 * std::numbers::pi * r_m; }

private:
  double const r_m;
};

auto area_test() {
  Triangle tri(3, 4, 5);
  Square squ(3);
  Circle cir(3);
  double epsilon = 1e-8;

  assert(std::abs(tri.area() - 6.0) < epsilon);
  assert(std::abs(squ.area() - 9.0) < epsilon);
  assert(std::abs(cir.area() - std::numbers::pi * 9.0) < epsilon);
}

auto perimeter_test() {
  Triangle tri(3, 4, 5);
  Square squ(3);
  Circle cir(3);
  double epsilon = 1e-8;

  assert(std::abs(tri.perimeter() - 12.0) < epsilon);
  assert(std::abs(squ.perimeter() - 12.0) < epsilon);
  assert(std::abs(cir.perimeter() - std::numbers::pi * 6.0) < epsilon);
}

int main() {
  area_test();
  perimeter_test();
  return 0;
}
