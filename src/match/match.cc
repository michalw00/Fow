#include "match.h"

namespace fow {
    void Match::InitMap(int rows, int columns) {
        map_ = std::make_unique<Map>(rows, columns);
    }

    void Match::InitPlayers(float basic_width, float basic_height, int number) {
        players_.resize(number);

        for (auto& player : players_) {
            player.InitRenderMap(*map_, basic_width, basic_height);
        }

        current_player_index_ = 0;

    }

    void Match::EndTurn() {
        NextPlayer();
    }

    void Match::NextPlayer() {
        if (current_player_index_ >= players_.size() - 1) {
            current_player_index_ = 0;
        } else {
            ++current_player_index_;
        }
    }
}