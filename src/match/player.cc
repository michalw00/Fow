#include "player.h"

#include <algorithm>
#include <unordered_map>

namespace fow {
    void Player::InitMaps(const Map& map, float basic_width, float basic_height) {
        auto&& tiles = map.GetTiles();
        auto& terrain_manager = map.GetTerrainManager();

        size_t columns = tiles.size();
        size_t rows = tiles[0].size();

        float edge_space = 0.f;
        basic_width -= edge_space*(columns/rows);
        basic_height -= edge_space;

        RVector2 start_position(-basic_width/2.f, -basic_height/2.f);

        RVector2 step(basic_width / columns, basic_height / rows);
        float spacing = 0.035f;
        RVector2 tile_size(step-step*spacing);

        render_map_.resize(columns);
        probability_map_.resize(columns);

        for (int i = 0; i < columns; ++i) {
            render_map_[i].reserve(rows);
            probability_map_[i].resize(rows);
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

    void Player::Update(const Map& map, std::vector<Player>&& other_players) {
        MoveSelectedUnit(map);
        UpdateRenderMap();
        UpdateProbabilityMap(map, std::move(other_players));
    }

    void Player::UpdateRenderMap() {
        int x = selected_tile_position_.x;
        int y = selected_tile_position_.y;
        if (x >= 0 && y >= 0) {
            render_map_[x][y]->SetIsSelected(true);
        }
    }

    void Player::UpdateProbabilityMap(const Map& map, std::vector<Player>&& other_players) {
        for (auto& row : probability_map_) {
            std::fill(row.begin(), row.end(), -1.f);
        }        

        std::vector<std::shared_ptr<Unit>> other_players_units;
        for (const auto& player : other_players) {
            for (auto& unit : player.units_) {
                other_players_units.push_back(unit);
            }
        }     

        std::unordered_map <Vector2I, std::vector<std::shared_ptr<Unit>>> scouted_tiles;
        for (const auto& unit : units_) {
            scouted_tiles.emplace(unit->GetPosition(), std::vector<std::shared_ptr<Unit>>{});
        }
        for (const auto& recon_tile : recon_tiles_) {
            scouted_tiles.emplace(recon_tile, std::vector<std::shared_ptr<Unit>>{});
        }

        std::unordered_map <Vector2I, std::unordered_map<Vector2I, Tile>> neighbors_cache;

        for (auto& unit : other_players_units) {
            Vector2I unit_position = unit->GetPosition();
            for (auto& scouted_tile : scouted_tiles) {
                if (unit_position == scouted_tile.first) {
                    break;
                }
                if (!neighbors_cache.contains(scouted_tile.first)) {
                    neighbors_cache.emplace(scouted_tile.first, map.GetNeighbors(scouted_tile.first));
                }
                if (neighbors_cache[scouted_tile.first].contains(unit_position)) {
                    scouted_tile.second.push_back(unit);
                }
            }
        }

        ScoutTilesIntersections(scouted_tiles, neighbors_cache);
        ScoutTilesSymmetricDifference(scouted_tiles, neighbors_cache);
        FillProbabilityMap(scouted_tiles, neighbors_cache);

        for (auto& unit : units_) {
            Vector2I unit_position = unit->GetPosition();
            probability_map_[unit_position.x][unit_position.y] = -1.f;
        }
    }

    void Player::ScoutTilesIntersections(std::unordered_map <Vector2I, std::vector<std::shared_ptr<Unit>>>& scouted_tiles,
        std::unordered_map <Vector2I, std::unordered_map<Vector2I, Tile>>& neighbors_cache) {

        for (auto it = scouted_tiles.begin(); it != std::prev(scouted_tiles.end()); ++it) {
            auto& it_cache = neighbors_cache[it->first];
            for (auto& unit : it->second) {           
                for (auto other = std::next(it); other != scouted_tiles.end(); ++other) {
                    auto& other_cache = neighbors_cache[other->first];
                    for (auto& other_unit : other->second) {
                        if (unit == other_unit) {                       
                            
                            std::unordered_map<Vector2I, Tile> new_cache;
                            for (auto& tile : it_cache) {
                                if (other_cache.contains(tile.first)) {
                                    new_cache.emplace(tile.first, tile.second);
                                }
                            }
                            for (auto& tile : neighbors_cache[it->first]) {
                                probability_map_[tile.first.x][tile.first.y] = 0.0f;
                            }
                            for (auto& tile : neighbors_cache[other->first]) {
                                probability_map_[tile.first.x][tile.first.y] = 0.0f;
                            }
                            neighbors_cache[it->first] = new_cache;
                            neighbors_cache[other->first] = new_cache;
                        }
                    }
                }
            }
        }
    }

    void Player::ScoutTilesSymmetricDifference(std::unordered_map <Vector2I, std::vector<std::shared_ptr<Unit>>>& scouted_tiles,
        std::unordered_map <Vector2I, std::unordered_map<Vector2I, Tile>>& neighbors_cache) {
        if (scouted_tiles.empty()) return;

        for (auto it = scouted_tiles.begin(); it != std::prev(scouted_tiles.end()); ++it) {
            auto& it_cache = neighbors_cache[it->first];
            for (auto other = std::next(it); other != scouted_tiles.end(); ++other) {
                auto& other_cache = neighbors_cache[other->first];

                std::vector<Vector2I> keys_to_erase;
                for (const auto& tile : it_cache) {
                    if (other_cache.contains(tile.first)) {
                        probability_map_[tile.first.x][tile.first.y] = 0.0f;
                        keys_to_erase.push_back(tile.first);
                    }
                }
                if (keys_to_erase.size() == it_cache.size()) {
                    break;
                } else {
                    for (const auto& key : keys_to_erase) {
                        it_cache.erase(key);
                        other_cache.erase(key);
                    }
                }
            }
        }
    }

    void Player::FillProbabilityMap(std::unordered_map <Vector2I, std::vector<std::shared_ptr<Unit>>>& scouted_tiles,
        std::unordered_map <Vector2I, std::unordered_map<Vector2I, Tile>>& neighbors_cache) {
        for (auto& scouted_tile : scouted_tiles) {
            auto& neighbor_tiles = neighbors_cache[scouted_tile.first];
            int neighbor_tiles_size = neighbor_tiles.size();
            for (auto& tile : neighbor_tiles) {
                probability_map_[tile.first.x][tile.first.y] = static_cast<float>(scouted_tile.second.size()) / neighbor_tiles_size;
            }
        }
    }

    void Player::StartTurn() {
        selected_unit_ = nullptr;
        prev_probability_map_ = probability_map_;
        recon_tiles_.clear();
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

            recon_tiles_.push_back(selected_unit_->GetPosition());
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