#include "texture_button.h"

#include <functional>

#include "../../structs/texture_states.h"
#include "button.h"
#include <Vector2.hpp>

namespace fow {

TextureButton::TextureButton(RVector2 position, RVector2 size, std::function<void()> action_lmb, TextureState texture, std::function<void()> action_rmb)
    : Button(position, action_lmb, action_rmb), texture_(texture) {
    area_ = { position, size };

    texture_.basic->width = size.GetX();
    texture_.basic->height = size.GetY();
    texture_.hovered->width = size.GetX();
    texture_.hovered->height = size.GetY();
    texture_.selected->width = size.GetX();
    texture_.selected->height = size.GetY();
}

void TextureButton::Draw() const {
  if (is_selected_ && texture_.selected) {
    texture_.selected->Draw(position_);
  } else if (is_hovered_ && texture_.hovered) {
    texture_.hovered->Draw(position_);
  } else {
    texture_.basic->Draw(position_);
  }
}

void TextureButton::Scale(RVector2 scale) {
  position_ *= scale;
  RVector2 size = area_.GetSize() * scale;
  area_ = { position_, size };
  texture_.basic->width = size.GetX();
  texture_.basic->height = size.GetY();
  texture_.hovered->width = size.GetX();
  texture_.hovered->height = size.GetY();
  texture_.selected->width = size.GetX();
  texture_.selected->height = size.GetY();
}

} // namespace fow