#include "map.h"

#include <algorithm>
#include <cmath>
#include <memory>
#include <random>
#include <stdexcept>
#include <unordered_set>
#include <vector>

#include "../../structs/vector2i.h"
#include "terrain.h"

namespace fow {

Map::Map(int rows, int columns, TerrainDistribution distribution, int k_cluster) {
  InitSize(rows, columns);
  InitTerrainCompatibility();
  InitTiles(distribution, k_cluster);
}

std::unordered_set<Vector2I> Map::GetNeighbors(Vector2I position, bool itself) const {
  if (neighbors_cache_.contains(position)) {
    return neighbors_cache_.at(position);
  }

  int x = position.x;
  int y = position.y;

  int rows = tiles_.size();
  int columns = tiles_[0].size();

  if (x < 0 || x >= rows || y < 0 || y >= columns) {
    throw std::out_of_range("Tile coordinates are out of range.");
  }

  int edge = 2;

  int i_min = -1;
  int i_max = 1;
  if (x == 0) ++i_min;
  else if (x == rows - 1) --i_max;
  else --edge;

  int j_min = -1;
  int j_max = 1;
  if (y == 0) ++j_min;
  else if (y == columns - 1) --j_max;
  else --edge;

  std::unordered_set<Vector2I> neighbors;

  int size = 0;
  switch (edge) {
    case (0):
      size = 8;
      break;
    case (1):
      size = 5;
      break;
    case (2):
      size = 3;
      break;
    default:
      break;
  }

  neighbors.reserve(size);

  for (int i = i_min; i <= i_max; ++i) {
    for (int j = j_min; j <= j_max; ++j) {
      if (itself || i != 0 || j != 0) {
        Vector2I neighbor = { x + i, y + j };
        neighbors.insert(neighbor);
      }
    }
  }
  neighbors_cache_[position] = neighbors;
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

void Map::InitTiles(TerrainDistribution distribution, int k) {
  std::random_device rd;
  // std::mt19937 gen(0); // specified seed
  std::mt19937 gen(rd()); // random seed
  RandomFillMap(distribution, gen);
  ClusterTerrains(gen, k);
}

void Map::InitTerrainCompatibility() {
  terrain_compatibility = {
    {TerrainType::kPlains, {}},
    {TerrainType::kHills, {}},
    {TerrainType::kMountains, {}},
    {TerrainType::kMarsh, {}},
    {TerrainType::kForest, {}},
    {TerrainType::kWater, {}},
    {TerrainType::kUrban, {}}
  };

  terrain_compatibility[TerrainType::kPlains] = {
    {TerrainType::kPlains, 0.85},
    {TerrainType::kHills, 0.5},
    {TerrainType::kMountains, 0.2},
    {TerrainType::kMarsh, 0.3},
    {TerrainType::kForest, 0.5},
    {TerrainType::kWater, 0.3},
    {TerrainType::kUrban, 0.0 }
  };

  terrain_compatibility[TerrainType::kHills] = {
    {TerrainType::kHills, 0.85},
    {TerrainType::kPlains, 0.5},
    {TerrainType::kMountains, 0.8},
    {TerrainType::kMarsh, 0.1},
    {TerrainType::kForest, 0.4},
    {TerrainType::kWater, 0.4}
  };

  terrain_compatibility[TerrainType::kMountains] = {
    {TerrainType::kMountains, 0.9},
    {TerrainType::kPlains, 0.5},
    {TerrainType::kHills, 0.8},
    {TerrainType::kMarsh, 0.05},
    {TerrainType::kForest, 0.3},
    {TerrainType::kWater, 0.5},
    {TerrainType::kUrban, 0.0 }
  };

  terrain_compatibility[TerrainType::kMarsh] = {
    {TerrainType::kMarsh, 0.85},
    {TerrainType::kPlains, 0.3},
    {TerrainType::kHills, 0.1},
    {TerrainType::kMountains, 0.05},
    {TerrainType::kForest, 0.7},
    {TerrainType::kWater, 0.7},
    {TerrainType::kUrban, 0.0 }
  };

  terrain_compatibility[TerrainType::kForest] = {
    {TerrainType::kForest, 1.0},
    {TerrainType::kPlains, 0.5},
    {TerrainType::kHills, 0.4},
    {TerrainType::kMountains, 0.3},
    {TerrainType::kMarsh, 0.7},
    {TerrainType::kWater, 0.3},
    {TerrainType::kUrban, 0.0 }
  };

  terrain_compatibility[TerrainType::kWater] = {
    {TerrainType::kWater, 0.8},
    {TerrainType::kPlains, 0.3},
    {TerrainType::kHills, 0.4},
    {TerrainType::kMountains, 0.5},
    {TerrainType::kMarsh, 0.7},
    {TerrainType::kForest, 0.3},
    {TerrainType::kUrban, 0.3 }
  };

  terrain_compatibility[TerrainType::kUrban] = {
    {TerrainType::kUrban, 1.0},
    {TerrainType::kPlains, 0.0},
    {TerrainType::kHills, 0.0},
    {TerrainType::kMountains, 0.0},
    {TerrainType::kMarsh, 0.0},
    {TerrainType::kForest, 0.0},
    {TerrainType::kWater, 0.3}
  };
}

double Map::GetCompatibility(TerrainType a, TerrainType b) const {
  if (auto outer = terrain_compatibility.find(a); outer != terrain_compatibility.end()) {
    if (auto inner = outer->second.find(b); inner != outer->second.end()) {
      return inner->second;
    }
  }
  return 0.0;
}

void Map::SetTileFromType(Vector2I pos, TerrainType type) { // TODO: sprawdzic granice mapy
    std::shared_ptr<Terrain> terrain = terrain_manager_.GetResource(type);
    tiles_[pos.y][pos.x].SetTerrain(terrain_manager_.GetResource(type));
    //tiles_[pos.y][pos.x].SetTerrain(std::make_shared<Terrain>(terrain));
}

void Map::RandomFillMap(TerrainDistribution distribution, std::mt19937 gen) {
  int columns = tiles_.size();
  int rows = tiles_[0].size();
  int n = columns * rows;

  int forest_amount = distribution.forest * n;
  int hills_amount = distribution.hills * n;
  int marsh_amount = distribution.marsh * n;
  int mountains_amount = distribution.mountains * n;
  int water_amount = distribution.water * n;
  int urban_amount = distribution.urban * n;
  int plains_amount = n - (forest_amount + hills_amount + marsh_amount + mountains_amount + water_amount + urban_amount);

  std::vector<std::shared_ptr<Terrain>> terrains;
  terrains.insert(terrains.end(), forest_amount, terrain_manager_.GetResource(TerrainType::kForest));
  terrains.insert(terrains.end(), hills_amount, terrain_manager_.GetResource(TerrainType::kHills));
  terrains.insert(terrains.end(), marsh_amount, terrain_manager_.GetResource(TerrainType::kMarsh));
  terrains.insert(terrains.end(), mountains_amount, terrain_manager_.GetResource(TerrainType::kMountains));
  terrains.insert(terrains.end(), water_amount, terrain_manager_.GetResource(TerrainType::kWater));
  terrains.insert(terrains.end(), urban_amount, terrain_manager_.GetResource(TerrainType::kUrban));
  terrains.insert(terrains.end(), plains_amount, terrain_manager_.GetResource(TerrainType::kPlains));

  std::shuffle(terrains.begin(), terrains.end(), gen);

  for (int i = 0; i < columns; ++i) {
    for (int j = 0; j < rows; ++j) {
      tiles_[i][j].SetTerrain(terrains[i * rows + j]);
    }
  }
}

void Map::ClusterTerrains(std::mt19937 gen, int k) {
  int columns = tiles_.size();
  int rows = tiles_[0].size();
  int n = columns * rows;

  int iterations = n * k;
  double temperature = 0.75;
  double final_temperature = 0.001;
  double cold_rate = std::pow(final_temperature / temperature, 1.0 / iterations);
  std::uniform_int_distribution<> columns_distribution(0, columns - 1);
  std::uniform_int_distribution<> rows_distribution(0, rows - 1);
  std::uniform_real_distribution<> real_distribution(0.0, 1.0);
  for (int i = 0; i < iterations; ++i) {
    int x1 = columns_distribution(gen);
    int y1 = rows_distribution(gen);
    Vector2I random_tile(x1, y1);
    std::unordered_set<Vector2I> tile_neighbors = GetNeighbors(random_tile);
    std::uniform_int_distribution<> neighbor_distribution(0, tile_neighbors.size()-1);
    int neighbor_index = neighbor_distribution(gen);
    Vector2I random_neighbor_tile = *std::next(tile_neighbors.cbegin(), neighbor_index);
    int x2 = random_neighbor_tile.x;
    int y2 = random_neighbor_tile.y;

    std::shared_ptr<Terrain> terrain1 = tiles_[x1][y1].GetTerrain();
    std::shared_ptr<Terrain> terrain2 = tiles_[x2][y2].GetTerrain();
    if (terrain1 == terrain2) {
      continue;
    }
    double prev1 = CalculateHappiness(random_tile);
    double prev2 = CalculateHappiness(random_neighbor_tile);

    tiles_[x1][y1].SetTerrain(terrain2);
    tiles_[x2][y2].SetTerrain(terrain1);

    double new1 = CalculateHappiness(random_tile);
    double new2 = CalculateHappiness(random_neighbor_tile);

    double delta = (new1 - prev1) + (new2 - prev2);
    if (delta <= 0.0 && real_distribution(gen) >= std::exp(delta / temperature)) {
      tiles_[x1][y1].SetTerrain(terrain1);
      tiles_[x2][y2].SetTerrain(terrain2);
    }
    temperature *= cold_rate;
  }
}

double Map::CalculateHappiness(Vector2I tile) const {
  auto neighbors = GetNeighbors(tile);
  
  double happiness = 0.0;
  TerrainType tile_type = tiles_[tile.x][tile.y].GetTerrain()->GetType();
  for (const auto& neighbor : neighbors) {
    TerrainType neighbor_type = tiles_[neighbor.x][neighbor.y].GetTerrain()->GetType();
    happiness += GetCompatibility(tile_type, neighbor_type);
  }
  happiness /= neighbors.size();
  return happiness;
}

} // namespace fow