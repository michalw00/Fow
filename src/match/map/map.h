#pragma once

#include <vector>

#include "tile.h"
#include "terrain.h"

namespace fow {

    class Map {
    public:
        Map(int rows, int columns);

        std::vector<std::vector<Tile>> GetTiles() const { return tiles_; }
        TerrainManager GetTerrainManager() const { return terrain_manager_; }
        void SetTerrainManager(TerrainManager terrain_manager) { terrain_manager_ = terrain_manager; }
    private:
        void InitSize(int rows, int columns);
        void InitTiles();

        TerrainManager terrain_manager_;
        std::vector<std::vector<Tile>> tiles_;
    };
}