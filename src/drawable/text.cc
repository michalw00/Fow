#include "text.h"

namespace fow {
    Text::Text(RVector2 position, const RText& rtext, bool centered) : Drawable(position), rtext_(rtext) {
        if (centered) {
            RVector2 offset = rtext.MeasureEx();
            position_ -= offset / 2.0;
        }
    }

    void Text::Draw() {
        rtext_.Draw(position_);
    }

    void Text::Scale(RVector2 scale) {
        rtext_.spacing *= scale.x;
        rtext_.fontSize *= scale.x;
        position_ *= scale;
    }
}