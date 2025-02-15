#include "button.h"

namespace fow {
    Button::Button(RVector2 position, std::function<void()> action)
        : Drawable(position), action_(action) {}

    void Button::CheckMouse(RVector2 mouse_position) {
        is_hovered_ = area_.CheckCollision(mouse_position);
        if (is_hovered_ && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            action_();
        }
    }   
}