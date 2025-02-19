#pragma once

#include <memory>
#include "map/map.h"

namespace fow {

	class Match {
	public:
		Match(int map_rows, int map_columns, std::shared_ptr<RTexture> texture);

		Map GetMap() const { return map_; }
	private:
		Map map_;
	};

}