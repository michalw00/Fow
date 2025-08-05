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
		Vector2I bounds;

		void FloodFill(Node start, std::unique_ptr<Map>& map_) {
			bounds.x = 16;
			bounds.y = 16;
			open_set.emplace_back(start);

			while (open_set.size() > 0) {
				Node top = open_set[open_set.size() - 1];
				open_set.pop_back();
				visited[top.pos.y][top.pos.x] = 1; // TODO: sprawdzic czy nie wykracza poza
				if (IsInBounds(top.pos, { 0,0 }, bounds))
					map_->SetTileFromType(top.pos, TerrainType::kWater);

				PushNode(top, 0, 1);
				PushNode(top, 1, 0);
				PushNode(top, 0, -1);
				PushNode(top, -1, 0);
			}
		}

		static inline bool IsInBounds(Vector2I point, Vector2I min, Vector2I max)
		{
			bool result = (point.x >= min.x) && (point.y >= min.y) &&
				(point.x < max.x) && (point.y < max.y);
			return result;
		}

		void PushNode(Node parent, int dx, int dy) {
			if (IsInBounds(parent.pos, { 0,0 }, bounds)) {
				if (!visited[parent.pos.y + dy][parent.pos.x + dx]) {
					parent.pos.x = parent.pos.x + dx;
					parent.pos.y = parent.pos.y + dy;
					open_set.push_back(parent);
				}

			}
		}
	};
}