#include<cassert>
////////////////////////////////////////////////////////////////////////

template < int X > struct Factorial
{
	constexpr static auto value = X * Factorial < X - 1 > ::value;
};

////////////////////////////////////////////////////////////////////////

template <> struct Factorial < 0 > 
{ 
	constexpr static auto value = 1;
};

////////////////////////////////////////////////////////////////////////

template < int X > constexpr auto factorial_v = Factorial < X > ::value;

////////////////////////////////////////////////////////////////////////

template < int N, int K > struct Binomial {
  constexpr static auto value = factorial_v< N > / factorial_v< K > / factorial_v< N - K >; 
};

////////////////////////////////////////

template < int N, int K > constexpr auto binomial_v = Binomial<N, K>::value;  

int main()
{
    static_assert(factorial_v < 5 > == 120); // support : cppinsights.io
    static_assert(binomial_v< 5, 1 > == 5);
}

////////////////////////////////////////////////////////////////////////

