#include "terrain.h"

namespace fow {
    Terrain::Terrain(TerrainType terrain_type) : terrain_type_(terrain_type) {}

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
}