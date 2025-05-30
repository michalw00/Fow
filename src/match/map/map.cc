#include "map.h"

#include <cstdlib>
#include <ctime>
#include <memory>
#include <stdexcept>
#include <unordered_set>

#include "../../structs/vector2i.h"
#include "terrain.h"

namespace fow {
Map::Map(int rows, int columns) {
  InitSize(rows, columns);
  InitTiles();
}

std::unordered_set<Vector2I> Map::GetNeighbors(Vector2I position, bool itself) const {
  int x = position.x;
  int y = position.y;

  int rows = tiles_.size();
  int columns = tiles_[0].size();

  if (x < 0 || x >= rows || y < 0 || y >= columns) {
    throw std::out_of_range("Tile coordinates are out of range.");
  }

  int i_min = -1;
  if (x == 0) { ++i_min; }

  int i_max = 1;
  if (x == rows - 1) { --i_max; }

  int j_min = -1;
  if (y == 0) { ++j_min; }

  int j_max = 1;
  if (y == columns - 1) { --j_max; }

  std::unordered_set<Vector2I> neighbors;

  neighbors.reserve(8);

  for (int i = i_min; i <= i_max; ++i) {
    for (int j = j_min; j <= j_max; ++j) {
      if (itself || i != 0 || j != 0) {
        Vector2I neighbor = { x + i, y + j };
        neighbors.insert(neighbor);
      }
    }
  }

  return neighbors;
}

void Map::InitSize(int rows, int columns) {
  tiles_.resize(columns);
  for (int i = 0; i < columns; ++i) {
    tiles_[i].resize(rows);
    for (int j = 0; j < rows; ++j) {
      tiles_[i][j].SetPosition({ i, j });
    }
  }
}

void Map::InitTiles() {
  std::shared_ptr<Terrain> terrain = terrain_manager_.GetResource(TerrainType::kPlains);
  srand(time(NULL));
  for (auto& row : tiles_) {
    for (auto& tile : row) {
      // Hardcoded map generation

      int random = rand() % 20;
      int random_change = random % 2;
      if (!random_change) {
        if (5 <= random && random <= 19) {
          terrain = terrain_manager_.GetResource(TerrainType::kPlains);
        } else if (1 <= random && random <= 4) {
          terrain = terrain_manager_.GetResource(TerrainType::kForest);
        } else {
          terrain = terrain_manager_.GetResource(TerrainType::kWater);
        }
      }

      tile.SetTerrain(terrain);

    }
  }
}

} // namespace fow