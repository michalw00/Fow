#include "player.h"

#include <memory>
#include <vector>

#include <Camera2D.hpp>

#include "map/map.h"
#include "match.h"
#include "targets/units/unit.h"

namespace fow {

void Match::InitMap(int rows, int columns) {
  map_ = std::make_unique<Map>(rows, columns);
}

void Match::InitPlayers(float basic_width, float basic_height, RCamera2D camera, int number) {
  players_.resize(number);
  for (auto& player : players_) {
    player.InitCamera(camera);
    player.InitMaps(map_, basic_width, basic_height);
  }
  players_[0].StartTurn();
  players_[0].AddUnit({ 1, 4 }, UnitType::kAntiTank, unit_manager_);
  players_[0].AddUnit({ 1, 3 }, UnitType::kInfantry, unit_manager_);
  players_[0].AddUnit({ 2, 1 }, UnitType::kInfantry, unit_manager_);
  players_[1].AddUnit({ 3, 2 }, UnitType::kInfantry, unit_manager_);
  players_[1].AddUnit({ 3, 4 }, UnitType::kInfantry, unit_manager_);
  current_player_index_ = 0;
}

void Match::EndTurn() {
  NextPlayer();
  players_[current_player_index_].StartTurn();
}

std::vector<Player> Match::GetOtherPlayers() const {
  std::vector<Player> other_players = players_;
  other_players.erase(other_players.begin() + current_player_index_);
  return other_players;
}

void Match::NextPlayer() {
  if (current_player_index_ >= players_.size() - 1) {
    current_player_index_ = 0;
  } else {
    ++current_player_index_;
  }
}

} // namespace fow