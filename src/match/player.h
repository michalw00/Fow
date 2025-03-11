#pragma once

#include <vector>

#include "Camera2D.hpp"
#include "Vector2.hpp"
#include "../drawable/button/texture_button.h"
#include "map/map.h"

#include <memory>

namespace fow {
    class Player {
    public:
        Player();
        void InitRenderMap(const Map& map);

        std::vector<std::vector<std::shared_ptr<TextureButton>>> GetRenderMap() const { return render_map_; }
    private:
        struct Coordinates {
            int width; 
            int height;
        };
        struct UnitWithCoordinates {
            // Unit unit;
            Coordinates tile_coordinates;
        };
        struct TileFow {
            Coordinates tile_coordinates;
            bool IsFow;
        };
   
        std::shared_ptr<RCamera2D> camera_;
        std::vector<UnitWithCoordinates> units_;
        std::vector<TileFow> tiles_fow_;
        std::vector<std::vector<std::shared_ptr<TextureButton>>> render_map_;
    };

}