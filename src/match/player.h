#pragma once

#include "Camera2D.hpp"
#include "Vector2.hpp"

#include <memory>

namespace fow {
    class Player {
    public:
        Player();
    private:
        std::shared_ptr<RCamera2D> camera_;
    };

}