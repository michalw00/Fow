#pragma once

#include <vector>

#include "tile.h"

namespace fow {

    class Map {
    public:
        Map(int rows, int columns, std::shared_ptr<RTexture> texture);

        std::vector<std::vector<Tile>> GetTiles() const { return tiles_; }
    private:
        void InitSize(int rows, int columns);
        void InitTiles(std::shared_ptr<RTexture> texture);

        std::vector<std::vector<Tile>> tiles_;
    };
}