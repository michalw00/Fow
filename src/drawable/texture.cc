#include "texture.h"

namespace fow {
    Texture::Texture(RVector2 position, RVector2 size, RTexture&& rtexture) : Drawable(position), rtexture_(std::move(rtexture)) {
        rtexture_.width = size.GetX();
        rtexture_.height = size.GetY();
    }

    void Texture::Draw() const {
        rtexture_.Draw(position_);
    }

    void Texture::Scale(RVector2 scale) {
        position_ *= scale;
        rtexture_.width *= scale.x;
        rtexture_.height *= scale.y;
    }
}