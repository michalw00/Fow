#pragma once

#include "../../drawable/button/texture_button.h"

namespace fow {
    class Tile {
    public:
        Tile();

        void SetTextureButton(std::shared_ptr<TextureButton>  texture_button) { texture_button_ = texture_button; }
        std::shared_ptr<TextureButton> GetTextureButton() const { return texture_button_; }
    private:
        std::shared_ptr<TextureButton> texture_button_;
    };

}