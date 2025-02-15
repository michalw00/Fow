#pragma once

#include <functional>
#include <memory>

#include <Vector2.hpp>
#include <Texture.hpp>

#include "button.h"

namespace fow {

    class TextureButton : public Button {
    public:
        TextureButton(RVector2 position, std::function<void()> action, std::shared_ptr<RTexture> texture, std::shared_ptr<RTexture> texture_hovered = nullptr);

        void Draw() override;
        void Scale(RVector2 scale) override;
    private:
        std::shared_ptr<RTexture> texture_;
        std::shared_ptr<RTexture> texture_hovered_;
    };
}