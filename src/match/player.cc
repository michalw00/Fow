#include "player.h"

#include <algorithm>

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

        for (int i = 0; i < columns; ++i) {
            render_map_.reserve(rows);
            for (int j = 0; j < rows; ++j) {
                RVector2 factor(i, j);
                RVector2 position = start_position + (step * factor);
                auto& tile = tiles[i][j];
                TerrainType tile_type = tiles[i][j].GetTerrain()->GetType();
                TextureState tile_textures = terrain_manager.GetTexture(tile_type);
                auto lmb_action = [this, i, j]() {
                    if (selected_tile_position_.x != i || selected_tile_position_.y != j) {
                        ClearSelectedTile();

                        if (selected_unit_
                            && selected_unit_->GetPosition().x == i
                            && selected_unit_->GetPosition().y == j) {
                            return;
                        }

                        SetSelectedTilePosition({ i, j });
                        SetSelectedUnit(nullptr);
                    } else {
                        ClearSelectedTile();
                    }
                };
                auto rmb_action = [this, i, j]() {SetMoveTilePosition({ i, j }); };
                auto&& button = std::make_shared<TextureButton>(position, tile_size, lmb_action, tile_textures, rmb_action);
                render_map_[i].emplace_back(button);
            }
        }
    }

    void Player::UpdateRenderMap() {
        int x = selected_tile_position_.x;
        int y = selected_tile_position_.y;
        if (x >= 0 && y >= 0) {
            render_map_[x][y]->SetIsSelected(true);
        }
    }

    void Player::StartTurn() {
        selected_unit_ = nullptr;
        ClearMoveTile();
        ClearSelectedTile();
        ResetUnitsMovementPoints();
    }

    void Player::AddUnit(Vector2I position, UnitType unit_type, const UnitManager& unit_manager) {
        units_.emplace_back(std::make_shared<Unit>(position, unit_type, unit_manager.GetResource(unit_type)));
    }

    void Player::SetSelectedUnit(std::shared_ptr<Unit> unit) { 
        selected_unit_ = unit;
        ClearMoveTile();
    }

    void Player::MoveSelectedUnit(const Map& map) { 

        const auto& tiles = map.GetTiles();

        if (!selected_unit_) {
            return;
        }

        auto IsOtherUnitThere = [this](auto it) {
            return it->GetPosition() == move_tile_position_; };

        Vector2I distance = selected_unit_->GetPosition() - move_tile_position_;
        distance.x = std::abs(distance.x);
        distance.y = std::abs(distance.y);

        if (move_tile_position_.x >= 0 && move_tile_position_.y >= 0
            && tiles[move_tile_position_.x][move_tile_position_.y].GetTerrain()->GetType() != TerrainType::kWater
            && !std::any_of(units_.cbegin(), units_.cend(), IsOtherUnitThere)
            && distance.x <= 1 && distance.y <= 1) {

            float diagonal_movement_cost = 1.5f;
            float basic_movement_cost = 1.f;

            if (distance.x == 1 && distance.y == 1
                && selected_unit_->GetMovementPoints()+0.1f >= diagonal_movement_cost) {
                selected_unit_->SubstractMovementPoints(diagonal_movement_cost);
            } else if (distance.x != 1 || distance.y != 1
                && selected_unit_->GetMovementPoints()+0.1f >= basic_movement_cost) {
                selected_unit_->SubstractMovementPoints(basic_movement_cost);
            } else {
                return;
            }

            selected_unit_->SetPosition(move_tile_position_);

            if (!(selected_unit_->GetMovementPoints() + 0.1f >= basic_movement_cost)) {
                selected_unit_ = nullptr;
            }
            ClearMoveTile();
        } else {
            return;
        }
    }

    void Player::ClearSelectedTile() {
        int x = selected_tile_position_.x;
        int y = selected_tile_position_.y;

        if (x >= 0 && y >= 0) {
            render_map_[x][y]->SetIsSelected(false);
            selected_tile_position_ = { -2, -2 };
        }
    }

    void Player::ClearMoveTile() {
        move_tile_position_ = { -1, -1 };
    }

    void Player::SetSelectedTilePosition(Vector2I position) {
        selected_tile_position_ = position;
    } 

    void Player::SetMoveTilePosition(Vector2I position) {
        if (selected_unit_) {
            move_tile_position_ = position;
        }

    }       

    void Player::ResetUnitsMovementPoints() {
        for (auto& unit : units_) {
            unit->ResetMovementPoints();
        }
    }
  
}