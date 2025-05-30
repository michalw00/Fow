#pragma once

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
}

