#pragma once

#include <functional>

#include <Rectangle.hpp>
#include <Vector2.hpp>
#include <Camera2D.hpp>

#include "../drawable.h"

namespace fow {
    class Button : public Drawable  {
    public:
        Button(RVector2 position, std::function<void()> action);
        virtual ~Button() {}; 
        void CheckMouse(RVector2 mouse_position);

        RRectangle GetArea() const { return area_; }
    protected:
        bool is_hovered_ = false;
        RRectangle area_;
        std::function<void()> action_;    
    };

}