#include<iostream>
#include<cmath>
#include<cassert>

int main() {
  int x = 0;

  std::cin >> x;

  const auto s = std::sqrt(5);
  const auto f1 = ( 1 + s ) / 2;
  const auto f2 = ( 1 - s ) / 2;
  
  double f = (std::pow(f1, x) - std::pow(f2, x)) / s;

  std::cout << static_cast< int > (std::round(f)) << '\n';
}
