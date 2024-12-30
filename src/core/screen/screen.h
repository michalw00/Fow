#pragma once

#include <map>
#include <vector>
#include <string>
#include <memory>

#include <Image.hpp>
#include <Text.hpp>
#include <Texture.hpp>
#include <Vector2.hpp>
#include <Camera2D.hpp>
#include <Window.hpp>

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
        virtual void Draw() = 0;
        virtual void Unload() = 0;
        virtual ScreenType Finish() = 0;

        void ScaleTextsPositions(const RWindow& window, float basic_width, float basic_height);
    protected:
        void AddImage(std::string name, RImage image);
        void AddTexture(std::string name, RTexture texture);
        
        void AddText(std::string name, const RText& text);
        void PlaceText(std::string name, RVector2 position, bool center_around_pos);
        void PlaceText(RText& text, RVector2 position, bool center_around_pos);

        struct DrawableText {
            RText text;
            RVector2 position;
        };

        std::vector<DrawableText> drawable_texts_;
    private:
        void ScaleText(RText& text, RVector2& position, const RWindow& window, float basic_width, float basic_height);
        void OffsetFromTextCenter(const RText& text, RVector2& position);

        std::map<std::string, RImage> images_;
        std::map<std::string, RTexture> textures_;
        std::map<std::string, RText> texts_;
    };

}