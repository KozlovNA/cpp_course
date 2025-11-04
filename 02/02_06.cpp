#include <algorithm>
#include <cmath>
#include <iostream>

int main() {
  double array[]{1, 2, 3, 4, 5}; // нужно сделать динамическое выделение памяти
  size_t size = std::size(array);

  double min = array[0];
  double max = array[0];

  double sum = 0;

  for (size_t i = 0; i < size; i++) {
    min = std::min(min, array[i]);
    max = std::max(max, array[i]);
    sum += array[i];
  }

  sum /= size;

  double s = 0;

  for (size_t i = 0; i < size; i++) {
    s += (array[i] - sum) * (array[i] - sum);
  }

  s /= size;
  s = std::sqrt(s);

  std::cout << "Минимальное значение: " << min << '\n';
  std::cout << "Максимальное значение: " << max << '\n';
  std::cout << "Среднее арифметическое: " << sum << '\n';
  std::cout << "Стандартное отклонение: " << s << '\n';
}
