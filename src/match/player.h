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
        void UpdateRenderMap();
          
        void StartTurn();

        void AddUnit(int position_width, int position_height, UnitType unit_type, const UnitManager& unit_manager);
        void SetSelectedUnit(std::shared_ptr<Unit> unit);
        const std::shared_ptr<Unit>& GetSelectedUnit() const { return selected_unit_; }                      
        void MoveSelectedUnit(const Map& map); 
        void ClearSelectedTile();
        void ClearMoveTile();

        std::shared_ptr<RCamera2D> GetCamera() { return camera_; }
        std::vector<std::shared_ptr<Unit>>& GetUnits() { return units_; }
        const std::vector<std::vector<std::shared_ptr<TextureButton>>>& GetRenderMap() const { return render_map_; }
    private:    
        void SetSelectedTilePosition(int width, int height);
        void SetMoveTilePosition(int width, int height);
        void ResetUnitsMovementPoints();

        std::shared_ptr<Unit> selected_unit_ = nullptr;
        int move_tile_width_ = -1;
        int move_tile_height_ = -1;
        int selected_tile_width_ = -2;
        int selected_tile_height_ = -2;

        std::shared_ptr<RCamera2D> camera_;
        std::vector<std::shared_ptr<Unit>> units_;
        std::vector<std::vector<std::shared_ptr<TextureButton>>> render_map_;
    };

}