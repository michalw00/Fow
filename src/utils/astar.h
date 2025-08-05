#pragma once
#include <vector>
#include <memory>
#include <queue>
#include <vector>
#include <unordered_set>
#include "../structs/vector2i.h"
#include "../match/map/map.h"
#include "../match/map/tile.h"
#include "../match/map/map.h"

namespace fow {

	class AStar {
	public:
		struct Node {
			Vector2I pos;
		};

		bool visited[1024][1024];
		std::vector<Node> open_set;

		void FloodFill(Node start, std::unique_ptr<Map>& map_) {

			open_set.emplace_back(start);

			while (open_set.size() > 0) {
				Node top = open_set[open_set.size() - 1];
				open_set.pop_back();
				visited[top.pos.x][top.pos.y] = 1; // TODO: sprawdzic czy nie wykracza poza
				map_->SetTileFromType(top.pos, TerrainType::kWater);

				PushNode(top, 0, 1);
				PushNode(top, 1, 0);
				PushNode(top, 0, -1);
				PushNode(top, -1, 0);
			}
		}

		void PushNode(Node parent, int dx, int dy) {
			if (visited[parent.pos.x + dx][parent.pos.y + dy]) {
				open_set.push_back(parent);
			}
		}
	};
}