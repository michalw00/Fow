#pragma once

#include <memory>

namespace fow {

    class Unit;

    class Target {
    public:
        Target(int position_width, int position_height) : position_width_(position_width), position_height_(position_height) {}

        void SetPosition(int position_width, int position_height) { position_width_ = position_width; position_height_ = position_height; }
        int GetPositionWidth() const { return position_width_; }
        int GetPositionHeight() const { return position_height_; }

        void Defense(Unit* unit);
    private:
        int position_width_;
        int position_height_;
    };

}