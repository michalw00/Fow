#include "player.h"

#include <algorithm>
#include <iterator>
#include <memory>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <Vector2.hpp>

#include "../drawable/button/texture_button.h"
#include "../structs/texture_states.h"
#include "../structs/vector2i.h"
#include "../utils/set_operations.h"
#include "map/map.h"
#include "map/terrain.h"
#include "targets/units/unit.h"

namespace fow {

void Player::InitMaps(const std::unique_ptr<Map>& map, float basic_width, float basic_height) {
  auto&& tiles = map->GetTiles();
  auto& terrain_manager = map->GetTerrainManager();

  size_t columns = tiles.size();
  size_t rows = tiles[0].size();

  float edge_space = 0.f;
  basic_width -= edge_space * (static_cast<float>(columns) / rows);
  basic_height -= edge_space;

  RVector2 start_position(-basic_width / 2.f, -basic_height / 2.f);

  RVector2 step(basic_width / columns, basic_height / rows);
  float spacing = 0.035f;
  RVector2 tile_size(step - step * spacing);

  render_map_.resize(columns);
  probabilities_map_.resize(columns);

  for (int i = 0; i < columns; ++i) {
    render_map_[i].reserve(rows);
    probabilities_map_[i].resize(rows);
    for (int j = 0; j < rows; ++j) {
      RVector2 factor(i, j);
      RVector2 position = start_position + (step * factor);
      auto& tile = tiles[i][j];
      TerrainType tile_type = tiles[i][j].GetTerrain()->GetType();
      TextureState tile_textures = terrain_manager.GetTexture(tile_type);

      auto lmb_action = [this, i, j]() {
        if ((selected_tile_position_.x != i || selected_tile_position_.y != j)
          && !selected_unit_) {
          ClearSelectedTile();
          SetSelectedTilePosition({ i, j });
        } else {
          ClearSelectedTile();
        }
      };
      auto rmb_action = [this, i, j]() {
        if (!show_prev_map_) {
          SetActionTilePosition({ i, j });
        }
      };

      auto&& button = std::make_shared<TextureButton>(position, tile_size, lmb_action, tile_textures, rmb_action);
      render_map_[i].emplace_back(button);
    }
  }
}

void Player::Update(const std::unique_ptr<Map>& map, std::vector<Player>&& other_players) {
  DoUnitAction(map);
  UpdateRenderMap();
  UpdateProbabilitiesMap(map, std::move(other_players));
}

void Player::DoUnitAction(const std::unique_ptr<Map>& map) {
  if (!selected_unit_) {
    return;
  }
  switch (current_action_) {
    case fow::UnitAction::kMove:
      MoveSelectedUnit(map);
      break;
    case fow::UnitAction::kRecon:
      ReconTile();
      break;
    case fow::UnitAction::kAttack:
      break;
    case fow::UnitAction::kReinforce:
      break;
    default:
      break;
  }
}

void Player::UpdateRenderMap() {
  int x = selected_tile_position_.x;
  int y = selected_tile_position_.y;
  if (x >= 0 && y >= 0) {
    render_map_[x][y]->SetIsSelected(true);
  }
}

void Player::UpdateProbabilitiesMap(const std::unique_ptr<Map>& map, std::vector<Player>&& other_players) {
  if (show_prev_map_ && turn != 0) {
    return;
  }
  if (!should_update_probabilities_map_) {
    return;
  }

  for (auto& row : probabilities_map_) {
    std::fill(row.begin(), row.end(), -1.f);
  }

  std::vector<std::shared_ptr<Unit>> enemy_units = GetEnemyUnits(std::move(other_players));
  std::unordered_set<Vector2I> scouted_tiles = GetScoutedTiles();

  std::unordered_map<Vector2I, std::unordered_set<Vector2I>> neighbors;
  std::unordered_map<std::shared_ptr<Unit>, std::unordered_set<Vector2I>> unit_related_tiles;

  for (auto& scouted_tile : scouted_tiles) {
    neighbors[scouted_tile] = map->GetNeighbors(scouted_tile);
    for (auto& unit : enemy_units) {
      if (neighbors.at(scouted_tile).contains(unit->GetPosition())) {
        unit_related_tiles[unit].insert(scouted_tile);
      }
    }
  }

  std::unordered_map<std::shared_ptr<Unit>, std::unordered_set<Vector2I>> possible_tiles = GetPossibleTiles(unit_related_tiles, neighbors, scouted_tiles);
  FillProbabilitiesMap(neighbors, possible_tiles, enemy_units);

  should_update_probabilities_map_ = false;
}

std::vector <std::shared_ptr<Unit>> Player::GetEnemyUnits(std::vector<Player>&& other_players) const {
  std::vector<std::shared_ptr<Unit>> enemy_units;
  for (const auto& player : other_players) {
    for (auto& unit : player.units_) {
      enemy_units.push_back(unit);
    }
  }
  return enemy_units;
}

std::unordered_set<Vector2I> Player::GetScoutedTiles() const {
  std::unordered_set<Vector2I> scouted_tiles;
  for (const auto& unit : units_) {
    scouted_tiles.insert(unit->GetPosition());
  }
  for (const auto& tile : was_unit_tiles_) {
    scouted_tiles.insert(tile);
  }
  for (const auto& tile : recon_tiles_) {
    scouted_tiles.insert(tile);
  }
  return scouted_tiles;
}

std::unordered_map<std::shared_ptr<Unit>, std::unordered_set<Vector2I>> Player::GetPossibleTiles(
    const std::unordered_map<std::shared_ptr<Unit>, std::unordered_set<Vector2I>>& unit_related_tiles,
    const std::unordered_map<Vector2I, std::unordered_set<Vector2I>>& neighbors,
    const std::unordered_set<Vector2I>& scouted_tiles) const {

  std::unordered_map<std::shared_ptr<Unit>, std::unordered_set<Vector2I>> possible_tiles;

  for (auto& unit : unit_related_tiles) {
    std::vector<std::unordered_set<Vector2I>> sets;
    for (auto& tile : unit.second) {
      sets.emplace_back(neighbors.at(tile));
    }
    possible_tiles.emplace(unit.first, SetIntersection(sets));
  }

  for (auto& unit : unit_related_tiles) {
    std::unordered_set<Vector2I> not_related_tiles = SetDifference(scouted_tiles, unit.second);
    std::unordered_set<Vector2I> not_related_tiles_neighbors;
    for (auto& not_related_tile : not_related_tiles) {
      not_related_tiles_neighbors.insert(neighbors.at(not_related_tile).cbegin(), neighbors.at(not_related_tile).cend());
    }
    std::vector<std::unordered_set<Vector2I>> exclude{ possible_tiles[unit.first], not_related_tiles_neighbors, scouted_tiles };
    possible_tiles[unit.first] = SetDifference(exclude);
  }
  return possible_tiles;
}

void Player::FillProbabilitiesMap(const std::unordered_map<Vector2I, std::unordered_set<Vector2I>>& neighbors,
    std::unordered_map<std::shared_ptr<Unit>, std::unordered_set<Vector2I>>& possible_tiles,
    const std::vector<std::shared_ptr<Unit>>& enemy_units) {
  for (auto& tile : neighbors) {
    for (auto& neighbor : tile.second) {
      auto is_unit = [neighbor](std::shared_ptr<Unit> unit) { return unit->GetPosition() == neighbor; };
      if (std::none_of(units_.begin(), units_.end(), is_unit)) {
        probabilities_map_[neighbor.x][neighbor.y] = 0.0f;
      } 
    }
  }
  for (auto& tile : recon_tiles_) {
    auto is_unit = [tile](std::shared_ptr<Unit> unit) { return unit->GetPosition() == tile; };
    auto is_enemy_there = [tile, &possible_tiles](std::shared_ptr<Unit> unit) { 
      if (unit->GetPosition() == tile) {
        possible_tiles[unit].clear();
        return true;
      } else {
        return false;
      };
    };
    if (std::any_of(enemy_units.cbegin(), enemy_units.cend(), is_enemy_there)) {
      probabilities_map_[tile.x][tile.y] = 1.f;
    } else if (std::none_of(units_.begin(), units_.end(), is_unit)) {
      probabilities_map_[tile.x][tile.y] = 0.f;
    } else {
      probabilities_map_[tile.x][tile.y] = -1.f;
    }
  }
  for (auto& unit : possible_tiles) {
    for (auto& tile : unit.second) {
      probabilities_map_[tile.x][tile.y] += 1.f / unit.second.size();
    }
  }
}

void Player::StartTurn() {
  ++turn;
  selected_unit_ = nullptr;
  ClearPossibleTiles();

  show_prev_map_ = false;
  prev_units_.clear();
  prev_units_.reserve(units_.size());
  std::transform(
      units_.begin(), units_.end(),
      std::back_inserter(prev_units_),
      [](const std::shared_ptr<Unit>& src) {
    return src ? std::make_shared<Unit>(*src) : nullptr;
  }
  );

  should_update_probabilities_map_ = true;
  prev_map_ = probabilities_map_;
  was_unit_tiles_.clear();
  recon_tiles_.clear();

  ClearActionTile();
  ClearSelectedTile();
  ResetUnitsMovementPoints();
  current_action_ = UnitAction::kMove;
}

void Player::AddUnit(Vector2I position, UnitType unit_type, const UnitManager& unit_manager) {
  units_.emplace_back(std::make_shared<Unit>(position, unit_type, unit_manager.GetResource(unit_type)));
}

void Player::SetSelectedUnit(std::shared_ptr<Unit> unit, const std::unique_ptr<Map>& map) {
  selected_unit_ = unit;
  if (unit) {
    UpdatePossibleTiles(map);
  } else {
    ClearPossibleTiles();
  }
  ClearActionTile();
}

void Player::MoveSelectedUnit(const std::unique_ptr<Map>& map) {
  const auto& tiles = map->GetTiles();

  if (!possible_move_tiles_.contains(action_tile_position_)) {
    return;
  }

  float diagonal_movement_cost = 1.5f;
  float basic_movement_cost = 1.f;

  Vector2I unit_position = selected_unit_->GetPosition();
  if (unit_position.x != action_tile_position_.x && unit_position.y != action_tile_position_.y) {
    selected_unit_->SubstractMovementPoints(diagonal_movement_cost);
  } else {
    selected_unit_->SubstractMovementPoints(basic_movement_cost);
  }

  was_unit_tiles_.emplace(unit_position);
  selected_unit_->SetPosition(action_tile_position_);
  UpdatePossibleTiles(map);

  if (selected_unit_->GetMovementPoints() + 0.1f < basic_movement_cost) {
    selected_unit_ = nullptr;
    ClearPossibleTiles();
  }
  ClearActionTile();
  should_update_probabilities_map_ = true;
}

void Player::ReconTile() {
  if (!possible_recon_tiles_.contains(action_tile_position_)) {
    return;
  }
  
  recon_tiles_.emplace(action_tile_position_);
  ClearActionTile();
  should_update_probabilities_map_ = true;
}

void Player::ClearSelectedTile() {
  int x = selected_tile_position_.x;
  int y = selected_tile_position_.y;

  if (x >= 0 && y >= 0) {
    render_map_[x][y]->SetIsSelected(false);
    selected_tile_position_ = { -2, -2 };
  }
}

void Player::ClearActionTile() {
  action_tile_position_ = { -1, -1 };
}

std::vector<std::shared_ptr<Unit>>& Player::GetUnits() {
  if (show_prev_map_ && turn != 0) {
    return prev_units_;
  } else {
    return units_;
  }
}

const std::vector<std::vector<float>>& Player::GetProbabilitiesMap() const {
  if (show_prev_map_ && turn != 0) {
    return prev_map_;
  } else {
    return probabilities_map_;
  }
}

void Player::SetSelectedTilePosition(Vector2I position) {
  selected_tile_position_ = position;
}

void Player::SetActionTilePosition(Vector2I position) {
  if (selected_unit_) {
    action_tile_position_ = position;
  }
}

void Player::ResetUnitsMovementPoints() {
  for (auto& unit : units_) {
    unit->ResetMovementPoints();
  }
}

void Player::UpdatePossibleTiles(const std::unique_ptr<Map>& map) {
  const auto& tiles = map->GetTiles();

  Vector2I unit_position = selected_unit_->GetPosition();
  auto closest_neighbors = map->GetNeighbors(unit_position);

  possible_move_tiles_ = closest_neighbors;
  auto IsWater = [unit_position, &tiles](Vector2I tile) {
    return tiles[tile.x][tile.y].GetTerrain()->GetType() == TerrainType::kWater;
  };
  std::erase_if(possible_move_tiles_, IsWater);

  auto IsOtherUnitsThere = [this, unit_position](Vector2I tile) {
    auto IsUnitThere = [tile](std::shared_ptr<Unit> unit) {
      return unit->GetPosition() == tile; };

    return std::any_of(units_.cbegin(), units_.cend(), IsUnitThere);
  };
  std::erase_if(possible_move_tiles_, IsOtherUnitsThere);

  auto NotEnoughMovementPoints = [this, unit_position](Vector2I tile) {
    float diagonal_movement_cost = 1.5f;
    float basic_movement_cost = 1.f;
    if (unit_position.x != tile.x && unit_position.y != tile.y) {
      return selected_unit_->GetMovementPoints() + 0.1f < diagonal_movement_cost;
    } else {
      return selected_unit_->GetMovementPoints() + 0.1f < basic_movement_cost;
    }
  };
  std::erase_if(possible_move_tiles_, NotEnoughMovementPoints);
  
  auto unit_recon_range = selected_unit_->GetUnitModifiers()->recon_range;
  possible_recon_tiles_.clear();

  std::unordered_set<Vector2I> current_neighbors = closest_neighbors;
  std::unordered_set<Vector2I> next_neighbors;

  for (int i = 0; i < unit_recon_range; ++i) {
    for (auto& neighbor : current_neighbors) {
      auto neighbor_neighbors = map->GetNeighbors(neighbor);
      next_neighbors.insert(neighbor_neighbors.cbegin(), neighbor_neighbors.cend());
    }
    next_neighbors = SetDifference(next_neighbors, current_neighbors);
    possible_recon_tiles_.insert(current_neighbors.cbegin(), current_neighbors.cend());
    current_neighbors = next_neighbors;
  }

  std::erase_if(possible_recon_tiles_, IsOtherUnitsThere);
  possible_recon_tiles_ = SetDifference(possible_recon_tiles_, recon_tiles_);
  possible_recon_tiles_ = SetDifference(possible_recon_tiles_, was_unit_tiles_);
}

void Player::ClearPossibleTiles() {
  possible_move_tiles_.clear();
  possible_recon_tiles_.clear();
  possible_attack_tiles_.clear();
}

} // namespace fow