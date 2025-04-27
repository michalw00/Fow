#pragma once

#include <functional>
#include <memory>

#include <Vector2.hpp>
#include <Texture.hpp>

#include "button.h"
#include "../../structs/texture_states.h"

namespace fow {   

    class TextureButton : public Button {
    public:
        TextureButton(RVector2 position, RVector2 size, std::function<void()> action_lmb, TextureState texture = {}, std::function<void()> action_rmb = []() {});

        void Draw() const override;
        void Scale(RVector2 scale) override;     
    private:
        TextureState texture_;
    };
}