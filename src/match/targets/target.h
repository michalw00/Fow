#pragma once

#include "../../structs/vector2i.h"

namespace fow {

class Unit;

class Target {
  public:
  Target(Vector2I position) : position_(position) {}

  void SetPosition(Vector2I position) { position_ = position; }
  Vector2I GetPosition() const { return position_; }

  void Defense(Unit* unit);
  private:
  Vector2I position_;
};

} // namespace fow