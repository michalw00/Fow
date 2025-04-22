#include "button.h"

namespace fow {
    Button::Button(RVector2 position, std::function<void()> action_lmb, std::function<void()> action_rmb)
        : Drawable(position), action_lmb_(action_lmb), action_rmb_(action_rmb)  {}

    void Button::CheckMouse(RVector2 mouse_position) {
        is_hovered_ = area_.CheckCollision(mouse_position);
        if (is_hovered_) {
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                action_lmb_();
            }
            if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
                action_rmb_();
            }
        }
    }   
}