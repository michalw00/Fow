#include "texture_button.h"

namespace fow {
    TextureButton::TextureButton(RVector2 position, std::function<void()> action, std::shared_ptr<RTexture> texture, std::shared_ptr<RTexture> texture_hovered)
        : Button(position, action), texture_(texture), texture_hovered_(texture_hovered) {

        float width = static_cast<float>(texture_->GetWidth());
        float height = static_cast<float>(texture_->GetHeight());
        RVector2 size = { width, height };
        area_ = { position, size };
    }

    void TextureButton::Draw() {
        if (is_hovered_ && texture_hovered_ != nullptr) {
            texture_hovered_->Draw(area_, position_);          
        } else {
            texture_->Draw(area_, position_);
        }
    }

    void TextureButton::Scale(RVector2 scale) {
        position_ *= scale;
        RVector2 area_size = area_.GetSize() * scale;
        area_ = { position_, area_size };
    }
}