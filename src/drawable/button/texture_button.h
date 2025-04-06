#pragma once

#include <functional>
#include <memory>

#include <Vector2.hpp>
#include <Texture.hpp>

#include "button.h"
#include "../texture_manager.h"

namespace fow {   

    class TextureButton : public Button {
    public:
        TextureButton(RVector2 position, RVector2 size, std::function<void()> action, TextureState texture);

        bool SetFow(bool fow) { fow_ = fow; }

        void Draw() const override;
        void Scale(RVector2 scale) override;     
    private:
        bool fow_ = true;

        TextureState texture_;
    };
}