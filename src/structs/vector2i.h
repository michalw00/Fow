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

}