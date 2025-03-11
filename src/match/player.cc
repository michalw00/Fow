#include "player.h"

namespace fow{
    Player::Player() {}

    void Player::InitRenderMap(const Map& map) {
        auto&& tiles = map.GetTiles();
        auto&& terrain_manager = map.GetTerrainManager();

        size_t columns = tiles.size();
        size_t rows = tiles[0].size();

        RVector2 start_position(-750, -400);

        RVector2 step(1500.f / columns, 800.f / rows);
        float spacing = 0.035f;
        RVector2 tile_size(step-step*spacing);

        render_map_.resize(columns);

        for (size_t i = 0; i < columns; ++i) {
            render_map_.reserve(rows);
            for (size_t j = 0; j < rows; ++j) {
                RVector2 factor(i, j);
                RVector2 position = start_position + (step * factor);
                TerrainType tile_type = tiles[i][j].GetTerrain()->GetType();
                TextureStates tile_textures = terrain_manager.GetTexture(tile_type);
                auto button = std::make_shared<TextureButton>(position, tile_size, [tiles, i, j]() {}, tile_textures);
                render_map_[i].emplace_back(button);
            }
        }
    }
}