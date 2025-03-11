#pragma once

#include <functional>
#include <memory>

#include <Vector2.hpp>
#include <Texture.hpp>

#include "button.h"

namespace fow {
    struct TextureStates {
        TextureStates(std::shared_ptr<RTexture> basic = nullptr, std::shared_ptr<RTexture> hovered = nullptr, std::shared_ptr<RTexture> fow = nullptr);           

        std::shared_ptr<RTexture> basic;
        std::shared_ptr<RTexture> hovered;
        std::shared_ptr<RTexture> fow;
    };

    class TextureButton : public Button {
    public:
        TextureButton(RVector2 position, RVector2 size, std::function<void()> action, TextureStates texture);

        bool SetFow(bool fow) { fow_ = fow; }

        void Draw() const override;
        void Scale(RVector2 scale) override;     
    private:
        bool fow_ = true;

        TextureStates texture_;
    };
}