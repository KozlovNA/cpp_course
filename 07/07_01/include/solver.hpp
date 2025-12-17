#pragma once

#include <optional>
#include <variant>
#include <utility>

using RootsVariant = std::variant<std::monostate, double, std::pair<double, double>>;

std::optional<RootsVariant> solve(double a, double b, double c);
