#include "screen.h"

#include <memory>

#include <raylib.h>
#include <Vector2.hpp>

#include "../../drawable/button/button.h"
#include "../../drawable/drawable.h"

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
  for (auto& drawable_static : drawables_static_) {
    drawable_static->Draw();
  }
}

void Screen::CheckButtons() {
  RVector2 mouse_position = GetMousePosition();
  for (auto& button_static : buttons_static_) {
    button_static->CheckMouse(mouse_position);
  }
  RVector2 mouse_position_world = camera_->GetScreenToWorld(mouse_position);
  for (auto& button : buttons_) {
    button->CheckMouse(mouse_position_world);
  }
}

void Screen::ScalePositions(float window_width, float window_height, bool inverse) {
  RVector2 scale = { window_width / basic_width_, window_height / basic_height_ };
  if (inverse) {
    scale = RVector2(1.f, 1.f) / scale;
  }
  for (auto& drawable : drawables_) {
    drawable->Scale(scale);
  }
  for (auto& drawable_static : drawables_static_) {
    drawable_static->Scale(scale);
  }
}

void Screen::PlaceDrawable(std::shared_ptr<Drawable> drawable, bool is_static) {
  if (is_static) {
    drawables_static_.push_back(drawable);
    if (drawable->GetIsButton()) {
      buttons_static_.push_back(std::static_pointer_cast<Button>(drawable));
    }
  } else {
    drawables_.push_back(drawable);
    if (drawable->GetIsButton()) {
      buttons_.push_back(std::static_pointer_cast<Button>(drawable));
    }
  }
}

} // namespace fow
