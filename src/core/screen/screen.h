#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <functional>

#include <Image.hpp>
#include <Text.hpp>
#include <Texture.hpp>
#include <Vector2.hpp>
#include <Camera2D.hpp>
#include <Window.hpp>
#include <Rectangle.hpp>

#include "../../drawable/drawable.h"
#include "../../drawable/button.h"

namespace fow {

    enum class ScreenType {
        kMenu,
        kMatch
    };

    class Screen {
    public:
        virtual ~Screen() {};

        virtual void Init() = 0;
        virtual void Update() = 0;     
        virtual ScreenType Finish() = 0;

        void Draw(RCamera2D& camera);

        void CheckButtons(const RCamera2D& camera);

        void ScaleTextsPositions(float window_width, float window_height, float basic_width, float basic_height);

        bool ShouldClose() { return should_close_; }
    protected:
        void AddImage(std::string&& name, RImage&& image);
        void AddTexture(std::string&& name, RTexture&& texture);      
        void AddText(std::string&& name, RText&& text);

        void PlaceText(RText text, RVector2 position, bool centered);
        void PlaceButton(RText text, RVector2 position, bool centered, std::function<void()> action);

        std::vector<std::shared_ptr<Drawable>> drawables_;
        std::vector<std::shared_ptr<Button>> buttons_;

        std::unordered_map<std::string, RImage> images_;
        std::unordered_map<std::string, RTexture> textures_;
        std::unordered_map<std::string, RText> texts_;

        bool should_close_ = false;
    };

}