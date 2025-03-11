#include "match_screen.h"

#include <Image.hpp>
#include <Texture.hpp>
#include "map/terrain.h"

#include "../drawable/button/texture_button.h"

namespace fow {
    void MatchScreen::Init() {

        match_ = std::make_unique<Match>();
        match_->InitMap(16, 30);
        match_->InitPlayers();
        auto&& players = match_->GetPlayers();
        auto&& player1_map = players[0].GetRenderMap();
        PlaceButtonsFromRenderMap(player1_map);
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

    void MatchScreen::PlaceButtonsFromRenderMap(std::vector<std::vector<std::shared_ptr<TextureButton>>> buttons) {
        for (auto& row : buttons) {
            for (auto& button : row) {
                PlaceButton(button);
            }
        }
    }
}