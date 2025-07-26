#include "texture_button.h"

#include <functional>

#include <Rectangle.hpp>
#include <Vector2.hpp>

#include "../../structs/texture_states.h"
#include "button.h"

namespace fow {

TextureButton::TextureButton(RVector2 position, RVector2 size, std::function<void()> action_lmb, TextureState texture, std::function<void()> action_rmb)
  : Button(position, action_lmb, action_rmb), texture_(texture) {
  area_ = { position, size };
}

void TextureButton::Draw() const {
  RRectangle src = { {0, 0}, texture_.basic->GetSize() };

  if (is_selected_ && texture_.selected) {
    texture_.selected->Draw(src, area_);
  } else if (is_hovered_ && texture_.hovered) {
    texture_.hovered->Draw(src, area_);
  } else {
    texture_.basic->Draw(src, area_);
  }
}

void TextureButton::Scale(RVector2 scale) {
  position_ *= scale;
  RVector2 size = area_.GetSize() * scale;
  area_ = { position_, size };
}

} // namespace fow