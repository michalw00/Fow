#include "screen.h"

#include "../../drawable/text.h"

namespace fow {

    void Screen::Draw() {
        for (auto& drawable : drawables_) {
            drawable->Draw();
        }
        drawables_.clear();
    }

    void Screen::CheckHoverButtons(const RCamera2D& camera) {
        for (auto& button : buttons_) {
            button->CheckMouseHover(camera);
        }
    }

    void Screen::ScaleTextsPositions(const RWindow& window, float basic_width, float basic_height) {
        RVector2 scale = { window.GetWidth() / basic_width, window.GetHeight() / basic_height };
        for (auto& drawable : drawables_) {   
            drawable->Scale(scale);
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

    void Screen::PlaceText(RText text, RVector2 position, bool centered) {
        text.SetSpacing(10.f);        
        drawables_.push_back(std::make_shared<Text>(position, text, centered));
    }

    void Screen::PlaceButton(RText text, RVector2 position, bool centered, std::function<void()> action) {
        text.SetSpacing(10.f);
        std::shared_ptr<TextButton> text_button = std::make_shared<TextButton>(position, text, centered, action);
        drawables_.push_back(text_button);
        buttons_.push_back(text_button);
    }

}
