#include "terrain.h"

#include <string>

namespace fow {

TerrainModifiers::TerrainModifiers(TerrainType terrain_type) {
  switch (terrain_type) {
    case TerrainType::kPlains:
      break;
    case TerrainType::kHills:
      range_extend = 1;
      movement_cost = 1.5f;
      break;
    case TerrainType::kMountains:
      range_extend = 1;
      movement_cost = 2.f;
      break;
    case TerrainType::kMarsh:
      movement_cost = 2.f;
      break;
    case TerrainType::kForest:
      movement_cost = 1.5f;
      break;
    case TerrainType::kWater:
      range_extend = -100;
      movement_cost = 2.f;
      break;
  }
}

Terrain::Terrain(TerrainType terrain_type) : terrain_type_(terrain_type), terrain_modifiers_(terrain_type) {}

std::string TerrainManager::GetName(TerrainType terrain_type) const {
  switch (terrain_type) {
    case TerrainType::kPlains: return "Plain";
    case TerrainType::kHills: return "Hills";
    case TerrainType::kMountains: return "Mountains";
    case TerrainType::kMarsh: return "Marsh";
    case TerrainType::kForest: return "Forest";
    case TerrainType::kWater: return "Water";
  }
}

std::string TerrainManager::GetTextureName(TerrainType terrain_type) const {
  switch (terrain_type) {
    case TerrainType::kPlains: return "terrain/plain/plain";
    case TerrainType::kHills: return "terrain/hills/hills";
    case TerrainType::kMountains: return "terrain/mountains/mountains";
    case TerrainType::kMarsh: return "terrain/marsh/marsh";
    case TerrainType::kForest: return "terrain/forest/forest";
    case TerrainType::kWater: return "terrain/water/water";
  }
}

} // namespace fow