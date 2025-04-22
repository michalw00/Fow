#include "match_screen.h"

#include <format>

#include <Image.hpp>
#include <Texture.hpp>
#include "map/terrain.h"

#include "../drawable/button/texture_button.h"
#include "../drawable/button/text_button.h"

namespace fow {
    void MatchScreen::Init() {
        InitMatch();
        InitSelectedUnitHud();    

        RVector2 end_turn_position = { basic_width_ - 140.f, basic_height_ - 50.f };
        RText end_turn_text("END TURN", 45.f);
        end_turn_button = std::make_shared<TextButton>(end_turn_position, [&]() { match_->EndTurn(); }, end_turn_text, true);
    }

    void MatchScreen::InitMatch() {
        match_ = std::make_unique<Match>();
        match_->InitMap(8, 15);
        match_->InitPlayers(basic_width_, basic_height_, *camera_.get());
    }

    void MatchScreen::InitSelectedUnitHud() {
        RVector2 origin(basic_width_/2.f, basic_height_ - 120.f);

        std::string unit_type_name = "UNIT_TYPE";
        std::shared_ptr<Text> unit_type_text = std::make_shared<Text>(origin, RText("", 40.f));
        ComplexDrawablePart unit_type(unit_type_name, unit_type_text);

        std::string hp_name = "HP";
        std::shared_ptr<Text> hp_text = std::make_shared<Text>(origin+RVector2(0.f, 40.f), RText("", 25.f), true);
        ComplexDrawablePart hp(hp_name, hp_text);

        std::string mp_name = "MP";
        std::shared_ptr<Text> mp_text = std::make_shared<Text>(origin + RVector2(0.f, 80.f), RText("", 25.f), true);
        ComplexDrawablePart mp(mp_name, mp_text);

        std::initializer_list<ComplexDrawablePart> parts = { unit_type, hp, mp };
        selected_unit_hud_ = std::make_unique<ComplexDrawable>(parts);
    }

    void MatchScreen::Update() {
        auto& player = match_->GetCurrentPlayer();
        player.MoveSelectedUnit(*match_->GetMap().get());
        player.UpdateRenderMap();

        camera_ = player.GetCamera();
        PlacePlayerButtons(player);
        auto& unit = player.GetSelectedUnit();

        if (unit) {
            ShowSelectedUnitHud(unit, match_->GetUnitManager());
        }

        PlaceDrawable(end_turn_button, true);

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
                PlaceDrawable(button);
            }
        }
        auto& units = player.GetUnits();
        const auto& unit_manager = match_->GetUnitManager();
        for (auto& unit : units) {
            int position_width = unit->GetPositionWidth();
            int position_height = unit->GetPositionHeight(); 
            RRectangle area = buttons[position_width][position_height]->GetArea();
            RVector2 size = { area.GetSize()};
            size.x *= 0.95;
            RVector2 ratio = { 1.0, 1.5 };
            size /= ratio;
            RVector2 position = area.GetPosition();
            position += (area.GetSize() - size) / 2.f;
            auto lmb_action = [&player, &unit]() {
                if (!player.GetSelectedUnit()) {
                    player.SetSelectedUnit(unit);
                    player.ClearSelectedTile();
                } else {
                    player.SetSelectedUnit(nullptr);
                }
            };
            std::shared_ptr<TextureButton> button = std::make_shared<TextureButton>(position, size, lmb_action, unit_manager.GetTexture(unit->GetType()));

            button->SetIsSelected(player.GetSelectedUnit() == unit);

            PlaceDrawable(button);
        }
    }

    void MatchScreen::ShowSelectedUnitHud(const std::shared_ptr<Unit>& unit, const UnitManager& unit_manager) {
        UnitType unit_type = unit->GetType();
        auto unit_modifiers = unit_manager.GetResource(unit_type);
        selected_unit_hud_->EditText("UNIT_TYPE", unit_manager.GetName(unit_type));
         
        std::string current_hp = std::format("{:.1f}", unit->GetHealthPoints());
        std::string max_hp = std::format("{:.1f}", unit_modifiers->start_health_points);
        selected_unit_hud_->EditText("HP", "HP: " + current_hp + " / " + max_hp);

        std::string current_mp = std::format("{:.1f}", unit->GetMovementPoints());
        std::string max_mp = std::format("{:.1f}", unit_modifiers->start_movement_points);
        selected_unit_hud_->EditText("MP", "MP: " + current_mp + " / " + max_mp);

        auto& hud_drawables = selected_unit_hud_->GetDrawables();
        for (auto& hud_drawable : hud_drawables) {
            PlaceDrawable(hud_drawable, true);
        }
    }
}