#pragma once

#include <cmath>
#include <compare>
#include <type_traits>
#include <functional>

#include "../utils/math_utils.h"

namespace fow {

struct Vector2I {
  int x;
  int y;

  auto operator<=>(const Vector2I&) const = default;
  bool operator==(const Vector2I&) const = default;

  bool operator==(int number) const {
    return x == number && y == number;
  }
  Vector2I operator+(const Vector2I& other) const {
    return { this->x + other.x, this->y + other.y };
  }
  Vector2I operator-(const Vector2I& other) const {
    return { this->x - other.x, this->y - other.y };
  } 
  static Vector2I GetClosestDirection(int x, int y) {
    if (x == 0 && y == 0) {
      return { 0, 0 };
    }

    const int abs_x = std::abs(x);
    const int abs_y = std::abs(y);

    const bool is_close_to_ox = (12 * abs_y <= 5 * abs_x);
    const bool is_close_to_oy = (12 * abs_x <= 5 * abs_y);

    if (is_close_to_ox) {
      return (x > 0) ? Vector2I{ 1, 0 } : Vector2I{ -1, 0 };
    }
    if (is_close_to_oy) {
      return (y > 0) ? Vector2I{ 0, 1 } : Vector2I{ 0, -1 };
    }

    if (sign(x) == sign(y)) {
      return (x > 0) ? Vector2I{ 1, 1 } : Vector2I{ -1, -1 };
    } else {
      return (x > 0) ? Vector2I{ 1, -1 } : Vector2I{ -1, 1 };
    }
  }

  Vector2I GetClosestDirection() const {
    return GetClosestDirection(x, y);
  }
};

} // namespace fow

namespace std {
template <>
struct hash<fow::Vector2I> {
  std::size_t operator()(const fow::Vector2I& v) const noexcept {
    std::size_t hx = std::hash<int>{}(v.x);
    std::size_t hy = std::hash<int>{}(v.y);

    return hx ^ (hy << 1);
  }
};

} // namespace std

