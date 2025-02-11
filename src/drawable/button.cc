#include "button.h"

#include <utility>

namespace fow {

    Button::Button(RVector2 position, std::function<void()> action)
        : Drawable(position), action_(action) {}

    void Button::CheckMouse(const RCamera2D& camera) {
        RVector2 mouse_point = camera.GetScreenToWorld(GetMousePosition());
        is_hovered = area_.CheckCollision(mouse_point);
        if (is_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            action_();
        }
    }

    TextureButton::TextureButton(RVector2 position, RTexture&& texture, std::function<void()> action)
        : texture_(std::move(texture)), Button(position, action) {
        
        float width = static_cast<float>(texture_.GetWidth());
        float height = static_cast<float>(texture_.GetHeight());
        RVector2 size = { width, height };
        area_ = { position, size };
    }

    void TextureButton::Draw() {        
        if (!is_hovered) {
            texture_.Draw(area_, position_);
        } else {
            texture_hovered_.Draw(area_, position_);
        }
    }

    void TextureButton::Scale(RVector2 scale) {
        position_ *= scale;
        RVector2 area_size = area_.GetSize() * scale;
        area_ = { position_, area_size };
    }

    TextButton::TextButton(RVector2 position, const RText& rtext, bool centered, std::function<void()> action)
    : rtext_(rtext), Button(position, action){
        RVector2 size = rtext.MeasureEx();
        if (centered) {
            position_ -= size / 2.0;
        }
        area_ = { position, size };
        rtext_hovered_ = rtext_;
        rtext_hovered_.fontSize += 3;
        rtext_hovered_.color.a -= 30;
    }

    void TextButton::Draw() {
        if (!is_hovered) {
            rtext_.Draw(position_);
        } else {
            rtext_hovered_.Draw(position_);
        }
        
    }

    void TextButton::Scale(RVector2 scale) {
        position_ *= scale;
        RVector2 area_size = area_.GetSize() * scale;
        area_ = { position_, area_size };
        rtext_.spacing *= scale.x;
        rtext_.fontSize *= scale.x;   
        rtext_hovered_.spacing *= scale.x;
        rtext_hovered_.fontSize *= scale.x;
    }

}