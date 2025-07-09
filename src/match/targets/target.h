#pragma once

#include "../../structs/vector2i.h"

namespace fow {

class Target {
  public:
  Target(Vector2I position) : position_(position) {}

  void SetPosition(Vector2I position) { position_ = position; }
  Vector2I GetPosition() const { return position_; }

  protected:
  Vector2I position_;
};

} // namespace fow