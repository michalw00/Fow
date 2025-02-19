#include "match_screen.h"

#include <Image.hpp>
#include <Texture.hpp>

#include "../assets/images/test.h"
#include "../drawable/button/texture_button.h"

namespace fow {
    void MatchScreen::Init() {
        
        RImage test_image = { TEST_DATA, TEST_WIDTH, TEST_HEIGHT, 1, TEST_FORMAT };
        AddImage("test", std::move(test_image));
        std::shared_ptr <RTexture> test_texture = std::make_shared<RTexture>(images_["test"]);
        AddTexture("test", test_texture);
    
        match_ = std::make_unique<Match>(16, 30, textures_["test"]);
        auto tiles = match_->GetMap().GetTiles();
        PlaceButtonsFromTiles(tiles);
    }

    void MatchScreen::Update() {
        CheckInputs();
    }

    ScreenType MatchScreen::Finish() {
        return ScreenType::kMenu;
    }

    void MatchScreen::CheckInputs() {
        if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
            input.DragScreen(camera_.get());
        }
        float mouse_wheel = GetMouseWheelMove();
        if (std::abs(mouse_wheel) > 0.0f) {
            input.Zoom(camera_.get(), mouse_wheel * 0.05f, 0.5f, 2.f);
        }
    }

    void MatchScreen::PlaceButtonsFromTiles(std::vector<std::vector<Tile>> tiles) {
        for (auto& row : tiles) {
            for (auto& tile : row) {
                PlaceButton(tile.GetTextureButton());
            }
        }
    }
}