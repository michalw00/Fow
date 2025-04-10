#pragma once

#include <vector>
#include <memory>

#include "Camera2D.hpp"
#include "Vector2.hpp"
#include "../drawable/button/texture_button.h"
#include "map/map.h"
#include "targets/units/unit.h"

namespace fow {
    class Player {
    public:
        void InitCamera(RCamera2D camera) {camera_ = std::make_shared<RCamera2D>(camera);}
        void InitRenderMap(const Map& map, float basic_width, float basic_height);
            
        void AddUnit(int position_width, int position_height, UnitType unit_type, const UnitManager& unit_manager);
        void SetSelectedUnit(std::shared_ptr<Unit> unit) { selected_unit_ = unit; }
        void SetSelectedTilePosition(int width, int height) { selected_tile_width_ = width; selected_tile_height_ = height; }
        void StartTurn();
        void MoveSelectedUnit(); 

        std::shared_ptr<RCamera2D> GetCamera() { return camera_; }
        const std::vector<std::shared_ptr<Unit>>& GetUnits() const { return units_; }
        const std::vector<std::vector<std::shared_ptr<TextureButton>>>& GetRenderMap() const { return render_map_; }
    private:      
        void ResetUnitsMovementPoints();

        std::shared_ptr<Unit> selected_unit_ = nullptr;
        int selected_tile_width_ = -1;
        int selected_tile_height_ = -1;

        std::shared_ptr<RCamera2D> camera_;
        std::vector<std::shared_ptr<Unit>> units_;
        std::vector<std::vector<std::shared_ptr<TextureButton>>> render_map_;
    };

}