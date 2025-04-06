#include "map.h"

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
        auto plain_terrain = terrain_manager_.GetResource(TerrainType::kPlains);
        for (auto& row : tiles_) {
            for (auto& tile : row) {
                tile.SetTerrain(plain_terrain);
            }
        } 
    }
}