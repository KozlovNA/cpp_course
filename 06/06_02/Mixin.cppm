export module rational:mixins; 

export namespace math
{
    template < typename T > struct addable
    {
        friend auto operator+(T lhs, T const & rhs) { return lhs += rhs; }
    protected: addable() = default;
    };

    template < typename T > struct subtractable
    {
        friend auto operator-(T lhs, T const & rhs) { return lhs -= rhs; }
    protected: subtractable() = default;
    };

    template < typename T > struct multipliable
    {
        friend auto operator*(T lhs, T const & rhs) { return lhs *= rhs; }
    protected: multipliable() = default;
    };

    template < typename T > struct dividable
    {
        friend auto operator/(T lhs, T const & rhs) { return lhs /= rhs; }
    protected: dividable() = default;
    };

    template < typename T > struct incrementable
    {
        friend auto operator++(T & self, int) { auto tmp = self; ++self; return tmp; }
    protected: incrementable() = default;
    };

    template < typename T > struct decrementable
    {
        friend auto operator--(T & self, int) { auto tmp = self; --self; return tmp; }
    protected: decrementable() = default;
    };
}
