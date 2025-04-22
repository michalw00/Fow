#include "screen.h"

namespace fow {

    void Screen::Clear() {
        drawables_.clear();
        buttons_.clear();
        drawables_static_.clear();
        buttons_static_.clear();
    }

    void Screen::Draw() const {  
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
