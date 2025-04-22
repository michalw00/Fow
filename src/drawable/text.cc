#include "text.h"

namespace fow {
    Text::Text(RVector2 position, const RText& rtext, bool centered) : Drawable(position), rtext_(rtext), centered_(centered) {
        Configurate();
    }

    void Text::ChangeText(std::string&& text) {
        if (centered_) {
            RVector2 offset = rtext_.MeasureEx();
            position_ += offset / 2.0;
        }
        rtext_.SetText(text);
        Configurate();
    }

    void Text::Draw() const {
        rtext_.Draw(position_);
    }

    void Text::Scale(RVector2 scale) {
        rtext_.spacing *= scale.x;
        rtext_.fontSize *= scale.x;
        position_ *= scale;
    }

    void Text::Configurate() {
        rtext_.SetSpacing(rtext_.GetFontSize()*0.1f);
        if (centered_) {
            RVector2 offset = rtext_.MeasureEx();
            position_ -= offset / 2.0;
        }
    }
}