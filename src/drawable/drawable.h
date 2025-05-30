#pragma once

#include <Vector2.hpp>

namespace fow {

class Drawable {
  public:
  Drawable(RVector2 position);
  virtual ~Drawable() {}

  virtual void Draw() const = 0;
  virtual void Scale(RVector2 scale) = 0;

  bool GetIsButton() const { return is_button_; }
  protected:
  RVector2 position_;
  bool is_button_ = false;
};

}