#include "match_screen.h"

#include <Image.hpp>
#include <Texture.hpp>

#include "../images/test.h"
#include "../drawable/button/texture_button.h"

namespace fow {
    void MatchScreen::Init() {
        RImage test_image = { TEST_DATA, TEST_WIDTH, TEST_HEIGHT, 1, TEST_FORMAT };
        AddImage("test", std::move(test_image));
        std::shared_ptr <RTexture> test_texture = std::make_shared<RTexture>(images_["test"]);
        AddTexture("test", test_texture);

        RVector2 test_pos = { 0,0 };
        std::shared_ptr<Button> test_button = std::make_shared<TextureButton>(test_pos, []() {}, textures_["test"]);
        PlaceButton(test_button);     
    }

    void MatchScreen::Update() {}

    ScreenType MatchScreen::Finish() {
        return ScreenType::kMenu;
    }
}