#include "screen.h"

namespace fow {

    void Screen::AddImage(std::string name, RImage image) {
        images_.emplace(name, image);
    }

    void Screen::AddTexture(std::string name, RTexture texture) {
        textures_.emplace(std::move(name), std::move(texture));
    }

    void Screen::AddText(std::string name, const RText& text) {
        texts_.emplace(name, text);
    }

    void Screen::PlaceText(std::string name, RVector2 position) {
        drawable_texts_.push_back(std::make_pair(texts_[name], position));
    }

    void Screen::PlaceText(const RText& text, RVector2 position) {
        drawable_texts_.push_back(std::make_pair(text, position));
    }

}
