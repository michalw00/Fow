#pragma once

#include <Rectangle.hpp>
#include <Texture.hpp>
#include <Vector2.hpp>

#include "drawable.h"

namespace fow {

class Texture : public Drawable {
  public:
  Texture(RVector2 position, RVector2 size, RTexture&& rtexture);

  void Draw() const override;
  void Scale(RVector2 scale) override;
  private:
  RTexture rtexture_;
  RRectangle area_;
};

} // namespace fow