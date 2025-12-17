#include "solver.hpp"
#include <cmath>

std::optional<RootsVariant> solve(double a, double b, double c) {
    const double eps = 1e-6;

    if (std::abs(a) < eps) {
        if (std::abs(b) < eps) {
            if (std::abs(c) < eps) {
                return std::monostate{};
            } else {
                return std::nullopt;
            }
        } else {
            double x = -c / b;
            if (std::abs(x) < eps) x = 0.0;
            return x;
        }
    } else {
        double D = b * b - 4 * a * c;

        if (std::abs(D) < eps) {
            double x = -b / (2 * a);
            if (std::abs(x) < eps) x = 0.0;
            return x;
        } else if (D < 0) {
            return std::nullopt;
        } else {
            double sqrt_D = std::sqrt(D);
            double x1 = (-b + sqrt_D) / (2 * a);
            double x2 = (-b - sqrt_D) / (2 * a);
            return std::make_pair(x1, x2);
        }
    }
}
