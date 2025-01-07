#include "screen.h"

namespace fow {

    void Screen::ScaleTextsPositions(const RWindow& window, float basic_width, float basic_height) {
        for (auto& drawable_text : drawable_texts_) {   
            ScaleText(drawable_text.text, drawable_text.position, window, basic_width, basic_height);
        }
    }

    void Screen::AddImage(std::string&& name, RImage&& image) {
        images_.emplace(std::move(name), std::move(image));
    }

    void Screen::AddTexture(std::string&& name, RTexture&& texture) {
        textures_.emplace(std::move(name), std::move(texture));
    }

    void Screen::AddText(std::string&& name, RText&& text) {
        texts_.emplace(std::move(name), std::move(text));
    }

    void Screen::PlaceText(std::string name, RVector2 position, bool center_around_pos) {
        RText text = texts_[name];
        text.SetSpacing(10.f);
        if (center_around_pos) {
            OffsetFromTextCenter(text, position);
        }
        drawable_texts_.push_back({ text, position });
    }

    void Screen::PlaceText(RText& text, RVector2 position, bool center_around_pos) {
        text.SetSpacing(10.f);
        if (center_around_pos) {
            OffsetFromTextCenter(text, position);
        }
        drawable_texts_.push_back({ text, position });
    }

    void Screen::ScaleText(RText& text, RVector2& position, const RWindow& window, float basic_width, float basic_height) {
        RVector2 scale = { window.GetWidth() / basic_width, window.GetHeight() / basic_height };
        text.spacing *= scale.x;
        text.fontSize *= scale.x;
        position *= scale;
    }

    void Screen::OffsetFromTextCenter(const RText& text, RVector2& position) {
        RVector2 offset = text.MeasureEx();
        offset /= 2.f;
        position -= offset;
    }

}
