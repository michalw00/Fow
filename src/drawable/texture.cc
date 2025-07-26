#include "texture.h"

#include <type_traits>

#include <Texture.hpp>
#include <Vector2.hpp>

#include "drawable.h"

namespace fow {

Texture::Texture(RVector2 position, RVector2 size, RTexture&& rtexture) : Drawable(position), rtexture_(std::move(rtexture)) {
  area_ = { position, size };
}

void Texture::Draw() const {
  RRectangle src = { {0, 0}, rtexture_.GetSize() };
  rtexture_.Draw(src, area_);
}

void Texture::Scale(RVector2 scale) {
  position_ *= scale;
  RVector2 size = area_.GetSize() * scale;
  area_ = { position_, size };
}

} // namespace fow