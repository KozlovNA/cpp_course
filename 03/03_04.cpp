#include <cassert>
#include <iostream>

class AttorneyF1;
class AttorneyF2;
class ClientF1;
class ClientF2;

class Entity {
private:
  friend AttorneyF1;
  friend AttorneyF2;

  auto f1() const {
    std::cout << "tun max verstapen\n";
    return 1uz;
  }

  auto f2() const {
    std::cout << "tun tun max verstapen\n";
    return 2uz;
  }
};

class AttorneyF1 {
private:
  friend ClientF1;

  static auto f1(Entity const &entity) { return entity.f1(); }
};

class AttorneyF2 {
private:
  friend ClientF2;

  static auto f2(Entity const &entity) { return entity.f2(); }
};

class ClientF1 {
public:
  static auto test_f1() {
    Entity entity;
    assert(AttorneyF1::f1(entity) == 1uz);
  }
};

class ClientF2 {
public:
  static auto test_f2() {
    Entity entity;
    assert(AttorneyF2::f2(entity) == 2uz);
  }
};

int main() {
  ClientF1::test_f1();
  ClientF2::test_f2();
  return 0;
}
