#include "screen.h"

#include "../../drawable/text.h"

namespace fow {

    void Screen::Draw(RCamera2D& camera) {
        camera.BeginMode();
        for (auto& drawable : drawables_) {
            drawable->Draw();
        }
        camera.EndMode();
    }

    void Screen::CheckButtons(const RCamera2D& camera) {
        for (auto& button : buttons_) {
            button->CheckMouse(camera);
        }
    }

    void Screen::ScaleTextsPositions(float window_width, float window_height, float basic_width, float basic_height) {
        RVector2 scale = { window_width / basic_width, window_height / basic_height };
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
        text.SetSpacing(10.f);
        texts_.emplace(std::move(name), std::move(text));
    }

    void Screen::PlaceText(RText text, RVector2 position, bool centered) {               
        drawables_.push_back(std::make_shared<Text>(position, text, centered));
    }

    void Screen::PlaceButton(RText text, RVector2 position, bool centered, std::function<void()> action) {
        std::shared_ptr<TextButton> text_button = std::make_shared<TextButton>(position, text, centered, action);
        drawables_.push_back(text_button);
        buttons_.push_back(text_button);
    }

}
