#include "text_button.h"

namespace fow {
    TextStates::TextStates(const RText& text, int hovered_font_size_increase, int hovered_color_alpha_decrease) {
        basic = text;
        hovered = text;
        hovered.fontSize += hovered_font_size_increase;
        hovered.color.a -= hovered_color_alpha_decrease;
    }

    TextButton::TextButton(RVector2 position, std::function<void()> action, const RText& text, bool centered)
        : Button(position, action), text_(text)  {
        RVector2 size = text.MeasureEx();
        if (centered) {
            position_ -= size / 2.0;
        }
        area_ = { position, size };
    }

    void TextButton::Draw() const {
        if (is_hovered_) {
            text_.hovered.Draw(position_);
        } else {        
            text_.basic.Draw(position_);
        }
    }

    void TextButton::Scale(RVector2 scale) {
        position_ *= scale;
        RVector2 area_size = area_.GetSize() * scale;
        area_ = { position_, area_size };
        text_.basic.spacing *= scale.x;
        text_.basic.fontSize *= scale.x;
        text_.hovered.spacing *= scale.x;
        text_.hovered.fontSize *= scale.x;
    }
}