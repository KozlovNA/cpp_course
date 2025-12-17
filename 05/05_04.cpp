#include <print>

////////////////////////////////////////

class ClientImpl {
public:
  void test() const { std::print("Client_Static::test\n"); }
};

////////////////////////////////////////

class ServerImpl {
public:
  void test() const { std::print("Server_Static::test\n"); }
};

////////////////////////////////////////

template <typename Strategy> class Entity : public Strategy {
public:
  void execute() const { this->test(); }
};

////////////////////////////////////////

void test(auto const &entity) { entity.test(); }

////////////////////////////////////////

int main() {
  Entity<ClientImpl> client_entity;

  Entity<ServerImpl> server_entity;

  //  --------------------------------

  client_entity.test();

  //  --------------------------------
  test(client_entity);
  test(server_entity);
}
