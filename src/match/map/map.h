#pragma once

#include <vector>

#include "tile.h"

namespace fow {

    class Map {
    private:
        std::vector<std::vector<Tile>> tiles_;
    };
}