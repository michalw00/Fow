#include "player.h"

#include "algorithm"

namespace fow {
    void Player::InitRenderMap(const Map& map, float basic_width, float basic_height) {
        auto&& tiles = map.GetTiles();
        auto& terrain_manager = map.GetTerrainManager();

        size_t columns = tiles.size();
        size_t rows = tiles[0].size();

        float edge_space = 100.f;
        basic_width -= edge_space*(columns/rows);
        basic_height -= edge_space;

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
                auto lmb_action = [this, i, j]() {
                    if (selected_tile_width_ != i && selected_tile_height_ != j) {
                        ClearSelectedTile();

                        if (selected_unit_ != nullptr
                            && selected_unit_->GetPositionWidth() == i
                            && selected_unit_->GetPositionHeight() == j) {
                            return;
                        }

                        SetSelectedTilePosition(i, j);
                        SetSelectedUnit(nullptr);
                    } else {
                        ClearSelectedTile();
                    }
                };
                auto rmb_action = [this, i, j]() {SetMoveTilePosition(i, j); };
                auto&& button = std::make_shared<TextureButton>(position, tile_size, lmb_action, tile_textures, rmb_action);
                render_map_[i].emplace_back(button);
            }
        }
    }

    void Player::UpdateRenderMap() {
        if ((selected_tile_width_ >= 0) && (selected_tile_height_ >= 0)) {
            render_map_[selected_tile_width_][selected_tile_height_]->SetIsSelected(true);
        }
    }

    void Player::StartTurn() {
        selected_unit_ = nullptr;
        ClearMoveTile();
        ClearSelectedTile();
        ResetUnitsMovementPoints();
    }

    void Player::AddUnit(int position_width, int position_height, UnitType unit_type, const UnitManager& unit_manager) {
        units_.emplace_back(std::make_shared<Unit>(position_width, position_height, unit_type, unit_manager.GetResource(unit_type)));
    }

    void Player::SetSelectedUnit(std::shared_ptr<Unit> unit) { 
        selected_unit_ = unit;
        ClearMoveTile();
    }

    void Player::MoveSelectedUnit(const Map& map) { 

        const auto& tiles = map.GetTiles();

        if (selected_unit_ == nullptr) {
            return;
        }

        auto IsOtherUnitThere = [this](auto it) {
            return (it->GetPositionWidth() == move_tile_width_
                && it->GetPositionHeight() == move_tile_height_); };

        int horizontal_distance = std::abs(selected_unit_->GetPositionWidth() - move_tile_width_);
        int vertical_distance = std::abs(selected_unit_->GetPositionHeight() - move_tile_height_);

        if (move_tile_width_ >= 0 
            && move_tile_height_ >= 0 
            && tiles[move_tile_width_][move_tile_height_].GetTerrain()->GetType() != TerrainType::kWater
            && !std::any_of(units_.cbegin(), units_.cend(), IsOtherUnitThere)
            && horizontal_distance <= 1 && vertical_distance <= 1) {

            float diagonal_movement_cost = 1.5f;
            float basic_movement_cost = 1.f;

            if (horizontal_distance == 1 && vertical_distance == 1 
                && selected_unit_->GetMovementPoints()+0.1f >= diagonal_movement_cost) {
                selected_unit_->SubstractMovementPoints(diagonal_movement_cost);
            } else if ((horizontal_distance != 1 || vertical_distance != 1) 
                && selected_unit_->GetMovementPoints()+0.1f >= basic_movement_cost) {
                selected_unit_->SubstractMovementPoints(basic_movement_cost);
            } else {
                return;
            }

            selected_unit_->SetPosition(move_tile_width_, move_tile_height_);

            if (!(selected_unit_->GetMovementPoints() + 0.1f >= basic_movement_cost)) {
                selected_unit_ = nullptr;
            }
            ClearMoveTile();
        } else {
            return;
        }
    }

    void Player::ClearSelectedTile() {
        if ((selected_tile_width_ >= 0) && selected_tile_height_ >= 0) {
            render_map_[selected_tile_width_][selected_tile_height_]->SetIsSelected(false);
            selected_tile_width_ = -2;
            selected_tile_height_ = -2;
        }
    }

    void Player::ClearMoveTile() {
        move_tile_width_ = -1;
        move_tile_height_ = -1;
    }

    void Player::SetSelectedTilePosition(int width, int height) {
        selected_tile_width_ = width;
        selected_tile_height_ = height;
    } 

    void Player::SetMoveTilePosition(int width, int height) { 
        if (selected_unit_ != nullptr) {
            move_tile_width_ = width;
            move_tile_height_ = height;
        }

    }       

    void Player::ResetUnitsMovementPoints() {
        for (auto& unit : units_) {
            unit->ResetMovementPoints();
        }
    }
  
}