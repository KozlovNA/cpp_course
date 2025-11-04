// герб сатор решение сложных задач на c++ 208 страница задача 3.9
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

class Adapter_v1 : public Entity_v1 {
public:
  virtual void test_v1() = 0;

private:
  void test() override final { this->test_v1(); }
};

class Adapter_v2 : public Entity_v2 {
public:
  virtual void test_v2() = 0;

private:
  void test() override final { this->test_v2(); }
};

class Client final : public Adapter_v1, public Adapter_v2 {
public:
  void test_v1() override final { std::cout << "Client::test_v1\n"; }

  void test_v2() override final { std::cout << "Client::test_v2\n"; }
};

int main() {
  Client *client = new Client();

  client->test_v1();
  client->test_v2();
  
  delete client;
  return 0;
}
