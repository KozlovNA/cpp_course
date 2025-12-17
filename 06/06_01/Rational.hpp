#pragma once

#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > struct addable
{
    friend auto operator+(T lhs, T const & rhs) { return lhs += rhs; }
protected: addable() = default;
};

//  -------------------------------------------------------------------------------------------

template < typename T > struct subtractable
{
    friend auto operator-(T lhs, T const & rhs) { return lhs -= rhs; }
protected: subtractable() = default;
};

//  -------------------------------------------------------------------------------------------

template < typename T > struct multipliable
{
    friend auto operator*(T lhs, T const & rhs) { return lhs *= rhs; }
protected: multipliable() = default;
};

//  -------------------------------------------------------------------------------------------

template < typename T > struct dividable
{
    friend auto operator/(T lhs, T const & rhs) { return lhs /= rhs; }
protected: dividable() = default;
};

//  -------------------------------------------------------------------------------------------

template < typename T > struct incrementable
{
    friend auto operator++(T & self, int) { auto tmp = self; ++self; return tmp; }
protected: incrementable() = default;
};

//  -------------------------------------------------------------------------------------------

template < typename T > struct decrementable
{
    friend auto operator--(T & self, int) { auto tmp = self; --self; return tmp; }
protected: decrementable() = default;
};

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename T >
class Rational : 
    private addable      < Rational < T > >,
    private subtractable < Rational < T > >,
    private multipliable < Rational < T > >,
    private dividable    < Rational < T > >,
    private incrementable< Rational < T > >,
    private decrementable< Rational < T > >
{
public :

//  -------------------------------------------------------------------------------------------

    /* explicit */ Rational(T num = 0, T den = 1) : m_num(num), m_den(den)
    {
        reduce();
    }

//  -------------------------------------------------------------------------------------------

    explicit operator double() const { return 1.0 * m_num / m_den; }

//  -------------------------------------------------------------------------------------------

    Rational & operator+=(Rational const & other);
    Rational & operator-=(Rational const & other); 
    Rational & operator*=(Rational const & other);
    Rational & operator/=(Rational const & other);

//  -------------------------------------------------------------------------------------------

    auto & operator++() { *this += 1; return *this; }
    auto & operator--() { *this -= 1; return *this; }

//  -------------------------------------------------------------------------------------------

    friend auto operator<=>(Rational const & lhs, Rational const & rhs)
    {
        auto left  = lhs.m_num * rhs.m_den;
        auto right = rhs.m_num * lhs.m_den;
        return left <=> right;
    }

//  -------------------------------------------------------------------------------------------

    friend bool operator==(Rational const & lhs, Rational const & rhs)
    {
        return lhs.m_num == rhs.m_num && lhs.m_den == rhs.m_den;
    }

//  -------------------------------------------------------------------------------------------

    friend auto & operator>>(std::istream & stream, Rational & rational)
    {
        return (stream >> rational.m_num).ignore() >> rational.m_den;
    }

//  -------------------------------------------------------------------------------------------

    friend auto & operator<<(std::ostream & stream, Rational const & rational)
    {
        return stream << rational.m_num << '/' << rational.m_den;
    }

//  -------------------------------------------------------------------------------------------

private :
    void reduce();

//  -------------------------------------------------------------------------------------------

    T m_num = 0, m_den = 1;
};
