#include <iostream>

int main() {
  char cv;
  std::cin >> cv;

  switch (cv) {
  [[likely]] case 'A' ... 'Z': {
    std::cout << "Заглавная буква\n";
    break;
  }
  [[likely]] case 'a' ... 'z': {
    std::cout << "Строчная буква\n";
    break;
  }
  [[likely]] case '0' ... '9': {
    std::cout << "Десятичная цифра\n";
    break;
  }
  [[likely]] case '!':
    [[fallthrough]];
  [[likely]] case '\"':
    [[fallthrough]];
  [[likely]] case '\'':
    [[fallthrough]];
  [[likely]] case ',':
    [[fallthrough]];
  [[likely]] case '-':
    [[fallthrough]];
  [[likely]] case '.':
    [[fallthrough]];
  [[likely]] case ':':
    [[fallthrough]];
  [[likely]] case ';':
    [[fallthrough]];
  [[likely]] case '?': {
    std::cout << "Знак препинания\n";
    break;
  }
  [[unlikely]] default: {
    std::cout << "Прочие символы\n";
    break;
  }
  }
  return 0;
}
