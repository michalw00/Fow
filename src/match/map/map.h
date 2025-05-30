#pragma once

#include <unordered_set>
#include <vector>

#include "../../structs/vector2i.h"
#include "terrain.h"
#include "tile.h"

namespace fow {

class Map {
  public:
  Map(int rows, int columns);

  std::vector<std::vector<Tile>> GetTiles() const { return tiles_; }
  const TerrainManager& GetTerrainManager() const { return terrain_manager_; }

  std::unordered_set<Vector2I> GetNeighbors(Vector2I position, bool itself = false) const;
  private:
  void InitSize(int rows, int columns);
  void InitTiles();

  TerrainManager terrain_manager_;
  std::vector<std::vector<Tile>> tiles_;
};

} // namespace fow