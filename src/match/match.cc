#include "match.h"

namespace fow {
    void Match::InitMap(int rows, int columns) {
        map_ = std::make_unique<Map>(rows, columns);
    }

    void Match::InitPlayers(int number) {
        players_.resize(number);

        for (auto& player : players_) {
            player.InitRenderMap(*map_);
        }
    }
}