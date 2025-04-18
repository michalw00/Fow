#include "texture_button.h"

namespace fow {

    TextureButton::TextureButton(RVector2 position, RVector2 size, std::function<void()> action_lmb, TextureState texture, std::function<void()> action_rmb)
        : Button(position, action_lmb, action_rmb), texture_(texture) {
        
        area_ = { position, size };
        texture.basic->width = size.GetX();
        texture.basic->height = size.GetY();
        texture.hovered->width = size.GetX();
        texture.hovered->height = size.GetY();
        texture.selected->width = size.GetX();
        texture.selected->height = size.GetY();

    }

    void TextureButton::Draw() const {
        if (is_selected_ && texture_.selected != nullptr) {
            texture_.selected->Draw(position_);
        } else if (is_hovered_ && texture_.hovered != nullptr) {
            texture_.hovered->Draw(position_);
        } else {
            texture_.basic->Draw(position_);
        }
    }

    void TextureButton::Scale(RVector2 scale) {
        position_ *= scale;
        RVector2 area_size = area_.GetSize() * scale;
        area_ = { position_, area_size };
    }
}