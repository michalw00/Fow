#include "terrain.h"

#include <string>

namespace fow {

Terrain::Terrain(TerrainType terrain_type) : terrain_type_(terrain_type) {}

std::string TerrainManager::GetName(TerrainType terrain_type) const {
  switch (terrain_type) {
    case TerrainType::kPlains: return "Plain";
    case TerrainType::kHills: return "Hills";
    case TerrainType::kMountains: return "Mountains";
    case TerrainType::kMarsh: return "Marsh";
    case TerrainType::kForest: return "Forest";
    case TerrainType::kWater: return "Water";
    default: return "";
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
    default: return "";
  }
}

} // namespace fow