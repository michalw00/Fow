#include "rectangle.h"

#include <Color.hpp>
#include <Vector2.hpp>

#include "drawable.h"

namespace fow {
Rectangle::Rectangle(RVector2 position, RVector2 size, const RColor& rcolor) : Drawable(position), rrectangle_(position, size), rcolor_(rcolor) {}

void Rectangle::Draw() const {
  rrectangle_.Draw(rcolor_);
}

void Rectangle::Scale(RVector2 scale) {
  position_ *= scale;
  rrectangle_.x *= scale.x;
  rrectangle_.y *= scale.y;
  rrectangle_.width *= scale.x;
  rrectangle_.height *= scale.y;
}

} // namespace fow