#pragma once

#include "terrain.h"
#include <memory>

namespace fow {
    class Tile {
    public:
        Tile(std::shared_ptr<Terrain> terrain = nullptr);

        void SetTerrain(std::shared_ptr<Terrain> terrain) { terrain_ = terrain; }
        std::shared_ptr<Terrain> GetTerrain() const { return terrain_; }
    private:
        std::shared_ptr<Terrain> terrain_;
    };

}