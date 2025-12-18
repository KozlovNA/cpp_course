#include <gtest/gtest.h>
#include <vector>
#include <variant>
#include <optional>
#include <new>
#include <stdexcept>
#include <limits>
#include <tuple>

import rational;

TEST(RationalTest, ThrowsExceptionOnZeroDenominatorConstructor)
{
    EXPECT_THROW(math::Rational<int>(1, 0), math::Exception);
}

TEST(RationalTest, ThrowsExceptionOnDivisionByZero)
{
    math::Rational<int> x(1, 1);
    math::Rational<int> y(0, 1);
    EXPECT_THROW(x /= y, math::Exception);
}

TEST(RationalTest, NoThrowOnValidOperations)
{
    math::Rational<int> x(1, 2);
    math::Rational<int> y(1, 3);
    EXPECT_NO_THROW(x + y);
    EXPECT_NO_THROW(x / y);
}

TEST(StdExceptionTest, BadAlloc)
{
    volatile std::size_t impossible_size = std::numeric_limits<std::size_t>::max() / 2;

    EXPECT_THROW({
        int* p = new int[impossible_size];
        delete[] p; 
    }, std::bad_alloc);
}

TEST(StdExceptionTest, BadVariantAccess)
{
    std::variant<int, float> v = 42;
    EXPECT_THROW(std::get<float>(v), std::bad_variant_access);
}

TEST(StdExceptionTest, BadOptionalAccess)
{
    std::optional<int> empty_opt;
    EXPECT_THROW(empty_opt.value(), std::bad_optional_access);
}

TEST(StdExceptionTest, OutOfRange)
{
    std::vector<int> v = {1, 2, 3};
    EXPECT_THROW((void)v.at(100), std::out_of_range);
}

TEST(StdExceptionTest, LengthError)
{
    std::vector<int> v;
    volatile std::size_t too_big = v.max_size() + 1;
    EXPECT_THROW(v.resize(too_big), std::length_error);
}
