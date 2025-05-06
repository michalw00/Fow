#pragma once

#include <vector>
#include <memory>
#include <unordered_set>

#include "Camera2D.hpp"
#include "Vector2.hpp"

#include "../drawable/button/texture_button.h"
#include "map/map.h"
#include "targets/units/unit.h"

namespace fow {
    class Player {
    public:
        void InitCamera(RCamera2D camera) {camera_ = std::make_shared<RCamera2D>(camera);}
        void InitMaps(const Map& map, float basic_width, float basic_height);

        void Update(const Map& map, std::vector<Player>&& other_players);
          
        void StartTurn();

        void AddUnit(Vector2I position, UnitType unit_type, const UnitManager& unit_manager);
        void SetSelectedUnit(std::shared_ptr<Unit> unit);
        const std::shared_ptr<Unit>& GetSelectedUnit() const { return selected_unit_; }                              
        void ClearSelectedTile();
        void ClearMoveTile();

        std::shared_ptr<RCamera2D> GetCamera() { return camera_; }
        std::vector<std::shared_ptr<Unit>>& GetUnits() { return units_; }
        const std::vector<std::vector<std::shared_ptr<Button>>>& GetRenderMap() const { return render_map_; }
        const std::vector<std::vector<float>>& GetProbabilityMap() const { return probability_map_; }
    private:
        void UpdateRenderMap();
        void UpdateProbabilityMap(const Map& map, std::vector<Player>&& other_players);
        void MoveSelectedUnit(const Map& map);

        void SetSelectedTilePosition(Vector2I position);
        void SetMoveTilePosition(Vector2I position);
        void ResetUnitsMovementPoints();

        std::shared_ptr<Unit> selected_unit_ = nullptr;
        Vector2I move_tile_position_ = { -1, -1 };
        Vector2I selected_tile_position_ = { -2, -2 };

        std::shared_ptr<RCamera2D> camera_;
        std::vector<std::shared_ptr<Unit>> units_;
        std::vector<std::vector<std::shared_ptr<Button>>> render_map_;
        std::vector<Vector2I> recon_tiles_;
        std::vector<std::vector<float>> probability_map_;
        std::vector<std::vector<float>> prev_probability_map_;
    };

}