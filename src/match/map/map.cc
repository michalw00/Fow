#include "map.h"

namespace fow {
    Map::Map(int rows, int columns, std::shared_ptr<RTexture> texture) {
        InitSize(rows, columns);
        InitTiles(texture);
    }
    void Map::InitSize(int rows, int columns) {
        tiles_.resize(columns);

        for (int i = 0; i < columns; ++i) {
            tiles_[i].resize(rows);
        }
    }

    void Map::InitTiles(std::shared_ptr<RTexture> texture) {      
        int columns = tiles_.size();
        int rows = tiles_[0].size();
        
        RVector2 start_position(-750, -400);
        float tile_width = 1500.f / columns-1;
        float tile_height = 800.f / rows-1;
        RVector2 step(tile_width + 1, tile_height + 1);
        texture->width = tile_width;
        texture->height = tile_height;

        for (int i = 0; i < columns; ++i) {
            for (int j = 0; j < rows; ++j) {
                RVector2 factor(i, j);
                RVector2 position = start_position + (step * factor);
                tiles_[i][j].SetTextureButton(std::make_shared<TextureButton>(position, [this, i, j]() {tiles_[i][j].GetTextureButton()->SetPosition(RVector2(-10000, -10000)); }, texture));
            }
        }
    }
}