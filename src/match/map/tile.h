#pragma once

#include <memory>

#include "terrain.h"
#include "position.h"

namespace fow {
    class Tile {
    public:
        Tile(std::shared_ptr<Terrain> terrain = nullptr);

        void SetTerrain(std::shared_ptr<Terrain> terrain) { terrain_ = terrain; }
        std::shared_ptr<Terrain> GetTerrain() const { return terrain_; }

        void SetPosition(Position position) { position_ = position; }
        Position GetPosition() const { return position_; }
    private:
        Position position_;
        std::shared_ptr<Terrain> terrain_;
    };

}