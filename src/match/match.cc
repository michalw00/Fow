#include "match.h"

namespace fow {
    void Match::InitMap(int rows, int columns) {
        map_ = std::make_unique<Map>(rows, columns);
    }

    void Match::InitPlayers(float basic_width, float basic_height, RCamera2D camera, int number) {
        players_.resize(number);
        for (auto& player : players_) {
            player.InitCamera(camera);
            player.InitRenderMap(*map_, basic_width, basic_height);
        }
        players_[0].AddUnit(1, 1, UnitType::kAntiTank, unit_manager_);
        players_[0].AddUnit(2, 2, UnitType::kInfantry, unit_manager_);
        players_[1].AddUnit(2, 2, UnitType::kInfantry, unit_manager_);
        current_player_index_ = 0;
    }

    void Match::EndTurn() {
        NextPlayer();
        players_[current_player_index_].StartTurn();
    }

    void Match::NextPlayer() {
        if (current_player_index_ >= players_.size() - 1) {
            current_player_index_ = 0;
        } else {
            ++current_player_index_;
        }
    }
}