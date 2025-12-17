#include <cassert>
#include <string>
#include <utility>

////////////////////////////////////////////////////

class Person {
public:
  std::string name;
  int age = 0;
  int grade = 0;
};

////////////////////////////////////////////////////

class Builder {
private:
  Person m_person;

public:
  Builder() = default;

  //  ------------------------------------------------

  Builder &name(const std::string &name) {
    m_person.name = name;
    return *this;
  }

  //  ------------------------------------------------

  Builder &age(int age) {
    m_person.age = age;
    return *this;
  }

  //  ------------------------------------------------

  Builder &grade(int grade) {
    m_person.grade = grade;
    return *this;
  }

  //  ------------------------------------------------

  Person get() { return std::move(m_person); }
};

////////////////////////////////////////////////////

int main() {
  Builder builder;

  auto person = builder.name("Ivan").age(25).grade(10).get();

  assert(person.name == "Ivan");
  assert(person.age == 25);
  assert(person.grade == 10);

  //  ------------------------------------------------

  Builder builder2;
  auto person2 = builder2.name("Maria").get();

  assert(person2.name == "Maria");
  assert(person2.age == 0);
  assert(person2.grade == 0);

  return 0;
}
