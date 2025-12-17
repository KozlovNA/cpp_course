#include <print>

////////////////////////////////////////////////////

class Entity {
public:
  virtual ~Entity() = default;

  //  ------------------------------

  virtual void test() const = 0;
};

////////////////////////////////////////////////////

class Client : public virtual Entity {
public:
  void test() const override { std::print("Client::test\n"); }
};

////////////////////////////////////////////////////

class Server : public virtual Entity {
public:
  void test() const override { std::print("Server::test\n"); }
};

////////////////////////////////////////////////////

template <typename T> class Decorator : public T, public virtual Entity {
public:
  //  ------------------------------------------------

  void test() const override {
    std::print("Decorator::test : ");

    T::test();
  }
};

////////////////////////////////////////////////////

int main() {
  Entity *entity_1 = new Client;

  Entity *entity_2 = new Decorator<Client>;

  //  ---------------------------------------------

  entity_2->test();

  //  ---------------------------------------------

  delete entity_2;

  delete entity_1;
}
