#include <cassert>
#include <vector>

template<typename ContainerType, typename... Pack>
auto PushPack(ContainerType & containter, Pack...args) {
  static_assert((std::is_same_v<Pack, int> && ...));
  (containter.push_back(args), ...);
}

auto RunTests() {
  std::vector<int> vec{1,2,3};
  PushPack(vec, 4, 5, 6, 7);
  std::vector<int> correct{1, 2, 3, 4, 5, 6, 7};
  assert(vec == correct);
}

int main() {
  RunTests();
  return 0;
}
