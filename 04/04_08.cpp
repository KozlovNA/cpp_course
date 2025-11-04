//////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <string>
#include <utility>

//////////////////////////////////////////////////////////////////

template < typename ... Ts > class Tuple {

  public: 
    constexpr std::size_t size() const {
      return sizeof...(Ts);
    }
};

//////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > class Tuple < T, Ts ... >
{
public :

	Tuple(T && x, Ts && ... ys)
	:
		m_head(std::forward < T  > (x )   ),
		
		m_tail(std::forward < Ts > (ys)...)
	{}

//  ------------------------------------------------
  constexpr std::size_t size() const {
    return 1 + sizeof...(Ts);
  } 

	template < std::size_t I > auto get() const
	{
		if constexpr (I > 0)
		{
			return m_tail.template get < I - 1 > ();
		}
		else
		{
			return m_head;
		}
	}

private :

	T m_head;
	
	Tuple < Ts ... > m_tail;
};

//////////////////////////////////////////////////////////////////

int main()
{
	Tuple < int, double, std::string > tuple(1, 2.0, "aaaaa");
  Tuple <> empty_tuple;

//  ----------------------------------------------------------

	assert(tuple.get < 0 > () == 1);
  static_assert(tuple.size() == 3);
  static_assert(empty_tuple.size() == 0);
}

//////////////////////////////////////////////////////////////////

