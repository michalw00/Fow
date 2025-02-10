#include "menu_screen.h"

#include <memory>

#include <Camera2D.hpp>
#include <Text.hpp>
#include <Vector2.hpp>

#include "screen.h"

namespace fow {

    void MenuScreen::Init() {
        AddText("Title", RText("FOW", 100.0f));
        AddText("Leave", RText("Leave", 50.f));
        AddText("Start game", RText("Start game", 50.f));
    }

    void MenuScreen::Update() {

        RVector2 title_position = { 0, -200 };
        PlaceText(texts_["Title"], title_position, true);
        RVector2 start_game_position = { 0, 0 };
        PlaceButton(texts_["Start game"], start_game_position, true, []() {});
        RVector2 leave_position = { 0, 100 }; 
        PlaceButton(texts_["Leave"], leave_position, true, []() {});

    }

    ScreenType MenuScreen::Finish() {
        return ScreenType::kMenu;
    }
}