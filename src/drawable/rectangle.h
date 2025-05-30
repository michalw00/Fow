#pragma once

#include "Color.hpp"
#include "Rectangle.hpp"
#include "Vector2.hpp"

#include "drawable.h"

namespace fow {

class Rectangle : public Drawable {
  public:
  Rectangle(RVector2 position, RVector2 size, const RColor& color);

  void Draw() const override;
  void Scale(RVector2 scale) override;
  private:
  RRectangle rrectangle_;
  RColor rcolor_;
};

} // namespace fow