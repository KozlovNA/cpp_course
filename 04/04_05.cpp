#include<cassert> 
#include<limits>

template <int N>
struct Fibonacci{
  static_assert( Fibonacci<N-1>::val <= std::numeric_limits<int>::max() - Fibonacci<N-2>::val);
  static constexpr int val = Fibonacci<N-1>::val + Fibonacci<N-2>::val;
};

template <>
struct Fibonacci<1> {
   static constexpr int val = 0;
};

template <>
struct Fibonacci<2> {
  static constexpr int val = 1;
};

template<int N>
constexpr auto const fibonacci_v = Fibonacci<N>::val;

int main() {
    static_assert(fibonacci_v<8> == 13); // 0 1 1 2 3 5 8 13

  return 0;
}
