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
    }
}