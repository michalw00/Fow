#include "tile.h"

#include <memory>

#include "../../structs/vector2i.h"
#include "terrain.h"

namespace fow {

Tile::Tile(Vector2I position, std::shared_ptr<Terrain> terrain) : position_(position), terrain_(terrain) {}

} // namespace fow