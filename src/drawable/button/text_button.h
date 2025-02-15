#pragma once

#include <functional>

#include <Vector2.hpp>
#include <Text.hpp>

#include "button.h"

namespace fow {
    class TextButton : public Button {
    public:
        TextButton(RVector2 position, std::function<void()> action, const RText& rtext, bool centered = true);

        void Draw() override;
        void Scale(RVector2 scale) override;
    private:
        RText rtext_;
        RText rtext_hovered_;

        int hovered_font_size_increase_ = 3;
        int hovered_color_alpha_decrease_ = 30;
    };
}