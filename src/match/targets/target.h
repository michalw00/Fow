#pragma once

#include <memory>
#include "../map/map.h"

namespace fow {

    class Unit;

    class Target {
    public:
        Target(Position position) : position_(position) {}

        void SetPosition(Position position) { position_ = position; }
        Position GetPosition() const { return position_; }

        void Defense(Unit* unit);
    private:
        Position position_;
    };

}