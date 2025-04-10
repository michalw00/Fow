#include "player.h"

#include "algorithm"

namespace fow {
    void Player::AddUnit(int position_width, int position_height, UnitType unit_type, const UnitManager& unit_manager) {
        units_.emplace_back(std::make_shared<Unit>(position_width, position_height, unit_type, unit_manager.GetResource(unit_type)));
    }

    void Player::InitRenderMap(const Map& map, float basic_width, float basic_height) {
        float edge_space = 100.f;
        basic_width -= edge_space;
        basic_height -= edge_space;

        auto&& tiles = map.GetTiles();
        auto& terrain_manager = map.GetTerrainManager();

        size_t columns = tiles.size();
        size_t rows = tiles[0].size();       

        RVector2 start_position(-basic_width/2.f, -basic_height/2.f);

        RVector2 step(basic_width / columns, basic_height / rows);
        float spacing = 0.035f;
        RVector2 tile_size(step-step*spacing);

        render_map_.resize(columns);

        for (size_t i = 0; i < columns; ++i) {
            render_map_.reserve(rows);
            for (size_t j = 0; j < rows; ++j) {
                RVector2 factor(i, j);
                RVector2 position = start_position + (step * factor);
                auto& tile = tiles[i][j];
                TerrainType tile_type = tiles[i][j].GetTerrain()->GetType();
                TextureState tile_textures = terrain_manager.GetTexture(tile_type);
                auto&& button = std::make_shared<TextureButton>(position, tile_size, [this, i, j]() {SetSelectedTilePosition(i, j); }, tile_textures);
                render_map_[i].emplace_back(button);
            }
        }
    }
    
    void Player::StartTurn() {
        selected_unit_ = nullptr;
        selected_tile_width_ = -1; 
        selected_tile_height_ = -1;
        ResetUnitsMovementPoints();
    }

    void Player::ResetUnitsMovementPoints() {
        for (auto& unit : units_) {
            unit->ResetMovementPoints();
        }
    }

    void Player::MoveSelectedUnit() { 

        if (selected_unit_ == nullptr) {
            return;
        }

        auto IsOtherUnitThere = [this](auto it) {
            return (it->GetPositionWidth() == selected_tile_width_
                && it->GetPositionHeight() == selected_tile_height_); };
       
        int horizontal_distance = std::abs(selected_unit_->GetPositionWidth() - selected_tile_width_);
        int vertical_distance = std::abs(selected_unit_->GetPositionHeight() - selected_tile_height_);

        if (selected_tile_width_ >= 0 
            && selected_tile_height_ >= 0
            && !std::any_of(units_.cbegin(), units_.cend(), IsOtherUnitThere)
            && horizontal_distance <= 1 && vertical_distance <= 1) {

            int diagonal_movement_cost = 1.5f;
            int basic_movement_cost = 1.f;

            if (horizontal_distance == 1 && vertical_distance == 1 
                && selected_unit_->GetMovementPoints()+0.1f >= diagonal_movement_cost) {
                selected_unit_->SubstractMovementPoints(diagonal_movement_cost);
            } else if (selected_unit_->GetMovementPoints()+0.1f >= basic_movement_cost) {
                selected_unit_->SubstractMovementPoints(basic_movement_cost);
            } else {
                return;
            }

            selected_unit_->SetPosition(selected_tile_width_, selected_tile_height_);
            
            selected_unit_ = nullptr;
            selected_tile_width_ = -1;
            selected_tile_height_ = -1;
        } else {
            return;
        }
    }
}