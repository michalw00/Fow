#include "map.h"
#include <time.h>

namespace fow {
    Map::Map(int rows, int columns) {
        InitSize(rows, columns);
        InitTiles();
    }
    void Map::InitSize(int rows, int columns) {
        tiles_.resize(columns);

        for (int i = 0; i < columns; ++i) {
            tiles_[i].resize(rows);
        }
    }

    void Map::InitTiles() { 
        std::shared_ptr<Terrain> terrain = terrain_manager_.GetResource(TerrainType::kPlains);
        srand(time(NULL));
        for (auto& row : tiles_) {
            for (auto& tile : row) {
                // Hardcoded map generation

                int random = rand()%20;
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
}