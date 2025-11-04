#include<iostream>
#include<cmath>
#include<cassert>

int main() {
  const double eps = 1e-6;
  double m = 1;
  double e = 0;

  for (int i = 1; m > eps; i++) {
    e += m;
    m /= i;
  }
  std::cout << e << '\n';
}
