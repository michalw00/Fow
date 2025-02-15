#include "text_button.h"

namespace fow {
    TextButton::TextButton(RVector2 position, std::function<void()> action, const RText& rtext, bool centered)
        : Button(position, action), rtext_(rtext)  {
        RVector2 size = rtext.MeasureEx();
        if (centered) {
            position_ -= size / 2.0;
        }
        area_ = { position, size };
        rtext_hovered_ = rtext_;
        rtext_hovered_.fontSize += hovered_font_size_increase_;
        rtext_hovered_.color.a -= hovered_color_alpha_decrease_;
    }

    void TextButton::Draw() {
        if (is_hovered_) {
            rtext_hovered_.Draw(position_);
        } else {        
            rtext_.Draw(position_);
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