////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <utility>
#include <cassert>

////////////////////////////////////////////////////////////////////////////////////

class Vector {
public:
  Vector() : m_array(nullptr), m_size(0), m_capacity(0) {
    std::cout << "Vector:: Vector (1)\n";
  }

  //  --------------------------------------------------------------------------------

  Vector(std::initializer_list<int> list) : Vector() {
    std::cout << "Vector:: Vector (2)\n";

    // m_array = (m_size = std::size(list)) ? new int[m_size]{} : nullptr;
    if (std::size(list) != 0) {
      m_capacity = std::size(list);
      m_size = std::size(list);
      m_array = new int[m_size]{};
    } else {
      m_capacity = 0;
      m_size = 0;
      m_array = nullptr;
    }

    std::ranges::copy(list, m_array);
  }

  //  --------------------------------------------------------------------------------

  Vector(Vector const &other) : Vector() {
    std::cout << "Vector:: Vector (3)\n";

    // m_array = (m_size = other.m_size) ? new int[m_size]{} : nullptr;
    if (other.m_size != 0) {
      m_capacity = other.m_capacity;
      m_size = other.m_size;
      m_array = new int[m_size]{};
    } else {
      m_capacity = 0;
      m_size = 0;
      m_array = nullptr;
    }

    std::ranges::copy(other.m_array, other.m_array + other.m_size, m_array);
  }

  //  --------------------------------------------------------------------------------

  Vector(Vector &&other)
      : m_array(std::exchange(other.m_array, nullptr)),

        m_size(std::exchange(other.m_size, 0)),
        m_capacity(std::exchange(other.m_capacity, 0)) {
    std::cout << "Vector:: Vector (4)\n";
  }

  //  --------------------------------------------------------------------------------

  void push_back(int v) {
    m_size++;
    if ((!(m_size < m_capacity)) && (m_capacity != 0)) {
      int *array_t = new int[m_capacity * 2];
      for (auto j = 0uz; j < m_size - 1; j++) {
        array_t[j] = m_array[j];
      }

      std::swap(m_array, array_t);

      m_capacity *= 2;

      delete[] array_t;

    } else if (m_capacity == 0) {

      int *array_t = new int[1];

      std::swap(m_array, array_t);

      m_capacity++;

      delete[] array_t;
    }

    m_array[m_size - 1] = v;
  }

  //  --------------------------------------------------------------------------------
  auto get_size() const { return m_size; }
  auto get_capacity() const { return m_capacity; }
  auto get_array() const { return m_array; }
  //  --------------------------------------------------------------------------------
  auto clear() { m_size = 0; }
  auto empty() {return (m_size == 0);}
  //  --------------------------------------------------------------------------------

  ~Vector() {
    std::cout << "Vector::~Vector\n";

    delete[] m_array;
  }

  auto &operator=(Vector other) {
    std::cout << "Vector::operator= (4)\n";

    swap(other);

    return *this;
  }

  //  --------------------------------------------------------------------------------

  void swap(Vector &other) {
    std::swap(m_array, other.m_array);

    std::swap(m_size, other.m_size);

    std::swap(m_capacity, other.m_capacity);
  }

private:
  int *m_array = nullptr;

  std::size_t m_size = 0;

  std::size_t m_capacity = 0;
};

////////////////////////////////////////////////////////////////////////////////////

int main() {
  Vector vector_1;

  Vector vector_2 = {1, 2, 3, 4, 5};

  vector_2.push_back(6);

  for (auto i = 0uz; i < vector_2.get_size(); i++) {
    std::cout << vector_2.get_array()[i] << ' ';
  }
  std::cout << '\n'
            << vector_2.get_capacity() << '\n'
            << vector_2.get_size() << '\n';

  assert(!vector_2.empty());
  vector_2.clear();
  assert(vector_2.get_capacity() == 10 && vector_2.get_size() == 0);
  assert(vector_2.empty());

  Vector vector_3 = vector_2;

  Vector vector_4 = std::move(vector_3);

  //  --------------------------------------

  vector_3 = vector_2;

  vector_4 = std::move(vector_3);
}

////////////////////////////////////////////////////////////////////////////////////
