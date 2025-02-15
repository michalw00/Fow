#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <Camera2D.hpp>
#include <Image.hpp>
#include <Text.hpp>
#include <Texture.hpp>

#include "../../drawable/button/button.h"
#include "../../drawable/drawable.h"
#include "../../drawable/text.h"

namespace fow {

    enum class ScreenType {
        kMenu,
        kMatch
    };

    class Screen {
    public:
        virtual ~Screen();

        virtual void Init() = 0;
        virtual void Update() = 0;     
        virtual ScreenType Finish() = 0;

        void Draw(RCamera2D& camera);

        void CheckButtons(const RCamera2D& camera);

        void ScalePositions(float window_width, float window_height, float basic_width, float basic_height);

        bool ShouldClose() const { return should_close_; }
        bool ShouldFinish() const { return should_finish_; }
    protected:
        void AddImage(std::string&& name, RImage&& image);
        void AddTexture(std::string&& name, std::shared_ptr <RTexture> texture);
        void AddRText(std::string&& name, RText&& rtext);

        void PlaceText(std::shared_ptr<Text> text);
        void PlaceButton(std::shared_ptr<Button> button);

        std::vector<std::shared_ptr<Drawable>> drawables_;
        std::vector<std::shared_ptr<Button>> buttons_;

        std::unordered_map<std::string, RImage> images_;
        std::unordered_map<std::string, std::shared_ptr<RTexture>> textures_;
        std::unordered_map<std::string, RText> rtexts_;

        bool should_close_ = false;
        bool should_finish_ = false;
    };

}