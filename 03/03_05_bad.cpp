#include <cassert>
#include <iostream>

class Entity_v1 {
public:
  virtual void test() { std::cout << "Entity_v1::test\n"; }
};

class Entity_v2 {
public:
  virtual void test() { std::cout << "Entity_v2::test\n"; }
};

class Client final : public Entity_v1, public Entity_v2 {
public:
  void test() override final { std::cout << "Client::test\n"; }
};

int main() {
  Client *client = new Client();

  client->test();

  delete client;
  return 0;
}
