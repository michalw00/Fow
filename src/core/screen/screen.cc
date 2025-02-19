#include "screen.h"

namespace fow {

    Screen::~Screen() {
        for (auto& image : images_) {
            image.second.data = nullptr;
        }
    }

    void Screen::Draw() {
        camera_->BeginMode();
        for (auto& drawable : drawables_) {
            drawable->Draw();
        }
        camera_->EndMode();
    }

    void Screen::CheckButtons() {
        RVector2 mouse_position = camera_->GetScreenToWorld(GetMousePosition());
        for (auto& button : buttons_) {
            button->CheckMouse(mouse_position);
        }
    }

    void Screen::ScalePositions(float window_width, float window_height) {
        RVector2 scale = { window_width / basic_width_, window_height / basic_height_ };
        for (auto& drawable : drawables_) {
            drawable->Scale(scale);
        }
    }

    void Screen::AddImage(std::string&& name, RImage&& image) {
        images_.emplace(std::move(name), std::move(image));
    }

    void Screen::AddTexture(std::string&& name, std::shared_ptr <RTexture> texture) {
        textures_.emplace(std::move(name), texture);
    }

    void Screen::AddRText(std::string&& name, RText&& rtext) {
        rtext.SetSpacing(10.f);
        rtexts_.emplace(std::move(name), rtext);
    }

    void Screen::PlaceText(std::shared_ptr<Text> text) {
        drawables_.push_back(text);
    }

    void Screen::PlaceButton(std::shared_ptr<Button> button) {
        drawables_.push_back(button);
        buttons_.push_back(button);
    }

}
