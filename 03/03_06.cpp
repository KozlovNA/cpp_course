#include <cassert>
#include <cmath>
#include <numbers>
#include <vector>

class Shape {
public:
  virtual ~Shape() = default;
  virtual double perimeter() const = 0;
  virtual double area() const = 0;
};

class Triangle final : public Shape {
public:
  Triangle(double const a, double const b, double const c)
      : a_m(a), b_m(b), c_m(c) {}

  double area() const override final {
    double p = a_m / 2 + b_m / 2 + c_m / 2;
    return std::sqrt(p * (p - a_m) * (p - b_m) * (p - c_m));
  }

  double perimeter() const override final { return a_m + b_m + c_m; }
  ~Triangle() override final = default;

private:
  double const a_m;
  double const b_m;
  double const c_m;
};

class Square final : public Shape {
public:
  Square(double const a) : a_m(a) {}

  double area() const override final { return a_m * a_m; }

  double perimeter() const override final { return 4 * a_m; }

  ~Square() override final = default;

private:
  double const a_m;
};

class Circle final : public Shape {
public:
  Circle(double const r) : r_m(r) {}

  double area() const override final { return std::numbers::pi * r_m * r_m; }

  double perimeter() const override final { return 2 * std::numbers::pi * r_m; }

  ~Circle() override final = default;

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

auto vector_of_shape_test() {
  std::vector<Shape *> arr;
  arr.push_back(new Triangle(3, 4, 5));
  arr.push_back(new Square(3));
  arr.push_back(new Circle(3));

  for (auto &v : arr) {
    delete v;
  }
}

int main() {
  area_test();
  perimeter_test();
  vector_of_shape_test();
  return 0;
}
