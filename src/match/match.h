#pragma once

#include <memory>
#include "map/map.h"
#include "player.h"

namespace fow {

	class Match {
	public:
		void InitMap(int rows, int columns);
		void InitPlayers(float basic_width, float basic_height, int number = 2);

		void EndTurn();

		void UpdateRenderMap();

		Map GetMap() const { return *map_; }
		std::vector<Player> GetPlayers() const { return players_; }
		const Player& GetCurrentPlayer() const { return players_.at(current_player_index_); }
	private:
		void NextPlayer();

		std::unique_ptr<Map> map_;
		std::vector<Player> players_;

		int current_player_index_;
	};

}