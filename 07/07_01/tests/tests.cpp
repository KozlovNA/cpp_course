#include <gtest/gtest.h>
#include "solver.hpp"

TEST(TestQuadraticSolver, InfiniteRoots) {
    auto result = solve(0.0, 0.0, 0.0);
    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(std::holds_alternative<std::monostate>(*result));
}

TEST(TestQuadraticSolver, NoRootsLinear) {
    auto result = solve(0.0, 0.0, 5.0);
    EXPECT_FALSE(result.has_value());
}

TEST(TestQuadraticSolver, NoRootsQuadratic) {
    auto result = solve(1.0, 0.0, 1.0);
    EXPECT_FALSE(result.has_value());
}

TEST(TestQuadraticSolver, OneRootLinear) {
    auto result = solve(0.0, 2.0, -4.0);
    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(std::holds_alternative<double>(*result));
    EXPECT_DOUBLE_EQ(std::get<double>(*result), 2.0);
}

TEST(TestQuadraticSolver, OneRootQuadratic) {
    auto result = solve(1.0, -2.0, 1.0);
    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE(std::holds_alternative<double>(*result));
    EXPECT_DOUBLE_EQ(std::get<double>(*result), 1.0);
}

TEST(TestQuadraticSolver, TwoRoots) {
    auto result = solve(1.0, -3.0, 2.0);
    ASSERT_TRUE(result.has_value());
    ASSERT_TRUE((std::holds_alternative<std::pair<double, double>>(*result)));
    
    auto roots = std::get<std::pair<double, double>>(*result);
    EXPECT_DOUBLE_EQ(roots.first, 2.0);
    EXPECT_DOUBLE_EQ(roots.second, 1.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
