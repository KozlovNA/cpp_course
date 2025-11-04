#include <algorithm>
#include <cmath>
#include <iostream>

int main() {
  double *array = new double[0];
  std::size_t size = 0;
  std::size_t capacity = 0;
  std::size_t n = 0;
  std::cin >> n;
  for (auto i = 0uz; i < n; i++) {
    size++;
    if ((!(size < capacity)) && (capacity != 0)) {
      double *array_t = new double[capacity * 2];

      for (auto j = 0uz; j < size-1; j++) {
        array_t[j] = array[j];
      }

      std::swap(array, array_t);

      capacity*=2;

      delete[] array_t;

    } else if (capacity == 0) {

      double *array_t = new double[1];

      std::swap(array, array_t);

      capacity++;

      delete[] array_t;
    }

    std::cin >> array[i];
  }

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
  delete[] array;
}
