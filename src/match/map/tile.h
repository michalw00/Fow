#pragma once

#include "../../drawable/button/texture_button.h"

namespace fow {
    class Tile {
    public:
        Tile(std::shared_ptr<TextureButton> texture_button);
    private:
        std::shared_ptr<TextureButton> texture_button_;
    };

}