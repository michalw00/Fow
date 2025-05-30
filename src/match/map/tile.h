#pragma once

#include <memory>

#include "../../structs/vector2i.h"
#include "terrain.h"

namespace fow {

class Tile {
  public:
  Tile(Vector2I position = { 0,0 }, std::shared_ptr<Terrain> terrain = nullptr);

  void SetTerrain(std::shared_ptr<Terrain> terrain) { terrain_ = terrain; }
  std::shared_ptr<Terrain> GetTerrain() const { return terrain_; }

  void SetPosition(Vector2I position) { position_ = position; }
  Vector2I GetPosition() const { return position_; }
  private:
  Vector2I position_;
  std::shared_ptr<Terrain> terrain_;
};

} // namespace fow