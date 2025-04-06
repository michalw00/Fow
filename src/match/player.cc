#include "player.h"

namespace fow {
    void Player::InitRenderMap(const Map& map, float basic_width, float basic_height) {
        float edge_space = 100.f;
        basic_width -= edge_space;
        basic_height -= edge_space;

        auto&& tiles = map.GetTiles();
        auto& terrain_manager = map.GetTerrainManager();

        size_t columns = tiles.size();
        size_t rows = tiles[0].size();       

        RVector2 start_position(-basic_width/2.f, -basic_height/2.f);

        RVector2 step(basic_width / columns, basic_height / rows);
        float spacing = 0.035f;
        RVector2 tile_size(step-step*spacing);

        render_map_.resize(columns);

        for (size_t i = 0; i < columns; ++i) {
            render_map_.reserve(rows);
            for (size_t j = 0; j < rows; ++j) {
                RVector2 factor(i, j);
                RVector2 position = start_position + (step * factor);
                TerrainType tile_type = tiles[i][j].GetTerrain()->GetType();
                TextureState tile_textures = terrain_manager.GetTexture(tile_type);
                auto&& button = std::make_shared<TextureButton>(position, tile_size, [tiles, i, j]() {}, tile_textures);
                render_map_[i].emplace_back(button);
            }
        }

    }
}