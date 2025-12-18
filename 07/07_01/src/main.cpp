#include <iostream>
#include "solver.hpp"

int main() {
    double a = 0, b = 0, c = 0;
    if (std::cin >> a >> b >> c) {
        auto result = solve(a, b, c);

        if (!result.has_value()) {
            std::cout << "no roots\n";
        } else {
            const auto& roots = result.value();
            if (std::get_if<std::monostate>(&roots)) {
                std::cout << "x_1, x_2 = (-inf, +inf) \n";
            } else if (const double* val = std::get_if<double>(&roots)) {
                std::cout << "x_1, x_2 = " << *val << '\n';
            } else if (const auto* pair_roots = std::get_if<std::pair<double, double>>(&roots)) {
                std::cout << "x_1 = " << pair_roots->first << '\n';
                std::cout << "x_2 = " << pair_roots->second << '\n';
            }
        }
    }
    return 0;
}
