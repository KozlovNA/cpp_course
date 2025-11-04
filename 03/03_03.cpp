#include <cassert>
#include <iostream>

struct Node {
  int v;
  Node *next = nullptr;
};

class List {
public:
  auto empty() const { return (head == nullptr && tail == nullptr); }

  auto push_front(int v) {
    auto node = new Node{.v = v};
    if (empty()) {
      head = tail = node;
    } else {
      head->next = node;
      head = node;
    }
  }

  auto push_back(int v) {
    auto node = new Node{.v = v};
    if (empty()) {
      head = tail = node;
    } else {
      node->next = tail;
      tail = node;
    }
  }

  auto show() const {
    for (auto iter = tail; iter != nullptr; iter = iter->next) {
      std::cout << iter->v << " ";
    }
    std::cout << '\n';
  }

  auto pop_back() {
    assert(!empty());
    auto node = tail;
    tail = tail->next;
    delete node;
    if (tail == nullptr) {
      head = nullptr;
    }
  }

  auto pop_front() {
    assert(!empty());
    if (tail == head) {
      delete tail;
      head = tail = nullptr;
    }
    auto node = head;
    auto iter = tail;
    while (iter->next != head) {
      iter = iter->next;
    }
    head = iter;
    iter->next = nullptr;
    delete node;
  }

  auto get() const {
    assert(!empty());
    auto first = tail;
    auto second = tail;
    while (first != nullptr && first->next != nullptr) {
      second = second->next;
      first = first->next->next;
    }
    return second->v;
  }

  ~List() {
    while (!empty()) {
      this->pop_back();
    }
  }

private:
  Node *head = nullptr;
  Node *tail = nullptr;
};

auto test() {
  List l;
  assert(l.empty() == 1);

  l.push_back(1);
  l.push_front(2);
  l.push_back(3);

  l.show();

  assert(l.get() == 1);

  List empty_l;

  empty_l.show();

  l.pop_back();
  l.show();
  l.pop_front();
  l.show();
  // empty_l.pop_back();
  // empty_l.pop_front();
}

int main() {
  test();
  return 0;
}
