#include "match_screen.h"

#include <Image.hpp>
#include <Texture.hpp>
#include "map/terrain.h"

#include "../drawable/button/texture_button.h"

namespace fow {
    void MatchScreen::Init() {

        match_ = std::make_unique<Match>();
        match_->InitMap(8, 15);
        match_->InitPlayers(basic_width_, basic_height_, *camera_.get());
    }

    void MatchScreen::Update() {
        drawables_.clear();
        buttons_.clear();      

        auto& player = match_->GetCurrentPlayer();
        player.MoveSelectedUnit();
        camera_ = player.GetCamera();
        PlacePlayerButtons(player);

        CheckInputs();              
    }

    ScreenType MatchScreen::Finish() {
        return ScreenType::kMenu;
    }

    void MatchScreen::CheckInputs() {
        if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
            input.DragScreen(camera_.get());
        }
        {
            float mouse_wheel = GetMouseWheelMove();
            if (std::abs(mouse_wheel) > 0.0f) {
                input.Zoom(camera_.get(), mouse_wheel * 0.05f, 0.5f, 4.f);
            }
        }
        if (IsKeyPressed(KEY_ENTER)) {
            match_->EndTurn();
        }
    }

    void MatchScreen::PlacePlayerButtons(Player& player) {
        auto& buttons = player.GetRenderMap();
        for (auto& row : buttons) {
            for (auto& button : row) {
                PlaceButton(button);
            }
        }
        const auto& units = player.GetUnits();
        const auto& unit_manager = match_->GetUnitManager();
        for (auto& unit : units) {
            int position_width = unit->GetPositionWidth();
            int position_height = unit->GetPositionHeight(); 
            RRectangle area = buttons[position_width][position_height]->GetArea();
            RVector2 ratio = { 1.0, 1.5 };
            RVector2 size = { area.GetSize()};
            size /= ratio;
            RVector2 position = area.GetPosition();
            position += (area.GetSize() - size) / 2.f;
            std::shared_ptr<TextureButton> button = std::make_shared<TextureButton>(position, size, [&player, &unit]() {player.SetSelectedUnit(unit); }, unit_manager.GetTexture(unit->GetType()));
            PlaceButton(button);
        }
    }
}