#include <cassert>
#include <vector>
#include <sstream>
#include <cmath>
#include <iostream>

import rational;

auto equal(double x, double y, double epsilon = 1e-6)
{
    return std::abs(x - y) < epsilon;
}

int main()
{
    math::Rational<int> x = 1, y(2, 1);

    std::vector < int > vector_2(5); 

    assert(equal(static_cast < double > (x), 1));

    assert((x += y) == math::Rational(+3, 1));
    assert((x -= y) == math::Rational(+1, 1));
    assert((x *= y) == math::Rational(+2, 1));
    assert((x /= y) == math::Rational(+1, 1));

    assert((x ++  ) == math::Rational(+1, 1));
    assert((x --  ) == math::Rational(+2, 1));
    assert((  ++ y) == math::Rational(+3, 1));
    assert((  -- y) == math::Rational(+2, 1));

    assert((x +  y) == math::Rational(+3, 1));
    assert((x -  y) == math::Rational(-1, 1));
    assert((x *  y) == math::Rational(+2, 1));
    assert((x /  y) == math::Rational(+1, 2));

    assert((x += 1) == math::Rational(+2, 1));
    assert((x +  1) == math::Rational(+3, 1));

    assert((x <  y) == 0);
    assert((x == y) == 1);

    std::stringstream stream_1("1/2");
    std::stringstream stream_2;

    stream_1 >> x;
    stream_2 << x;

    assert(stream_2.str() == stream_1.str());
}
