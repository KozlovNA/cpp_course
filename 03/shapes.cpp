#include <iostream>
#include <vector>

class Shape {
public:
  Shape(double a, double b) : m_a(a), m_b(b) {}
  virtual ~Shape() = default;
  virtual double perimeter() const = 0;

protected:
  double m_a = 0, m_b = 0;
};

class Rectangle : public Shape {
public:
  Rectangle(double a, double b) : Shape(a, b) {};

  double perimeter() const override final { return 2 * m_a + 2 * m_b; }
};

class Square final : public Rectangle {
public:
  Square(double a) : Rectangle(a, a) {}
};

int main() {
  std::vector<Shape *> shapes;
  shapes.push_back(new Square(5));

  for (auto & shape : shapes) {
    std::cout << shape->perimeter();
    delete shape;
  }
}
