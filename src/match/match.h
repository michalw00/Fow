#pragma once

#include <memory>
#include "map/map.h"
#include "player.h"

namespace fow {

	class Match {
	public:
		void InitMap(int rows, int columns);
		void InitPlayers(int number = 2);

		void UpdateRenderMap();

		Map GetMap() const { return *map_; }
		std::vector<Player> GetPlayers() const { return players_; }
	private:
		std::unique_ptr<Map> map_;
		std::vector<Player> players_;
	};

}