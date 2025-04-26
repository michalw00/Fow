#pragma once

namespace fow {

    struct Position {
        int x;
        int y;

        auto operator<=>(const Position&) const = default;
        bool operator==(const Position&) const = default;

        bool operator==(int number) const {
            return x == number && y == number;
        }
        Position operator+(const Position& other) const {
            return { this->x + other.x, this->y + other.y };
        }
        Position operator-(const Position& other) const {
            return { this->x - other.x, this->y - other.y };
        }
    };

}