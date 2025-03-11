#pragma once

#include <Vector2.hpp>

namespace fow {
    class Drawable {
    public:
        Drawable(RVector2 position);
        virtual ~Drawable() {}

        virtual void Draw() const = 0;
        virtual void Scale(RVector2 scale) = 0;

        void SetPosition(RVector2 position) { position_ = position; }
    protected:
        RVector2 position_;
    };
}