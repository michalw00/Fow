#pragma once

#include <functional>

#include <Rectangle.hpp>
#include <Vector2.hpp>
#include <Text.hpp>
#include <Texture.hpp>
#include <Camera2D.hpp>

#include "drawable.h"

namespace fow {

    class Button : public Drawable  {
    public:
        Button(RVector2 position, std::function<void()> action);
        virtual ~Button() {}; 
        void CheckMouse(const RCamera2D& camera);
    protected:
        bool is_hovered = 0;
        RRectangle area_;
        std::function<void()> action_;    
    };

    class TextureButton : public Button {
        TextureButton(RVector2 position, RTexture&& texture, std::function<void()> action);

        void Draw() override;
        void Scale(RVector2 scale) override;
    private: 
        RTexture texture_; 
        RTexture texture_hovered_;
    };

    class TextButton : public Button {
    public:
        TextButton(RVector2 position, const RText& rtext, bool centered, std::function<void()> action);

        void Draw() override;
        void Scale(RVector2 scale) override;
    private:
        RText rtext_;
        RText rtext_hovered_;
    };
}