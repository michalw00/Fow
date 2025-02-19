#include "match.h"

namespace fow {
    Match::Match(int map_rows, int map_columns, std::shared_ptr<RTexture> texture) : map_(map_rows, map_columns, texture) {}
}