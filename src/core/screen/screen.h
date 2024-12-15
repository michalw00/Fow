#pragma once

#include <map>
#include <string>

#include <Image.hpp>
#include <Text.hpp>
#include <Texture.hpp>

namespace fow {

    enum class ScreenType {
        kMenu,
        kMatch
    };

    class Screen {
    public:
        virtual void Init() = 0;
        virtual void Update() = 0;
        virtual void Draw() = 0;
        virtual void Unload() = 0;
        virtual ScreenType Finish() = 0;

        void AddImage(std::string name, RImage image);
        void AddTexture(std::string name, RTexture texture);
        void AddText(std::string name, RText text);
    private:
        std::map<std::string, RImage> images_;
        std::map<std::string, RTexture> textures_;
        std::map<std::string, RText> texts_;
    };

}